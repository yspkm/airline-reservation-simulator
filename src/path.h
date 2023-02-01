#pragma once

#include "param.h"
#ifndef _CRT_SECURE_NO_WARNIGS
#define _CRT_SECURE_NO_WARNINGS
#endif
// am/pm 출력을 위한 열겨형
enum ampm
{
    AM = 0,
    PM = 1,
};
// tunit은 1개 슬롯(5분)을 의미합니다.
typedef double tunit_t; // 1 [tunit_t] == 5 minute
// city_t는 원래 char이었지만 graph_t를 짤 때 문제가 생겨서 int로 바겼습니다.
typedef int city_t;
// mhd_t는 빠르게 출력하기 위해 만들어진 구조체. struct tm과 유사합니다.
typedef struct
{
    int m;
    int h;
    int d;
} mhd_t;

// 경로에 대한 데이터 구조체
typedef struct
{
    char name[MAX_NAME]; // name
    char src;
    char dst;
    char path[MAXDEPTH];     // src-dst0-dst1--dst
    tunit_t dtime[MAXDEPTH]; // src(출발시간)-dst0(출발시간-dst
    int pidx;                // last idx
    tunit_t curtime;         // for bst;
    double actual_time_min;
} path_t;