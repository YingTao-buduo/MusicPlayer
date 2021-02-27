// 2DProjectConsole.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
#include <glut.h>
#include "mine.h"


HANDLE L = NULL; //歌词处理线程句柄
HANDLE P = NULL; //歌曲播放线程句柄
int ww, hh;     // for display window width and height
string lyric;	//当前歌词
int m2l = 0;    //计算歌词显示位置的参数
int musicState = 1;	//目前音乐状态（0：暂停，1：播放中）
int key;

void Myinit(void);
void Reshape(int w, int h);
void MyMouse(int button, int state, int x, int y);
void MyTime(int value);
void Display(void);

void ShowLyric();
DWORD WINAPI PutLyric(LPVOID lpParameter);
DWORD WINAPI PlayAudio(LPVOID lpParameter);

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);  //初始化GLUT库；
	glutInitWindowSize(800, 600);  //设置显示窗口大小
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  //设置显示模式；（注意双缓冲）
	glutCreateWindow("节奏播放器"); // 创建显示窗口
	Myinit();
	glutTimerFunc(520, MyTime, 10);
	glutDisplayFunc(Display);  //注册显示回调函数
	glutMouseFunc(MyMouse);    //注册鼠标按钮回调函数
	glutReshapeFunc(Reshape);  //注册窗口改变回调函数
	
	int subMenuID = glutCreateMenu(MySubMenuOne);
	glutAddMenuEntry("one", 1);
	int menuID = glutCreateMenu(MyMainMenu);
	glutAddMenuEntry("two", 2);
	glutAddMenuEntry("three", 3);
	glutAddSubMenu("sub", subMenuID);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	L = CreateThread(NULL, 0, PutLyric, NULL, 0, NULL); //创建新线程，处理歌词
	P = CreateThread(NULL, 0, PlayAudio, NULL, 0, NULL);//创建新线程，播放音乐
	glutMainLoop();  //进入事件处理循环
	return 0;
}

void Myinit(void)
{
	InitUI(musicState); //初始化界面
}

//渲染绘制子程序--------------------------------------------------------------------------
void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);   //刷新颜色缓冲区；
	InitUI(musicState);
	ShowLyric();		//显示歌词
	glutSwapBuffers();  //双缓冲的刷新模式；
}

//-----------------------------------------------
void Reshape(int w, int h)  //窗口改变时自动获取显示窗口的宽w和高h
{
	glMatrixMode(GL_PROJECTION);  //投影矩阵模式
	glLoadIdentity();     //矩阵堆栈清空
	glViewport(0, 0, w, h);  //设置视区大小
	gluOrtho2D(0, w, 0, h);   //设置裁剪窗口大小
	ww = w;
	hh = h;
}

//鼠标按钮响应事件..
void MyMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){  // 暂停按钮事件
		if ((x > 380) && (x < 420) && (hh - y > 30) && (hh - y < 70)) {
			if (musicState == 1) {
				SuspendThread(L);
				musicState = 0;
			}
			else {
				ResumeThread(L);
				musicState = 1;
			}
		}
	}
}


void MyTime(int value)
{
	if(musicState) glutPostRedisplay();
	glutTimerFunc(520, MyTime, 10);
}

//显示歌词
void ShowLyric() {
	glColor3f(0, 1, 0);
	SelectFont(30, GB2312_CHARSET, "楷体_GB2312");
	glRasterPos2f(400 - m2l * 8, 120);
	DrawCNString(lyric.data());
}

//处理歌词
DWORD WINAPI PutLyric(LPVOID lpParameter) {
	vector<Lyric> lyricData = Ready();
	for (int i = 0; i < lyricData.size(); i++) {
		if (i > 0)
			Sleep(lyricData[i].time - lyricData[i - 1].time);
		lyric = lyricData[i].text;
		m2l = lyricData[i].text.size();
	}
	return 0;
}

//新线程播放音乐
DWORD WINAPI PlayAudio(LPVOID lpParameter) {
	mciSendString(L"open testmp3.mp3 alias aa", NULL, 0, NULL);//alias后面为设备名称
	mciSendString(L"play aa", NULL, 0, NULL);//wait表示播放完毕之后返回
	while (true) {
		if (musicState == 0) {
			mciSendString(L"pause aa", NULL, 0, NULL);
			key = 1;
		}
		if (musicState == 1 && key) {
			mciSendString(L"play aa", NULL, 0, NULL);
			key = 0;
		}
	}
	mciSendString(L"close aa", NULL, 0, NULL);
	return 0;
}