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
#      This file is the CMake template for the CHIP SDK application layer,
#      data model, and ZigBee Cluster Library (ZCL) code.
#

add_library(ChipDataModel
    AttributeAccessInterface.cpp
    AttributeCache.cpp
    AttributeCache.h
    AttributePathExpandIterator.cpp
    AttributePathExpandIterator.h
    AttributePathParams.h
    BufferedReadCallback.cpp
    CASEClient.cpp
    CASEClient.h
    CASEClientPool.h
    CASESessionManager.cpp
    CASESessionManager.h
    CommandHandler.cpp
    CommandSender.cpp
    DeviceProxy.cpp
    DeviceProxy.h
    EventManagement.cpp
    EventPathParams.h
    InteractionModelEngine.cpp
    MessageDef/ArrayBuilder.cpp
    MessageDef/ArrayParser.cpp
    MessageDef/AttributeDataIB.cpp
    MessageDef/AttributeDataIB.h
    MessageDef/AttributeDataIBs.cpp
    MessageDef/AttributeDataIBs.h
    MessageDef/AttributePathIB.cpp
    MessageDef/AttributePathIB.h
    MessageDef/AttributePathIBs.cpp
    MessageDef/AttributePathIBs.h
    MessageDef/AttributeReportIB.cpp
    MessageDef/AttributeReportIB.h
    MessageDef/AttributeReportIBs.cpp
    MessageDef/AttributeReportIBs.h
    MessageDef/AttributeStatusIB.cpp
    MessageDef/AttributeStatusIB.h
    MessageDef/AttributeStatusIBs.cpp
    MessageDef/AttributeStatusIBs.h
    MessageDef/Builder.cpp
    MessageDef/Builder.h
    MessageDef/ClusterPathIB.cpp
    MessageDef/ClusterPathIB.h
    MessageDef/CommandDataIB.cpp
    MessageDef/CommandPathIB.cpp
    MessageDef/CommandStatusIB.cpp
    MessageDef/DataVersionFilterIB.cpp
    MessageDef/DataVersionFilterIB.h
    MessageDef/DataVersionFilterIBs.cpp
    MessageDef/DataVersionFilterIBs.h
    MessageDef/EventDataIB.cpp
    MessageDef/EventDataIB.h
    MessageDef/EventFilterIB.cpp
    MessageDef/EventFilterIBs.cpp
    MessageDef/EventPathIB.cpp
    MessageDef/EventPathIB.h
    MessageDef/EventPathIBs.cpp
    MessageDef/EventPathIBs.h
    MessageDef/EventReportIB.cpp
    MessageDef/EventReportIB.h
    MessageDef/EventReportIBs.cpp
    MessageDef/EventReportIBs.h
    MessageDef/EventStatusIB.cpp
    MessageDef/EventStatusIB.h
    MessageDef/InvokeRequestMessage.cpp
    MessageDef/InvokeRequests.cpp
    MessageDef/InvokeResponseIB.cpp
    MessageDef/InvokeResponseIBs.cpp
    MessageDef/InvokeResponseMessage.cpp
    MessageDef/ListBuilder.cpp
    MessageDef/ListParser.cpp
    MessageDef/MessageDefHelper.cpp
    MessageDef/MessageDefHelper.h
    MessageDef/Parser.cpp
    MessageDef/Parser.h
    MessageDef/ReadRequestMessage.cpp
    MessageDef/ReadRequestMessage.h
    MessageDef/ReportDataMessage.cpp
    MessageDef/ReportDataMessage.h
    MessageDef/StatusIB.cpp
    MessageDef/StatusIB.h
    MessageDef/StatusResponseMessage.cpp
    MessageDef/StructBuilder.cpp
    MessageDef/StructParser.cpp
    MessageDef/SubscribeRequestMessage.cpp
    MessageDef/SubscribeResponseMessage.cpp
    MessageDef/TimedRequestMessage.cpp
    MessageDef/WriteRequestMessage.cpp
    MessageDef/WriteResponseMessage.cpp
    OperationalDeviceProxy.cpp
    OperationalDeviceProxy.h
    OperationalDeviceProxyPool.h
    ReadClient.cpp
    ReadHandler.cpp
    StatusResponse.cpp
    StatusResponse.h
    TimedHandler.cpp
    TimedHandler.h
    TimedRequest.cpp
    TimedRequest.h
    WriteClient.cpp
    WriteHandler.cpp
    decoder.cpp
    encoder-common.cpp
    reporting/Engine.cpp
    reporting/Engine.h
)

set(COMMON_INCLUDES
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/include
    ${PROJECT_SOURCE_DIR}/src/lib
    ${PROJECT_SOURCE_DIR}/src/app/chip-zcl
    ${PROJECT_SOURCE_DIR}/src/app/gen
)

set(COMMON_LIBS
    SystemLayer
    SupportLayer
    TransportLayer
    TransportLayerTests
    ${CHIP_PLATFORM_LIBS}
    chip-config
)

target_include_directories(ChipDataModel PRIVATE ${COMMON_INCLUDES})
target_link_libraries(ChipDataModel PRIVATE chip-config)
