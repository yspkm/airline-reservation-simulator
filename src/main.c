#define _CRT_SECURE_NO_WARNINGS
#include "inputgen.h"
#include "state.h"

#include <stdio.h>

extern void print_table(table_t *, city_t);
int input_test(sys_state_t *state, int input_cnt);
void delete_test(sys_state_t *state, int del_cnt_max);

int main(int argc, char *argv[]) {
  sys_state_t state;
  path_t path_buf;
  rbtree_t *rptr = NULL;
  graph_t *gptr = NULL;
  input_t *iptr = NULL;
  path_t *optr = NULL;
  int cnt_reservatinos = 0;
  int input = -1, rid_del = -1;
  char buf[512] = {0};

  printf("start program\n");
  while (true) {
    printf("init random system (yes/no)?\n >> ");
    scanf("%s", buf);
    if (strcmp(buf, "yes") == 0) {
      printf("init system.. wait a moment\n");
      init_state(&state);
      printf("generate random input file (input.csv)\n");
      inputgen();
    } else if (strcmp(buf, "no") == 0) {
      printf("load system.. wait a moment\n");
      load_state(&state);
      break;
    } else
      printf("wrong input\n\n");
    printf("restart program\n");
  }

  printf("test ? (y/n): \n >> ");
  scanf("%s", path_buf.name);

  if (strcmp(path_buf.name, "y") == 0) {
    while (true) {
      printf("test size: \n >> ");
      scanf("%d", &input);
      if (1 <= input && input <= MAX_INPUT)
        break;
      printf("wrong input, (%d<=input&&input<=%d)\n", 1, MAX_INPUT);
    }
    printf("input test ? (y/n): \n >> ");
    scanf("%s", path_buf.name);
    if (strcmp(path_buf.name, "y") == 0) {
      int test_cnt = input_test(&state, input);
      printf("delete test ? (y/n): \n >> ");
      scanf("%s", path_buf.name);
      if (strcmp(path_buf.name, "y") == 0)
        delete_test(&state, test_cnt);
    }
  }
  while (true) {
    // for convinience
    rptr = &state.reservation_information;
    gptr = &state.path_for_each_city;
    iptr = &state.input_buffer[state.rid % MAX_INPUT];
    optr = &state.reservation_buffer[state.rid % MAX_INPUT];
    printf("1: input\n");
    printf("2: delete\n");
    printf("3: print_rbtree\n");
    printf("4: search path\n");
    printf("5: search location of city\n");
    printf("6: search schedule table entry\n");
    printf("7: search distacne of city\n");
    printf("8: print whole slot table of city\n");
    printf("9: exit\n");
    printf(" >> ");
    scanf("%d", &input);
    getchar();
    cnt_reservatinos = count_reservations(rptr);
    switch (input) {
    case INSERTTION:
      if (cnt_reservatinos >= MAX_RESERVATION) {
        printf("full of reservatoins: %d >= %d", cnt_reservatinos,
               MAX_RESERVATION);
        break;
      }
      printf("input: name, src, dst, day\n >> ");
      init_input(iptr);
      get_input(iptr);
      init_path(optr, iptr, false);
      if (UNFOUND ==
          find_path(gptr, iptr->src - 'a', iptr->dst - 'a', iptr->day, optr)) {
        printf("path not found\n");
        break;
      }
      printf("available path: \n >> ");
      print_path(optr);
      printf("\n");
      if (rb_insert_key(rptr, state.rid, (data_t)optr)) {
        printf("input success\n\n");
        state.rid++;
      }
      break;
    case DELETION:
      printf("delete rid\n >> ");
      scanf("%d", &rid_del);
      getchar();
      if (!rb_search(rptr, rid_del)) {
        printf("there isn't rid(%d)\n", rid_del);
        break;
      }
      RB_DELETE(rptr, rid_del);
      printf("\n");
      break;
    case PRINT_RBTREE:
      print_reservation(rptr);
      break;
    case SEARCH_PATH:
      printf("input: src, dst, day\n >> ");
      init_input(iptr);
      get_input_for_search(iptr);
      printf("\n");
      init_path(&path_buf, iptr, true);
      if (UNFOUND == find_path(gptr, iptr->src - 'a', iptr->dst - 'a',
                               iptr->day, &path_buf)) {
        printf("path not found\n");
        break;
      }
      print_path(&path_buf);
      printf("\n\n");
      break;
    case SEARCH_SCHEDULE_TABLE_ENTRY:
      printf("input: src, day, hour, min \n >> ");
      get_input_for_search_schedule_table_entry(iptr);
      print_table_entry(gptr, iptr);
      break;
    case SEARCH_LOCATION_OF_CITY:
      printf("input: city \n >> ");
      get_input_for_search_location_of_city(iptr);
      print_location_of_city(gptr, iptr);
      break;
    case SEARCH_DISTANCE:
      printf("input: src, dst \n >> ");
      get_input_for_search_distance(iptr);
      print_distance(gptr, iptr);
      break;
    case PRINT_SCHEDULE_TABLE_WHOLE:
      printf("input: city \n >> ");
      get_input_for_search_location_of_city(iptr);
      printf("out: \n >>\nSLOT TABLE OF CITY %c\n", iptr->src);
      print_table(&gptr->v->t, iptr->src - 'a');
      printf("\n");
      break;
    case EXIT_PROGRAM:
      printf("exit success\n");
      goto DONE;
      break;
    default:
      printf("input in [1-9], retry\n\n");
      break;
    }
  }
DONE:
  exit(EXIT_SUCCESS);
}

