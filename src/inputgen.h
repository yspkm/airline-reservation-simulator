#pragma once

#include <stdio.h>
#include <string.h>
#include "param.h"

#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <assert.h>

// 이 경로에 저장됩니다. 
#define CSVFNAME "./input.csv"
// 이름의 최대 길이는 100이지만 실제로는 50미만입니다. 
// CSV라서 안전을 위해 2배로 했습니다. 
#define NAMELEN 100
// 버퍼의 최대 사이즈 입니다. 
#define BUFSIZE 4096
// 라인당 길이의 최대 사이즈 입니다.
#define MAXLINE 1024;

int inputgen(void);
