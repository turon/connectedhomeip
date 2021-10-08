/*
 *
 *    Copyright (c) 2020 Project CHIP Authors
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

/**
 *    @file
 *      This file implements a process to effect a functional test for
 *      the Message Header class within the transport layer
 *
 */
#include <lib/support/CodeUtils.h>
#include <lib/support/ErrorStr.h>
#include <lib/support/UnitTestRegistration.h>
#include <protocols/Protocols.h>
#include <transport/raw/MessageHeader.h>

#include <nlunit-test.h>

namespace {

using namespace chip;

void TestPacketHeaderInitialState(nlTestSuite * inSuite, void * inContext)
{
    PacketHeader header;

    NL_TEST_ASSERT(inSuite, !header.IsSecureSessionControlMsg());
    NL_TEST_ASSERT(inSuite, header.GetMessageCounter() == 0);
    NL_TEST_ASSERT(inSuite, header.GetSessionId() == 0);
    NL_TEST_ASSERT(inSuite, !header.IsEncrypted());
    NL_TEST_ASSERT(inSuite, !header.GetDestinationNodeId().HasValue());
    NL_TEST_ASSERT(inSuite, !header.GetDestinationGroupId().HasValue());
    NL_TEST_ASSERT(inSuite, !header.GetSourceNodeId().HasValue());
}

void TestPayloadHeaderInitialState(nlTestSuite * inSuite, void * inContext)
{
    PayloadHeader header;

    NL_TEST_ASSERT(inSuite, header.GetMessageType() == 0);
    NL_TEST_ASSERT(inSuite, header.GetExchangeID() == 0);
    NL_TEST_ASSERT(inSuite, header.HasProtocol(Protocols::NotSpecified));
}

void TestPacketHeaderEncodeDecode(nlTestSuite * inSuite, void * inContext)
{
    PacketHeader header;
    uint8_t buffer[64];
    uint16_t encodeLen;
    uint16_t decodeLen;

    header.SetMessageCounter(123);
    NL_TEST_ASSERT(inSuite, header.Encode(buffer, &encodeLen) == CHIP_NO_ERROR);

    // change it to verify decoding
    header.SetMessageCounter(222).SetSourceNodeId(1).SetDestinationNodeId(2);

    NL_TEST_ASSERT(inSuite, header.Decode(buffer, &decodeLen) == CHIP_NO_ERROR);
    NL_TEST_ASSERT(inSuite, encodeLen == decodeLen);
    NL_TEST_ASSERT(inSuite, header.GetMessageCounter() == 123);
    NL_TEST_ASSERT(inSuite, !header.GetDestinationNodeId().HasValue());

    header.SetSourceNodeId(55);
    NL_TEST_ASSERT(inSuite, header.Encode(buffer, &encodeLen) == CHIP_NO_ERROR);

    // change it to verify decoding
    header.SetMessageCounter(222).SetSourceNodeId(1).SetDestinationNodeId(2);

    NL_TEST_ASSERT(inSuite, header.Decode(buffer, &decodeLen) == CHIP_NO_ERROR);
    NL_TEST_ASSERT(inSuite, encodeLen == decodeLen);
    NL_TEST_ASSERT(inSuite, header.GetMessageCounter() == 123);
    NL_TEST_ASSERT(inSuite, !header.GetDestinationNodeId().HasValue());
    NL_TEST_ASSERT(inSuite, header.GetSourceNodeId() == Optional<uint64_t>::Value(55ull));

    header.ClearSourceNodeId().SetDestinationNodeId(11);
    NL_TEST_ASSERT(inSuite, header.Encode(buffer, &encodeLen) == CHIP_NO_ERROR);

    // change it to verify decoding
    header.SetMessageCounter(222).SetSourceNodeId(1).SetDestinationNodeId(2);
    NL_TEST_ASSERT(inSuite, header.Decode(buffer, &decodeLen) == CHIP_NO_ERROR);
    NL_TEST_ASSERT(inSuite, encodeLen == decodeLen);
    NL_TEST_ASSERT(inSuite, header.GetMessageCounter() == 123);
    NL_TEST_ASSERT(inSuite, header.GetDestinationNodeId() == Optional<uint64_t>::Value(11ull));
    NL_TEST_ASSERT(inSuite, !header.GetSourceNodeId().HasValue());

    header.SetMessageCounter(234).SetSourceNodeId(77).SetDestinationNodeId(88);
    NL_TEST_ASSERT(inSuite, header.Encode(buffer, &encodeLen) == CHIP_NO_ERROR);

    // change it to verify decoding
    header.SetMessageCounter(222).SetSourceNodeId(1).SetDestinationNodeId(2);
    NL_TEST_ASSERT(inSuite, header.Decode(buffer, &decodeLen) == CHIP_NO_ERROR);
    NL_TEST_ASSERT(inSuite, encodeLen == decodeLen);
    NL_TEST_ASSERT(inSuite, header.GetMessageCounter() == 234);
    NL_TEST_ASSERT(inSuite, header.GetDestinationNodeId() == Optional<uint64_t>::Value(88ull));
    NL_TEST_ASSERT(inSuite, header.GetSourceNodeId() == Optional<uint64_t>::Value(77ull));

    header.SetMessageCounter(234).SetSourceNodeId(77).SetDestinationNodeId(88).SetSecureSessionControlMsg(true);
    NL_TEST_ASSERT(inSuite, header.Encode(buffer, &encodeLen) == CHIP_NO_ERROR);

    // change it to verify decoding
    header.SetMessageCounter(222).SetSourceNodeId(1).SetDestinationNodeId(2);
    NL_TEST_ASSERT(inSuite, header.Decode(buffer, &decodeLen) == CHIP_NO_ERROR);
    NL_TEST_ASSERT(inSuite, header.GetMessageCounter() == 234);
    NL_TEST_ASSERT(inSuite, header.GetDestinationNodeId() == Optional<uint64_t>::Value(88ull));
    NL_TEST_ASSERT(inSuite, header.GetSourceNodeId() == Optional<uint64_t>::Value(77ull));
    NL_TEST_ASSERT(inSuite, header.IsSecureSessionControlMsg());

    header.SetMessageCounter(234).SetSourceNodeId(77).SetDestinationNodeId(88).SetSessionId(2);
    NL_TEST_ASSERT(inSuite, header.Encode(buffer, &encodeLen) == CHIP_NO_ERROR);

    // change it to verify decoding
    header.SetMessageCounter(222).SetSourceNodeId(1).SetDestinationNodeId(2);
    NL_TEST_ASSERT(inSuite, header.Decode(buffer, &decodeLen) == CHIP_NO_ERROR);
    NL_TEST_ASSERT(inSuite, header.GetMessageCounter() == 234);
    NL_TEST_ASSERT(inSuite, header.GetDestinationNodeId() == Optional<uint64_t>::Value(88ull));
    NL_TEST_ASSERT(inSuite, header.GetSourceNodeId() == Optional<uint64_t>::Value(77ull));
    NL_TEST_ASSERT(inSuite, header.IsEncrypted());
    NL_TEST_ASSERT(inSuite, header.GetSessionId() == 2);

    header.SetMessageCounter(234).SetSourceNodeId(77).SetDestinationNodeId(88);
    NL_TEST_ASSERT(inSuite, header.Encode(buffer, &encodeLen) == CHIP_NO_ERROR);

    // change it to verify decoding
    header.SetMessageCounter(222).SetSourceNodeId(1).SetDestinationNodeId(2);
    NL_TEST_ASSERT(inSuite, header.Decode(buffer, &decodeLen) == CHIP_NO_ERROR);
    NL_TEST_ASSERT(inSuite, header.GetMessageCounter() == 234);
    NL_TEST_ASSERT(inSuite, header.GetDestinationNodeId() == Optional<uint64_t>::Value(88ull));
    NL_TEST_ASSERT(inSuite, header.GetSourceNodeId() == Optional<uint64_t>::Value(77ull));

    // Verify Group Id helpers
    header.SetMessageCounter(234).SetSourceNodeId(77).SetDestinationGroupId(45);
    NL_TEST_ASSERT(inSuite, header.Encode(buffer, &encodeLen) == CHIP_ERROR_INTERNAL);

    header.ClearDestinationNodeId();
    NL_TEST_ASSERT(inSuite, header.Encode(buffer, &encodeLen) == CHIP_NO_ERROR);

    // change it to verify decoding
    header.SetMessageCounter(222).SetSourceNodeId(1).SetDestinationGroupId(2);
    NL_TEST_ASSERT(inSuite, header.Decode(buffer, &decodeLen) == CHIP_NO_ERROR);
    NL_TEST_ASSERT(inSuite, header.GetMessageCounter() == 234);
    NL_TEST_ASSERT(inSuite, header.GetDestinationGroupId() == Optional<uint16_t>::Value((uint16_t) 45));
    NL_TEST_ASSERT(inSuite, header.GetSourceNodeId() == Optional<uint64_t>::Value(77ull));
}

void TestPayloadHeaderEncodeDecode(nlTestSuite * inSuite, void * inContext)
{
    PayloadHeader header;
    uint8_t buffer[64];
    uint16_t encodeLen;
    uint16_t decodeLen;

    header.SetMessageType(Protocols::Id(VendorId::Common, 0), 112).SetExchangeID(2233);
    NL_TEST_ASSERT(inSuite, header.GetProtocolID() == Protocols::Id(VendorId::Common, 0));

    header.SetMessageType(Protocols::Id(VendorId::Common, 1221), 112).SetExchangeID(2233).SetInitiator(true);
    NL_TEST_ASSERT(inSuite, header.Encode(buffer, &encodeLen) == CHIP_NO_ERROR);

    header.SetMessageType(Protocols::Id(VendorId::Common, 4567), 221).SetExchangeID(3322);
    NL_TEST_ASSERT(inSuite, header.Decode(buffer, &decodeLen) == CHIP_NO_ERROR);
    NL_TEST_ASSERT(inSuite, encodeLen == decodeLen);
    NL_TEST_ASSERT(inSuite, header.GetMessageType() == 112);
    NL_TEST_ASSERT(inSuite, header.GetExchangeID() == 2233);
    NL_TEST_ASSERT(inSuite, header.GetProtocolID() == Protocols::Id(VendorId::Common, 1221));
    NL_TEST_ASSERT(inSuite, header.IsInitiator());

    header.SetMessageType(Protocols::Id(VendorId::Common, 1221), 112).SetExchangeID(2233);

    NL_TEST_ASSERT(inSuite, header.Encode(buffer, &encodeLen) == CHIP_NO_ERROR);

    header.SetMessageType(Protocols::Id(VendorId::NotSpecified, 0), 111).SetExchangeID(222);

    NL_TEST_ASSERT(inSuite, header.Decode(buffer, &decodeLen) == CHIP_NO_ERROR);
    NL_TEST_ASSERT(inSuite, encodeLen == decodeLen);
    NL_TEST_ASSERT(inSuite, header.GetExchangeID() == 2233);
    NL_TEST_ASSERT(inSuite, header.GetProtocolID() == Protocols::Id(VendorId::Common, 1221));

    header.SetMessageType(Protocols::Id(VendorId::NotSpecified, 4567), 221).SetExchangeID(3322);

    NL_TEST_ASSERT(inSuite, header.Decode(buffer, &decodeLen) == CHIP_NO_ERROR);
    NL_TEST_ASSERT(inSuite, encodeLen == decodeLen);
    NL_TEST_ASSERT(inSuite, header.GetExchangeID() == 2233);
    NL_TEST_ASSERT(inSuite, header.GetProtocolID() == Protocols::Id(VendorId::Common, 1221));
}

void TestPacketHeaderEncodeDecodeBounds(nlTestSuite * inSuite, void * inContext)
{
    PacketHeader header;
    uint8_t buffer[64];
    uint16_t unusedLen;

    for (uint16_t shortLen = 0; shortLen < 8; shortLen++)
    {
        NL_TEST_ASSERT(inSuite, header.Encode(buffer, shortLen, &unusedLen) != CHIP_NO_ERROR);
        NL_TEST_ASSERT(inSuite, header.Decode(buffer, shortLen, &unusedLen) != CHIP_NO_ERROR);
    }

    // Now check that with 8 bytes we can successfully encode a
    // default-constructed PacketHeader.
    static const size_t minLen = 8;
    uint16_t encoded_len;
    NL_TEST_ASSERT(inSuite, header.Encode(buffer, minLen, &encoded_len) == CHIP_NO_ERROR);
    NL_TEST_ASSERT(inSuite, encoded_len == minLen);
    // Verify that decoding at any smaller length fails.
    for (uint16_t shortLen = 0; shortLen < encoded_len; shortLen++)
    {
        NL_TEST_ASSERT(inSuite, header.Decode(buffer, shortLen, &unusedLen) != CHIP_NO_ERROR);
    }
    uint16_t decoded_len;
    NL_TEST_ASSERT(inSuite, header.Decode(buffer, encoded_len, &decoded_len) == CHIP_NO_ERROR);
    NL_TEST_ASSERT(inSuite, decoded_len == encoded_len);

    // Now test encoding/decoding with a source node id present.
    header.SetSourceNodeId(1);
    for (uint16_t shortLen = minLen; shortLen < minLen + 8; shortLen++)
    {
        NL_TEST_ASSERT(inSuite, header.Encode(buffer, shortLen, &unusedLen) != CHIP_NO_ERROR);
    }
    NL_TEST_ASSERT(inSuite, header.Encode(buffer, minLen + 8, &encoded_len) == CHIP_NO_ERROR);
    NL_TEST_ASSERT(inSuite, encoded_len == minLen + 8);
    for (uint16_t shortLen = 0; shortLen < encoded_len; shortLen++)
    {
        NL_TEST_ASSERT(inSuite, header.Decode(buffer, shortLen, &unusedLen) != CHIP_NO_ERROR);
    }
    NL_TEST_ASSERT(inSuite, header.Decode(buffer, encoded_len, &decoded_len) == CHIP_NO_ERROR);
    NL_TEST_ASSERT(inSuite, decoded_len == encoded_len);

    // Now test encoding/decoding with a source and destination node id present.
    header.SetDestinationNodeId(1);
    for (uint16_t shortLen = minLen; shortLen < minLen + 16; shortLen++)
    {
        NL_TEST_ASSERT(inSuite, header.Encode(buffer, shortLen, &unusedLen) != CHIP_NO_ERROR);
    }
    NL_TEST_ASSERT(inSuite, header.Encode(buffer, minLen + 16, &encoded_len) == CHIP_NO_ERROR);
    NL_TEST_ASSERT(inSuite, encoded_len == minLen + 16);
    for (uint16_t shortLen = 0; shortLen < encoded_len; shortLen++)
    {
        NL_TEST_ASSERT(inSuite, header.Decode(buffer, shortLen, &unusedLen) != CHIP_NO_ERROR);
    }
    NL_TEST_ASSERT(inSuite, header.Decode(buffer, encoded_len, &decoded_len) == CHIP_NO_ERROR);
    NL_TEST_ASSERT(inSuite, decoded_len == encoded_len);

    // Now test encoding/decoding with a source node id and destination group id present.
    header.ClearDestinationNodeId();
    header.SetDestinationGroupId(25);
    for (uint16_t shortLen = minLen; shortLen < minLen + 10; shortLen++)
    {
        NL_TEST_ASSERT(inSuite, header.Encode(buffer, shortLen, &unusedLen) != CHIP_NO_ERROR);
    }
    NL_TEST_ASSERT(inSuite, header.Encode(buffer, minLen + 10, &encoded_len) == CHIP_NO_ERROR);
    NL_TEST_ASSERT(inSuite, encoded_len == minLen + 10);
    for (uint16_t shortLen = 0; shortLen < encoded_len; shortLen++)
    {
        NL_TEST_ASSERT(inSuite, header.Decode(buffer, shortLen, &unusedLen) != CHIP_NO_ERROR);
    }
    NL_TEST_ASSERT(inSuite, header.Decode(buffer, encoded_len, &decoded_len) == CHIP_NO_ERROR);
    NL_TEST_ASSERT(inSuite, decoded_len == encoded_len);
}

void TestPayloadHeaderEncodeDecodeBounds(nlTestSuite * inSuite, void * inContext)
{
    PayloadHeader header;
    uint8_t buffer[64];
    uint16_t unusedLen;

    for (uint16_t shortLen = 0; shortLen < 6; shortLen++)
    {
        NL_TEST_ASSERT(inSuite, header.Encode(buffer, shortLen, &unusedLen) != CHIP_NO_ERROR);
        NL_TEST_ASSERT(inSuite, header.Decode(buffer, shortLen, &unusedLen) != CHIP_NO_ERROR);
    }
}

struct SpecComplianceTestVector {
    uint8_t encoded[8];
    uint8_t messageFlags;
    uint16_t sessionId;
    uint8_t sessionType;
    uint8_t securityFlags;
    uint32_t messageCounter;

