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

// path_t ����ü�� ������ ����
void init_path(path_t *p, input_t *i, bool is_search);
// input_t ����ü�� ������ ����
void init_input(input_t *i);
// ��ü ���� ��Ȳ�� ����� Ʈ�� ���·� �����
void print_reservation(rbtree_t *T);
// ��ü ���� ��Ȳ�� ���̺����·� �����
void print_paths_inorder(rbtree_t *T, rbnode_t *cur);
// �ý��� ���� ������ �ʱ�ȭ��
void init_state(sys_state_t *state);
// �ý��� ���� ������ �ܺ� ���Ͽ��� �ҷ���
void load_state(sys_state_t *state);
// ���̺� ��Ʈ�� ����(������ ���̺�)�� �����
void print_table_entry(graph_t *g, input_t *in);
// �׷��� ���� input���� ���� src�� dst ������ �Ÿ� ������ �����
void print_distance(graph_t *g, input_t *i);
// �׷��� ���� input���� ���� src�� ��ġ ������ �����
void print_location_of_city(graph_t *g, input_t *i);
// �� ���� ������ rbtree counter�� ������
int count_reservations(rbtree_t *T);
