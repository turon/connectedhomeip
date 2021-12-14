#
#
#    Copyright (c) 2020 Project CHIP Authors
#
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#
#        http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.
#

#
#    Description:
#      This file is the CMake template for the CHIP SDK system layer library tests.
#

set(COMMON_INCLUDES
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/include
    ${PROJECT_SOURCE_DIR}/src/lib
    ${PROJECT_SOURCE_DIR}/src/lib/core
    ${PROJECT_SOURCE_DIR}/src/system
    ${PROJECT_SOURCE_DIR}/third_party/lwip/repo/lwip/src/include
    ${NLUNIT_TEST_INCLUDES}
)

set(COMMON_LIBS
    ${PLATFORM_LINK_START}
    BleLayer
    InetLayer
    SystemLayer
    SupportLayer
    nlfaultinjection
    nlunit-test
    ${CHIP_PLATFORM_LIBS}
    ${PLATFORM_LINK_END}
    chip-config
)

set(COMMON_LDPATH
    ${NLUNIT_TEST_LDPATH}
    ${NLFAULT_INJECTION_LDPATH}
)

#### TestSystemErrorStr
add_executable(TestSystemErrorStr TestSystemErrorStr.cpp)
target_include_directories(TestSystemErrorStr PRIVATE ${COMMON_INCLUDES})
target_link_libraries(TestSystemErrorStr PRIVATE ${COMMON_LIBS})
target_link_directories(TestSystemErrorStr PRIVATE ${COMMON_LDPATH})
add_test(NAME TestSystemErrorStr COMMAND TestSystemErrorStr)
add_dependencies(check TestSystemErrorStr)


#### TestSystemPacketBuffer
add_executable(TestSystemPacketBuffer TestSystemPacketBuffer.cpp)
target_include_directories(TestSystemPacketBuffer PRIVATE ${COMMON_INCLUDES})
target_link_libraries(TestSystemPacketBuffer PRIVATE ${COMMON_LIBS})
target_link_directories(TestSystemPacketBuffer PRIVATE ${COMMON_LDPATH})
add_test(NAME TestSystemPacketBuffer COMMAND TestSystemPacketBuffer)
add_dependencies(check TestSystemPacketBuffer)

#### TestSystemTimer
add_executable(TestSystemTimer TestSystemTimer.cpp)
target_include_directories(TestSystemTimer PRIVATE ${COMMON_INCLUDES})
target_link_libraries(TestSystemTimer PRIVATE ${COMMON_LIBS})
target_link_directories(TestSystemTimer PRIVATE ${COMMON_LDPATH})
add_test(NAME TestSystemTimer COMMAND TestSystemTimer)
add_dependencies(check TestSystemTimer)
