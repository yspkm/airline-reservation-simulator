#pragma once

#include <stdio.h>
#include <string.h>
#include "param.h"

#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <assert.h>

// �� ��ο� ����˴ϴ�. 
#define CSVFNAME "./input.csv"
// �̸��� �ִ� ���̴� 100������ �����δ� 50�̸��Դϴ�. 
// CSV�� ������ ���� 2��� �߽��ϴ�. 
#define NAMELEN 100
// ������ �ִ� ������ �Դϴ�. 
#define BUFSIZE 4096
// ���δ� ������ �ִ� ������ �Դϴ�.
#define MAXLINE 1024;

int inputgen(void);
