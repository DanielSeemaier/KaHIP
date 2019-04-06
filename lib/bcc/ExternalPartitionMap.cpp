#include "ExternalPartitionMap.h"

namespace BCC {
    ExternalPartitionMap::ExternalPartitionMap(graph_access &G) {
        set(G);
    }

    void ExternalPartitionMap::set(graph_access &G) {
        m_k = G.get_partition_count();
        m_partitionMap.resize(G.number_of_nodes());
        for (std::size_t u = 0; u < G.number_of_nodes(); ++u) m_partitionMap[u] = G.getPartitionIndex(u);
    }

    void ExternalPartitionMap::apply(graph_access &G) {
        G.set_partition_count(m_k);
        for (std::size_t u = 0; u < G.number_of_nodes(); ++u) G.setPartitionIndex(u, m_partitionMap[u]);
    }
}