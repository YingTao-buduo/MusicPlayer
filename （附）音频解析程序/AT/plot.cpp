#include "plot.h"

/*************** 定义数字转 LPWSTR 字符型函数 ****************/
void num2WSTR(double x, wchar_t*& buffer);

/******************* 以下是相关方法的具体实现 **************************/
// 数字转 LPWSTR 字符
void num2WSTR(double x, wchar_t*& buffer)
{
	// NUM TO WSS TO WSTR
	std::wstringstream ss;
	ss << x;
	size_t size = ss.str().length();
	buffer = new wchar_t[size + 1];
	ss >> buffer;
	buffer[size] = 0;
}

// DynaWin 构造函数
DynaWin::DynaWin(double XLIM, double YLIM, unsigned short xSegment, unsigned short ySegment, int xResolution)
{
	this->XLIM = XLIM;
	this->YLIM = YLIM;
	this->xSegment = xSegment;
	this->ySegment = ySegment;
	this->xResolution = xResolution;
	this->DynaQue = new double[xResolution + 1];
	this->xAxis = new AxisX[xSegment + 1];
}

//背景初始化
void DynaWin::InitBackGround()
{
	// 定义画布
	initgraph(1100, 400, 1);
	// 初始化画笔
	setlinecolor(RED);
	setlinestyle(PS_SOLID | PS_ENDCAP_ROUND | PS_JOIN_ROUND, 3);
	// 定义坐标原点以及方向
	setorigin(CENTERX, CENTERY);
	setaspectratio(1, -1);
	// 绘制静态窗口
	rectangle(0, 150, 1000, -150);
	line(0, 0, 1000, 0);
	// 标注说明
	setbkmode(TRANSPARENT);
	settextcolor(YELLOW);
	setaspectratio(1, 1);// 纠正字体倒置
	settextstyle(30, 0, L"宋体");
	outtextxy(450, -185, L"wave");
	settextstyle(10, 0, L"宋体");
	outtextxy(870, 180, L"Version:");
	// 绘制刻度
	unsigned short yVertex = 2 * ySegment + 1;
	double yUnit = YLIM / ySegment;
	setbkmode(TRANSPARENT);
	settextcolor(YELLOW);
	settextstyle(15, 0, L"10");
	setlinestyle(PS_DASH, 1);				// 虚线
	// 水平刻度线
	for (int i = 1; i <= yVertex; ++i)
	{
		// 表明 y 刻度值
		double label = YLIM - (i - 1) * yUnit;
		wchar_t* buffer;
		num2WSTR(label, buffer);
		outtextxy(-30, (int)((i - ySegment - 1) * (ROWS / ySegment)) - 10, buffer);
		delete[] buffer;
		buffer = (wchar_t*)NULL;

		// 画出虚线
		line(0, (int)((i - ySegment - 1) * (ROWS / ySegment)), 1000, (int)((i - ySegment - 1) * (ROWS / ySegment)));
	}
	setaspectratio(1, -1);					// 恢复坐标方向
	canvas = GetWorkingImage();				// 画板地址
	getimage(&local, -50, -160, 1100, 320);	// 保存局部背景
}


// 更新窗
void DynaWin::UpateWin(double y)	// 更新 win
{
	++DynaNum;										// 信息个数
	UpdateAxisX();									// 更新AxisX

	if (DynaNum <= xResolution + 1)					// 队列未满
		DynaQue[DynaNum - 1] = y;

	else	// 队列已满
	{
		for (int i = 0; i <= xResolution - 1; ++i)	// 出队列
		{
			DynaQue[i] = DynaQue[i + 1];			// 向左移位
		}
		DynaQue[xResolution] = y;					// 尾部添加新元素
	}
}

// 绘制窗
void DynaWin::ShowWin()
{
	// 选定画板
	SetWorkingImage(canvas);

	// 背景覆盖	
	putimage(-50, -160, &local);

	// (1) 显示 AxisX
	setlinecolor(RED);
	setlinestyle(PS_DASH, 2);
	for (int j = 0; j <= xSegment - 1; ++j)
	{
		// 绘制虚线
		line((int)xAxis[j].index, -150, (int)xAxis[j].index, 150);
		// 绘制标注
		setaspectratio(1, 1);
		setbkmode(TRANSPARENT);
		settextcolor(YELLOW);
		settextstyle(15, 0, L"10");
		double label = xAxis[j].label;
		wchar_t* wstr;
		num2WSTR(label, wstr);
		outtextxy((int)xAxis[j].index - 10, 0, wstr);
		delete[] wstr;
		wstr = NULL;
		setaspectratio(1, -1);						// 回复坐标系
	}

	// (2) 显示 DynaQue
	setlinecolor(WHITE);
	setlinestyle(PS_SOLID | PS_ENDCAP_ROUND | PS_JOIN_ROUND, 2);
	if (DynaNum <= xResolution)						// 队列未满
	{
		for (int i = 0; i <= DynaNum - 2; ++i)		// 0 to DynaNum-1 (DynaNum 个)
		{
			line((int)(i * COLS / xResolution), (int)(DynaQue[i] / YLIM * ROWS), (int)((i + 1) * COLS / xResolution), (int)(DynaQue[i + 1] / YLIM * ROWS));
		}
	}
	else	// 队列已满
	{
		for (int i = 0; i <= xResolution - 1; ++i)	// 0 to xResolution (xResolution + 1 个) 即显示全部 DynaQue
		{
			line((int)(i * COLS / xResolution), (int)(DynaQue[i] / YLIM * ROWS), (int)((i + 1) * COLS / xResolution), (int)(DynaQue[i + 1] / YLIM * ROWS));
		}
	}
}

// 更新坐标
void DynaWin::UpdateAxisX()
{
	if (DynaNum <= xResolution)										// 队列未满
		for (int i = 0; i <= xSegment - 1; ++i)
		{
			xAxis[i].index = (i + 1) * COLS / xSegment;
			xAxis[i].label = (i + 1) * XLIM / xSegment;
		}
	else	// 队列已满
	{

		for (int i = 0; i <= xSegment - 1; ++i)						// 向左移动
		{
			xAxis[i].index -= COLS / xResolution;
		}
		if (xAxis[0].index <= 0)									// AxisX 动态更新
		{
			int j;
			for (j = 0; j <= xSegment - 2; ++j)						// 队列更替
			{
				xAxis[j].index = xAxis[j + 1].index;
				xAxis[j].label = xAxis[j + 1].label;
			}
			xAxis[j].index = xAxis[j - 1].index + COLS / xSegment;	// 尾部添加新元素
			xAxis[j].label = xAxis[j - 1].label + XLIM / xSegment;
		}
	}
}