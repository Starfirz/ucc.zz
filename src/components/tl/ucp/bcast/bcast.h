/**
 * Copyright (C) Mellanox Technologies Ltd. 2021.  ALL RIGHTS RESERVED.
 *
 * See file LICENSE for terms.
 */
#ifndef BCAST_H_
#define BCAST_H_
#include "../tl_ucp.h"
#include "../tl_ucp_coll.h"

ucc_status_t ucc_tl_ucp_bcast_init(ucc_tl_ucp_task_t *task);
ucc_status_t
ucc_tl_ucp_bcast_knomial_init(ucc_base_coll_args_t *coll_args,
                              ucc_base_team_t *team, ucc_coll_task_t **task_h);
ucc_status_t
ucc_tl_ucp_bcast_sag_knomial_init(ucc_base_coll_args_t *coll_args,
                              ucc_base_team_t *team, ucc_coll_task_t **task_h);

ucc_status_t ucc_tl_ucp_bcast_knomial_start(ucc_coll_task_t *task);
ucc_status_t ucc_tl_ucp_bcast_knomial_progress(ucc_coll_task_t *task);

#ifdef HAVE_DPU_OFFLOAD

typedef struct bcast_host_coll {
    ucs_list_link_t super;          /* op item */
    ucc_coll_task_t *coll_task;     /* collective task */
    int complete;                   /* completion flag */
    ucp_mem_h s_memh;               /* send memh */
    ucp_mem_h r_memh;               /* receive memh */
} bcast_host_coll_t;

/* active collectives running on the HOST */
ucs_list_link_t active_colls;

//algorithm ID
enum {
    UCC_TL_UCP_BCAST_ALG_KNOMIAL,
    UCC_TL_UCP_BCAST_ALG_SAG_KNOMIAL,
    UCC_TL_UCP_BCAST_ALG_OFFLOAD,
    UCC_TL_UCP_BCAST_ALG_LAST
};

extern ucc_base_coll_alg_info_t
    ucc_tl_ucp_bcast_algs[UCC_TL_UCP_BCAST_ALG_LAST + 1];

#define UCC_TL_UCP_BCAST_DEFAULT_ALG_SELECT_STR              \
    "bcast:0-32k:@0#bcast:32k-inf:@1"

ucc_status_t ucc_tl_ucp_bcast_offload_init(ucc_base_coll_args_t *coll_args,
                                                ucc_base_team_t      *team,
                                                ucc_coll_task_t     **task_h);
ucc_status_t ucc_tl_ucp_bcast_offload_start(ucc_coll_task_t *task);
ucc_status_t ucc_tl_ucp_bcast_offload_progress(ucc_coll_task_t *task);

static inline int ucc_tl_ucp_bcast_alg_from_str(const char *str)
{
    int i;

    for (i = 0; i < UCC_TL_UCP_BCAST_ALG_LAST; i++) {
        if (0 == strcasecmp(str, ucc_tl_ucp_bcast_algs[i].name)) {
            break;
        }
    }
    return i;
}

#endif // HAVE_DPU_OFFLOAD

#endif
