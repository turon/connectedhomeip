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
#      This file is the CMake template for the CHIP SDK system layer library.
#

add_subdirectory(tests)

add_library(SystemLayer)

set(COMMON_INCLUDES
    ${PROJECT_SOURCE_DIR}/src/
    ${PROJECT_SOURCE_DIR}/src/include
    ${PROJECT_SOURCE_DIR}/src/lib
    ${PROJECT_SOURCE_DIR}/src/lib/core
    ${PROJECT_SOURCE_DIR}/src/system
    ${PROJECT_SOURCE_DIR}/third_party/lwip/repo/lwip/src/include
    ${PROJECT_SOURCE_DIR}/third_party/nlfaultinjection/repo/include
)

set(COMMON_SOURCES
    PlatformEventSupport.h
    SystemAlignSize.h
    SystemClock.cpp
    SystemClock.h
    SystemConfig.h
    SystemError.cpp
    SystemError.h
    SystemEvent.h
    SystemFaultInjection.h
    SystemLayer.cpp
    SystemLayer.h
#   SystemLayerImpl${chip_system_config_event_loop}.cpp
#   SystemLayerImpl${chip_system_config_event_loop}.h
    SystemLayerImpl.h
    SystemMutex.cpp
    SystemMutex.h
    SystemPacketBuffer.cpp
    SystemPacketBuffer.h
    SystemStats.cpp
    SystemStats.h
    SystemTimer.cpp
    SystemTimer.h
    TLVPacketBufferBackingStore.cpp
    TLVPacketBufferBackingStore.h
    TimeSource.h
    WakeEvent.cpp
    WakeEvent.h
)

target_compile_definitions(SystemLayer PRIVATE)
target_compile_options(SystemLayer PRIVATE)
target_include_directories(SystemLayer PRIVATE ${COMMON_INCLUDES})
target_sources(SystemLayer PRIVATE ${COMMON_SOURCES})

target_link_libraries(SystemLayer PRIVATE chip-config)