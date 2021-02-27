#include "mine.h"
#include <glut.h>
#include <iostream>
#include <fstream>
#define random(a, b) (rand() % (b - a) + a)
using namespace std;

void MyMainMenu(int value) {

}
void MySubMenuOne(int value) {

}

//暂停按钮
void StopButton(int mx, int my) {
	int n = 30;
	int r = 20;
	glLineWidth(3.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < n; i++) {
		glVertex2f(mx + r * sin(2 * 3.14 / n * i), my + r * cos(2 * 3.14 / n * i));
	}
	glEnd();

	int l = 10;
	glRectf(mx - l, my - l, mx + l, my + l);
	glColor3f(0 / 255.0f, 0 / 255.0f, 0 / 255.0f);
	glLineWidth(5.0);
	glBegin(GL_LINES);
	glVertex2f(mx + 0, my + l);
	glVertex2f(mx + 0, my - l);
	glEnd();
}

//开始按钮
void StartButton(int mx, int my) {
	int n = 30;
	int r = 20;
	glLineWidth(3.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < n; i++) {
		glVertex2f(mx + r * sin(2 * 3.14 / n * i), my + r * cos(2 * 3.14 / n * i));
	}
	glEnd();

	int l = 13;
	glBegin(GL_TRIANGLES);
	glVertex2f(mx + l, my + 0);
	glVertex2f(mx - l / 2, my - l * cos(3.14 / 6));
	glVertex2f(mx - l / 2, my + l * cos(3.14 / 6));
	glEnd();
}

