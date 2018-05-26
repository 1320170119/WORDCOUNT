#define _CRT_SECURE_NO_WARNNINGS
#include<stdio.h>
#include<io.h>
#include<string.h>
#include <direct.h>
#include <stdlib.h>
#include<io.h>
#include<string>
#include "stdlib.h"
#include"iostream"

using namespace std;


int count_line(char file[])
{
	int l_num = 0;
	char ch;
	freopen(file, "r", stdin);
	while ((ch = getchar()) != EOF) {
		if (ch == '\n')
			l_num++;
	}
	fclose(stdin);

	return l_num;
}
int count_blankline(char file[])
{
	int b_num = 0, ch_num = 0;
	char ch;
	freopen(file, "r", stdin);
	while ((ch = getchar()) != EOF) {
		if (ch == '\n') {
			if (ch_num <= 1)
				b_num++;
			ch_num = 0;
		}
		else if (ch != ' '&&ch != '\t')
			ch_num++;
	}
	fclose(stdin);

	return b_num;
}

 
int count_noteline(char file[])
{
	int n_num = 0, line = 0, ch_num = 0, flag_1 = 0, flag_2 = 0, flag_3 = 0, thisline = 0;
	char ch;
	freopen(file, "r", stdin);
	while ((ch = getchar()) != EOF) {
		if (ch == '\n') {
			if (line&&ch_num > 0)
				line++;
			ch_num = 0;
			flag_1 = thisline = 0;
		}
		if (thisline == 1)
			continue;
		if (ch != ' '&&ch != '\t'&&ch != '\n')
			ch_num++;
		if (flag_2) {
			if (ch != ' '&&ch != '\t'&&ch != '\n')
				ch_num++;
			if (ch == '*')
				flag_3 = 1;
			else if (ch == '/'&&flag_3) {
				n_num += line;
				line = 0;
				flag_2 = flag_3 = 0;
				thisline = 1;
			}
			else
				flag_3 = 0;
		}
		else if (ch == '/') {
			if (flag_1 == 0)
				flag_1 = 1;
			else if (flag_1 == 1 && ch_num <= 3) {
				n_num++;
				thisline = 1;
			}
		}
		else if (ch == '*') {
			if (flag_1 == 1) {
				flag_2 = 1;
				line = 1;
			}
		}
		else
			flag_1 = 0;
	}
	fclose(stdin);

	return n_num;
}


int count_codeline(char file[])
{
	int line = count_line(file);
	int blank = count_blankline(file);
	int note = count_noteline(file);
	int cl_num = line - blank - note;

	return cl_num;
}
void gezhonghang(char Filename[]) {

};
void getWord(FILE *fp, int *num_char, int *num_word) {
	char ch;
	do {
		*num_char = *num_char + 1;
		ch = fgetc(fp);
	} while ((ch >= 'a'&&ch<'z') || (ch >= 'A'&&ch <= 'Z') || ch == '_');
	*num_word = *num_word + 1;
	fseek(fp, -1, SEEK_CUR);
}



