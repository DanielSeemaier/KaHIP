#include "VieClusAdapter.h"

#include <memory>

#include <VieClus_interface.h>

#include "timer.h"
#include "ExternalPartitionMap.h"
#include "ModularityMetric.h"

using namespace std::string_literals;

namespace BCC {
    double compute_and_set_clustering(graph_access &G, PartitionConfig &partition_config) {
        VieClus::Graph graph{
                G.number_of_nodes(),
                G.UNSAFE_metis_style_xadj_array(),
                G.UNSAFE_metis_style_adjncy_array(),
                G.UNSAFE_metis_style_vwgt_array(),
                G.UNSAFE_metis_style_adjwgt_array()
        };
        int clustering_k = -1;
        auto partition_map = std::make_unique<int[]>(G.number_of_nodes());

        timer t;
        double modularity;

        if (partition_config.bcc_vieclus_mode == VIECLUS_NORMAL) {
            modularity = VieClus::run_default(graph, partition_config.bcc_time_limit, partition_config.seed,
                                              &clustering_k, partition_map.get());
        } else if (partition_config.bcc_vieclus_mode == VIECLUS_SHALLOW) {
            modularity = VieClus::run_shallow(graph, partition_config.bcc_time_limit, partition_config.seed,
                                              &clustering_k, partition_map.get());
        } else if (partition_config.bcc_vieclus_mode == VIECLUS_SHALLOW_NO_LP) {
            modularity = VieClus::run_shallow_no_lp(graph, partition_config.bcc_time_limit, partition_config.seed,
                                                    &clustering_k, partition_map.get());
        } else {
            throw std::runtime_error("Invalid value for PartitionConfig::bcc_vieclus_mode: "s
                                     + std::to_string(partition_config.bcc_vieclus_mode));
        }

        std::cout << "[BCC] time(VieClus)=" << t.elapsed() << ";"
                  << " modularity=" << modularity << std::endl;
        if (clustering_k < 0) {
            throw std::runtime_error("VieClus algorithm did not report the number of clusters");
        }
        std::cout << "[BCC] no_clusters=" << clustering_k << std::endl;
        if (partition_config.bcc_combine_mode == BCC_SECOND_PARTITION_INDEX) {
            G.resizeSecondPartitionIndex(G.number_of_nodes());
        } else if (partition_config.bcc_combine_mode == BCC_FIRST_PARTITION_INDEX) {
            G.set_partition_count(clustering_k);
        } else {
            throw std::runtime_error("Invalid value for PartitionConifg::bcc_combine_mode: "s
                                     + std::to_string(partition_config.bcc_combine_mode));
        }

        for (NodeID v = 0; v < G.number_of_nodes(); ++v) {
            if (partition_config.bcc_combine_mode == BCC_FIRST_PARTITION_INDEX) {
                G.setPartitionIndex(v, partition_map[v]);
            } else if (partition_config.bcc_combine_mode == BCC_SECOND_PARTITION_INDEX) {
                G.setSecondPartitionIndex(v, partition_map[v]);
            }
        }

        delete[] graph.xadj;
        delete[] graph.adjncy;
        delete[] graph.vwgt;
        delete[] graph.adjwgt;

        // check modularity score to make sure that the call to VieClus worked out
        if (partition_config.bcc_verify) {
            ExternalPartitionMap partition(G);
            G.set_partition_count(clustering_k);
            for (NodeID v = 0; v < G.number_of_nodes(); ++v) {
                G.setPartitionIndex(v, partition_map[v]);
            }
            double check = ModularityMetric(G).quality();
            if (std::abs(modularity - check) > 0.005) {
                throw std::runtime_error("VieClus and KaHIP report different modularity scores: "s
                                         + std::to_string(modularity) + " vs "s + std::to_string(check));
            }
            partition.apply(G);
        }

        if (partition_config.bcc_combine_mode == BCC_SECOND_PARTITION_INDEX) {
            partition_config.combine = true;
        }

        return modularity;
    }
}