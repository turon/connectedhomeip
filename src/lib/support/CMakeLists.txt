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
#      This file is the CMake template for the CHIP SDK support library code.
#

add_subdirectory(tests)

add_library(SupportLayer)

set(COMMON_INCLUDES
    ${PROJECT_SOURCE_DIR}/src/
    ${PROJECT_SOURCE_DIR}/src/include
    ${PROJECT_SOURCE_DIR}/src/lib
    ${PROJECT_SOURCE_DIR}/third_party/nlfaultinjection/repo/include
)

set(COMMON_SOURCES
    Base64.cpp
    Base64.h
    BitFlags.h
    BufferReader.cpp
    BufferReader.h
    BufferWriter.cpp
    BufferWriter.h
    BytesCircularBuffer.cpp
    BytesCircularBuffer.h
    BytesToHex.cpp
    BytesToHex.h
    CHIPArgParser.cpp
    CHIPCounter.cpp
    CHIPCounter.h
    CHIPMem.cpp
    CHIPMem.h
    CHIPMemString.h
    CHIPPlatformMemory.cpp
    CHIPPlatformMemory.h
    CodeUtils.h
    DLLUtil.h
    Defer.h
    ErrorStr.cpp
    ErrorStr.h
    FibonacciUtils.cpp
    FibonacciUtils.h
    FixedBufferAllocator.cpp
    FixedBufferAllocator.h
    Iterators.h
    LifetimePersistedCounter.cpp
    LifetimePersistedCounter.h
    ObjectLifeCycle.h
    PersistedCounter.cpp
    PersistedCounter.h
    PersistentStorageMacros.h
    Pool.cpp
    Pool.h
    PrivateHeap.cpp
    PrivateHeap.h
    ReferenceCountedHandle.h
    SafeInt.h
    SerializableIntegerSet.cpp
    SerializableIntegerSet.h
    StateMachine.h
    ThreadOperationalDataset.cpp
    ThreadOperationalDataset.h
    TimeUtils.cpp
    TimeUtils.h
    UnitTestRegistration.cpp
    UnitTestRegistration.h
    UnitTestUtils.cpp
    UnitTestUtils.h
    Variant.h
    ZclString.cpp
    ZclString.h
    logging/CHIPLogging.cpp
    logging/CHIPLogging.h
    verhoeff/Verhoeff.cpp
    verhoeff/Verhoeff.h
    verhoeff/Verhoeff10.cpp
    verhoeff/Verhoeff16.cpp
    verhoeff/Verhoeff32.cpp
    verhoeff/Verhoeff36.cpp
)

target_compile_definitions(SupportLayer PRIVATE)
target_compile_options(SupportLayer PRIVATE)
target_include_directories(SupportLayer PRIVATE ${COMMON_INCLUDES})
target_sources(SupportLayer PRIVATE ${COMMON_SOURCES})

target_link_libraries(SupportLayer PRIVATE chip-config)