int main(int argc, char* argv[])
{
	
	int num = argc-1;
	
	if (argv[1][1] == 's')
	{
		char choice[100][100];
		char ch;
		char s[200];
		FILE *fp;
		const char *to_search = argv[num];
		long handle; //用于查找的句柄
		struct _finddata_t fileinfo; //文件信息的结构体 
		handle = _findfirst(to_search, &fileinfo); //第一次查找 
		if (-1 == handle)return -1;
		else
		{
			printf("%s\n", fileinfo.name); //打印出找到的文件的文件名 
			char as[100];
			memset(as, '\0', 100);
			for (int i = 0; i < strlen(fileinfo.name); i++)
			{
				as[i] = fileinfo.name[i];
			}
			int num_word = 0, num_line = 0, num_char = 0, flag;
			fopen_s(&fp, as, "a+");
			if (fp == NULL) {
				printf("the file open bit");
			}
			while (!feof(fp)) {
				ch = fgetc(fp);
				if ((ch >= 'a'&&ch < 'z') || (ch >= 'A'&&ch <= 'Z')) {
					getWord(fp, &num_char, &num_word);
				}
				else if (ch == '\n') {
					num_line++;
				}
				else if (ch == '\0' || ch == '\t') {
					flag = 1;
				}
				else
					num_char += 1;
			}
			fclose(fp);
			for (int i = 1; i <num; i++)
			{

				if (argv[i][1] == 'c')
				{
					printf("字符数为:%d", num_char-1);
					printf("\n");
				}if (argv[i][1] == 'w')
				{
					printf("单词数为:%d", num_word);
					printf("\n");
				}if (argv[i][1] == 'l')
				{
					printf("行数为:%d", num_line);
					printf("\n");
				}
				if (argv[i][1] == 'a')

				{
					cout<<"空行行数"<<count_blankline(as)<<endl;
					cout << "注释行数" << count_noteline(as) << endl;
					cout << "代码行数" << count_codeline(as) << endl;

				}
			}

		}
		while (!_findnext(handle, &fileinfo)) //循环查找其他符合的文件，知道找不到其他的为止 
		{
			printf("%s\n", fileinfo.name);
			char choice[100][100];
			char ch;
			char s[200];
			FILE *fp;
			char as[100];
			memset(as, '\0', 100);
			for (int i = 0; i < strlen(fileinfo.name); i++)
			{
				as[i] = fileinfo.name[i];
			}
			int num_word = 0, num_line = 0, num_char = 0, flag;
			fopen_s(&fp, as, "a+");
			if (fp == NULL) {
				printf("the file open bit");
			}
			while (!feof(fp)) {
				ch = fgetc(fp);
				if ((ch >= 'a'&&ch < 'z') || (ch >= 'A'&&ch <= 'Z')) {
					getWord(fp, &num_char, &num_word);
				}
				else if (ch == '\n') {
					num_line++;
				}
				else if (ch == '\0' || ch == '\t') {
					flag = 1;
				}
				else
					num_char += 1;
			}
			fclose(fp);
			for (int i = 1; i <num; i++)
			{

				if (argv[i][1] == 'c')
				{
					printf("字符数为:%d", num_char-1);
					printf("\n");
				}if (argv[i][1] == 'w')
				{
					printf("单词数为:%d", num_word);
					printf("\n");
				}if (argv[i][1] == 'l')
				{
					printf("行数为:%d", num_line);
					printf("\n");
				}
				if (argv[i][1] == 'a')

				{

					cout << "空行行数" << count_blankline(as) << endl;
					cout << "注释行数" << count_noteline(as) << endl;
					cout << "代码行数" << count_codeline(as) << endl;
				}
			}
		}
	
	}
	else
	{
		
		FILE *fp;
		char ch;
		int num_word = 0, num_line = 0, num_char = 0, flag;
		fopen_s(&fp, argv[num], "a+");
		if (fp == NULL) {
			printf("the file open bit");
		}
		while (!feof(fp)) {
			ch = fgetc(fp);
			if ((ch >= 'a'&&ch < 'z') || (ch >= 'A'&&ch <= 'Z')) {
				getWord(fp, &num_char, &num_word);
			}
			else if (ch == '\n') {
				num_line++;
			}
			else if (ch == '\0' || ch == '\t') {
				flag = 1;
			}
			else
				num_char += 1;
		}
		fclose(fp);
		for (int i = 1; i <num; i++)
		{

            if (argv[i][1] == 'c')
			{
				printf("字符数为:%d", num_char-1);
				printf("\n");
			}if (argv[i][1] == 'w')
			{
				printf("单词数为:%d", num_word);
				printf("\n");
			}if (argv[i][1] == 'l')
			{
				printf("行数为:%d", num_line);
				printf("\n");
			}
			if (argv[i][1] == 'a')

			{

				cout << "空行行数" << count_blankline(argv[num]) << endl;
				cout << "注释行数" << count_noteline(argv[num]) << endl;
				cout << "代码行数" << count_codeline(argv[num]) << endl;
			}
		}
	}

	system("pause");
	return 0;

}

