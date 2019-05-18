/******************************************************************************
 * definitions.h 
 *
 * Source of KaHIP -- Karlsruhe High Quality Partitioning.
 * Christian Schulz <christian.schulz.phone@gmail.com>
 *****************************************************************************/

#ifndef DEFINITIONS_H_CHR
#define DEFINITIONS_H_CHR

#include <limits>
#include <queue>
#include <vector>

#include "limits.h"
#include "macros_assertions.h"
#include "stdio.h"


// allows us to disable most of the output during partitioning
#ifdef KAFFPAOUTPUT
        #define PRINT(x) x
#else
        #define PRINT(x) do {} while (false);
#endif

/**********************************************
 * Constants
 * ********************************************/
//Types needed for the graph ds
typedef unsigned int 	NodeID;
typedef double 		EdgeRatingType;
typedef unsigned int 	PathID;
typedef unsigned int 	PartitionID;
typedef unsigned int 	NodeWeight;
typedef int 		EdgeWeight;
typedef EdgeWeight 	Gain;
#ifdef MODE64BITEDGES
typedef uint64_t 	EdgeID;
#else
typedef unsigned int 	EdgeID;
#endif
typedef int 		Color;
typedef unsigned int 	Count;
typedef std::vector<NodeID> boundary_starting_nodes;
typedef long FlowType;

const EdgeID UNDEFINED_EDGE            = std::numeric_limits<EdgeID>::max();
const NodeID UNDEFINED_NODE            = std::numeric_limits<NodeID>::max();
const NodeID UNASSIGNED                = std::numeric_limits<NodeID>::max();
const NodeID ASSIGNED                  = std::numeric_limits<NodeID>::max()-1;
const PartitionID INVALID_PARTITION    = std::numeric_limits<PartitionID>::max();
const PartitionID BOUNDARY_STRIPE_NODE = std::numeric_limits<PartitionID>::max();
const int NOTINQUEUE 		       = std::numeric_limits<int>::max();
const int ROOT 			       = 0;

//for the gpa algorithm
struct edge_source_pair {
        EdgeID e;
        NodeID source;
};

struct source_target_pair {
        NodeID source;
        NodeID target;
};

//matching array has size (no_of_nodes), so for entry in this table we get the matched neighbor
typedef std::vector<NodeID> CoarseMapping;
typedef std::vector<NodeID> Matching;
typedef std::vector<NodeID> NodePermutationMap;

typedef double ImbalanceType;
//Coarsening
typedef enum {
        EXPANSIONSTAR,
        EXPANSIONSTAR2,
 	WEIGHT,
 	REALWEIGHT,
	PSEUDOGEOM,
	EXPANSIONSTAR2ALGDIST,
        SEPARATOR_MULTX,
        SEPARATOR_ADDX,
        SEPARATOR_MAX,
        SEPARATOR_LOG,
        SEPARATOR_R1,
        SEPARATOR_R2,
        SEPARATOR_R3,
        SEPARATOR_R4,
        SEPARATOR_R5,
        SEPARATOR_R6,
        SEPARATOR_R7,
        SEPARATOR_R8
} EdgeRating;

inline std::string edge_rating_to_string(EdgeRating edge_rating) {
    switch (edge_rating) {
        case EXPANSIONSTAR: return "EXPANSIONSTAR";
        case EXPANSIONSTAR2: return "EXPANSIONSTAR2";
        case WEIGHT: return "WEIGHT";
        case REALWEIGHT: return "REALWEIGHT";
        case PSEUDOGEOM: return "PSEUDOGEOM";
        case EXPANSIONSTAR2ALGDIST: return "EXPANSIONSTAR2ALGDIST";
        case SEPARATOR_MULTX: return "SEPARATOR_MULTX";
        case SEPARATOR_ADDX: return "SEPARATOR_ADDX";
        case SEPARATOR_MAX: return "SEPARATOR_MAX";
        case SEPARATOR_LOG: return "SEPARATOR_LOG";
        case SEPARATOR_R1: return "SEPARATOR_R1";
        case SEPARATOR_R2: return "SEPARATOR_R2";
        case SEPARATOR_R3: return "SEPARATOR_R3";
        case SEPARATOR_R4: return "SEPARATOR_R4";
        case SEPARATOR_R5: return "SEPARATOR_R5";
        case SEPARATOR_R6: return "SEPARATOR_R6";
        case SEPARATOR_R7: return "SEPARATOR_R7";
        case SEPARATOR_R8: return "SEPARATOR_R8";
        default: return std::to_string(edge_rating);
    }
}

