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
// TABLE 엔트리는 #slot primary key, dst double, tunit tunit_t으로 이루어집니다.
typedef struct {
  city_t dst; // dst는 목적지 도시의 번호를 의미합니다.
  tunit_t tunit; // tunit_t는 일반적인 항공 관제 방식에 따라 5분을 1으로 하며,
                 // 소수점 단위를 포함합니다. 본 프로그램에서는 5분 단위의
                 // 슬롯을 채택합니다 (김포공항과 동일한 방식 입니다. )
} tnode_t;

// table에서 src는 메타데이터입니다.
// 내부 함수에서 모호하다보니 스스로의 도시값을 src로 포함합니다.
typedef struct {
  city_t dsts[MAXFLIGHT * MAXDAY];
  city_t src;
} table_t;

// 테이블을 랜덤으로 생성합니다. 각 데이터는 288개의 슬롯마다 삽입됩니다.
// 각각의 경우에서 dst 값을 랜덤으로 잡고, 형성됩니다.
// 새롭게 만들어진 슬롯테이블 데이터는 로컬 저장소 (./pathinfo에 저장됩니다.)
void get_rand_table(table_t *t, city_t src, bool adj[][MAXNODE]);
// 이전에 만들어진 슬롯테이블 정보를 로컬 저장소에서 불러옵니다 .
void load_table(table_t *t, city_t src, bool adj[][MAXNODE]);
// 특정도시의  테이블 정보를 출력합니다.
void print_table(table_t *t, city_t src);
// tunit 단위에 대한 mhd_t를 생성하여 이를 정해진 형식으로 출력합니다.
void print_tunit(tunit_t in);
// mhd형식으로 출력합니다. 시간:분, 날짜형태입니다 .
void print_mhd(mhd_t in);
// 특정 시간이 am인지 pm인지 반환합니다.
enum ampm get_ampm_mhd(mhd_t in);
// 특정 시간이 am인지 pm인지를 반환하지만 input 데이터형이 tunit입니다.
// c언어라서 상속이 불가능하기 때문입니다.
enum ampm get_ampm(tunit_t in);
// tunit_t에서 mhd_t를 생성하여 반환합니다. 값을 직접 반환하므로 메모리 할당을
// 하지 않습니다.
mhd_t get_mhd(tunit_t t);
// 예를 들어 3.5인 경우는 4로 올립니다. 이유는 슬롯이 5분 단위이기 때문이고
// 인덱스는 정수형이어야 하기 때문입니다.
int ceil_tunit(tunit_t t);
// 특정 시간대에 해당 도시로 가는지 찾습니다. 선형탐색이라 시간이 매우 많이
// 걸립니다.
int serach_path(table_t *t, city_t dst, tunit_t atime);
// tunit_t에서 시간 값을 추출합니다.
int get_hour(tunit_t tunit);
// tunit_t에서 분 값을 추출합니다.
int get_min(tunit_t tunit);
// tunit_t에서 날자 데이터를 추출합니다.
int get_day(tunit_t tunit);
// mhd_t 데이터형에서 tunit_t 데이터형을 반환합니다.
tunit_t get_tunit(mhd_t in);
