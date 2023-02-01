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
// 각 노드의 좌표를 의미하며, 랜덤 생성됩니다.
typedef struct
{
    double x;
    double y;
} point_t;

// 인접리스트 형태 그래프의 각 노드에 해당됩니다.
typedef struct __gnode_
{
    struct __gnode_ *next;
    int dst;  // dst
    double w; // distance in km
} gnode_t;

// 헤더 노드는 위치데이터와
// 항공스케쥴 테이블이 포함됩니다.
typedef struct
{
    int src; // src
    gnode_t head;
    point_t p;
    table_t t; // monthly flight table
} ghead_t;

// 각 헤더 노드의 배열을 그래프구조체로 정의하여 추상화했습니다.
typedef struct
{
    ghead_t v[MAXNODE];
} graph_t;

// 그래프 초기화를 위한 메소드 입니다.
// 그래프 클래스의 의 v 멤버 변수는 어떤  헤더 더미 노드의 어레이 입니다.
// 각 더미노드를 통해 연결된 adj[u]를  v <-- adj[u]의 값을 의미합니다.
// src는 추후 값 접근의 편리성을 위해 첨가한 메타데이터 입니다.
void init_flight_system(graph_t *g, bool adj[][MAXNODE], bool isrand);
// find_path: find path between city src to city dst,
//      input: graph_t* g, city_t src, city_t dst, int day
//      output: path_t* p
// dfs를 사용하는 이유는 bfs의 경우 슬롯 사이즈가 너무 커서 폭의 문제가 생기고
// 각 가중치가 다르기 때문에 bfs는 최단경로가 아닙니다.
// 또한 dijkstra를 쓰지 않은 이유는 시간 단위로 생성되지 않을 수 있어서
// 이 부분을 해결하기가 쉽지 않기 때문입니다. simplified 버전의 경우
// dijkstra나 bfs를 사용할 수 있을 것입니다.
int find_path(graph_t *g, city_t src, city_t dst, int day, path_t *p);
// time slot table에서의 dfs를 하기 전에 간략하게 연결 자체의 여부를 빠르게 판단합니다.
bool is_connected(graph_t *g, city_t src, city_t dst);
// is_connected의 서브루틴입니다.
bool __is_connected_(graph_t *g, city_t cur, city_t dst);
// path_t 구조체의 정보를 출력합니다. path_t 구조체는 원래 graph_t에 있었으나
// 너무 많은 곳에서 따로 input 정보로 사용되다보니 path.h에 분리했습니다.
// 이 함수는 그 과정에서의 부산물이라고 볼 수 있습니다.
void print_path(path_t *p);
// actual time은 5분 단위 슬롯이 아닌 실제 분단위 정보를 의미합니다.
// 따라서 이 값은 5를 곱할 필요 없이 사용될 수 있습니다.
void print_acutual_time(double acutual_time);
// dfs: 특정 날짜의 0시 0분에 특정 도시에서 출발하여 특정 dst 도시로의 경로를 얻습니다
// 총 걸린시간과 경로별 시간데이터가 모두 저장됩니다.
// path_t 구조체에 모든 정보가 담기게 되고, 이를 재가공하여 사용합니다.
int dfs(graph_t *g, city_t src, city_t dst, tunit_t curtime, path_t *path);
// dfs의 서브루틴입니다.
int do_dfs(graph_t *g, city_t, city_t, path_t *path);
// 그래프를 랜덤으로 생성하고 정해진 경로에 저장합니다.
void get_rand_graph(graph_t *g, bool mark[][MAXNODE]);
// 랜덤화된 위치 정보를 반환합니다.
// x 값의 범위: [0, {MAX_X:3000}]
// y 값의 범위: [0, {MAX_Y:3000}]
point_t get_rand_point(unsigned seed);
// 각 노드의 위치정보를 개행문자 없이 출력합니다.
void print_point(point_t p);
// 각 노드 사이의 거리를 계산합니다. 단위는 km입니다.
double get_dist(graph_t *g, int src, int dst);
// 전체 그래프를 사람이 읽을 수 있는 형태로 파일에 저장합니다.
void gprint(graph_t *g);
// 개행문자 없이 출력됩니다.
// 가중치를 포함하지 않는 그래프 헤더 출력입니다.
void ghprint(FILE *f, ghead_t *h);
// 개행 문자 없이 출력됩니다.
// 가중치를 포함한 그래프 헤더 출력입니다.
void ghprint_with_weight(ghead_t *h);
// ghinsert는 바로 graph_t 구조체 사용이 불가능하므로
// 좀 더 사용이 쉬운 인터테이스를 첨가했습니다.
void ginsert(graph_t *g, int src, int dst, double w);
// 노드 정보를 삽입합니다.
void ghinsert(ghead_t *h, int dst, double w);
// 모든 노드의 adj node에 대한 리스트를 방문하여 각각을 free합니다.
void clear_graph(graph_t *g);
// clear_graph의 서브루틴, 최종적으로 헤드의 next를 free합니다.
bool rm_head(ghead_t *h);
// 그래프 초기화를 위한 메소드 입니다.
// 그래프 클래스의 의 v 멤버 변수는 어떤  헤더 더미 노드의 어레이 입니다.
// 각 더미노드를 통해 연결된 adj[u]를  v <-- adj[u]의 값을 의미합니다.
// src는 추후 값 접근의 편리성을 위해 첨가한 메타데이터 입니다.
void init_graph(graph_t *g);