typedef enum {
        PERMUTATION_QUALITY_NONE,
	PERMUTATION_QUALITY_FAST,
	PERMUTATION_QUALITY_GOOD
} PermutationQuality;

inline std::string permutation_quality_to_string(PermutationQuality permutation_quality) {
    switch (permutation_quality) {
        case PERMUTATION_QUALITY_NONE: return "PERMUTATION_QUALITY_NONE";
        case PERMUTATION_QUALITY_FAST: return "PERMUTATION_QUALITY_FAST";
        case PERMUTATION_QUALITY_GOOD: return "PERMUTATION_QUALITY_GOOD";
        default: return std::to_string(permutation_quality);
    }
}

typedef enum {
        MATCHING_RANDOM,
	MATCHING_GPA,
	MATCHING_RANDOM_GPA,
        CLUSTER_COARSENING
} MatchingType;

inline std::string matching_type_to_string(MatchingType matching_type) {
    switch (matching_type) {
        case MATCHING_RANDOM: return "MATCHING_RANDOM";
        case MATCHING_GPA: return "MATCHING_GPA";
        case MATCHING_RANDOM_GPA: return "MATCHING_RANDOM_GPA";
        case CLUSTER_COARSENING: return "CLUSTER_COARSENING";
        default: return std::to_string(matching_type);
    }
}

typedef enum {
	INITIAL_PARTITIONING_RECPARTITION,
	INITIAL_PARTITIONING_BIPARTITION
} InitialPartitioningType;

inline std::string initial_partitioning_type_to_string(InitialPartitioningType initial_partitioning_type) {
    switch (initial_partitioning_type) {
        case INITIAL_PARTITIONING_RECPARTITION: return "INITIAL_PARTITIONING_RECPARTITION";
        case INITIAL_PARTITIONING_BIPARTITION: return "INITIAL_PARTITIONING_BIPARTITION";
        default: return std::to_string(initial_partitioning_type);
    }
}

typedef enum {
        REFINEMENT_SCHEDULING_FAST,
	REFINEMENT_SCHEDULING_ACTIVE_BLOCKS,
	REFINEMENT_SCHEDULING_ACTIVE_BLOCKS_REF_KWAY
} RefinementSchedulingAlgorithm;

inline std::string refinement_scheduling_algorithm_to_string(RefinementSchedulingAlgorithm refinement_scheduling_algorithm) {
    switch (refinement_scheduling_algorithm) {
        case REFINEMENT_SCHEDULING_FAST: return "REFINEMENT_SCHEDULING_FAST";
        case REFINEMENT_SCHEDULING_ACTIVE_BLOCKS: return "REFINEMENT_SCHEDULING_ACTIVE_BLOCKS";
        case REFINEMENT_SCHEDULING_ACTIVE_BLOCKS_REF_KWAY: return "REFINEMENT_SCHEDULING_ACTIVE_BLOCKS_REF_KWAY";
        default: return std::to_string(refinement_scheduling_algorithm);
    }
}

typedef enum {
        REFINEMENT_TYPE_FM,
	REFINEMENT_TYPE_FM_FLOW,
	REFINEMENT_TYPE_FLOW
} RefinementType;

inline std::string refinement_type_to_string(RefinementType refinement_type) {
    switch (refinement_type) {
        case REFINEMENT_TYPE_FM: return "REFINEMENT_TYPE_FM";
        case REFINEMENT_TYPE_FM_FLOW: return "REFINEMENT_TYPE_FM_FLOW";
        case REFINEMENT_TYPE_FLOW: return "REFINEMENT_TYPE_FLOW";
        default: return std::to_string(refinement_type);
    }
}

typedef enum {
        STOP_RULE_SIMPLE,
	STOP_RULE_MULTIPLE_K,
	STOP_RULE_STRONG
} StopRule;

inline std::string stop_rule_to_string(StopRule stop_rule) {
    switch (stop_rule) {
        case STOP_RULE_SIMPLE: return "STOP_RULE_SIMPLE";
        case STOP_RULE_MULTIPLE_K: return "STOP_RULE_MULTIPLE_K";
        case STOP_RULE_STRONG: return "STOP_RULE_STRONG";
        default: return std::to_string(stop_rule);
    }
}

typedef enum {
        BIPARTITION_BFS,
	BIPARTITION_FM
} BipartitionAlgorithm ;

