#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include "사용자 정의 구조체.c"

int gerund_cnt = 0;
int infinitive_cnt = 0;
int start_UI();
void open_controler(int menu_key);
int game_page();
int add_verb();
void add_gerund();
void add_infinitive();
int delete_verb();
void delete_gerund();
void delete_infinitive();
int check_gerund_len();
int check_infinitive_len();

int start_UI()
{
	int menu_key = 0;
wrong_number:
	menu_key = 0;

	system("cls");
	
	printf("Select Menu...\n\n");
	printf("0.End page\n");
	printf("1.Start game\n");
	printf("2.Add verb\n");
	printf("3.Delete verb\n");
	
	while (!_kbhit()){}
	menu_key = _getch();

	if (menu_key <= 47 || menu_key >= 52)
	{
		system("cls");
		printf("Please press right button..");
		Sleep(600);
		goto wrong_number;
	}
	printf("%d", menu_key);

	return menu_key-48;
	fflush(stdin);
}//메뉴판 리턴값으로 0,1,2,3을 가져 사용자가 선택한 메뉴를 확인한다.
void open_controler(int menu_key)
{
	int control_key;

	system("cls");

	switch (menu_key)
	{
	case 0:
		printf("You selected 'End page'...\n");
		break;

	case 1:
		game_page();
		break;
		//게임 실행 함수

	case 2:
		control_key = add_verb();

		if (control_key == 1)
			add_gerund();//동명사 추가
		else
			add_infinitive();//부정사 추가
		break;

	case 3:
		control_key = delete_verb();

		if (control_key == 1)
			delete_gerund();//동명사 제거
		else
			delete_infinitive();//부정사 제거
		break;
		//동사 삭제 실행 함수

	}
}
int game_page()
{
	char word[50] = { 0 };
	char key = 0;
	int score = 0;
	int slt_txt = 0;
	int slt_line = 0;
	int random = 0;
	int life = 3;
	FILE *gerund;
	FILE *infinitive;
	
	srand(time(NULL));


	do//반복해서 다음 문제를 생산
	{
		gerund = fopen("gerund.txt", "r");
		infinitive = fopen("infinitive.txt", "r");

		slt_txt = rand() % 2 + 1;

		if (slt_txt == 1)//동명사
		{
			slt_line = rand() % check_gerund_len();//gerund.txt  안에서 단어를 고른다.

			for (int i = 0; i <= slt_line; i++)
				fgets(word, 50, gerund);
		}
		else if (slt_txt == 2)//부정사
		{
			slt_line = rand() % check_infinitive_len();//infinitive.txt안에서 단어를 고른다.

			for (int i = 0; i < slt_line; i++)
				fgets(word, 50, infinitive);
		}

			system("cls");

		back:
			printf("Press 'G' if you think the verb which you are seeing must take 'Gerund' as object...\n");
			printf("Press 'I' if you think the verb which you are seeing must take 'infinitive' as object...\n");
			printf("If you press different key instead of those two key.... You will die...\n\n");
			printf("Verb : %s\n\n", word);
			printf("Your score : %d\n", score);
			printf("Your life : %d\n", life);

			fflush(stdin);
			key = _getch();
			printf("%c", key);

			if (key < 91)
			{
				key += 32;
			}
			if (key != 'g'&&key != 'i')
			{
				system("cls");
				goto back;
			}
		if (slt_txt == 1)//gerund
		{
			if (key == 'g')//Correct
			{
				random = rand() % 10;
				if (random == 9)
					score = score + 300 * random;
				else
					score += 300;
			}
			else if (key == 'i')//Miss
			{
				life--;
			}
		}
		else if (slt_txt == 2)
		{
			if (key == 'i')//Correct
			{
				random = rand() % 10;
				if (random == 9)
					score = score + 300 * random;
				else
					score += 300;
			}
			else if (key == 'g')//Miss
			{
				life--;
			}
		}
		fclose(gerund);
		fclose(infinitive);

	}while (life);
}
int add_verb()
{
	int vb_menu_key = 0;

	system("cls");

wrong_number:
	printf("Which verb will you add? \n\n");
	printf("1. The verb only have 'gerund' as object\n");
	printf("2. The verb only have 'infinitive' as object\n");

	cursor(1);
	printf("Input : ");
	vb_menu_key = _getche();
	
	if (vb_menu_key <= 48 || vb_menu_key >= 51)
	{
		system("cls");

		printf("Please press right button..\n\n");
		goto wrong_number;
	}
	
	return vb_menu_key - 48;
}//어떤 동사를 추가할지 결정하며, 1이면 동명사를, 2이면 부정사를 추가한다. (종료는 없다)
void add_gerund()
{
	int same_key = 0;//만약 입력받은 값이 fgets로 받아온 값과 동일할때, 걸러주기 위한 변수 1,0이라고생각하자
	char word[50] = { 0 };//입력받을 배열(영문자에서 가장 긴 문자는 45자이다)
	char check[50] = { 0 };//메모장에서 하나씩 읽어 현재 word배열의 단어가 있는지 확인 후 없으면 다음 단어를 읽는다.

	system("cls");

	FILE *fp = fopen("gerund.txt", "a+");//모든걸 다 할 수 있는 a+ 추가 쓰기 읽기일껄...?
	do
	{ 
		system("cls");
		printf("Press X to quit this page!!!!\n");
		printf("Input verb which only take gerund as object : ");
		fgets(word,50,stdin);

		if (word == "X" ||word ==  "x")
			return;
	
		while (1)
		{
			fgets(check, 50, fp);//파일에서부터 동사를 하나씩 받아 check변수에 저장한다.
			if (!strcmp(check, word))//이후 이 check를 word와 비교한다. 나중에 strncmp로 변경
			{
				same_key = 0;
				printf("The word which you inputed had aleady written\n");
				Sleep(1200);

				break;
			}
			if (feof(fp))//파일을 다 읽었다면 탈~출!
			{
				same_key = 0;
				break;
			}
			same_key = 1;
		}
	} while (same_key);


	for (int i = 0; i < strlen(word); i++)
	{
		if (word[i]>64 &&word[i]<91)
			word[i] += 32;
	}

	fputs(word, fp);
	fclose(fp);		
}
void add_infinitive()
{
	int same_key = 0;//만약 입력받은 값이 fgets로 받아온 값과 동일할때, 걸러주기 위한 변수 1,0이라고생각하자
	char word[50] = { 0 };//입력받을 배열(영문자에서 가장 긴 문자는 45자이다)
	char check[50] = { 0 };//메모장에서 하나씩 읽어 현재 word배열의 단어가 있는지 확인 후 없으면 다음 단어를 읽는다.

	system("cls");

	FILE *fp = fopen("infinitive.txt", "a+");//모든걸 다 할 수 있는 a+ 추가 쓰기 읽기일껄...?
	do
	{
		system("cls");
		printf("Press X to quit this page!!!!\n");
		printf("Input verb which only take Infinitive as object : ");
		fgets(word, 50, stdin);

		if (word == "X" || word == "x")
			return;

		while (1)
		{
			fgets(check, 50, fp);//파일에서부터 동사를 하나씩 받아 check변수에 저장한다.
			if (!strcmp(check, word))//이후 이 check를 word와 비교한다. 나중에 strncmp로 변경
			{
				same_key = 0;
				break;
			}
			if (feof(fp))//파일을 다 읽었다면 탈~출!
			{
				same_key = 0;
				break;
			}
			same_key = 1;
		}
	} while (same_key);

	for (int i = 0; i < strlen(word); i++)
	{
		if (word[i] >64 && word[i] < 91)
			word[i] += 32;
	}

	fputs(word, fp);
	fclose(fp);
}
int delete_verb()
{
	int vb_menu_key = 0;

	system("cls");

wrong_number:
	printf("Which verb will you delete? \n\n");
	printf("1. The verb only have 'gerund' as object\n");
	printf("2. The verb only have 'infinitive' as object\n");

	cursor(1);
	printf("Input : ");
	vb_menu_key = _getch();

	if (vb_menu_key <= 48 || vb_menu_key >= 51)
	{
		system("cls");

		printf("Please press right button..\n\n");
		goto wrong_number;
	}

	return vb_menu_key - 48;
}
void delete_gerund()
{
	char word[50] = { 0 };
	char check[50] = { 0 };
	char key = 0;

	FILE *Temp_Fp = fopen("temp.txt", "w");
	fclose(Temp_Fp);//temp 텍스트를 초기화 해주고


	FILE *fp = fopen("gerund.txt", "r");
	Temp_Fp = fopen("temp.txt", "a");
	 
	system("cls");

	printf("Input word you want to delete : ");
	fgets(word, 50, stdin);

	for (auto int i = 0; i < strlen(word); i++)//무조건 소문자로 입력하기 위해서...
	{
		if (word[i] > 64 && word[i] < 91)
			word[i] += 32;
	}

	while (1)
	{
		fgets(check, 50, fp);//미리 저장되어 있던 gerund 텍스트에서 단어를 하나씩 읽어 내가 입력한 단어와 비교한다.
		key = strncmp(word, check, strlen(word));//서로 같으면 0을 반환한다.
		
		if (key)//만약 단어장에서  뽑아온 단어와 입력 단어가 서로 다르면 텍스트에 넣고 같다면 그냥 패스
			fputs(check, Temp_Fp);

		if (feof(fp))
			break;
	}
	fclose(fp);
	fclose(Temp_Fp);

	fp = fopen("gerund.txt", "w");//다시 값을 넣어줄 gerund 텍스트를 백지상태로 만들어준다.
	fclose(fp);

	Temp_Fp = fopen("temp.txt", "r");
	fp = fopen("gerund.txt", "a");
	while (1)
	{
		fgets(word, 50, Temp_Fp);//임시 텍스트에서 받아서
		fputs(word, fp);//다시 gerund에 넣는다.
		printf("test\n");
		if (feof(Temp_Fp))
			break;
	}

	fclose(fp);
	fclose(Temp_Fp);
}
void delete_infinitive()
{
	char word[50] = { 0 };
	char check[50] = { 0 };
	char key = 0;

	FILE *Temp_Fp = fopen("temp.txt", "w");
	fclose(Temp_Fp);//temp 텍스트를 초기화 해주고


	FILE *fp = fopen("infinitive.txt", "r");
	Temp_Fp = fopen("temp.txt", "a");

	system("cls");

	printf("Input word you want to delete : ");
	fgets(word, 50, stdin);

	for (auto int i = 0; i < strlen(word); i++)//무조건 소문자로 입력하기 위해서...
	{
		if (word[i] > 64 && word[i] < 91)
			word[i] += 32;
	}

	while (1)
	{
		fgets(check, 50, fp);//미리 저장되어 있던 infinitive 텍스트에서 단어를 하나씩 읽어 내가 입력한 단어와 비교한다.
		key = strncmp(word, check, strlen(word));//서로 같으면 0을 반환한다.

		if (key)//만약 단어장에서  뽑아온 단어와 입력 단어가 서로 다르면 텍스트에 넣고 같다면 그냥 패스
			fputs(check, Temp_Fp);

		if (feof(fp))
			break;
	}
	fclose(fp);
	fclose(Temp_Fp);

	fp = fopen("infinitive.txt", "w");//다시 값을 넣어줄 intivinitive텍스트를 백지상태로 만들어준다.
	fclose(fp);

	Temp_Fp = fopen("temp.txt", "r");
	fp = fopen("infinitive.txt", "a");
	while (1)
	{
		fgets(word, 50, Temp_Fp);//임시 텍스트에서 받아서
		fputs(word, fp);//다시 infinitive에 넣는다.
		printf("test\n");
		if (feof(Temp_Fp))
			break;
	}

	fclose(fp);
	fclose(Temp_Fp);
}
int check_gerund_len()
{
	int len = 0;
	char word[50] = { 0 };
	FILE* fp = fopen("gerund.txt", "r");
	

	while (1)
	{
		fgets(word, 50, fp);
		if (feof(fp))
			return len;
		len++;
	}
}
int check_infinitive_len()
{
	int len = 0;
	char word[50] = { 0 };
	FILE* fp = fopen("infinitive.txt", "r");


	while (1)
	{
		fgets(word, 50, fp);
		if (feof(fp))
			return len;
		len++;
	}
}