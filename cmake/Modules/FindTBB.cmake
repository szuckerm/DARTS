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

find_path(TBB_INCLUDE_DIR "tbb/tbb.h" 
  HINTS ${TBB_ROOT}/include
  /usr/include
  /usr/local/include
  /opt/local/include
  /opt/intel/tbb/include
  /lustre/work/capsl/opt/intel/tbb/include
  ~/local/tbb/include 
)

find_library(TBB_LIBRARIES NAMES tbb 
  HINTS ${TBB_ROOT}/lib
  /lustre/work/capsl/opt/intel/tbb/lib/intel64/cc4.1.0_libc2.4_kernel2.6.16.21
  ~/local/tbb/lib/intel64/cc4.1.0_libc2.4_kernel2.6.16.21
  /opt/intel/tbb/lib/intel64/cc4.1.0_libc2.4_kernel2.6.16.21/
  PATHS /usr/lib /usr/local/lib /opt/local/lib /opt/intel/tbb/lib 
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(TBB DEFAULT_MSG TBB_LIBRARIES
  TBB_INCLUDE_DIR)

if(TBB_FOUND)
  message(STATUS "Found TBB in ${TBB_INCLUDE_DIR};${TBB_LIBRARIES}")
  set( TBB_INCLUDE_DIR ${TBB_INCLUDE_DIR} )
  set( TBB_LIBRARIES ${TBB_LIBRARIES} )
endif(TBB_FOUND)
