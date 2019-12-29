/*
 * Copyright (c) 2018-2022 curoky(cccuroky@gmail.com).
 *
 * This file is part of learn-cpp.
 * See https://github.com/curoky/learn-cpp for further info.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// http://c.biancheng.net/cpp/html/3044.html

// 默认情况下，close()/closesocket()
// 会立即向网络中发送FIN包，不管输出缓冲区中是否还有数据，而shutdown()
// 会等输出缓冲区中的数据传输完毕再发送FIN包。也就意味着，调用 close()/closesocket()
// 将丢失输出缓冲区中的数据，而调用 shutdown() 不会。
