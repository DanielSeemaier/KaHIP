/******************************************************************************
 * partition_config.h 
 *
 * Source of KaHIP -- Karlsruhe High Quality Partitioning.
 * Christian Schulz <christian.schulz.phone@gmail.com>
 *****************************************************************************/

#ifndef PARTITION_CONFIG_DI1ES4T0
#define PARTITION_CONFIG_DI1ES4T0

#include <ostream>
#include "definitions.h"

// Configuration for the partitioning.
struct PartitionConfig {
    PartitionConfig() {}

    //============================================================
    //=======================MATCHING=============================
    //============================================================
    bool edge_rating_tiebreaking;

    EdgeRating edge_rating;

    PermutationQuality permutation_quality;

    MatchingType matching_type;

    bool match_islands;

    bool first_level_random_matching;

    bool rate_first_level_inner_outer;

    NodeWeight max_vertex_weight;

    NodeWeight largest_graph_weight;

    NodeWeight work_load;

    unsigned aggressive_random_levels;

    bool disable_max_vertex_weight_constraint;

    //============================================================
    //===================INITIAL PARTITIONING=====================
    //============================================================
    unsigned int initial_partitioning_repetitions;

    unsigned int minipreps;

    bool refined_bubbling;

    InitialPartitioningType initial_partitioning_type;

    bool initial_partition_optimize;

    BipartitionAlgorithm bipartition_algorithm;

    bool initial_partitioning;

    int bipartition_tries;

    int bipartition_post_fm_limits;

    int bipartition_post_ml_limits;

    //============================================================
    //====================REFINEMENT PARAMETERS===================
    //============================================================
    bool corner_refinement_enabled;

    bool use_bucket_queues;

    RefinementType refinement_type;

    PermutationQuality permutation_during_refinement;

    ImbalanceType imbalance;

    unsigned bubbling_iterations;

    unsigned kway_rounds;

    bool quotient_graph_refinement_disabled;

    KWayStopRule kway_stop_rule;

    double kway_adaptive_limits_alpha;

    double kway_adaptive_limits_beta;

    unsigned max_flow_iterations;

    unsigned local_multitry_rounds;

    unsigned local_multitry_fm_alpha;

    bool graph_allready_partitioned;

    unsigned int fm_search_limit;

    unsigned int kway_fm_search_limit;

    NodeWeight upper_bound_partition;

    double bank_account_factor;

    RefinementSchedulingAlgorithm refinement_scheduling_algorithm;

    bool most_balanced_minimum_cuts;

    bool most_balanced_minimum_cuts_node_sep;

    unsigned toposort_iterations;

    bool softrebalance;

    bool rebalance;

    double flow_region_factor;

    bool gpa_grow_paths_between_blocks;

    //=======================================
    //==========GLOBAL SEARCH PARAMETERS=====
    //=======================================
    unsigned global_cycle_iterations;

    bool use_wcycles;

    bool use_fullmultigrid;

    unsigned level_split;

    bool no_new_initial_partitioning;

    bool omit_given_partitioning;

    StopRule stop_rule;

    int num_vert_stop_factor;

    bool no_change_convergence;

    //=======================================
    //===PERFECTLY BALANCED PARTITIONING ====
    //=======================================
    bool remove_negative_cycles;

    bool kaba_include_removal_of_paths;

    bool kaba_enable_zero_weight_cycles;

    double kabaE_internal_bal;

    CycleRefinementAlgorithm cycle_refinement_algorithm;

    int kaba_internal_no_aug_steps_aug;

    unsigned kaba_packing_iterations;

    bool kaba_flip_packings;

    MLSRule kaba_lsearch_p; // more localized search pseudo directed

    bool kaffpa_perfectly_balanced_refinement;

    unsigned kaba_unsucc_iterations;


    //=======================================
    //============PAR_PSEUDOMH / MH =========
    //=======================================
    double time_limit;

    double epsilon;

    unsigned no_unsuc_reps;

    unsigned local_partitioning_repetitions;

    bool mh_plain_repetitions;

    bool mh_easy_construction;

    bool mh_enable_gal_combine;

    bool mh_no_mh;

    bool mh_print_log;

    int mh_flip_coin;

    int mh_initial_population_fraction;

    bool mh_disable_cross_combine;

    bool mh_cross_combine_original_k;

    bool mh_disable_nc_combine;

    bool mh_disable_combine;

