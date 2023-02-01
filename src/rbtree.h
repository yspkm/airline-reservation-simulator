#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <wchar.h>
#include <time.h>
#include <math.h>
#include "param.h"
#include "path.h"
#include "table.h"
#include "graph.h"
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
typedef int key_t;
typedef void* data_t;

typedef struct __rbnode_
{
	char color; // 'R', 'B'
	key_t key;
	data_t data;
	struct __rbnode_ *p;
	struct __rbnode_ *left;
	struct __rbnode_ *right;
} rbnode_t;

typedef struct __rbtree_
{
	rbnode_t *root;
	rbnode_t *nil;
} rbtree_t;

typedef struct __rbedge_
{
	struct __rbedge_ *prev;
	char *str;
} rbedge_t;

// alloc & free
// rbtree의 초기화 
void rb_malloc(rbtree_t *T);
// rbtree의 제거, 모든 키를 삭제하고 할당된 값들을 없앰
void rb_free(rbtree_t *T);

// rb_print의 서브루틴
// edge 구조체를 초기화함
void init_edge(rbedge_t *_this, rbedge_t *prev, char *str);
// rbtree 구조를 보기 용이한 형태로 출력함
int rb_print(rbtree_t *T, rbnode_t *cur, rbedge_t *prev, bool isLeft);
// edge의 모양을 출력함 하단의 str0, str1, str2, str3 넷 중 하나의 모습 
void show_edges(rbedge_t *e);

// operations
// 트리 내에서 cur을 기준으로 최대인 노드를 반환함
rbnode_t *rb_maximum(rbtree_t *T, rbnode_t *cur);
// 트리 내에서 x 노드를 기준으로 최소의 노드를 반환함
rbnode_t *rb_minimum(rbtree_t *T, rbnode_t *cur);
// cur을 기준으로 트리 내의 predecessor 반환함
rbnode_t *tree_predecessor(rbtree_t *T, rbnode_t *cur);
// x를 기준으로 T의 successor를 반환함
rbnode_t *tree_successor(rbtree_t *T, rbnode_t *cur);
// T에서 key 값 k이 있으면 true 반환
// T에서 key 값 k가 없으면 false 반환
bool rb_search(rbtree_t *T, key_t k);
// cur을 기준으로 key_t k인 노드를 반환함
rbnode_t *rb_recursive_search(rbtree_t *T, rbnode_t *cur, key_t k);
// T에서 x를 기준으로 left rotate
void left_rotate(rbtree_t *T, rbnode_t *x);
// T에서 x를 기준으로 right rotate
void right_rotate(rbtree_t *T, rbnode_t *x);
// src에서 dst로 옮기는 함수 (obsolete)
void rb_transplant(rbtree_t *T, rbnode_t *src, rbnode_t *dst);
// nearest neighbor를 구해서 해당 키 값 반환
key_t nearest_neighbor(rbtree_t *T, key_t k);

// insert
// 키 값 입력, 
// insert rbtree, key값에 대한 노드를 생성하고 아이템 삽입
bool rb_insert_key(rbtree_t *T, key_t k, data_t item);

// rb_insert_key의 서브루틴
// 이미 생성된 노드를 삽입함
bool rb_insert(rbtree_t *T, rbnode_t *z);
// rb_insert의 서브루틴, rbtree 구조를 유지함
void rb_insert_fixup(rbtree_t *T, rbnode_t *z);

// delete 특정 k 값을 가진 노드 삭제
// 실패시 false
// 성공할 경우 true 반환하고 node 메모리 할당 해제
bool rb_delete_key(rbtree_t *T, key_t k);
// rb_delete: rb_delete_key의 서브루틴 
// 어떤 키 값에 해당되는 노드를 찾고 그 노드를 반환합니다.  
rbnode_t *rb_delete(rbtree_t *T, rbnode_t *z);
// rb_delete의 서브루틴
// rb_delete 이후 rbtree 구조를 유지함
void rb_delete_fixup(rbtree_t *T, rbnode_t *z);

// test function (obsolete)
void tester(void);
// INSERT PRIMITIVE
bool RB_INSERT(rbtree_t *T, key_t k);
// DELETE PRIMITIVE
bool RB_DELETE(rbtree_t *T, key_t k);
// PRINT PRIMITIVE
void PRINT_BST(rbtree_t *T);