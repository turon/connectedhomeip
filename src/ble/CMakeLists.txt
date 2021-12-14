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
#      This file is the CMake template for the CHIP SDK Bluetooth Low Energy (BLE) layer,
#      and Bluetooth Transport Protocol (BTP) code.
#

add_subdirectory(tests)

add_library(BleLayer)

set(COMMON_INCLUDES
    ${PROJECT_SOURCE_DIR}/src/
    ${PROJECT_SOURCE_DIR}/src/include
    ${PROJECT_SOURCE_DIR}/src/lib
    ${PROJECT_SOURCE_DIR}/src/lib/core
    ${PROJECT_SOURCE_DIR}/src/system
    ${PROJECT_SOURCE_DIR}/third_party/nlfaultinjection/repo/include
)

set(COMMON_SOURCES
    BLEEndPoint.cpp
    BLEEndPoint.h
    Ble.h
    BleApplicationDelegate.h
    BleConfig.h
    BleConnectionDelegate.h
    BleError.cpp
    BleError.h
    BleLayer.cpp
    BleLayer.h
    BlePlatformDelegate.h
    BleUUID.cpp
    BleUUID.h
    BtpEngine.cpp
    BtpEngine.h
    CHIPBleServiceData.h
)

target_compile_definitions(BleLayer PRIVATE)
target_compile_options(BleLayer PRIVATE)
target_include_directories(BleLayer PRIVATE ${COMMON_INCLUDES})
target_sources(BleLayer PRIVATE ${COMMON_SOURCES})

target_link_libraries(BleLayer PRIVATE chip-config)
