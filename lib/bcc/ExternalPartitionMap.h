#ifndef KAHIP_EXTERNALPARTITIONMAP_H
#define KAHIP_EXTERNALPARTITIONMAP_H

#include <definitions.h>
#include <data_structure/graph_access.h>

namespace BCC {
    class ExternalPartitionMap {
    public:
        ExternalPartitionMap() = default;

        explicit ExternalPartitionMap(graph_access &G);

        void set(graph_access &G);

        void apply(graph_access &G);

    private:
        std::vector<PartitionID> m_partitionMap{};
        PartitionID m_k{0};
    };
}

#endif // KAHIP_EXTERNALPARTITIONMAP_H
