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
#      This file is the CMake template for the CHIP SDK support library tests.
#

set(COMMON_INCLUDES
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/lib
    ${PROJECT_SOURCE_DIR}/src/include
    ${NLUNIT_TEST_INCLUDE}
)

set(COMMON_LIBS
    SupportLayer
    nlunit-test
    ${CHIP_PLATFORM_LIBS}
    chip-config
)

set(COMMON_LDPATH
    ${NLUNIT_TEST_LDPATH}
)

set(COMMON_CFLAGS
     _GNU_SOURCE  # enable vasprintf
)

#### TestErrorStr
add_executable(TestErrorStr TestErrorStr.cpp)
target_include_directories(TestErrorStr PRIVATE ${COMMON_INCLUDES})
target_link_libraries(TestErrorStr PRIVATE ${COMMON_LIBS})
target_link_directories(TestErrorStr PRIVATE ${COMMON_LDPATH})
target_compile_definitions(TestErrorStr PUBLIC ${COMMON_CFLAGS})
add_test(NAME TestErrorStr COMMAND TestErrorStr)
add_dependencies(check TestErrorStr)

#### TestTimeUtils
add_executable(TestTimeUtils TestTimeUtils.cpp)
target_include_directories(TestTimeUtils PRIVATE ${COMMON_INCLUDES})
target_link_libraries(TestTimeUtils PRIVATE ${COMMON_LIBS})
target_link_directories(TestTimeUtils PRIVATE ${COMMON_LDPATH})
add_test(NAME TestTimeUtils COMMAND TestTimeUtils)
add_dependencies(check TestTimeUtils)

#### TestCHIPArgParser
add_executable(TestCHIPArgParser TestCHIPArgParser.cpp)
target_include_directories(TestCHIPArgParser PRIVATE ${COMMON_INCLUDES})
target_link_libraries(TestCHIPArgParser PRIVATE ${COMMON_LIBS})
target_link_directories(TestCHIPArgParser PRIVATE ${COMMON_LDPATH})
add_test(NAME TestCHIPArgParser COMMAND TestCHIPArgParser)
add_dependencies(check TestCHIPArgParser)