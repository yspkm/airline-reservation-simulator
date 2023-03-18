#pragma once

#include "graph.h"
#include "input.h"
#include "param.h"
#include "path.h"
#include "rbtree.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
typedef struct {
  // like pid, it increases continuously
  size_t rid; // reservation id
  // path graph with time table
  graph_t path_for_each_city;
  // for reservation delete and search
  rbtree_t reservation_information;
  // adjcent matrix for efficiency
  bool adj[MAXNODE][MAXNODE];
  // input buffer for efficiency
  input_t input_buffer[MAX_INPUT];
  // reservation(output) buffer
  path_t reservation_buffer[MAX_RESERVATION];
} sys_state_t;

// path_t 구조체의 내용을 지움
void init_path(path_t *p, input_t *i, bool is_search);
// input_t 구조체의 내용을 지움
void init_input(input_t *i);
// 전체 예약 상황을 레드블랙 트리 형태로 출력함
void print_reservation(rbtree_t *T);
// 전체 예약 상황을 테이블형태로 출력함
void print_paths_inorder(rbtree_t *T, rbnode_t *cur);
// 시스템 상태 변수를 초기화함
void init_state(sys_state_t *state);
// 시스템 상태 변수를 외부 파일에서 불러옴
void load_state(sys_state_t *state);
// 테이블 엔트리 정보(스케쥴 테이블)을 출력함
void print_table_entry(graph_t *g, input_t *in);
// 그래프 상의 input에서 받은 src와 dst 사이의 거리 정보를 출력함
void print_distance(graph_t *g, input_t *i);
// 그래프 상의 input에서 받은 src의 위치 정보를 출력함
void print_location_of_city(graph_t *g, input_t *i);
// 총 예약 개수를 rbtree counter로 측정함
int count_reservations(rbtree_t *T);
