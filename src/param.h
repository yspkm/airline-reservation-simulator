// #pragma warning(disable:4996)
#pragma once
// visual studio C++ 컴파일러와 gcc간의
// 호환성을 위해 추가된 코드입니다.
// 입력단위에서의 필드 개수
#define MAX_DATA 4
// 한 라인에서 입력 가능한 필드당 최대 문자수
// 4개의 필드일 경우 4096 개의 입력이 이루어짐
#define MAX_LINE 1024
#define _CRT_SECURE_NO_WARNINGS
// 이름 길이의 최대 값
#define MAX_NAME 50
// 최대 인풋버퍼 사이즈
#define MAX_INPUT 512
// 최대 예약 횟수--> 인풋버퍼 사이즈와 동일
#define MAX_RESERVATION MAX_INPUT

// 노드 최대 개수 --> 도시 개수
#define MAXNODE 26
// 최대 탐색 깊이
#define MAXDEPTH 64
// 최대 x값 (동서로 3000km)
#define MAX_X 3000
// 최대 y값 (남북으로 3000km)
#define MAX_Y 3000
// 경로가 발견된 경우
#define FOUND 0
// 경로가 발견되지 않은 경우
#define UNFOUND -1

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
// RED-BLACK TREE BLACK
#define BLACK 'B'
// RED-BLACK TREE RED
#define RED 'R'
// DUMMY DATA FOR OBSOLETE CODES
#define DUMMY_DATA 0x0

// 5분 단위로 출발
// 시간당 12개
// 24시간 운영
// 288개의 출발
#define VELOCITY 500 // km/h
#define DEAPT_TERM_MINUTES 5
#define MAXFLIGHT 288 // (60/DEAPT_TERM_MINUTES)*24

// 26 개의 도시
#ifndef MAXNODE
#define MAXNODE 26
#endif

// 각 도시별로 10개의 도시와 상호 연결됨
#ifndef MAXEDGE
#define MAXEDGE 10
#endif

// 31일을 한 달으로 정의함
#ifndef MAXDAY
#define MAXDAY 31
#endif

// about input메뉴
// 예약 삽입 (이름, src, dst, 날짜)
#define INSERTTION 1
// 특정 rid 삭제
#define DELETION 2
// RB TREE 프린트
#define PRINT_RBTREE 3
// 경로 탐색
#define SEARCH_PATH 4
// 각 도시의 위치 출력
#define SEARCH_LOCATION_OF_CITY 5
// 테이블의 특정 시간대 엔트리 출력
#define SEARCH_SCHEDULE_TABLE_ENTRY 6
// 두 도시 사이의 거리와 걸리는 시간 출력
#define SEARCH_DISTANCE 7
// input: a->b, day, min
// a(x,y)-->b(x,y): distance: , start: , end:
// 전체 테이블 엔트리 출력
#define PRINT_SCHEDULE_TABLE_WHOLE 8
// 프로그램 종료
#define EXIT_PROGRAM 9

// obsolete
#define TEST_INSERTION
#define TEST_DELETION
#define TEST
