/*
 *
 *    Copyright (c) 2020-2022 Project CHIP Authors
 *    Copyright (c) 2019-2020 Google LLC.
 *    Copyright (c) 2013-2018 Nest Labs, Inc.
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

#include <type_traits>

#include <controller/CHIPDeviceController.h>
#include <controller/CHIPDeviceControllerFactory.h>
#include <controller/ExampleOperationalCredentialsIssuer.h>
#include <lib/support/BytesToHex.h>
#include <lib/support/CHIPMem.h>
#include <lib/support/CodeUtils.h>
#include <lib/support/DLLUtil.h>
#include <lib/support/ScopedBuffer.h>
#include <lib/support/TestGroupData.h>
#include <lib/support/logging/CHIPLogging.h>

using namespace chip;

static_assert(std::is_same<uint32_t, ChipError::StorageType>::value, "python assumes CHIP_ERROR maps to c_uint32");

extern "C" {

struct PyEmberAfAttributeMetadata
{
    uint32_t attributeId;
    uint8_t attributeType;
};

struct PyEmberAfCluster
{
    uint32_t clusterId;
    uint16_t attributeCount;
    PyEmberAfAttributeMetadata *attributes;
};

struct PyEmberAfEndpointType
{
    uint8_t clusterCount;
    PyEmberAfCluster *cluster;
};

uint32_t pychip_Server_RegisterEndpoint(EndpointId endpointId, void *buf)
{
    PyEmberAfEndpointType *endpointType = (PyEmberAfEndpointType *)(buf);

    printf("%d\n", endpointType->clusterCount);

    PyEmberAfCluster *cluster = endpointType->cluster;
    for (int i = 0; i < endpointType->clusterCount; i++) {
        printf("\t%08x\n", cluster[i].clusterId);
        printf("\t%d\n", cluster[i].attributeCount);

        auto *attributeMetadata = cluster[i].attributes;
        for (int j = 0; j < cluster[i].attributeCount; j++) {
            printf("\t\t%d\n", attributeMetadata[j].attributeId);
        }
    }

    // uint8_t *buf8 = (uint8_t *)buf;
    // for (int i = 0; i < 200; i++) {
    //     printf("%02x ", buf8[i]);
    //     if (i % 7 == 0)
    //         printf("\n");
    // }

    return 0;
}

} // extern "C"
