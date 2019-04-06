#include "MappingVerifier.h"

using namespace std::string_literals;

namespace BCC {
    void verify_mapping(graph_access &G, const std::vector<NodeID> &mapping, const PartitionConfig &partition_config) {
        if (partition_config.bcc_combine_mode != BCC_SECOND_PARTITION_INDEX) {
            throw std::runtime_error("this check is pointless for combine modes other than BCC_SECOND_PARTITION_INDEX");
        }
        if (!partition_config.combine) {
            throw std::runtime_error("PartitionConfig::combine should be set to true");
        }
        if (mapping.size() != G.number_of_nodes()) {
            throw std::runtime_error("bad mapping size: "s + std::to_string(mapping.size()) + " vs "s
                                     + std::to_string(G.number_of_nodes()));
        }

        for (NodeID u = 0; u < G.number_of_nodes(); ++u) {
            for (EdgeID e = G.get_first_edge(u); e < G.get_first_invalid_edge(u); ++e) {
                NodeID v = G.getEdgeTarget(e);
                // u and v are in different clusters -> edge may not be contracted
                if (G.getSecondPartitionIndex(u) != G.getSecondPartitionIndex(v) && mapping[u] == mapping[v]) {
                    throw std::runtime_error("bad mapping: "s + std::to_string(u) + " and "s + std::to_string(v)
                                             + " are in different clusters but are mapped to the same coarser node");
                }
            }
        }
    }
}