    bool isSecure;
};

struct SpecComplianceTestVector theSpecComplianceTestVector[] = {
    {
        .encoded = { 0x00,0x88,0x77,0x01,0x44,0x33,0x22,0x11 },
        .messageFlags = 0x00,
        .sessionId = 0x7788,
        .sessionType = 0x01,
        .securityFlags = 0x01,
        .messageCounter = 0x11223344,
        .isSecure = true,
    },
    {
        .encoded = { 0x00,0xEE,0xDD,0xCC,0x40,0x30,0x20,0x10 },
        .messageFlags = 0x00,
        .sessionId = 0xDDEE,
        .sessionType = 0x00,
        .securityFlags = 0xCC,
        .messageCounter = 0x10203040,
        .isSecure = true,
    },
    {
        .encoded = { 0x00,0x00,0x00,0xCC,0x40,0x30,0x20,0x10 },
        .messageFlags = 0x00,
        .sessionId = 0x0000,
        .sessionType = 0x00,
        .securityFlags = 0x00,
        .messageCounter = 0x10203040,
        .isSecure = false,
    },
};

const unsigned theSpecComplianceTestVectorLength = sizeof(theSpecComplianceTestVector) / sizeof(struct SpecComplianceTestVector);

#define MSG_HEADER_SIZE 8

void TestSpecComplianceEncode(nlTestSuite * inSuite, void * inContext)
{
    struct SpecComplianceTestVector *testEntry;
    PacketHeader packetHeader;
    uint8_t buffer[MSG_HEADER_SIZE];
    uint16_t encodeSize;

    for (unsigned i = 0; i < theSpecComplianceTestVectorLength; i++)
    {
        testEntry = &theSpecComplianceTestVector[i];

        packetHeader.SetMessageFlags(testEntry->messageFlags);
        packetHeader.SetSecurityFlags(testEntry->securityFlags);
        packetHeader.SetSessionId(testEntry->sessionId);
        packetHeader.SetMessageCounter(testEntry->messageCounter);

        NL_TEST_ASSERT(inSuite, packetHeader.Encode(buffer, sizeof(buffer), &encodeSize) == CHIP_NO_ERROR);
        NL_TEST_ASSERT(inSuite, encodeSize == MSG_HEADER_SIZE);
        NL_TEST_ASSERT(inSuite, memcmp(buffer, testEntry->encoded, MSG_HEADER_SIZE) == 0);
    }
}

void TestSpecComplianceDecode(nlTestSuite * inSuite, void * inContext)
{
    struct SpecComplianceTestVector *testEntry;
    PacketHeader packetHeader;
    uint16_t decodeSize;

    for (unsigned i = 0; i < theSpecComplianceTestVectorLength; i++)
    {
        testEntry = &theSpecComplianceTestVector[i];

        NL_TEST_ASSERT(inSuite, packetHeader.Decode(testEntry->encoded, MSG_HEADER_SIZE, &decodeSize) == CHIP_NO_ERROR);
        NL_TEST_ASSERT(inSuite, decodeSize == MSG_HEADER_SIZE);
        NL_TEST_ASSERT(inSuite, packetHeader.GetMessageFlags() == testEntry->messageFlags);
        NL_TEST_ASSERT(inSuite, packetHeader.GetSecurityFlags() == testEntry->securityFlags);
        NL_TEST_ASSERT(inSuite, packetHeader.GetSessionId() == testEntry->sessionId);
        NL_TEST_ASSERT(inSuite, packetHeader.GetMessageCounter() == testEntry->messageCounter);
        NL_TEST_ASSERT(inSuite, packetHeader.IsEncrypted() == testEntry->isSecure);
    }
}

} // namespace

// clang-format off
static const nlTest sTests[] =
{
    NL_TEST_DEF("PacketInitialState", TestPacketHeaderInitialState),
    NL_TEST_DEF("PayloadInitialState", TestPayloadHeaderInitialState),
    NL_TEST_DEF("PacketEncodeDecode", TestPacketHeaderEncodeDecode),
    NL_TEST_DEF("PayloadEncodeDecode", TestPayloadHeaderEncodeDecode),
    NL_TEST_DEF("PacketEncodeDecodeBounds", TestPacketHeaderEncodeDecodeBounds),
    NL_TEST_DEF("PayloadEncodeDecodeBounds", TestPayloadHeaderEncodeDecodeBounds),
    NL_TEST_DEF("SpecComplianceEncode", TestSpecComplianceEncode),
    NL_TEST_DEF("SpecComplianceDecode", TestSpecComplianceDecode),
    NL_TEST_SENTINEL()
};
// clang-format on

int TestMessageHeader(void)
{
    nlTestSuite theSuite = { "Transport-MessageHeader", &sTests[0], nullptr, nullptr };
    nlTestRunner(&theSuite, nullptr);
    return nlTestRunnerStats(&theSuite);
}

CHIP_REGISTER_TEST_SUITE(TestMessageHeader)
