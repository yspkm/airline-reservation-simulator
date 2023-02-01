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
// rbtree�� �ʱ�ȭ 
void rb_malloc(rbtree_t *T);
// rbtree�� ����, ��� Ű�� �����ϰ� �Ҵ�� ������ ����
void rb_free(rbtree_t *T);

// rb_print�� �����ƾ
// edge ����ü�� �ʱ�ȭ��
void init_edge(rbedge_t *_this, rbedge_t *prev, char *str);
// rbtree ������ ���� ������ ���·� �����
int rb_print(rbtree_t *T, rbnode_t *cur, rbedge_t *prev, bool isLeft);
// edge�� ����� ����� �ϴ��� str0, str1, str2, str3 �� �� �ϳ��� ��� 
void show_edges(rbedge_t *e);

// operations
// Ʈ�� ������ cur�� �������� �ִ��� ��带 ��ȯ��
rbnode_t *rb_maximum(rbtree_t *T, rbnode_t *cur);
// Ʈ�� ������ x ��带 �������� �ּ��� ��带 ��ȯ��
rbnode_t *rb_minimum(rbtree_t *T, rbnode_t *cur);
// cur�� �������� Ʈ�� ���� predecessor ��ȯ��
rbnode_t *tree_predecessor(rbtree_t *T, rbnode_t *cur);
// x�� �������� T�� successor�� ��ȯ��
rbnode_t *tree_successor(rbtree_t *T, rbnode_t *cur);
// T���� key �� k�� ������ true ��ȯ
// T���� key �� k�� ������ false ��ȯ
bool rb_search(rbtree_t *T, key_t k);
// cur�� �������� key_t k�� ��带 ��ȯ��
rbnode_t *rb_recursive_search(rbtree_t *T, rbnode_t *cur, key_t k);
// T���� x�� �������� left rotate
void left_rotate(rbtree_t *T, rbnode_t *x);
// T���� x�� �������� right rotate
void right_rotate(rbtree_t *T, rbnode_t *x);
// src���� dst�� �ű�� �Լ� (obsolete)
void rb_transplant(rbtree_t *T, rbnode_t *src, rbnode_t *dst);
// nearest neighbor�� ���ؼ� �ش� Ű �� ��ȯ
key_t nearest_neighbor(rbtree_t *T, key_t k);

// insert
// Ű �� �Է�, 
// insert rbtree, key���� ���� ��带 �����ϰ� ������ ����
bool rb_insert_key(rbtree_t *T, key_t k, data_t item);

// rb_insert_key�� �����ƾ
// �̹� ������ ��带 ������
bool rb_insert(rbtree_t *T, rbnode_t *z);
// rb_insert�� �����ƾ, rbtree ������ ������
void rb_insert_fixup(rbtree_t *T, rbnode_t *z);

// delete Ư�� k ���� ���� ��� ����
// ���н� false
// ������ ��� true ��ȯ�ϰ� node �޸� �Ҵ� ����
bool rb_delete_key(rbtree_t *T, key_t k);
// rb_delete: rb_delete_key�� �����ƾ 
// � Ű ���� �ش�Ǵ� ��带 ã�� �� ��带 ��ȯ�մϴ�.  
rbnode_t *rb_delete(rbtree_t *T, rbnode_t *z);
// rb_delete�� �����ƾ
// rb_delete ���� rbtree ������ ������
void rb_delete_fixup(rbtree_t *T, rbnode_t *z);

// test function (obsolete)
void tester(void);
// INSERT PRIMITIVE
bool RB_INSERT(rbtree_t *T, key_t k);
// DELETE PRIMITIVE
bool RB_DELETE(rbtree_t *T, key_t k);
// PRINT PRIMITIVE
void PRINT_BST(rbtree_t *T);