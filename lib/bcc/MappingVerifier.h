#ifndef KAHIP_MAPPINGVERIFICATOR_H
#define KAHIP_MAPPINGVERIFICATOR_H

#include <lib/data_structure/graph_access.h>
#include <lib/partition/partition_config.h>

namespace BCC {
    void verify_mapping(graph_access &G, const std::vector<NodeID> &matching, const PartitionConfig &partition_config);
}

#endif // KAHIP_MAPPINGVERIFICATOR_H
