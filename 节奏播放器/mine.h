#pragma once
#include <string>
#include <vector>
#include <windows.h>
#pragma comment (lib, "winmm.lib")
using namespace std;
//��ʾ����
void DrawCNString(const char* str);
void SelectFont(int size, int charset, const char* face);//���塢��С

//�Ҽ��˵�
void MyMainMenu(int value);
void MySubMenuOne(int value);

//ui
void InitUI(int musicState);

//���
struct Lyric {//��ʽṹ��
	int time = 0;
	string text;
};
struct Info {
	string title;
	string singer;
	string album;
};
void ReadLrc();//��Ӳ�̶�ȡlrc����ļ�
vector<Lyric> Ready();//װ�ظ��



