#pragma once

#include "param.h"
#include "path.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
// TABLE ��Ʈ���� #slot primary key, dst double, tunit tunit_t���� �̷�����ϴ�.
typedef struct {
  city_t dst; // dst�� ������ ������ ��ȣ�� �ǹ��մϴ�.
  tunit_t tunit; // tunit_t�� �Ϲ����� �װ� ���� ��Ŀ� ���� 5���� 1���� �ϸ�,
                 // �Ҽ��� ������ �����մϴ�. �� ���α׷������� 5�� ������
                 // ������ ä���մϴ� (�������װ� ������ ��� �Դϴ�. )
} tnode_t;

// table���� src�� ��Ÿ�������Դϴ�.
// ���� �Լ����� ��ȣ�ϴٺ��� �������� ���ð��� src�� �����մϴ�.
typedef struct {
  city_t dsts[MAXFLIGHT * MAXDAY];
  city_t src;
} table_t;

// ���̺��� �������� �����մϴ�. �� �����ʹ� 288���� ���Ը��� ���Ե˴ϴ�.
// ������ ��쿡�� dst ���� �������� ���, �����˴ϴ�.
// ���Ӱ� ������� �������̺� �����ʹ� ���� ����� (./pathinfo�� ����˴ϴ�.)
void get_rand_table(table_t *t, city_t src, bool adj[][MAXNODE]);
// ������ ������� �������̺� ������ ���� ����ҿ��� �ҷ��ɴϴ� .
void load_table(table_t *t, city_t src, bool adj[][MAXNODE]);
// Ư��������  ���̺� ������ ����մϴ�.
void print_table(table_t *t, city_t src);
// tunit ������ ���� mhd_t�� �����Ͽ� �̸� ������ �������� ����մϴ�.
void print_tunit(tunit_t in);
// mhd�������� ����մϴ�. �ð�:��, ��¥�����Դϴ� .
void print_mhd(mhd_t in);
// Ư�� �ð��� am���� pm���� ��ȯ�մϴ�.
enum ampm get_ampm_mhd(mhd_t in);
// Ư�� �ð��� am���� pm������ ��ȯ������ input ���������� tunit�Դϴ�.
// c���� ����� �Ұ����ϱ� �����Դϴ�.
enum ampm get_ampm(tunit_t in);
// tunit_t���� mhd_t�� �����Ͽ� ��ȯ�մϴ�. ���� ���� ��ȯ�ϹǷ� �޸� �Ҵ���
// ���� �ʽ��ϴ�.
mhd_t get_mhd(tunit_t t);
// ���� ��� 3.5�� ���� 4�� �ø��ϴ�. ������ ������ 5�� �����̱� �����̰�
// �ε����� �������̾�� �ϱ� �����Դϴ�.
int ceil_tunit(tunit_t t);
// Ư�� �ð��뿡 �ش� ���÷� ������ ã���ϴ�. ����Ž���̶� �ð��� �ſ� ����
// �ɸ��ϴ�.
int serach_path(table_t *t, city_t dst, tunit_t atime);
// tunit_t���� �ð� ���� �����մϴ�.
int get_hour(tunit_t tunit);
// tunit_t���� �� ���� �����մϴ�.
int get_min(tunit_t tunit);
// tunit_t���� ���� �����͸� �����մϴ�.
int get_day(tunit_t tunit);
// mhd_t ������������ tunit_t ���������� ��ȯ�մϴ�.
tunit_t get_tunit(mhd_t in);
