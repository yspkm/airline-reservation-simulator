#pragma once

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#include "table.h"
#include "path.h"
#include "param.h"
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
// �� ����� ��ǥ�� �ǹ��ϸ�, ���� �����˴ϴ�.
typedef struct
{
    double x;
    double y;
} point_t;

// ��������Ʈ ���� �׷����� �� ��忡 �ش�˴ϴ�.
typedef struct __gnode_
{
    struct __gnode_ *next;
    int dst;  // dst
    double w; // distance in km
} gnode_t;

// ��� ���� ��ġ�����Ϳ�
// �װ������� ���̺��� ���Ե˴ϴ�.
typedef struct
{
    int src; // src
    gnode_t head;
    point_t p;
    table_t t; // monthly flight table
} ghead_t;

// �� ��� ����� �迭�� �׷�������ü�� �����Ͽ� �߻�ȭ�߽��ϴ�.
typedef struct
{
    ghead_t v[MAXNODE];
} graph_t;

// �׷��� �ʱ�ȭ�� ���� �޼ҵ� �Դϴ�.
// �׷��� Ŭ������ �� v ��� ������ �  ��� ���� ����� ��� �Դϴ�.
// �� ���̳�带 ���� ����� adj[u]��  v <-- adj[u]�� ���� �ǹ��մϴ�.
// src�� ���� �� ������ ������ ���� ÷���� ��Ÿ������ �Դϴ�.
void init_flight_system(graph_t *g, bool adj[][MAXNODE], bool isrand);
// find_path: find path between city src to city dst,
//      input: graph_t* g, city_t src, city_t dst, int day
//      output: path_t* p
// dfs�� ����ϴ� ������ bfs�� ��� ���� ����� �ʹ� Ŀ�� ���� ������ �����
// �� ����ġ�� �ٸ��� ������ bfs�� �ִܰ�ΰ� �ƴմϴ�.
// ���� dijkstra�� ���� ���� ������ �ð� ������ �������� ���� �� �־
// �� �κ��� �ذ��ϱⰡ ���� �ʱ� �����Դϴ�. simplified ������ ���
// dijkstra�� bfs�� ����� �� ���� ���Դϴ�.
int find_path(graph_t *g, city_t src, city_t dst, int day, path_t *p);
// time slot table������ dfs�� �ϱ� ���� �����ϰ� ���� ��ü�� ���θ� ������ �Ǵ��մϴ�.
bool is_connected(graph_t *g, city_t src, city_t dst);
// is_connected�� �����ƾ�Դϴ�.
bool __is_connected_(graph_t *g, city_t cur, city_t dst);
// path_t ����ü�� ������ ����մϴ�. path_t ����ü�� ���� graph_t�� �־�����
// �ʹ� ���� ������ ���� input ������ ���Ǵٺ��� path.h�� �и��߽��ϴ�.
// �� �Լ��� �� ���������� �λ깰�̶�� �� �� �ֽ��ϴ�.
void print_path(path_t *p);
// actual time�� 5�� ���� ������ �ƴ� ���� �д��� ������ �ǹ��մϴ�.
// ���� �� ���� 5�� ���� �ʿ� ���� ���� �� �ֽ��ϴ�.
void print_acutual_time(double acutual_time);
// dfs: Ư�� ��¥�� 0�� 0�п� Ư�� ���ÿ��� ����Ͽ� Ư�� dst ���÷��� ��θ� ����ϴ�
// �� �ɸ��ð��� ��κ� �ð������Ͱ� ��� ����˴ϴ�.
// path_t ����ü�� ��� ������ ���� �ǰ�, �̸� �簡���Ͽ� ����մϴ�.
int dfs(graph_t *g, city_t src, city_t dst, tunit_t curtime, path_t *path);
// dfs�� �����ƾ�Դϴ�.
int do_dfs(graph_t *g, city_t, city_t, path_t *path);
// �׷����� �������� �����ϰ� ������ ��ο� �����մϴ�.
void get_rand_graph(graph_t *g, bool mark[][MAXNODE]);
// ����ȭ�� ��ġ ������ ��ȯ�մϴ�.
// x ���� ����: [0, {MAX_X:3000}]
// y ���� ����: [0, {MAX_Y:3000}]
point_t get_rand_point(unsigned seed);
// �� ����� ��ġ������ ���๮�� ���� ����մϴ�.
void print_point(point_t p);
// �� ��� ������ �Ÿ��� ����մϴ�. ������ km�Դϴ�.
double get_dist(graph_t *g, int src, int dst);
// ��ü �׷����� ����� ���� �� �ִ� ���·� ���Ͽ� �����մϴ�.
void gprint(graph_t *g);
// ���๮�� ���� ��µ˴ϴ�.
// ����ġ�� �������� �ʴ� �׷��� ��� ����Դϴ�.
void ghprint(FILE *f, ghead_t *h);
// ���� ���� ���� ��µ˴ϴ�.
// ����ġ�� ������ �׷��� ��� ����Դϴ�.
void ghprint_with_weight(ghead_t *h);
// ghinsert�� �ٷ� graph_t ����ü ����� �Ұ����ϹǷ�
// �� �� ����� ���� �������̽��� ÷���߽��ϴ�.
void ginsert(graph_t *g, int src, int dst, double w);
// ��� ������ �����մϴ�.
void ghinsert(ghead_t *h, int dst, double w);
// ��� ����� adj node�� ���� ����Ʈ�� �湮�Ͽ� ������ free�մϴ�.
void clear_graph(graph_t *g);
// clear_graph�� �����ƾ, ���������� ����� next�� free�մϴ�.
bool rm_head(ghead_t *h);
// �׷��� �ʱ�ȭ�� ���� �޼ҵ� �Դϴ�.
// �׷��� Ŭ������ �� v ��� ������ �  ��� ���� ����� ��� �Դϴ�.
// �� ���̳�带 ���� ����� adj[u]��  v <-- adj[u]�� ���� �ǹ��մϴ�.
// src�� ���� �� ������ ������ ���� ÷���� ��Ÿ������ �Դϴ�.
void init_graph(graph_t *g);