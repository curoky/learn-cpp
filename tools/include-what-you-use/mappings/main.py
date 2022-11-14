#!/usr/bin/env python3
# Copyright (c) 2018-2022 curoky(cccuroky@gmail.com).
#
# This file is part of my-own-x.
# See https://github.com/curoky/my-own-x for further info.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import os
import re
from graphlib import TopologicalSorter
from pathlib import Path
from typing import List

import typer
from pydantic import BaseModel

app = typer.Typer(add_completion=False, help='')


def inPath(sub: str, path: Path) -> bool:
    return sub in path.as_posix().split('/')


class Mapping(BaseModel):
    from_header: Path
    from_type: str = 'private'
    to_header: Path
    to_type: str = 'public'

    wildcard: bool = False

    def __str__(self) -> str:
        return '{} -> {}'.format(self.from_header, self.to_header)

    __repr__ = __str__

    @staticmethod
    def dumpTo(mps: List['Mapping'], path: Path):

        content = []
        mps = Mapping.checkDup(mps)
        mps = Mapping.checkEqual(mps)
        mps = Mapping.checkWildcard(mps)
        Mapping.checkCycle(mps)
        for m in mps:
            if m.wildcard:
                content.append(
                    f'\t{{include : [ "@<{m.from_header}/.*>", {m.from_type}, "<{m.to_header}>", {m.to_type} ]}},'
                )
            else:
                content.append(
                    f'\t{{ include : [ "<{m.from_header}>", {m.from_type}, "<{m.to_header}>", {m.to_type} ]}},'
                )

        path.write_text('[\n' + '\n'.join(sorted(content)) + '\n]\n')

    @staticmethod
    def checkDup(mappings: List['Mapping']):
        '''
        if one target both is public and private, then remove public
        '''
        pubs = set()
        pris = set()

        def check_and_add(type: str, t):
            if type == 'public':
                pubs.add(t)
            elif type == 'private':
                pris.add(t)

        for m in mappings:
            check_and_add(m.from_type, m.from_header)
            check_and_add(m.to_type, m.to_header)

        inter = pubs.intersection(pris)
        print(f'remove dup size: {len(inter)}')
        # return list(filter(lambda m: m.to_header not in inter, mappings))

        ans = []
        for m in mappings:
            if m.to_header in inter:
                m.to_type = 'private'
            ans.append(m)
        return ans

    @staticmethod
    def checkWildcard(mappings: List['Mapping']):
        '''
        if to_header/from_header in from_header's wildcard
        eg:
        a/x/*.h -> a/x.h
        ...   -> a/x/1.h

        '''
        wildcard = set()
        from_to = dict()
        for m in mappings:
            if m.wildcard:
                wildcard.add(m.from_header.as_posix())
                from_to[m.from_header.as_posix()] = m.to_header.as_posix()
        res = []
        for m in mappings:
            flag = False
            for p in wildcard:
                if m.to_header.as_posix().startswith(p) and from_to[p] != m.to_header.as_posix():
                    # print(m)
                    flag = True
                    break
            if not flag:
                res.append(m)

        return res

    @staticmethod
    def checkEqual(mappings: List['Mapping']):
        '''
        filter to_header == from_header
        '''
        return list(filter(lambda m: m.to_header != m.from_header, mappings))

    @staticmethod
    def checkPrefix(mappings: List['Mapping'], prefix: str):
        '''
        all include need startswith prefix
        '''
        return list(
            filter(
                lambda m: m.from_header.as_posix().startswith(prefix) and m.to_header.as_posix().
                startswith(prefix), mappings))

    @staticmethod
    def checkCycle(mappings: List['Mapping']):
        graph = {}
        for m in mappings:
            if not m.wildcard:
                if m.from_header not in graph:
                    graph[m.from_header] = {m.to_header}
                else:
                    graph[m.from_header].add(m.to_header)
        try:
            t = list(TopologicalSorter(graph=graph).static_order())
        except Exception as e:
            print(str(e))


def mapImplInFilename(root: Path,
                      pattern='**/*.h*',
                      suffixs=['Internal-inl', 'Internal', '-inl', '-pre']):
    '''
    aaa/xxx-inl.h => aaa/xxx.h
    '''
    ans = []
    for inl in root.glob(pattern):
        for suf in suffixs:
            if inl.stem.endswith(suf):
                base = inl.parent / (inl.stem[:-len(suf)] + inl.suffix)
                if base.is_file():
                    ans.append(
                        Mapping(to_header=base.relative_to(root),
                                from_header=inl.relative_to(root)))
    return ans


