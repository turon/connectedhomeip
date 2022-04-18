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
import chip.clusters.ClusterObjects as ClusterObjects
from .AfTypes import *
import builtins

class Server():
    endpointList = {}
    _handle = chip.native.GetLibraryHandle()

    def __init__(self):
        print("Hello")

    def _RegisterEndpoint(self, endpointId):
        if (endpointId not in self.endpointList):
            raise ValueError(f"{endpointId} not in endpoint list")

        endpoint = self.endpointList[endpointId]
        #emberAfEndpointType = {"clusterCount": len(endpoint), "cluster": []}
        c_emberAfEndpointType = EmberAfEndpointType()
        c_emberAfEndpointType.clusterCount = len(endpoint)
        c_emberAfEndpointType.cluster = (EmberAfCluster * c_emberAfEndpointType.clusterCount)()

        i = 0
        for cluster in endpoint:
            c_cluster = c_emberAfEndpointType.cluster[i]

            c_cluster.clusterId = cluster.id
            c_cluster.attributeCount = len(cluster.descriptor.Fields)
            c_cluster.attributes = (EmberAfAttributeMetadata * c_cluster.attributeCount)()

            #emberAfCluster = {"clusterId": cluster.id, "attributeCount": len(cluster.descriptor.Fields), "attributes": []}

            j = 0 
            for field in cluster.descriptor.Fields:
                c_metadata = c_cluster.attributes[j]
           
                c_metadata.attributeId = field.Tag
                c_metadata.attributeType = 1

                #emberAfAttributeMetadata = {"attributeId": field.Tag, "attributeType": 1}
                #emberAfCluster["attributes"].append(emberAfAttributeMetadata)
                j = j + 1

            #emberAfEndpointType["cluster"].append(emberAfCluster)
            i = i + 1

        #c_emberAfEndpointType = EmberAfEndpointType.build(emberAfEndpointType)
        #print(c_emberAfEndpointType)

        self._handle.pychip_Server_RegisterEndpoint.restype = ctypes.c_uint32
        builtins.chipStack.Call(
                lambda: self._handle.pychip_Server_RegisterEndpoint(ctypes.c_uint16(endpointId), ctypes.byref(c_emberAfEndpointType))
        )

    def CreateEndpoint(self, endpointId = int, clusterList = typing.List[ClusterObjects.Cluster]):
        if (endpointId in self.endpointList):
            raise ValueError(f"{endpointId} already exists on this node!")

        self.endpointList[endpointId] = clusterList
        return self._RegisterEndpoint(endpointId)
