#include <iostream>
#include <math.h>
#include <regex.h>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <memory>

#include <VieClus_interface.h>

#include "balance_configuration.h"
#include "data_structure/graph_access.h"
#include "graph_io.h"
#include "partition/graph_partitioner.h"
#include "partition/partition_config.h"
#include "quality_metrics.h"
#include "random_functions.h"
#include "timer.h"

#include "bcc/VieClusAdapter.h"
#include "configuration.h"

#include <getopt.h>

using namespace std::string_literals;

static struct option options[] = {
        {"help", no_argument, nullptr, 'h'},
        {"preconfiguration", required_argument, nullptr, 'P'},
        {"k", required_argument, nullptr, 'k'},
        {"graph", required_argument, nullptr, 'G'},
        {"seed", required_argument, nullptr, 'S'},
        {"verify", no_argument, nullptr, 'v'},
        {"time-limit", required_argument, nullptr, 'L'},
        {"clustering-mode", required_argument, nullptr, 'm'},
        {"vieclus-mode", required_argument, nullptr, 'M'},
        {"combine-mode", required_argument, nullptr, 'c'},
        {nullptr, 0, nullptr, 0}
};

class MissingArgumentException : public std::exception {
    std::string _what_message;

public:
    explicit MissingArgumentException(const char *argument_name)
            : _what_message("[BCC] Missing argument: "s + argument_name) {
    }

    const char *what() const noexcept override {
        return _what_message.c_str();
    }
};

static void _print_help() {
    std::cout << "Mandatory arguments:\n"
              << "\t--preconfiguration=[fast, fastsocial, eco, ecosocial, strong, strongsocial]\n"
              << "\t--k=integer\n"
              << "\t--graph=filename\n"
              << "\nOptional arguments:\n"
              << "\t--seed=integer\n"
              << "\t--verify (enable some time consuming checks)\n"
              << "\t--time-limit=integer (time limit for VieClus evolutionary algorithm)\n"
              << "\t--clustering-mode=[no_clustering, toplevel, multilevel]\n"
              << "\t--vieclus-mode=[default, shallow, shallownolp]\n"
              << "\t--combine-mode=[second, first]\n"
              << std::endl;
}

