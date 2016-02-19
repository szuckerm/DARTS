################################################################################
#                                                                              #
# Copyright (c) 2011-2014, University of Delaware                              # 
# All rights reserved.                                                         #
#                                                                              #
# Redistribution and use in source and binary forms, with or without           # 
# modification, are permitted provided that the following conditions           # 
# are met:                                                                     #
#                                                                              #
# 1. Redistributions of source code must retain the above copyright            # 
# notice, this list of conditions and the following disclaimer.                # 
#                                                                              #
# 2. Redistributions in binary form must reproduce the above copyright         # 
# notice, this list of conditions and the following disclaimer in the          # 
# documentation and/or other materials provided with the distribution.         # 
#                                                                              #
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS          # 
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT            # 
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS            # 
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE               # 
# COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,         # 
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,         # 
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;             # 
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER             # 
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT           # 
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN            # 
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE              # 
# POSSIBILITY OF SUCH DAMAGE.                                                  # 
#                                                                              #
################################################################################

set(common_src
    Atomics.cpp
    Thread.cpp
    getClock.cpp)

set(common_inc
    ${CMAKE_SOURCE_DIR}/include/common/Atomics.h
    ${CMAKE_SOURCE_DIR}/include/common/AutoLock.h
    ${CMAKE_SOURCE_DIR}/include/common/darts.h
    ${CMAKE_SOURCE_DIR}/include/common/getClock.h
    ${CMAKE_SOURCE_DIR}/include/common/Lock.h
    ${CMAKE_SOURCE_DIR}/include/common/rdtsc.h
    ${CMAKE_SOURCE_DIR}/include/common/Thread.h
    ${CMAKE_SOURCE_DIR}/include/common/ringbuffer.h
    ${CMAKE_SOURCE_DIR}/include/common/dartsPool.h)

add_library(common STATIC ${common_src} ${common_inc})
target_link_libraries(common ${CMAKE_THREAD_LIBS_INIT} )

set_target_properties(common PROPERTIES PUBLIC_HEADER
"${CMAKE_SOURCE_DIR}/include/common/Atomics.h;${CMAKE_SOURCE_DIR}/include/common/AutoLock.h;${CMAKE_SOURCE_DIR}/include/common/darts.h;${CMAKE_SOURCE_DIR}/include/common/getClock.h;${CMAKE_SOURCE_DIR}/include/common/Lock.h;${CMAKE_SOURCE_DIR}/include/common/rdtsc.h;${CMAKE_SOURCE_DIR}/include/common/Thread.h;${CMAKE_SOURCE_DIR}/include/common/ringbuffer.h;${CMAKE_SOURCE_DIR}/include/common/dartsPool.h")

install(TARGETS common 
    EXPORT dartsLibraryDepends
    ARCHIVE DESTINATION darts/lib/           COMPONENT bin
    PUBLIC_HEADER DESTINATION darts/include/ COMPONENT dev)