inline std::string bipartition_algorithm_to_string(BipartitionAlgorithm bipartition_algorithm) {
    switch (bipartition_algorithm) {
        case BIPARTITION_BFS: return "BIPARTITION_BFS";
        case BIPARTITION_FM: return "BIPARTITION_FM";
        default: return std::to_string(bipartition_algorithm);
    }
}

typedef enum {
        KWAY_SIMPLE_STOP_RULE,
	KWAY_ADAPTIVE_STOP_RULE
} KWayStopRule;

inline std::string kway_stop_rule_to_string(KWayStopRule kway_stop_rule) {
    switch (kway_stop_rule) {
        case KWAY_SIMPLE_STOP_RULE: return "KWAY_SIMPLE_STOP_RULE";
        case KWAY_ADAPTIVE_STOP_RULE: return "KWAY_ADAPTIVE_STOP_RULE";
        default: return std::to_string(kway_stop_rule);
    }
}

typedef enum {
        COIN_RNDTIE,
	COIN_DIFFTIE,
	NOCOIN_RNDTIE,
	NOCOIN_DIFFTIE
} MLSRule;

inline std::string mls_rule_to_string(MLSRule mls_rule) {
    switch (mls_rule) {
        case COIN_RNDTIE: return "COIN_RNDTIE";
        case COIN_DIFFTIE: return "COIN_DIFFTIE";
        case NOCOIN_RNDTIE: return "NOCOIN_RNDTIE";
        case NOCOIN_DIFFTIE: return "NOCOIN_DIFFTIE";
        default: return std::to_string(mls_rule);
    }
}

typedef enum {
        CYCLE_REFINEMENT_ALGORITHM_PLAYFIELD,
        CYCLE_REFINEMENT_ALGORITHM_ULTRA_MODEL,
	CYCLE_REFINEMENT_ALGORITHM_ULTRA_MODEL_PLUS
} CycleRefinementAlgorithm;

inline std::string cycle_refinement_algorithm_to_string(CycleRefinementAlgorithm cycle_refinement_algorithm) {
    switch (cycle_refinement_algorithm) {
        case CYCLE_REFINEMENT_ALGORITHM_PLAYFIELD: return "CYCLE_REFINEMENT_ALGORITHM_PLAYFIELD";
        case CYCLE_REFINEMENT_ALGORITHM_ULTRA_MODEL: return "CYCLE_REFINEMENT_ALGORITHM_ULTRA_MODEL";
        case CYCLE_REFINEMENT_ALGORITHM_ULTRA_MODEL_PLUS: return "CYCLE_REFINEMENT_ALGORITHM_ULTRA_MODEL_PLUS";
        default: return std::to_string(cycle_refinement_algorithm);
    }
}

typedef enum {
        RANDOM_NODEORDERING,
        DEGREE_NODEORDERING
} NodeOrderingType;

inline std::string node_ordering_type_to_string(NodeOrderingType node_ordering_type) {
    switch (node_ordering_type) {
        case RANDOM_NODEORDERING: return "RANDOM_NODEORDERING";
        case DEGREE_NODEORDERING: return "DEGREE_NODEORDERING";
        default: return std::to_string(node_ordering_type);
    }
}

typedef enum {
        NSQUARE,
        NSQUAREPRUNED,
        COMMUNICATIONGRAPH
} LsNeighborhoodType;

inline std::string ls_neighborhood_type_to_string(LsNeighborhoodType ls_neighborhood_type) {
    switch (ls_neighborhood_type) {
        case NSQUARE: return "NSQUARE";
        case NSQUAREPRUNED: return "NSQUAREPRUNED";
        case COMMUNICATIONGRAPH: return "COMMUNICATIONGRAPH";
        default: return std::to_string(ls_neighborhood_type);
    }
}

typedef enum {
        MAP_CONST_RANDOM,
        MAP_CONST_IDENTITY,
        MAP_CONST_OLDGROWING,
        MAP_CONST_OLDGROWING_FASTER,
        MAP_CONST_OLDGROWING_MATRIX,
        MAP_CONST_FASTHIERARCHY_BOTTOMUP,
        MAP_CONST_FASTHIERARCHY_TOPDOWN
} ConstructionAlgorithm;

