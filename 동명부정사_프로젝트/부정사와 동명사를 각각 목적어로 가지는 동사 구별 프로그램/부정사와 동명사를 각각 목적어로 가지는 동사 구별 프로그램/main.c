/*
1. 동사의 추가가 가능해야한다. o
2. 동사의 삭제가 가능해야 한다. o
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
