#ifndef KAHIP_CLUSTER_H
#define KAHIP_CLUSTER_H

#include "data_structure/graph_access.h"
#include "partition/partition_config.h"

namespace BCC {

double compute_and_set_clustering(graph_access &G, PartitionConfig &partition_config);

}

#endif // KAHIP_CLUSTER_H
