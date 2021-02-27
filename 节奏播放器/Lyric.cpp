#include "mine.h"
#include <iostream>
#include <fstream>
#include <glut.h>
#include <vector>
#include <windows.h>
#pragma comment (lib, "winmm.lib")

using namespace std;

string Utf8ToGbk(const char* src_str) {
	int len = MultiByteToWideChar(CP_UTF8, 0, src_str, -1, NULL, 0);
	wchar_t* wszGBK = new wchar_t[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, src_str, -1, wszGBK, len);
	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char* szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
	string strTemp(szGBK);
	if (wszGBK) delete[] wszGBK;
	if (szGBK) delete[] szGBK;
	return strTemp;
}

vector<string> lrc;

void ReadLrc() {
	ifstream infile;
	string temp;
	infile.open("lyric.lrc", ios::in);
	if (!infile.is_open())
		cout << "Open file failure" << endl;

	while (!infile.eof())
	{
		infile >> temp;
		lrc.push_back(temp);
	}
	infile.close();
}

//½âÎö¸è´Ê
Lyric getLyric(string str) {
	Lyric r;
	int t1 = str.find_last_of("]");
	int min1 = str[str.find_first_of(":") - 2] - 48;
	int min2 = str[str.find_first_of(":") - 1] - 48;
	int sec1 = str[str.find_first_of(":") + 1] - 48;
	int sec2 = str[str.find_first_of(":") + 2] - 48;
	int msec1 = str[str.find_first_of(":") + 4] - 48;
	int msec2 = str[str.find_first_of(":") + 5] - 48;
	r.time = ((((min1 * 10) + min2) * 60) + ((sec1 * 10) + sec2)) * 1000 + msec1 * 100 + msec2 * 10;
	r.text = Utf8ToGbk(str.substr(t1 + 1).data());
	return r;
}

string getInfo(string str) {
	int f = str.find_first_of(":");
	int e = str.find_last_of("]");
	return str.substr(f + 1, e - f - 1);
}

vector<Lyric> Ready() {
	ReadLrc();
	string title = getInfo(lrc[0]);
	string singer = getInfo(lrc[1]);
	string album = getInfo(lrc[2]);
	vector<Lyric> lyricData;
	int k = 0;
	for (int i = 3; i < lrc.size(); i++) {
		lyricData.push_back(getLyric(lrc[i]));
	}
	return lyricData;
}

