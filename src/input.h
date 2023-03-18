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
// CSV 파일을 입력받기 위한 구조체
// s는 데이터 개수(어트리뷰트 개수)
// MAX_LINE은 어트리뷰트 당 문자열 사이즈
// 어트리뷰트 하나인데 라인을 채우는 경우를 대비해서
// MAX_LINE 값 사용
struct data {
  char s[MAX_DATA][MAX_LINE];
};
// input_t: 입력을 받기 위한 구조체
// 모든 경우에서 입력 처리를 하며, main()내의 input 버퍼의 엔트리에 해당됨
typedef struct {
  char src;
  char dst;
  char name[MAX_NAME];
  int day;
  int hour;
  int min;
} input_t;
// 정해진 형태의 input이 맞으면 true, 아니면 false반환
bool is_right_input(input_t *in);
// test_input 단위를 in 버퍼 어레이에 저장함
void get_test_inputs(input_t in[MAX_INPUT], int len);
// txt에서 읽어온 라인 하나에서 컴마 단위로 구분하여 data구조체에 저장함
void getfield(char *line, struct data *d, int end_idx);
// 사용자로부터 reservation 인풋을 받음
void get_input(input_t *in);
// 디버깅용 함수
void print_input(input_t *in);
// search 기능에서 필요한 input 함수
void get_input_for_search(input_t *in);
// 어떤 특정 노드에 대한 schedule table(slot table)의
// 특정 튜플을 얻기 위한 쿼리를 얻는 함수
void get_input_for_search_schedule_table_entry(input_t *in);
// 도시의 위치를 검색하기 위한 쿼리를 얻는 함수
void get_input_for_search_location_of_city(input_t *in);
// 도시 간 거리를 알기 위한 쿼리를 얻는 함수
void get_input_for_search_distance(input_t *in);
