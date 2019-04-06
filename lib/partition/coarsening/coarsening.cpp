/******************************************************************************
 * coarsening.cpp 
 * *
 * Source of KaHIP -- Karlsruhe High Quality Partitioning.
 * Christian Schulz <christian.schulz.phone@gmail.com>
 *****************************************************************************/

#include <limits>
#include <sstream>
#include <lib/bcc/MappingVerifier.h>

#include "coarsening.h"
#include "coarsening_configurator.h"
#include "contraction.h"
#include "data_structure/graph_hierarchy.h"
#include "definitions.h"
#include "edge_rating/edge_ratings.h"
#include "graph_io.h"
#include "matching/gpa/gpa_matching.h"
#include "matching/random_matching.h"
#include "stop_rules/stop_rules.h"

#include "bcc/VieClusAdapter.h"
#include "bcc/ExternalPartitionMap.h"

coarsening::coarsening() {

}

coarsening::~coarsening() {

}

void
coarsening::perform_coarsening(const PartitionConfig &partition_config, graph_access &G, graph_hierarchy &hierarchy) {

    NodeID no_of_coarser_vertices = G.number_of_nodes();
    NodeID no_of_finer_vertices = G.number_of_nodes();

    edge_ratings rating(partition_config);
    CoarseMapping *coarse_mapping = nullptr;

    graph_access *finer = &G;
    matching *edge_matcher = nullptr;
    contraction *contracter = new contraction();
    PartitionConfig copy_of_partition_config = partition_config;

    stop_rule *coarsening_stop_rule = nullptr;
    if (partition_config.mode_node_separators) {
        coarsening_stop_rule = new separator_simple_stop_rule(copy_of_partition_config, G.number_of_nodes());
    } else {
        if (partition_config.stop_rule == STOP_RULE_SIMPLE) {
            coarsening_stop_rule = new simple_stop_rule(copy_of_partition_config, G.number_of_nodes());
        } else if (partition_config.stop_rule == STOP_RULE_MULTIPLE_K) {
            coarsening_stop_rule = new multiple_k_stop_rule(copy_of_partition_config, G.number_of_nodes());
        } else {
            coarsening_stop_rule = new strong_stop_rule(copy_of_partition_config, G.number_of_nodes());
        }
    }

    coarsening_configurator coarsening_config;

    unsigned int level = 0;
    bool contraction_stop = false;
    do {
        auto *coarser = new graph_access();
        coarse_mapping = new CoarseMapping();
        Matching edge_matching;
        NodePermutationMap permutation;

        bool bcc_calculate_clustering = partition_config.bcc_mode == BCC_MULTILEVEL
                                        && !partition_config.initial_partitioning;
        if (bcc_calculate_clustering) {
            BCC::ExternalPartitionMap backup;
            if (partition_config.bcc_combine_mode == BCC_FIRST_PARTITION_INDEX) {
                backup.set(*finer);
            }

            std::cout << "[BCCInfo] Calculating  a clustering on level " << level << std::endl;
            BCC::compute_and_set_clustering(*finer, copy_of_partition_config);

            if (partition_config.bcc_combine_mode == BCC_FIRST_PARTITION_INDEX) {
                // BCC::compute_and_set_clustering() stores the clustering as graph partition, i.e. using setPartitionIndex()
                // thus we copy it to coarser_mapping[] and switch the matching_type to coarsening, then restore its
                // original partition (for vcycle 2+)
                // with matching_type == CLUSTER_COARSENING, the contraction algorithm respects coarse_mapping[]
                coarse_mapping->resize(finer->number_of_nodes());
                for (NodeID u = 0; u < finer->number_of_nodes(); ++u) {
                    coarse_mapping->at(u) = finer->getPartitionIndex(u);
                }
                no_of_coarser_vertices = finer->get_partition_count();
                copy_of_partition_config.matching_type = CLUSTER_COARSENING;
                backup.apply(*finer);
            }
        }

        coarsening_config.configure_coarsening(copy_of_partition_config, &edge_matcher, level);
        if (partition_config.matching_type != CLUSTER_COARSENING)
            rating.rate(*finer, level);

        if (!bcc_calculate_clustering || partition_config.bcc_combine_mode == BCC_SECOND_PARTITION_INDEX) {
            edge_matcher->match(copy_of_partition_config, *finer, edge_matching,
                                *coarse_mapping, no_of_coarser_vertices, permutation);
        }

        delete edge_matcher;

        if (partition_config.bcc_mode != BCC_NO_CLUSTERING
            && partition_config.bcc_combine_mode == BCC_SECOND_PARTITION_INDEX
            && !partition_config.initial_partitioning) {
            if (partition_config.matching_type == CLUSTER_COARSENING) {
                BCC::verify_mapping(*finer, *coarse_mapping, copy_of_partition_config);
            } else {
                BCC::verify_mapping(*finer, edge_matching, copy_of_partition_config);
            }
        }

        if (partition_config.graph_allready_partitioned) {
            contracter->contract_partitioned(copy_of_partition_config, *finer, *coarser, edge_matching,
                                             *coarse_mapping, no_of_coarser_vertices, permutation);
        } else {
            contracter->contract(copy_of_partition_config, *finer, *coarser, edge_matching,
                                 *coarse_mapping, no_of_coarser_vertices, permutation);
        }

        hierarchy.push_back(finer, coarse_mapping);
        contraction_stop = coarsening_stop_rule->stop(no_of_finer_vertices, no_of_coarser_vertices);

        no_of_finer_vertices = no_of_coarser_vertices;

        finer = coarser;

        level++;
    } while (contraction_stop);

    hierarchy.push_back(finer, nullptr); // append the last created level

    delete contracter;
    delete coarsening_stop_rule;
}


