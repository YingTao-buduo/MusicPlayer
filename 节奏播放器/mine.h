#pragma once
#include <string>
#include <vector>
#include <windows.h>
#pragma comment (lib, "winmm.lib")
using namespace std;
//显示汉字
void DrawCNString(const char* str);
void SelectFont(int size, int charset, const char* face);//字体、大小

//右键菜单
void MyMainMenu(int value);
void MySubMenuOne(int value);

//ui
void InitUI(int musicState);

//歌词
struct Lyric {//歌词结构体
	int time = 0;
	string text;
};
struct Info {
	string title;
	string singer;
	string album;
};
void ReadLrc();//从硬盘读取lrc歌词文件
vector<Lyric> Ready();//装载歌词