int input_test(sys_state_t *state, int input_cnt) {
  printf("================\n");
  printf("INPUT TEST START\n\n");
  rbtree_t *rptr = NULL;
  graph_t *gptr = NULL;
  input_t *iptr = NULL;
  path_t *optr = NULL;
  int input = -1;
  int input_idx;

  input_idx = 0;
  // from input.csv
  // which was generated by ./inputgen/inputgen.c
  get_test_inputs(&state->input_buffer[input_idx % MAX_INPUT], MAX_INPUT);
  input = INSERTTION;
  while (true) {
    if (state->rid >= input_cnt)
      break;

    // for convinience
    rptr = &state->reservation_information;
    gptr = &state->path_for_each_city;
    iptr = &state->input_buffer[input_idx++ % MAX_INPUT];
    optr = &state->reservation_buffer[state->rid % MAX_INPUT];

    switch (input) {
    case INSERTTION:
      if (UNFOUND ==
          find_path(gptr, iptr->src - 'a', iptr->dst - 'a', iptr->day, optr)) {
        printf("path not found\n");
        break;
      }
      printf("user name: %s\n", iptr->name);
      printf("available path: \n >> ");
      print_path(optr);
      printf("\n");
      if (rb_insert_key(rptr, state->rid, (data_t)optr)) {
        printf("input success\n\n");
        strcpy(optr->name, iptr->name);
        state->rid++;
      }
      goto PRINT;
      break;
    case PRINT_RBTREE:
    PRINT:
      print_reservation(rptr);
      break;
    }
  }
  printf("INPUT TEST END\n");
  printf("==============\n\n");
  return count_reservations(rptr);
}

void delete_test(sys_state_t *state, int del_cnt_max) {
  printf("=================\n");
  printf("DELETE TEST START\n\n");
  int input = -1, rid_del = -1;
  int del_cnt;

  rbtree_t *rptr = NULL;
  rptr = &state->reservation_information;

  del_cnt = 0;
  input = DELETION;
  srand((unsigned)time(NULL));
  goto PRINT;
  while (true) {
    if (!count_reservations(rptr))
      break;

    while (true) {
      rid_del = rand() % state->rid;
      if (rb_search(rptr, rid_del)) {
        del_cnt++;
        break;
      }
    }

    switch (input) {
    case DELETION:
      printf(" >> delete RID(%d)\n", rid_del);
      RB_DELETE(rptr, rid_del);
      printf("\n");
      goto PRINT;
      break;
    case PRINT_RBTREE:
    PRINT:
      print_reservation(rptr);
      input = DELETION;
      break;
    }
  }

  printf("DELETE TEST END\n");
  printf("===============\n\n");
}
