#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include "����� ���� ����ü.c"

void test01();

void test01()
{
	int key = 0;

	key = _getch();
	printf("%d", key);

	Sleep(10000);
}