#pragma once

#include "param.h"
#include <stdio.h>
#include <string.h>

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

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
