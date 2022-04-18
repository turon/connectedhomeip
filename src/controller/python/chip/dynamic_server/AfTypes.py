'''
   Copyright (c) 2021 Project CHIP Authors

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
'''

import construct
import ctypes
import chip.native
import chip.exceptions
import typing
from dataclasses import dataclass
from enum import IntEnum
import builtins

# EmberAfAttributeMetadata = construct.Struct(
#     "attributeId" / construct.Int32ul,
#     "attributeType" / construct.Int8ul,
# )
# 
# EmberAfCluster = construct.Struct(
#     "clusterId" / construct.Int32ul,
#     "attributeCount" / construct.Int16ul,
#     "attributes" / construct.Array(construct.this.attributeCount, EmberAfAttributeMetadata),
# )
# 
# EmberAfEndpointType = construct.Struct(
#     "clusterCount" / construct.Int8ul,
#     "cluster" / construct.Array(construct.this.clusterCount, EmberAfCluster)
# )

class EmberAfAttributeMetadata(ctypes.Structure):
    _fields_ = [
        ('attributeId', ctypes.c_uint32),
        ('attributeType', ctypes.c_uint8)
    ]

class EmberAfCluster(ctypes.Structure):
    _fields_ = [
        ('clusterId', ctypes.c_uint32),
        ('attributeCount', ctypes.c_uint16),
        ('attributes', ctypes.POINTER(EmberAfAttributeMetadata))
    ]

    # def __init__(self, attributeCount):
    #     elems = (ctypes.POINTER(EmberAfAttributeMetadata) * attributeCount)()
    #     self.attributes = ctypes.cast(elems, ctypes.POINTER(EmberAfAttributeMetadata))
    #     self.attributeCount = attributeCount

class EmberAfEndpointType(ctypes.Structure):
    _fields_ = [
        ('clusterCount', ctypes.c_uint8),
        ('cluster', ctypes.POINTER(EmberAfCluster))
    ]

    # def __init__(self, clusterCount):
    #     elems = (ctypes.POINTER(EmberAfCluster) * clusterCount)()
    #     self.cluster = ctypes.cast(elems, ctypes.POINTER(EmberAfCluster))
    #     self.clusterCount = clusterCount


def DoWork():
    _handle = chip.native.GetLibraryHandle()

    endpoint = EmberAfEndpointType()
    endpoint.clusterCount = 2
    endpoint.cluster = (EmberAfCluster * 2)()
    endpoint.cluster[0].clusterId = 15 
    endpoint.cluster[0].attributeCount = 2
    endpoint.cluster[0].attributes = (EmberAfAttributeMetadata * 2)()
    endpoint.cluster[0].attributes[0].attributeId = 200
    endpoint.cluster[0].attributes[1].attributeId = 201

    endpoint.cluster[1].clusterId = 10
    endpoint.cluster[1].attributeCount = 2
    endpoint.cluster[1].attributes = (EmberAfAttributeMetadata * 2)()
    endpoint.cluster[1].attributes[0].attributeId = 300
    endpoint.cluster[1].attributes[1].attributeId = 301


    _handle.pychip_Server_RegisterEndpoint.restype = ctypes.c_uint32
    builtins.chipStack.Call(
            lambda: _handle.pychip_Server_RegisterEndpoint(ctypes.c_uint16(3), ctypes.byref(endpoint))
    )
