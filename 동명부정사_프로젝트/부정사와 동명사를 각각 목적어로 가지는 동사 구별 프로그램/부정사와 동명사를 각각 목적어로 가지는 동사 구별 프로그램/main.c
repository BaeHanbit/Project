/*
1. ������ �߰��� �����ؾ��Ѵ�. o
2. ������ ������ �����ؾ� �Ѵ�. o
*/
#include <Windows.h>

void main()
{
	int menu_key = 0;

	do
	{
		menu_key = start_UI();
		open_controler(menu_key);
	} while (menu_key);

	system("pause");
}