def mapImplInContent(root: Path,
                     pattern='**/*.h*',
                     sub_dirs=['internal', 'detail', 'impl', 'stubs']):
    # Note: 'stubs' is only for protobuf
    '''
    if HHH/foo.h 's content is following:
    > #include <HHH/detail/x.h> # include from root
    > #include "HHH/detail/y.h" # include from root
    > #include "detail/z.h"     # include from relative

    HHH/detail/x.h -> HHH/foo.h
    HHH/detail/y.h -> HHH/foo.h
    HHH/detail/y.h -> HHH/foo.h

    '''
    include_pattern = re.compile(r'# *include *["<]([^>"]+)[">]')

    ans = []
    for src in root.glob(pattern):
        for inc in map(lambda x: Path(x), set(include_pattern.findall(src.read_text()))):
            # include from relative path from cwd
            if (src.parent / inc).is_file():
                inc = (src.parent / inc).resolve()
            # include from root path
            elif (root / inc).is_file():
                inc = (root / inc).resolve()
            else:
                continue

            if any([inPath(sub, inc) for sub in sub_dirs]):
                if all([not inPath(sub, src) for sub in sub_dirs]):
                    ans.append(
                        Mapping(from_header=inc.relative_to(root), to_header=src.relative_to(root)))
                elif any([inPath(sub, src) for sub in sub_dirs]):
                    ans.append(
                        Mapping(from_header=inc.relative_to(root),
                                to_header=src.relative_to(root),
                                to_type='private'))
    return ans


def mapPrefix(root: Path, pattern='**/*.h*'):
    '''
    map aaa/**/*.hpp -> aaa.hpp
    '''
    include_pattern = re.compile(r'# *include *["<]([^>"]+)[">]')

    ans = []
    for src in root.glob(pattern):
        if os.path.splitext(src.name)[1] not in ['.h', '.hpp']:
            continue
        if (target := Path(os.path.splitext(src.as_posix())[0])) and target.is_dir():
            # print(f'{src}->{target}')
            for inc in map(lambda x: Path(x), set(include_pattern.findall(src.read_text()))):
                # include from relative path from cwd
                if (src.parent / inc).is_file():
                    inc = (src.parent / inc).resolve()
                # include from root path
                elif (root / inc).is_file():
                    inc = (root / inc).resolve()
                else:
                    continue
                ans.append(
                    Mapping(from_header=inc.relative_to(root), to_header=src.relative_to(root)))
    return ans


@app.command()
def generate():
    externalPath = Path('/home/curoky/repos/my-own-x/external').resolve()

    # facebook
    for name in [
            'com_github_facebook_folly',
            'com_github_facebook_wangle',
            'com_github_facebook_proxygen',
            'com_github_facebook_fbthrift',
            'com_github_facebook_fatal',
            'com_google_protobuf/src',
            'com_github_oneapi_src_onetbb/include',
    ]:
        maps = mapImplInFilename(externalPath / name)
        maps += mapPrefix(externalPath / name)
        maps += mapImplInContent(externalPath / name)
        ignored_to_header = {'folly/detail/Futex-inl.h'}
        maps = list(filter(lambda m: m.to_header.as_posix() not in ignored_to_header, maps))
        Mapping.dumpTo(maps, Path('mappings/' + name.replace('/', '_') + '.imp'))

    # tbb
    maps = mapImplInFilename(externalPath / 'com_github_oneapi_src_onetbb/include/oneapi')
    maps += mapImplInContent(externalPath / 'com_github_oneapi_src_onetbb/include/oneapi')
    Mapping.dumpTo(maps, Path('mappings/tbb.imp'))

    # boost
    ignored_to_header = [
        'boost/xpressive/detail/core/matcher/action_matcher.hpp',
        'boost/python/detail/type_list_impl.hpp',
        'boost/contract/detail/inlined/detail/checking.hpp',
        'boost/numeric/odeint/integrate/detail/integrate_adaptive.hpp',
        'boost/numeric/odeint/iterator/integrate/detail/integrate_const.hpp',
    ]
    maps = mapPrefix(externalPath / 'boost', pattern='boost/**/*.hpp')
    maps += mapImplInContent(externalPath / 'boost', pattern='boost/**/*.hpp')
    maps = list(filter(lambda m: m.to_header.as_posix() not in ignored_to_header, maps))
    Mapping.dumpTo(maps, Path('mappings/boost.imp'))


@app.command()
def merge():

    def mergePartTo(files: List[Path], path: Path):
        res = ''
        for file in files:
            res += file.read_text()
        path.write_text('[\n' + res + '\n]\n')

    mergePartTo(
        [
            Path('mappings/gcc.libc.imp.part1'),
            Path('mappings/gcc.libc.imp.part2'),
            # Path('mappings/gcc.libc.imp.part10'),
        ],
        Path('mappings/gcc.libc.imp'))

    mergePartTo([
        Path('mappings/gcc.stl.headers.imp.part1'),
        Path('mappings/gcc.stl.headers.imp.part2'),
        Path('mappings/gcc.stl.headers.imp.part10'),
    ], Path('mappings/gcc.stl.headers.imp'))

    mergePartTo([
        Path('mappings/gcc.symbols.imp.part1'),
        Path('mappings/gcc.symbols.imp.part2'),
        Path('mappings/gcc.symbols.imp.part10'),
    ], Path('mappings/gcc.symbols.imp'))

    mergePartTo([
        Path('mappings/stl.c.headers.imp.part1'),
    ], Path('mappings/stl.c.headers.imp'))
    mergePartTo([
        Path('mappings/libstdc++.imp.part10'),
    ], Path('mappings/libstdc++.imp'))


if __name__ == '__main__':
    app()