void Buttons(int mx, int my) {
	int l = 13;
	glColor3f(1, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(mx + l + 50, my + 0);
	glVertex2f(mx - l / 2 + 50, my - l * cos(3.14 / 6));
	glVertex2f(mx - l / 2 + 50, my + l * cos(3.14 / 6));
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(mx + l + 60, my + 0);
	glVertex2f(mx - l / 2 + 60, my - l * cos(3.14 / 6));
	glVertex2f(mx - l / 2 + 60, my + l * cos(3.14 / 6));
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex2f(mx - l - 50, my + 0);
	glVertex2f(mx + l / 2 - 50, my - l * cos(3.14 / 6));
	glVertex2f(mx + l / 2 - 50, my + l * cos(3.14 / 6));
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(mx - l - 60, my + 0);
	glVertex2f(mx + l / 2 - 60, my - l * cos(3.14 / 6));
	glVertex2f(mx + l / 2 - 60, my + l * cos(3.14 / 6));
	glEnd();

	glLineWidth(5.0);
	glBegin(GL_LINES);
	glVertex2f(680, 50);
	glVertex2f(750, 50);
	glEnd();
	glColor3f(1, 0.7, 0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 30; i++) {
		glVertex2f(750 + 7 * sin(2 * 3.14 / 30 * i), 50 + 7 * cos(2 * 3.14 / 30 * i));
	}
	glEnd();
}

//读取音乐节奏
vector<float> ReadData() {
	ifstream infile;
	vector<float> data;
	int temp;
	infile.open("data.txt", ios::in);
	if (!infile.is_open())
		cout << "Open file failure" << endl;
	while (!infile.eof())
	{
		infile >> temp;
		data.push_back(temp);
	}
	infile.close();
	cout << "Done!" << endl;
	return data;
}
int index = 0;
vector<float> dat = ReadData();


void StyleOne(int mx, int my) {
	int radius1 = random(50, 100);
	glColor3f(random(50, 100) / 255.0f, random(150, 250) / 255.0f, random(150, 250) / 255.0f);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 50; i++) {
		glVertex2f(mx - 250 + radius1 * sin(2 * 3.14 / 50 * i), mx - 30 + radius1 * cos(2 * 3.14 / 50 * i));
	}
	glEnd();
	int radius2 = random(50, 100);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 50; i++) {
		glVertex2f(mx + 250 + radius1 * sin(2 * 3.14 / 50 * i), mx - 30 + radius1 * cos(2 * 3.14 / 50 * i));
	}
	glEnd();
	int radius = random(100, 200);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 50; i++) {
		glVertex2f(mx + radius * sin(2 * 3.14 / 50 * i), mx - 30 + radius * cos(2 * 3.14 / 50 * i));
	}
	glEnd();
	

	int s = 22;
	float r[41] = { 0 };
	//random(5, 10);
	r[0] = (dat[index++] / 10000 - 100) * 5;
	for (int i = 2; i < 21; i += 2) {
		r[i] = r[0] - i;
		r[20 + i] = r[i];
	}
	for (int i = 1; i < 41; i += 2) {
		r[i] = random(1, 8);
	}
	glColor3f(random(150, 255) / 255.0f, random(50, 100) / 255.0f, random(0, 50) / 255.0f);
	glRectf(mx - 8 + s * (0), my - 10 * r[0], mx + 8 + s * (0), my + 10 * r[0]);
	glRectf(mx - 8 + s * (-1), my - 10 * r[21], mx + 8 + s * (-1), my + 10 * r[21]);
	glRectf(mx - 8 + s * (1), my - 10 * r[1], mx + 8 + s * (1), my + 10 * r[1]);
	glRectf(mx - 8 + s * (-2), my - 10 * r[22], mx + 8 + s * (-2), my + 10 * r[22]);
	glRectf(mx - 8 + s * (2), my - 10 * r[2], mx + 8 + s * (2), my + 10 * r[2]);
	glRectf(mx - 8 + s * (-3), my - 10 * r[23], mx + 8 + s * (-3), my + 10 * r[23]);
	glRectf(mx - 8 + s * (3), my - 10 * r[3], mx + 8 + s * (3), my + 10 * r[3]);
	glRectf(mx - 8 + s * (-4), my - 10 * r[24], mx + 8 + s * (-4), my + 10 * r[24]);
	glRectf(mx - 8 + s * (4), my - 10 * r[4], mx + 8 + s * (4), my + 10 * r[4]);
	glRectf(mx - 8 + s * (-5), my - 10 * r[25], mx + 8 + s * (-5), my + 10 * r[25]);
	glRectf(mx - 8 + s * (5), my - 10 * r[5], mx + 8 + s * (5), my + 10 * r[5]);
	glRectf(mx - 8 + s * (-6), my - 10 * r[26], mx + 8 + s * (-6), my + 10 * r[26]);
	glRectf(mx - 8 + s * (6), my - 10 * r[6], mx + 8 + s * (6), my + 10 * r[6]);
	glRectf(mx - 8 + s * (-7), my - 10 * r[27], mx + 8 + s * (-7), my + 10 * r[27]);
	glRectf(mx - 8 + s * (7), my - 10 * r[7], mx + 8 + s * (7), my + 10 * r[7]);
	glRectf(mx - 8 + s * (-8), my - 10 * r[28], mx + 8 + s * (-8), my + 10 * r[28]);
	glRectf(mx - 8 + s * (8), my - 10 * r[8], mx + 8 + s * (8), my + 10 * r[8]);
	glRectf(mx - 8 + s * (-9), my - 10 * r[29], mx + 8 + s * (-9), my + 10 * r[29]);
	glRectf(mx - 8 + s * (9), my - 10 * r[9], mx + 8 + s * (9), my + 10 * r[9]);
	glRectf(mx - 8 + s * (-10), my - 10 * r[30], mx + 8 + s * (-10), my + 10 * r[30]);
	glRectf(mx - 8 + s * (10), my - 10 * r[10], mx + 8 + s * (10), my + 10 * r[10]);
	glRectf(mx - 8 + s * (-11), my - 10 * r[31], mx + 8 + s * (-11), my + 10 * r[31]);
	glRectf(mx - 8 + s * (11), my - 10 * r[11], mx + 8 + s * (11), my + 10 * r[11]);
	glRectf(mx - 8 + s * (-12), my - 10 * r[32], mx + 8 + s * (-12), my + 10 * r[32]);
	glRectf(mx - 8 + s * (12), my - 10 * r[12], mx + 8 + s * (12), my + 10 * r[12]);
	glRectf(mx - 8 + s * (-13), my - 10 * r[33], mx + 8 + s * (-13), my + 10 * r[33]);
	glRectf(mx - 8 + s * (13), my - 10 * r[13], mx + 8 + s * (13), my + 10 * r[13]);
	glRectf(mx - 8 + s * (-14), my - 10 * r[34], mx + 8 + s * (-14), my + 10 * r[34]);
	glRectf(mx - 8 + s * (14), my - 10 * r[14], mx + 8 + s * (14), my + 10 * r[14]);
	glRectf(mx - 8 + s * (-15), my - 10 * r[35], mx + 8 + s * (-15), my + 10 * r[35]);
	glRectf(mx - 8 + s * (15), my - 10 * r[15], mx + 8 + s * (15), my + 10 * r[15]);
	glRectf(mx - 8 + s * (-16), my - 10 * r[36], mx + 8 + s * (-16), my + 10 * r[36]);
	glRectf(mx - 8 + s * (16), my - 10 * r[16], mx + 8 + s * (16), my + 10 * r[16]);
	glRectf(mx - 8 + s * (-17), my - 10 * r[37], mx + 8 + s * (-17), my + 10 * r[37]);
	glRectf(mx - 8 + s * (17), my - 10 * r[17], mx + 8 + s * (17), my + 10 * r[17]);
	glRectf(mx - 8 + s * (-18), my - 10 * r[38], mx + 8 + s * (-18), my + 10 * r[38]);
	glRectf(mx - 8 + s * (18), my - 10 * r[18], mx + 8 + s * (18), my + 10 * r[18]);
	glRectf(mx - 8 + s * (-19), my - 10 * r[39], mx + 8 + s * (-19), my + 10 * r[39]);
	glRectf(mx - 8 + s * (19), my - 10 * r[19], mx + 8 + s * (19), my + 10 * r[19]);
	glRectf(mx - 8 + s * (-20), my - 10 * r[40], mx + 8 + s * (-20), my + 10 * r[40]);
	glRectf(mx - 8 + s * (20), my - 10 * r[20], mx + 8 + s * (20), my + 10 * r[20]);

	
}

void Name() {
	glColor3f(1, 0.7, 0);
	glRecti(0, 25, 200, 75);
	glColor3f(0, 0, 0);
	SelectFont(20, GB2312_CHARSET, "楷体_GB2312");
	glRasterPos2f(10, 45);
	DrawCNString("1801010019-郑文道");
}

//初始化界面
void InitUI(int musicState) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	StyleOne(400, 380);
	
	glColor3f(0.0, 0.0, 0.0);
	glRectf(0, 0, 800, 160);
	//下分割线
	glColor3f(250 / 255.0f, 0 / 255.0f, 0 / 255.0f);
	glLineWidth(5.0);
	glBegin(GL_LINES);
	glVertex2f(0, 100);
	glVertex2f(800, 100);
	glEnd();
	if(musicState == 1) StopButton(400, 50);
	if(musicState == 0) StartButton(400, 50);
	Buttons(400, 50);
	Name();
}

