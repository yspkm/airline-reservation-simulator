#pragma once

#include "param.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
// CSV ������ �Է¹ޱ� ���� ����ü
// s�� ������ ����(��Ʈ����Ʈ ����)
// MAX_LINE�� ��Ʈ����Ʈ �� ���ڿ� ������
// ��Ʈ����Ʈ �ϳ��ε� ������ ä��� ��츦 ����ؼ�
// MAX_LINE �� ���
struct data {
  char s[MAX_DATA][MAX_LINE];
};
// input_t: �Է��� �ޱ� ���� ����ü
// ��� ��쿡�� �Է� ó���� �ϸ�, main()���� input ������ ��Ʈ���� �ش��
typedef struct {
  char src;
  char dst;
  char name[MAX_NAME];
  int day;
  int hour;
  int min;
} input_t;
// ������ ������ input�� ������ true, �ƴϸ� false��ȯ
bool is_right_input(input_t *in);
// test_input ������ in ���� ��̿� ������
void get_test_inputs(input_t in[MAX_INPUT], int len);
// txt���� �о�� ���� �ϳ����� �ĸ� ������ �����Ͽ� data����ü�� ������
void getfield(char *line, struct data *d, int end_idx);
// ����ڷκ��� reservation ��ǲ�� ����
void get_input(input_t *in);
// ������ �Լ�
void print_input(input_t *in);
// search ��ɿ��� �ʿ��� input �Լ�
void get_input_for_search(input_t *in);
// � Ư�� ��忡 ���� schedule table(slot table)��
// Ư�� Ʃ���� ��� ���� ������ ��� �Լ�
void get_input_for_search_schedule_table_entry(input_t *in);
// ������ ��ġ�� �˻��ϱ� ���� ������ ��� �Լ�
void get_input_for_search_location_of_city(input_t *in);
// ���� �� �Ÿ��� �˱� ���� ������ ��� �Լ�
void get_input_for_search_distance(input_t *in);