inline std::string construction_algorithm_to_string(ConstructionAlgorithm construction_algorithm) {
    switch (construction_algorithm) {
        case MAP_CONST_RANDOM: return "MAP_CONST_RANDOM";
        case MAP_CONST_IDENTITY: return "MAP_CONST_IDENTITY";
        case MAP_CONST_OLDGROWING: return "MAP_CONST_OLDGROWING";
        case MAP_CONST_OLDGROWING_FASTER: return "MAP_CONST_OLDGROWING_FASTER";
        case MAP_CONST_OLDGROWING_MATRIX: return "MAP_CONST_OLDGROWING_MATRIX";
        case MAP_CONST_FASTHIERARCHY_BOTTOMUP: return "MAP_CONST_FASTHIERARCHY_BOTTOMUP";
        case MAP_CONST_FASTHIERARCHY_TOPDOWN: return "MAP_CONST_FASTHIERARCHY_TOPDOWN";
        default: return std::to_string(construction_algorithm);
    }
}

typedef enum {
        DIST_CONST_RANDOM,
        DIST_CONST_IDENTITY,
        DIST_CONST_HIERARCHY,
        DIST_CONST_HIERARCHY_ONLINE
} DistanceConstructionAlgorithm;

inline std::string distance_construction_algorithm_to_string(DistanceConstructionAlgorithm distance_construction_algorithm) {
    switch (distance_construction_algorithm) {
        case DIST_CONST_RANDOM: return "DIST_CONST_RANDOM";
        case DIST_CONST_IDENTITY: return "DIST_CONST_IDENTITY";
        case DIST_CONST_HIERARCHY: return "DIST_CONST_HIERARCHY";
        case DIST_CONST_HIERARCHY_ONLINE: return "DIST_CONST_HIERARCHY_ONLINE";
        default: return std::to_string(distance_construction_algorithm);
    }
}

typedef enum {
        PRE_CONFIG_MAPPING_FAST,
        PRE_CONFIG_MAPPING_ECO,
        PRE_CONFIG_MAPPING_STRONG
} PreConfigMapping;

inline std::string preconfig_mapping_to_string(PreConfigMapping preconfig_mapping) {
    switch (preconfig_mapping) {
        case PRE_CONFIG_MAPPING_FAST: return "PRE_CONFIG_MAPPING_FAST";
        case PRE_CONFIG_MAPPING_ECO: return "PRE_CONFIG_MAPPING_ECO";
        case PRE_CONFIG_MAPPING_STRONG: return "PRE_CONFIG_MAPPING_STRONG";
        default: return std::to_string(preconfig_mapping);
    }
}

typedef enum {
        BCC_NO_CLUSTERING,
        BCC_TOPLEVEL,
        BCC_MULTILEVEL,
} BCCMode;

inline std::string bcc_mode_to_string(BCCMode bcc_mode) {
    switch (bcc_mode) {
        case BCC_NO_CLUSTERING: return "BCC_NO_CLUSTERING";
        case BCC_TOPLEVEL: return "BCC_TOPLEVEL";
        case BCC_MULTILEVEL: return "BCC_MULTILEVEL";
        default: return std::to_string(bcc_mode);
    }
}

typedef enum {
        VIECLUS_NORMAL,
        VIECLUS_SHALLOW,
        VIECLUS_SHALLOW_NO_LP,
        VIECLUS_SHALLOW_NO_LP_SIZE_CONSTRAINED,
} VieClusMode;

inline std::string vieclus_mode_to_string(VieClusMode vieclus_mode) {
    switch (vieclus_mode) {
        case VIECLUS_NORMAL: return "VIECLUS_NORMAL";
        case VIECLUS_SHALLOW: return "VIECLUS_SHALLOW";
        case VIECLUS_SHALLOW_NO_LP: return "VIECLUS_SHALLOW_NO_LP";
        case VIECLUS_SHALLOW_NO_LP_SIZE_CONSTRAINED: return "VIECLUS_SHALLOW_NO_LP_SIZE_CONSTRAINED";
        default: return std::to_string(vieclus_mode);
    }
}

typedef enum {
        BCC_FIRST_PARTITION_INDEX,
        BCC_SECOND_PARTITION_INDEX
} BCCCombineMode;

inline std::string bcc_combine_mode_to_string(BCCCombineMode bcc_combine_mode) {
    switch (bcc_combine_mode) {
        case BCC_FIRST_PARTITION_INDEX: return "BCC_FIRST_PARTITION_INDEX";
        case BCC_SECOND_PARTITION_INDEX: return "BCC_SECOND_PARTITION_INDEX";
        default: return std::to_string(bcc_combine_mode);
    }
}

#endif

