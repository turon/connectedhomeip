#
#
#    Copyright (c) 2020 Project CHIP Authors
#
#    Licensed under the Apache License, Version 2.0 (the     License    );
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#
#        http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an     AS IS     BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.
#

#
#    Description:
#      This file is the CMake template for the CHIP SDK QR code library.
#

add_subdirectory(tests)

add_library(SetupPayload)

set(COMMON_INCLUDES
    ${PROJECT_SOURCE_DIR}/src/
    ${PROJECT_SOURCE_DIR}/src/include
    ${PROJECT_SOURCE_DIR}/src/lib
    ${PROJECT_SOURCE_DIR}/src/lib/core
    ${PROJECT_SOURCE_DIR}/src/system
)

set(COMMON_SOURCES
    AdditionalDataPayload.h
    AdditionalDataPayloadGenerator.cpp
    AdditionalDataPayloadGenerator.h
    AdditionalDataPayloadParser.cpp
    AdditionalDataPayloadParser.h
    Base38.h
    Base38Decode.cpp
    Base38Decode.h
    Base38Encode.cpp
    Base38Encode.h
    ManualSetupPayloadGenerator.cpp
    ManualSetupPayloadGenerator.h
    ManualSetupPayloadParser.cpp
    ManualSetupPayloadParser.h
    QRCodeSetupPayloadGenerator.cpp
    QRCodeSetupPayloadGenerator.h
    QRCodeSetupPayloadParser.cpp
    QRCodeSetupPayloadParser.h
    SetupPayload.cpp
    SetupPayload.h
    SetupPayloadHelper.cpp
    SetupPayloadHelper.h
)

target_compile_definitions(SetupPayload PRIVATE)
target_compile_options(SetupPayload PRIVATE)
target_include_directories(SetupPayload PRIVATE ${COMMON_INCLUDES})
target_sources(SetupPayload PRIVATE ${COMMON_SOURCES})

target_link_libraries(SetupPayload PRIVATE chip-config)
