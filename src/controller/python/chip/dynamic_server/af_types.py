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

EmberAfAttributeMetadata = construct.Struct(
    "attributeId" / construct.Int32ul,
    "attributeType" / construct.Int8ul,
)

EmberAfCluster = construct.Struct(
    "clusterId" / construct.Int32ul,
    "attributeCount" / construct.Int16ul,
    "attributes" / construct.Array(construct.this.attributeCount, EmberAfAttributeMetadata),
)

EmberAfEndpointType = construct.Struct(
    "clusterCount" / construct.Int8ul,
    "cluster" / construct.Array(construct.this.clusterCount, EmberAfCluster)
)
