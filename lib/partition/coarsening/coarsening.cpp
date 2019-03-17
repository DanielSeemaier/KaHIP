/******************************************************************************
 * coarsening.cpp 
 * *
 * Source of KaHIP -- Karlsruhe High Quality Partitioning.
 * Christian Schulz <christian.schulz.phone@gmail.com>
 *****************************************************************************/

#include <limits>
#include <sstream>

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

#include "bcc/clustering.h"
#include "bcc/ExternalPartitionMap.h"

coarsening::coarsening() {

}

coarsening::~coarsening() {

}

void coarsening::perform_coarsening(const PartitionConfig & partition_config, graph_access & G, graph_hierarchy & hierarchy) {

        NodeID no_of_coarser_vertices = G.number_of_nodes();
        NodeID no_of_finer_vertices   = G.number_of_nodes();

        edge_ratings rating(partition_config);
        CoarseMapping* coarse_mapping = NULL;

        graph_access* finer                      = &G;
        matching* edge_matcher                   = NULL;
        contraction* contracter                  = new contraction();
        PartitionConfig copy_of_partition_config = partition_config;

        stop_rule* coarsening_stop_rule = NULL;
        if( partition_config.mode_node_separators ) {
                coarsening_stop_rule = new separator_simple_stop_rule(copy_of_partition_config, G.number_of_nodes());
        } else {
                if(partition_config.stop_rule == STOP_RULE_SIMPLE) {
                        coarsening_stop_rule = new simple_stop_rule(copy_of_partition_config, G.number_of_nodes());
                } else if(partition_config.stop_rule == STOP_RULE_MULTIPLE_K) {
                        coarsening_stop_rule = new multiple_k_stop_rule(copy_of_partition_config, G.number_of_nodes());
                } else {
                        coarsening_stop_rule = new strong_stop_rule(copy_of_partition_config, G.number_of_nodes());
                }
        }

        coarsening_configurator coarsening_config;

        unsigned int level    = 0;
        bool contraction_stop = false;
        do {
                graph_access* coarser = new graph_access();
                coarse_mapping        = new CoarseMapping();
                Matching edge_matching;
                NodePermutationMap permutation;

                bool bcc = partition_config.bcc_full_cluster_contraction && !partition_config.initial_partitioning;

                if (bcc) {
                		BCC::ExternalPartitionMap backup;
                		if (partition_config.bcc_combine == 1) {
							backup.set(*finer);
                		}

                        std::cout << "[MODE_CLUSTER_COARSENING] calculating  a clustering on level " << level << std::endl;
                        BCC::compute_and_set_clustering(*finer, copy_of_partition_config);

                        if (partition_config.bcc_combine == 1) {
							copy_of_partition_config.matching_type = CLUSTER_COARSENING;
							coarse_mapping->resize(finer->number_of_nodes());
							for (NodeID u = 0; u < finer->number_of_nodes(); ++u) coarse_mapping->at(u) = finer->getPartitionIndex(u);
							no_of_coarser_vertices = finer->get_partition_count();

							backup.apply(*finer);
                        }
                }

                coarsening_config.configure_coarsening(copy_of_partition_config, &edge_matcher, level);
				if( partition_config.matching_type != CLUSTER_COARSENING)
						rating.rate(*finer, level);

                if (!bcc || partition_config.bcc_combine == 2) {
                        edge_matcher->match(copy_of_partition_config, *finer, edge_matching,
                                            *coarse_mapping, no_of_coarser_vertices, permutation);
                }

                delete edge_matcher; 

                if(partition_config.graph_allready_partitioned) {
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
        } while( contraction_stop ); 

        hierarchy.push_back(finer, NULL); // append the last created level

        delete contracter;
        delete coarsening_stop_rule;
}


