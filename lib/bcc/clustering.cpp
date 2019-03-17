#include "clustering.h"

#include <memory>

#include <VieClus_interface.h>

#include "timer.h"

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

	if (partition_config.bcc_default_clustering) {
		std::cout << "[MODE_CLUSTER_COARSENING] calling VieClus::run_default()" << std::endl;
		modularity = VieClus::run_default(graph, partition_config.bcc_time_limit, partition_config.seed, &clustering_k, partition_map.get());
	} else if (partition_config.bcc_shallow_clustering) {
		std::cout << "[MODE_CLUSTER_COARSENING] calling VieClus::run_shallow()" << std::endl;
		modularity = VieClus::run_shallow(graph, partition_config.bcc_time_limit, partition_config.seed, &clustering_k, partition_map.get());
	} else if (partition_config.bcc_shallow_no_lp_clustering) {
		std::cout << "[MODE_CLUSTER_COARSENING] calling VieClus::run_shallow_no_lp()" << std::endl;
		modularity = VieClus::run_shallow_no_lp(graph, partition_config.bcc_time_limit, partition_config.seed, &clustering_k, partition_map.get());
	} else {
		std::cerr << "[MODE_CLUSTER_COARSENING] error: no VieClus mode was set" << std::endl;
		std::exit(1);
	}

	std::cout << "[MODE_CLUSTER_COARSENING] VieClus took: " << t.elapsed() << std::endl;
	std::cout << "[MODE_CLUSTER_COARSENING] modularity: " << modularity << std::endl;
	if (clustering_k < 0) {
		std::cout << "[MODE_CLUSTER_COARSENING] error: clustering did not set k" << std::endl;
		std::exit(1);
	}
	std::cout << "[MODE_CLUSTER_COARSENING] no_clusters: " << clustering_k << std::endl;
	if (partition_config.bcc_combine == 2) {
		G.resizeSecondPartitionIndex(G.number_of_nodes());
	} else if (partition_config.bcc_combine == 1) {
		G.set_partition_count(clustering_k);
	}

	for (NodeID v = 0; v < G.number_of_nodes(); ++v) {
		if (partition_config.bcc_combine == 1) {
			G.setPartitionIndex(v, partition_map[v]);
		} else {
			G.setSecondPartitionIndex(v, partition_map[v]);
		}
	}

	delete[] graph.xadj;
	delete[] graph.adjncy;
	delete[] graph.vwgt;
	delete[] graph.adjwgt;

	if (partition_config.bcc_combine == 2) {
		partition_config.combine = true;
	}

	return modularity;
}

}