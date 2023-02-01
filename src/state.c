#include "state.h"
#include <assert.h>

#define _CRT_SECURE_NO_WARNINGS

void init_state(sys_state_t *state)
{
    init_flight_system(&state->path_for_each_city, state->adj, true);
    rb_malloc(&state->reservation_information);
    state->rid = 0;
}

void load_state(sys_state_t *state)
{
    init_flight_system(&state->path_for_each_city, state->adj, false);
    rb_malloc(&state->reservation_information);
    state->rid = 0;
}


static int count_reservations_inorder(rbtree_t *T, rbnode_t *cur, int* cur_cnt)
{
    if (cur != T->nil && T->root!=NULL)
    {
        count_reservations_inorder(T, cur->left, cur_cnt);
        *cur_cnt += 1;
        count_reservations_inorder(T, cur->right, cur_cnt);
    }
    return 0;
}

int count_reservations(rbtree_t * T){
    int ret = 0;
    count_reservations_inorder(T, T->root, &ret);
    return ret;
}

void print_paths_inorder(rbtree_t *T, rbnode_t *cur)
{
    path_t *p;
    mhd_t t;
    if (cur != T->nil && T->root!=NULL)
    {
        print_paths_inorder(T, cur->left);
        printf("RID(%d): ", cur->key);
        p = cur->data;
        t = get_mhd(p->dtime[0]);
        printf("%s, %d, %c, %c, ", p->name, t.d, p->src + 'a', p->dst + 'a');
        print_path((path_t *)cur->data);
        printf("\n");
        print_paths_inorder(T, cur->right);
    }
}

void print_reservation(rbtree_t *T)
{
    printf("\n\n >> CURRENT RESERVATIONS\n\n");
    if (T->root == T->nil)
    {
        printf("(void)\n\n");
        return;
    }

    printf(" >> RB-Tree Structure with RID\n\n");
    PRINT_BST(T);
    printf("\n >> Sorted Info with RID\n\n");
    print_paths_inorder(T, T->root);
    printf("\n >> number of reservations: %d\n", count_reservations(T));
    printf("\n");
}

void init_input(input_t *i)
{
    memset(i->name, 0x0, sizeof(i->name));
    i->src = '\0';
    i->day = -1;
    i->dst = '\0';
}

void init_path(path_t *p, input_t *i, bool is_search)
{
    memset(p->name, 0x0, sizeof(p->name));
    memset(p->path, 0x0, sizeof(p->path));
    if (!is_search)
    {
        strcpy(p->name, i->name);
    }
}

void print_location_of_city(graph_t *g, input_t *i)
{
    point_t p = g->v[i->src - 'a'].p;
    printf("output: \n >> %c", i->src);
    printf("(");
    print_point(p);
    printf(")\n\n");
}

void print_distance(graph_t *g, input_t *i)
{
    point_t p_src = g->v[i->src - 'a'].p;
    point_t p_dst = g->v[i->dst - 'a'].p;
    double d = get_dist(g, i->src - 'a', i->dst - 'a');
    printf("output: \n >> distance: %g\n", d);
    printf(" >> between %c(", i->src);
    print_point(p_src);
    printf(") and %c(", i->dst);
    print_point(p_dst);
    printf(")\n");
    printf(" >> time taken : ");
    print_tunit((tunit_t)(d / (500.0 / (60.0 / 5.0))));
    printf("\n\n");
}

void print_table_entry(graph_t *g, input_t *i)
{
    mhd_t mhd;
    mhd.d = i->day;
    mhd.h = i->hour;
    mhd.m = i->min;
    tunit_t tidx = get_tunit(mhd);
    city_t dst = g->v[i->src - 'a'].t.dsts[ceil_tunit(tidx)];
    printf("output: dst, hour:mimute, day\n >> ");
    printf("%c, ", dst + 'a');
    print_tunit(ceil_tunit(tidx));
    printf("\n\n");
}