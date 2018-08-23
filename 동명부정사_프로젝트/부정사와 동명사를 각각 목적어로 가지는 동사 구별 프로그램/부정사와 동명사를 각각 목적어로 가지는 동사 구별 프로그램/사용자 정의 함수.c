#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include "����� ���� ����ü.c"

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
}//�޴��� ���ϰ����� 0,1,2,3�� ���� ����ڰ� ������ �޴��� Ȯ���Ѵ�.
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
		//���� ���� �Լ�

	case 2:
		control_key = add_verb();

		if (control_key == 1)
			add_gerund();//����� �߰�
		else
			add_infinitive();//������ �߰�
		break;

	case 3:
		control_key = delete_verb();

		if (control_key == 1)
			delete_gerund();//����� ����
		else
			delete_infinitive();//������ ����
		break;
		//���� ���� ���� �Լ�

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


	do//�ݺ��ؼ� ���� ������ ����
	{
		gerund = fopen("gerund.txt", "r");
		infinitive = fopen("infinitive.txt", "r");

		slt_txt = rand() % 2 + 1;

		if (slt_txt == 1)//�����
		{
			slt_line = rand() % check_gerund_len();//gerund.txt  �ȿ��� �ܾ ����.

			for (int i = 0; i <= slt_line; i++)
				fgets(word, 50, gerund);
		}
		else if (slt_txt == 2)//������
		{
			slt_line = rand() % check_infinitive_len();//infinitive.txt�ȿ��� �ܾ ����.

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
}//� ���縦 �߰����� �����ϸ�, 1�̸� ����縦, 2�̸� �����縦 �߰��Ѵ�. (����� ����)
void add_gerund()
{
	int same_key = 0;//���� �Է¹��� ���� fgets�� �޾ƿ� ���� �����Ҷ�, �ɷ��ֱ� ���� ���� 1,0�̶���������
	char word[50] = { 0 };//�Է¹��� �迭(�����ڿ��� ���� �� ���ڴ� 45���̴�)
	char check[50] = { 0 };//�޸��忡�� �ϳ��� �о� ���� word�迭�� �ܾ �ִ��� Ȯ�� �� ������ ���� �ܾ �д´�.

	system("cls");

	FILE *fp = fopen("gerund.txt", "a+");//���� �� �� �� �ִ� a+ �߰� ���� �б��ϲ�...?
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
			fgets(check, 50, fp);//���Ͽ������� ���縦 �ϳ��� �޾� check������ �����Ѵ�.
			if (!strcmp(check, word))//���� �� check�� word�� ���Ѵ�. ���߿� strncmp�� ����
			{
				same_key = 0;
				printf("The word which you inputed had aleady written\n");
				Sleep(1200);

				break;
			}
			if (feof(fp))//������ �� �о��ٸ� Ż~��!
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
	int same_key = 0;//���� �Է¹��� ���� fgets�� �޾ƿ� ���� �����Ҷ�, �ɷ��ֱ� ���� ���� 1,0�̶���������
	char word[50] = { 0 };//�Է¹��� �迭(�����ڿ��� ���� �� ���ڴ� 45���̴�)
	char check[50] = { 0 };//�޸��忡�� �ϳ��� �о� ���� word�迭�� �ܾ �ִ��� Ȯ�� �� ������ ���� �ܾ �д´�.

	system("cls");

	FILE *fp = fopen("infinitive.txt", "a+");//���� �� �� �� �ִ� a+ �߰� ���� �б��ϲ�...?
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
			fgets(check, 50, fp);//���Ͽ������� ���縦 �ϳ��� �޾� check������ �����Ѵ�.
			if (!strcmp(check, word))//���� �� check�� word�� ���Ѵ�. ���߿� strncmp�� ����
			{
				same_key = 0;
				break;
			}
			if (feof(fp))//������ �� �о��ٸ� Ż~��!
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
	fclose(Temp_Fp);//temp �ؽ�Ʈ�� �ʱ�ȭ ���ְ�


	FILE *fp = fopen("gerund.txt", "r");
	Temp_Fp = fopen("temp.txt", "a");
	 
	system("cls");

	printf("Input word you want to delete : ");
	fgets(word, 50, stdin);

	for (auto int i = 0; i < strlen(word); i++)//������ �ҹ��ڷ� �Է��ϱ� ���ؼ�...
	{
		if (word[i] > 64 && word[i] < 91)
			word[i] += 32;
	}

	while (1)
	{
		fgets(check, 50, fp);//�̸� ����Ǿ� �ִ� gerund �ؽ�Ʈ���� �ܾ �ϳ��� �о� ���� �Է��� �ܾ�� ���Ѵ�.
		key = strncmp(word, check, strlen(word));//���� ������ 0�� ��ȯ�Ѵ�.
		
		if (key)//���� �ܾ��忡��  �̾ƿ� �ܾ�� �Է� �ܾ ���� �ٸ��� �ؽ�Ʈ�� �ְ� ���ٸ� �׳� �н�
			fputs(check, Temp_Fp);

		if (feof(fp))
			break;
	}
	fclose(fp);
	fclose(Temp_Fp);

	fp = fopen("gerund.txt", "w");//�ٽ� ���� �־��� gerund �ؽ�Ʈ�� �������·� ������ش�.
	fclose(fp);

	Temp_Fp = fopen("temp.txt", "r");
	fp = fopen("gerund.txt", "a");
	while (1)
	{
		fgets(word, 50, Temp_Fp);//�ӽ� �ؽ�Ʈ���� �޾Ƽ�
		fputs(word, fp);//�ٽ� gerund�� �ִ´�.
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
	fclose(Temp_Fp);//temp �ؽ�Ʈ�� �ʱ�ȭ ���ְ�


	FILE *fp = fopen("infinitive.txt", "r");
	Temp_Fp = fopen("temp.txt", "a");

	system("cls");

	printf("Input word you want to delete : ");
	fgets(word, 50, stdin);

	for (auto int i = 0; i < strlen(word); i++)//������ �ҹ��ڷ� �Է��ϱ� ���ؼ�...
	{
		if (word[i] > 64 && word[i] < 91)
			word[i] += 32;
	}

	while (1)
	{
		fgets(check, 50, fp);//�̸� ����Ǿ� �ִ� infinitive �ؽ�Ʈ���� �ܾ �ϳ��� �о� ���� �Է��� �ܾ�� ���Ѵ�.
		key = strncmp(word, check, strlen(word));//���� ������ 0�� ��ȯ�Ѵ�.

		if (key)//���� �ܾ��忡��  �̾ƿ� �ܾ�� �Է� �ܾ ���� �ٸ��� �ؽ�Ʈ�� �ְ� ���ٸ� �׳� �н�
			fputs(check, Temp_Fp);

		if (feof(fp))
			break;
	}
	fclose(fp);
	fclose(Temp_Fp);

	fp = fopen("infinitive.txt", "w");//�ٽ� ���� �־��� intivinitive�ؽ�Ʈ�� �������·� ������ش�.
	fclose(fp);

	Temp_Fp = fopen("temp.txt", "r");
	fp = fopen("infinitive.txt", "a");
	while (1)
	{
		fgets(word, 50, Temp_Fp);//�ӽ� �ؽ�Ʈ���� �޾Ƽ�
		fputs(word, fp);//�ٽ� infinitive�� �ִ´�.
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