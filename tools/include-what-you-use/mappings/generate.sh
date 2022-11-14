#!/usr/bin/env bash
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

set -uo pipefail

OUT=$PWD/mappings

############################## gcc.libc.imp ##############################
cd /usr/include && grep '^ *# *include' {sys/,net/,}* | perl -nle 'm/^([^:]+).*<([^>]+)>/ && print qq@    { include: [ "<$2>", private, "<$1>", public ] },@' | grep bits/ | sort >$OUT/'gcc.libc.imp.part1'
cd /usr/include && grep -R '^ *# *error "Never use\|include' * | perl -nle 'm/<([^>]+).*directly.*<([^>]+)/ && print qq@    { include: [ "<$1>", private, "<$2>", public ] },@' | sort >$OUT/'gcc.libc.imp.part2'

############################## gcc.stl.headers.imp ##############################
cd /usr/include/c++/11 && grep -r headername | perl -nle 'm/^([^:]+).*@headername\{([^,]*)\}/ && print qq@  { include: ["<$1>", private, "<$2>", public ] },@' | sort -u >$OUT/'gcc.stl.headers.imp.part1'
cd /usr/include/x86_64-linux-gnu/c++/11 && grep -r headername | perl -nle 'm/^([^:]+).*@headername\{([^,]*)\}/ && print qq@  { include: ["<$1>", private, "<$2>", public ] },@' | sort -u >$OUT/'gcc.stl.headers.imp.part2'

############################## gcc.symbols.imp ##############################
grep -R '__.*_defined' /usr/include | perl -nle 'm,/usr/include/([^:]*):#\s*\S+ __(.*)_defined, and print qq@    { symbol: [ "$2", public, "<$1>", public ] },@' | sort -u | sed 's$x86_64-linux-gnu/$$g' >$OUT/'gcc.symbols.imp.part1'
sed -i '/<bits/d' $OUT/'gcc.symbols.imp.part1'

grep -R '#define\s*__need_.*' /usr/include | perl -nle 'm,/usr/include/([^:]*):#define\s*__need_(.*), and print qq@    { symbol: [ "$2", public, "<$1>", public ] },@' | sort -u | sed 's$x86_64-linux-gnu/$$g' >$OUT/'gcc.symbols.imp.part2'
sed -i '/<bits/d' $OUT/'gcc.symbols.imp.part2'

############################## stl.c.headers.imp ##############################
curl -s https://raw.githubusercontent.com/cplusplus/draft/c%2B%2B20/source/lib-intro.tex |
  sed '/begin{floattable}.*{tab:cpp.c.headers}/,/end{floattable}/p' | grep tcode | perl -nle 'm/tcode{<c(.*)>}/ && print qq@  { include: [ "<$1.h>", public, "<c$1>", public ] },@' | sort -u >$OUT/'stl.c.headers.imp.part1'