static PartitionConfig _parse_arguments(int argc, char **argv) {
    std::string preconfiguration_name;
    int k = 0;
    std::string graph_filename;
    int seed = 0;
    bool verify = false;
    int time_limit = 0;
    std::string clustering_mode_name;
    std::string vieclus_mode_name;
    std::string combine_mode_name;

    while (true) {
        int index;
        int c = getopt_long_only(argc, argv, "hP:k:G:S:vL:m:M:c:", options, &index);
        if (c == -1) break;

        switch (c) {
            case 0:
                break;

            case 'h': // --help
                _print_help();
                exit(EXIT_SUCCESS);
                break;

            case 'P': // --preconfiguration
                preconfiguration_name = optarg;
                break;

            case 'k': // --k
                k = std::stoi(optarg);
                break;

            case 'G': // --graph
                graph_filename = optarg;
                break;

            case 'S': // --seed
                seed = std::stoi(optarg);
                break;

            case 'v': // --verify
                verify = true;
                break;

            case 'L': // --time-limit
                time_limit = std::stoi(optarg);
                break;

            case 'm': // --clustering-mode
                clustering_mode_name = optarg;
                break;

            case 'M': // --vieclus-mode
                vieclus_mode_name = optarg;
                break;

            case 'c': // --combine-mode
                combine_mode_name = optarg;
                break;

            case '?':
                // getopt_long_only() already printed an error message
                exit(EXIT_FAILURE);

            default:
                std::cerr << "[BCC] Missing option argument for " << (char) index << std::endl;
                exit(EXIT_FAILURE);
        }
    }

    PartitionConfig partition_config;

    if (!preconfiguration_name.empty()) {
        configuration preconfigurations;
        preconfigurations.standard(partition_config);

        if (preconfiguration_name == "fast") preconfigurations.fast(partition_config);
        else if (preconfiguration_name == "fastsocial") preconfigurations.fastsocial(partition_config);
        else if (preconfiguration_name == "eco") preconfigurations.eco(partition_config);
        else if (preconfiguration_name == "ecosocial") preconfigurations.ecosocial(partition_config);
        else if (preconfiguration_name == "strong") preconfigurations.strong(partition_config);
        else if (preconfiguration_name == "strongsocial") preconfigurations.strongsocial(partition_config);
        else throw std::runtime_error("Invalid value for --preconfiguration: "s + preconfiguration_name);
    } else {
        throw MissingArgumentException("--preconfiguration");
    }

    if (!graph_filename.empty()) {
        partition_config.graph_filename = graph_filename;
    } else {
        throw MissingArgumentException("--graph");
    }

    if (k > 0) {
        partition_config.k = k;
    } else {
        throw MissingArgumentException("--k");
    }

    if (!clustering_mode_name.empty()) {
        if (clustering_mode_name == "no_clustering") partition_config.bcc_mode = BCC_NO_CLUSTERING;
        else if (clustering_mode_name == "toplevel") partition_config.bcc_mode = BCC_TOPLEVEL;
        else if (clustering_mode_name == "multilevel") partition_config.bcc_mode = BCC_MULTILEVEL;
        else throw std::runtime_error("Invalid value for --clustering-mode: "s + clustering_mode_name);
    }

    if (!vieclus_mode_name.empty()) {
        if (vieclus_mode_name == "default") partition_config.bcc_vieclus_mode = VIECLUS_NORMAL;
        else if (vieclus_mode_name == "shallow") partition_config.bcc_vieclus_mode = VIECLUS_SHALLOW;
        else if (vieclus_mode_name == "shallownolp") partition_config.bcc_vieclus_mode = VIECLUS_SHALLOW_NO_LP;
        else throw std::runtime_error("Invalid value for --vieclus-mode: "s + vieclus_mode_name);
    }

    if (!combine_mode_name.empty()) {
        if (combine_mode_name == "first") partition_config.bcc_combine_mode = BCC_FIRST_PARTITION_INDEX;
        else if (combine_mode_name == "second") partition_config.bcc_combine_mode = BCC_SECOND_PARTITION_INDEX;
        else throw std::runtime_error("Invalid value for --combine-mode: "s + combine_mode_name);
    }

    partition_config.seed = seed;
    partition_config.bcc_time_limit = time_limit;
    partition_config.bcc_verify = verify;
    partition_config.LogDump(stdout);

    return partition_config;
}

int main(int argc, char **argv) {
    VieClus::setup(&argc, &argv);
    PartitionConfig partition_config = _parse_arguments(argc, argv);
    std::cout << "[BCC] partition_configuration(initial)=" << partition_config << std::endl;

    timer t;

    // load graph G
    graph_access G;
    graph_io::readGraphWeighted(G, partition_config.graph_filename);
    std::cout << "[BCC] io_time=" << t.elapsed() << std::endl;
    G.set_partition_count(partition_config.k);
    std::cout << "[BCC] n(G)=" << G.number_of_nodes()
              << "; m(G)=" << G.number_of_edges()
              << "; k(G)=" << G.get_partition_count() << std::endl;

    // configuration
    balance_configuration bc;
    bc.configurate_balance(partition_config, G);
    std::cout << "[BCC] partition_configuration(balanced)=" << partition_config << std::endl;

    srand(partition_config.seed);
    random_functions::setSeed(partition_config.seed);

    if (partition_config.bcc_mode == BCC_TOPLEVEL) {
        BCC::compute_and_set_clustering(G, partition_config);
    }

    // perform partitioning
    t.restart();
    graph_partitioner().perform_partitioning(partition_config, G);
    std::cout << "[BCC] partitioner_time=" << t.elapsed() << std::endl;

    // print some statistics
    quality_metrics qm;
    std::cout << "[BCC] cut(final)=" << qm.edge_cut(G) << std::endl;
    std::cout << "[BCC] boundary_nodes(final)=" << qm.boundary_nodes(G) << std::endl;
    std::cout << "[BCC] balance(final)=" << qm.balance(G) << std::endl;
    std::cout << "[BCC] max_comm_vol(final)=" << qm.max_communication_volume(G) << std::endl;

    // write the partition to the disc
    if (!partition_config.filename_output.empty()) {
        graph_io::writePartition(G, partition_config.filename_output);
    }

    VieClus::teardown();
    return 0;
}