    bool mh_enable_quickstart;

    bool mh_disable_diversify_islands;

    bool mh_diversify;

    bool mh_diversify_best;

    bool mh_enable_tournament_selection;

    bool mh_optimize_communication_volume;

    unsigned mh_num_ncs_to_compute;

    unsigned mh_pool_size;

    bool combine; // in this case the second index is filled and edges between both partitions are not contracted

    unsigned initial_partition_optimize_fm_limits;

    unsigned initial_partition_optimize_multitry_fm_alpha;

    unsigned initial_partition_optimize_multitry_rounds;

    unsigned walshaw_mh_repetitions;

    unsigned scaleing_factor;

    bool scale_back;

    bool suppress_partitioner_output;

    unsigned maxT;

    unsigned maxIter;
    //=======================================
    //===============BUFFOON=================
    //=======================================
    bool disable_hard_rebalance;

    bool buffoon;

    bool kabapE;

    bool mh_penalty_for_unconnected;
    //=======================================
    //===============MISC====================
    //=======================================
    std::string input_partition;

    int seed;

    bool fast;

    bool eco;

    bool strong;

    bool kaffpaE;

    bool balance_edges;

    // number of blocks the graph should be partitioned in
    PartitionID k;

    bool compute_vertex_separator;

    bool only_first_level;

    bool use_balance_singletons;

    int amg_iterations;

    std::string graph_filename;

    std::string filename_output;

    bool kaffpa_perfectly_balance;

    bool mode_node_separators;

    //=======================================
    //===========SNW PARTITIONING============
    //=======================================
    NodeOrderingType node_ordering;

    int cluster_coarsening_factor;

    bool ensemble_clusterings;

    int label_iterations;

    int label_iterations_refinement;

    int number_of_clusterings;

    bool label_propagation_refinement;

    double balance_factor;

    bool cluster_coarsening_during_ip;

    bool set_upperbound;

    int repetitions;

    //=======================================
    //===========NODE SEPARATOR==============
    //=======================================
    int max_flow_improv_steps;

    int max_initial_ns_tries;

    double region_factor_node_separators;

    bool sep_flows_disabled;

    bool sep_fm_disabled;

    bool sep_loc_fm_disabled;

    int sep_loc_fm_no_snodes;

    bool sep_greedy_disabled;

    int sep_fm_unsucc_steps;

    int sep_loc_fm_unsucc_steps;

    int sep_num_fm_reps;

    int sep_num_loc_fm_reps;

    int sep_num_vert_stop;

    bool sep_full_boundary_ip;

    bool faster_ns;

    EdgeRating sep_edge_rating_during_ip;

    //=======================================
    //=========LABEL PROPAGATION=============
    //=======================================
    NodeWeight cluster_upperbound;

    //=======================================
    //=========INITIAL PARTITIONING==========
    //=======================================

    // variables controling the size of the blocks during
    // multilevel recursive bisection
    // (for the case where k is not a power of 2)
    std::vector<int> target_weights;

    bool initial_bipartitioning;

    int grow_target;

    //=======================================
    //===============QAP=====================
    //=======================================

    int communication_neighborhood_dist;

    LsNeighborhoodType ls_neighborhood;

    ConstructionAlgorithm construction_algorithm;

    DistanceConstructionAlgorithm distance_construction_algorithm;

    std::vector<int> group_sizes;

    std::vector<int> distances;

    int search_space_s;

    PreConfigMapping preconfiguration_mapping;

    int max_recursion_levels_construction;

    bool enable_mapping;

    //=======================================
    //===============Shared Mem OMP==========
    //=======================================
    bool enable_omp;

    //=======================================
    //=============CLUSTER COARSENING========
    //=======================================
    bool bcc_enable;
    bool bcc_default_clustering;
    bool bcc_shallow_clustering;
    bool bcc_shallow_no_lp_clustering;
    int bcc_time_limit;
    bool bcc_full_cluster_contraction;
    int bcc_combine;

    bool bcc_verify;
    BCCMode bcc_mode;
    VieClusMode bcc_vieclus_mode;
    BCCCombineMode bcc_combine_mode;
    bool bcc_continue_coarsening;
    bool bcc_reuse_clustering;

    void LogDump(FILE *out) const {
    }

    void disable_bcc() {
        bcc_mode = BCC_NO_CLUSTERING;
        bcc_verify = false;
        bcc_continue_coarsening = false;
        combine = false;
        bcc_reuse_clustering = false;
    }

