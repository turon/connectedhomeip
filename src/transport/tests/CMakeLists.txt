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
#      This file is the CMake template for the CHIP SDK transport layer library tests.
#

set(COMMON_INCLUDES
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/include
    ${PROJECT_SOURCE_DIR}/src/lib
    ${PROJECT_SOURCE_DIR}/src/lib/core
    ${PROJECT_SOURCE_DIR}/src/system
    ${PROJECT_SOURCE_DIR}/src/inet/tests
    ${PROJECT_SOURCE_DIR}/src/transport/tests
    ${NLUNIT_TEST_INCLUDES}
    ${PROJECT_SOURCE_DIR}/third_party/lwip/repo/lwip/src/include
)

set(COMMON_LIBS
    ${PLATFORM_LINK_START}
    InetLayerTests
    TransportLayer
    BleLayer
    ChipCrypto
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

add_executable(TestPairingSession TestPairingSession.cpp)
target_include_directories(TestPairingSession PRIVATE ${COMMON_INCLUDES})
target_link_libraries(TestPairingSession PRIVATE ${COMMON_LIBS})
target_link_directories(TestPairingSession PRIVATE ${COMMON_LDPATH})
add_test(NAME TestPairingSession COMMAND TestPairingSession)
add_dependencies(check TestPairingSession)

add_executable(TestPeerConnections TestPeerConnections.cpp)
target_include_directories(TestPeerConnections PRIVATE ${COMMON_INCLUDES})
target_link_libraries(TestPeerConnections PRIVATE ${COMMON_LIBS})
target_link_directories(TestPeerConnections PRIVATE ${COMMON_LDPATH})
add_test(NAME TestPeerConnections COMMAND TestPeerConnections)
add_dependencies(check TestPeerConnections)

if(CHIP_TARGET_STYLE_UNIX)

add_executable(TestSecureSession TestSecureSession.cpp)
target_include_directories(TestSecureSession PRIVATE ${COMMON_INCLUDES})
target_link_libraries(TestSecureSession PRIVATE ${COMMON_LIBS})
target_link_directories(TestSecureSession PRIVATE ${COMMON_LDPATH})
add_test(NAME TestSecureSession COMMAND TestSecureSession)
add_dependencies(check TestSecureSession)

add_executable(TestSessionManager TestSessionManager.cpp)
target_include_directories(TestSessionManager PRIVATE ${COMMON_INCLUDES})
target_link_libraries(TestSessionManager PRIVATE ${COMMON_LIBS})
target_link_directories(TestSessionManager PRIVATE ${COMMON_LDPATH})
add_test(NAME TestSessionManager COMMAND TestSessionManager)
add_dependencies(check TestSessionManager)

add_executable(TestSessionHandle TestSessionHandle.cpp)
target_include_directories(TestSessionHandle PRIVATE ${COMMON_INCLUDES})
target_link_libraries(TestSessionHandle PRIVATE ${COMMON_LIBS})
target_link_directories(TestSessionHandle PRIVATE ${COMMON_LDPATH})
add_test(NAME TestSessionHandle COMMAND TestSessionHandle)
add_dependencies(check TestSessionHandle)

endif(CHIP_TARGET_STYLE_UNIX)