    friend std::ostream &operator<<(std::ostream &os, const PartitionConfig &config) {
        os << "{edge_rating_tiebreaking=" << config.edge_rating_tiebreaking
           << ", edge_rating=" << edge_rating_to_string(config.edge_rating)
           << ", permutation_quality=" << permutation_quality_to_string(config.permutation_quality)
           << ", matching_type=" << matching_type_to_string(config.matching_type)
           << ", match_islands=" << config.match_islands
           << ", first_level_random_matching=" << config.first_level_random_matching
           << ", rate_first_level_inner_outer=" << config.rate_first_level_inner_outer
           << ", max_vertex_weight=" << config.max_vertex_weight
           << ", largest_graph_weight=" << config.largest_graph_weight
           << ", work_load=" << config.work_load
           << ", aggressive_random_levels=" << config.aggressive_random_levels
           << ", disable_max_vertex_weight_constraint=" << config.disable_max_vertex_weight_constraint
           << ", initial_partitioning_repetitions=" << config.initial_partitioning_repetitions
           << ", minipreps=" << config.minipreps
           << ", refined_bubbling=" << config.refined_bubbling
           << ", initial_partitioning_type=" << initial_partitioning_type_to_string(config.initial_partitioning_type)
           << ", initial_partition_optimize=" << config.initial_partition_optimize
           << ", bipartition_algorithm=" << bipartition_algorithm_to_string(config.bipartition_algorithm)
           << ", initial_partitioning=" << config.initial_partitioning
           << ", bipartition_tries=" << config.bipartition_tries
           << ", bipartition_post_fm_limits=" << config.bipartition_post_fm_limits
           << ", bipartition_post_ml_limits=" << config.bipartition_post_ml_limits
           << ", corner_refinement_enabled=" << config.corner_refinement_enabled
           << ", use_bucket_queues=" << config.use_bucket_queues
           << ", refinement_type=" << refinement_type_to_string(config.refinement_type)
           << ", permutation_during_refinement=" << permutation_quality_to_string(config.permutation_during_refinement)
           << ", imbalance=" << config.imbalance
           << ", bubbling_iterations=" << config.bubbling_iterations
           << ", kway_rounds=" << config.kway_rounds
           << ", quotient_graph_refinement_disabled=" << config.quotient_graph_refinement_disabled
           << ", kway_stop_rule=" << kway_stop_rule_to_string(config.kway_stop_rule)
           << ", kway_adaptive_limits_alpha=" << config.kway_adaptive_limits_alpha
           << ", kway_adaptive_limits_beta=" << config.kway_adaptive_limits_beta
           << ", max_flow_iterations=" << config.max_flow_iterations
           << ", local_multitry_rounds=" << config.local_multitry_rounds
           << ", local_multitry_fm_alpha=" << config.local_multitry_fm_alpha
           << ", graph_allready_partitioned=" << config.graph_allready_partitioned
           << ", fm_search_limit=" << config.fm_search_limit
           << ", kway_fm_search_limit=" << config.kway_fm_search_limit
           << ", upper_bound_partition=" << config.upper_bound_partition
           << ", bank_account_factor=" << config.bank_account_factor
           << ", refinement_scheduling_algorithm=" << refinement_scheduling_algorithm_to_string(config.refinement_scheduling_algorithm)
           << ", most_balanced_minimum_cuts=" << config.most_balanced_minimum_cuts
           << ", most_balanced_minimum_cuts_node_sep=" << config.most_balanced_minimum_cuts_node_sep
           << ", toposort_iterations=" << config.toposort_iterations
           << ", softrebalance=" << config.softrebalance
           << ", rebalance=" << config.rebalance
           << ", flow_region_factor=" << config.flow_region_factor
           << ", gpa_grow_paths_between_blocks=" << config.gpa_grow_paths_between_blocks
           << ", global_cycle_iterations=" << config.global_cycle_iterations
           << ", use_wcycles=" << config.use_wcycles
           << ", use_fullmultigrid=" << config.use_fullmultigrid
           << ", level_split=" << config.level_split
           << ", no_new_initial_partitioning=" << config.no_new_initial_partitioning
           << ", omit_given_partitioning=" << config.omit_given_partitioning
           << ", stop_rule=" << stop_rule_to_string(config.stop_rule)
           << ", num_vert_stop_factor=" << config.num_vert_stop_factor
           << ", no_change_convergence=" << config.no_change_convergence
           << ", remove_negative_cycles=" << config.remove_negative_cycles
           << ", kaba_include_removal_of_paths=" << config.kaba_include_removal_of_paths
           << ", kaba_enable_zero_weight_cycles=" << config.kaba_enable_zero_weight_cycles
           << ", kabaE_internal_bal=" << config.kabaE_internal_bal
           << ", cycle_refinement_algorithm=" << cycle_refinement_algorithm_to_string(config.cycle_refinement_algorithm)
           << ", kaba_internal_no_aug_steps_aug=" << config.kaba_internal_no_aug_steps_aug
           << ", kaba_packing_iterations=" << config.kaba_packing_iterations
           << ", kaba_flip_packings=" << config.kaba_flip_packings
           << ", kaba_lsearch_p=" << mls_rule_to_string(config.kaba_lsearch_p)
           << ", kaffpa_perfectly_balanced_refinement=" << config.kaffpa_perfectly_balanced_refinement
           << ", kaba_unsucc_iterations=" << config.kaba_unsucc_iterations
           << ", time_limit=" << config.time_limit
           << ", epsilon=" << config.epsilon
           << ", no_unsuc_reps=" << config.no_unsuc_reps
           << ", local_partitioning_repetitions=" << config.local_partitioning_repetitions
           << ", mh_plain_repetitions=" << config.mh_plain_repetitions
           << ", mh_easy_construction=" << config.mh_easy_construction
           << ", mh_enable_gal_combine=" << config.mh_enable_gal_combine
           << ", mh_no_mh=" << config.mh_no_mh
           << ", mh_print_log=" << config.mh_print_log
           << ", mh_flip_coin=" << config.mh_flip_coin
           << ", mh_initial_population_fraction=" << config.mh_initial_population_fraction
           << ", mh_disable_cross_combine=" << config.mh_disable_cross_combine
           << ", mh_cross_combine_original_k=" << config.mh_cross_combine_original_k
           << ", mh_disable_nc_combine=" << config.mh_disable_nc_combine
           << ", mh_disable_combine=" << config.mh_disable_combine
           << ", mh_enable_quickstart=" << config.mh_enable_quickstart
           << ", mh_disable_diversify_islands=" << config.mh_disable_diversify_islands
           << ", mh_diversify=" << config.mh_diversify
           << ", mh_diversify_best=" << config.mh_diversify_best
           << ", mh_enable_tournament_selection=" << config.mh_enable_tournament_selection
           << ", mh_optimize_communication_volume=" << config.mh_optimize_communication_volume
           << ", mh_num_ncs_to_compute=" << config.mh_num_ncs_to_compute
           << ", mh_pool_size=" << config.mh_pool_size
           << ", combine=" << config.combine
           << ", initial_partition_optimize_fm_limits=" << config.initial_partition_optimize_fm_limits
           << ", initial_partition_optimize_multitry_fm_alpha=" << config.initial_partition_optimize_multitry_fm_alpha
           << ", initial_partition_optimize_multitry_rounds=" << config.initial_partition_optimize_multitry_rounds
           << ", walshaw_mh_repetitions=" << config.walshaw_mh_repetitions
           << ", scaleing_factor=" << config.scaleing_factor
           << ", scale_back=" << config.scale_back
           << ", suppress_partitioner_output=" << config.suppress_partitioner_output
           << ", maxT=" << config.maxT
           << ", maxIter=" << config.maxIter
           << ", disable_hard_rebalance=" << config.disable_hard_rebalance
           << ", buffoon=" << config.buffoon
           << ", kabapE=" << config.kabapE
           << ", mh_penalty_for_unconnected=" << config.mh_penalty_for_unconnected
           << ", input_partition=" << config.input_partition
           << ", seed=" << config.seed
           << ", fast=" << config.fast
           << ", eco=" << config.eco
           << ", strong=" << config.strong
           << ", kaffpaE=" << config.kaffpaE
           << ", balance_edges=" << config.balance_edges
           << ", k=" << config.k
           << ", compute_vertex_separator=" << config.compute_vertex_separator
           << ", only_first_level=" << config.only_first_level
           << ", use_balance_singletons=" << config.use_balance_singletons
           << ", amg_iterations=" << config.amg_iterations
           << ", graph_filename=" << config.graph_filename
           << ", filename_output=" << config.filename_output
           << ", kaffpa_perfectly_balance=" << config.kaffpa_perfectly_balance
           << ", mode_node_separators=" << config.mode_node_separators
           << ", node_ordering=" << node_ordering_type_to_string(config.node_ordering)
           << ", cluster_coarsening_factor=" << config.cluster_coarsening_factor
           << ", ensemble_clusterings=" << config.ensemble_clusterings
           << ", label_iterations=" << config.label_iterations
           << ", label_iterations_refinement=" << config.label_iterations_refinement
           << ", number_of_clusterings=" << config.number_of_clusterings
           << ", label_propagation_refinement=" << config.label_propagation_refinement
           << ", balance_factor=" << config.balance_factor
           << ", cluster_coarsening_during_ip=" << config.cluster_coarsening_during_ip
           << ", set_upperbound=" << config.set_upperbound
           << ", repetitions=" << config.repetitions
           << ", max_flow_improv_steps=" << config.max_flow_improv_steps
           << ", max_initial_ns_tries=" << config.max_initial_ns_tries
           << ", region_factor_node_separators=" << config.region_factor_node_separators
           << ", sep_flows_disabled=" << config.sep_flows_disabled
           << ", sep_fm_disabled=" << config.sep_fm_disabled
           << ", sep_loc_fm_disabled=" << config.sep_loc_fm_disabled
           << ", sep_loc_fm_no_snodes=" << config.sep_loc_fm_no_snodes
           << ", sep_greedy_disabled=" << config.sep_greedy_disabled
           << ", sep_fm_unsucc_steps=" << config.sep_fm_unsucc_steps
           << ", sep_loc_fm_unsucc_steps=" << config.sep_loc_fm_unsucc_steps
           << ", sep_num_fm_reps=" << config.sep_num_fm_reps
           << ", sep_num_loc_fm_reps=" << config.sep_num_loc_fm_reps
           << ", sep_num_vert_stop=" << config.sep_num_vert_stop
           << ", sep_full_boundary_ip=" << config.sep_full_boundary_ip
           << ", faster_ns=" << config.faster_ns
           << ", sep_edge_rating_during_ip=" << edge_rating_to_string(config.sep_edge_rating_during_ip)
           << ", cluster_upperbound=" << config.cluster_upperbound
           << ", initial_bipartitioning=" << config.initial_bipartitioning
           << ", grow_target=" << config.grow_target
           << ", communication_neighborhood_dist=" << config.communication_neighborhood_dist
           << ", ls_neighborhood=" << ls_neighborhood_type_to_string(config.ls_neighborhood)
           << ", construction_algorithm=" << construction_algorithm_to_string(config.construction_algorithm)
           << ", distance_construction_algorithm=" << distance_construction_algorithm_to_string(config.distance_construction_algorithm)
           << ", search_space_s=" << config.search_space_s
           << ", preconfiguration_mapping=" << preconfig_mapping_to_string(config.preconfiguration_mapping)
           << ", max_recursion_levels_construction=" << config.max_recursion_levels_construction
           << ", enable_mapping=" << config.enable_mapping
           << ", enable_omp=" << config.enable_omp
           << ", bcc_enable=" << config.bcc_enable
           << ", bcc_default_clustering=" << config.bcc_default_clustering
           << ", bcc_shallow_clustering=" << config.bcc_shallow_clustering
           << ", bcc_shallow_no_lp_clustering=" << config.bcc_shallow_no_lp_clustering
           << ", bcc_time_limit=" << config.bcc_time_limit
           << ", bcc_full_cluster_contraction=" << config.bcc_full_cluster_contraction
           << ", bcc_combine=" << config.bcc_combine
           << ", bcc_verify=" << config.bcc_verify
           << ", bcc_mode=" << bcc_mode_to_string(config.bcc_mode)
           << ", bcc_vieclus_mode=" << vieclus_mode_to_string(config.bcc_vieclus_mode)
           << ", bcc_combine_mode=" << bcc_combine_mode_to_string(config.bcc_combine_mode)
           << ", bcc_continue_coarsening=" << config.bcc_continue_coarsening
           << ", bcc_reuse_clustering=" << config.bcc_reuse_clustering
           << "}";
        return os;
    }
};

#endif /* end of include guard: PARTITION_CONFIG_DI1ES4T0 */
