#include "plot.h"

/*************** ��������ת LPWSTR �ַ��ͺ��� ****************/
void num2WSTR(double x, wchar_t*& buffer);

/******************* ��������ط����ľ���ʵ�� **************************/
// ����ת LPWSTR �ַ�
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

// DynaWin ���캯��
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

//������ʼ��
void DynaWin::InitBackGround()
{
	// ���廭��
	initgraph(1100, 400, 1);
	// ��ʼ������
	setlinecolor(RED);
	setlinestyle(PS_SOLID | PS_ENDCAP_ROUND | PS_JOIN_ROUND, 3);
	// ��������ԭ���Լ�����
	setorigin(CENTERX, CENTERY);
	setaspectratio(1, -1);
	// ���ƾ�̬����
	rectangle(0, 150, 1000, -150);
	line(0, 0, 1000, 0);
	// ��ע˵��
	setbkmode(TRANSPARENT);
	settextcolor(YELLOW);
	setaspectratio(1, 1);// �������嵹��
	settextstyle(30, 0, L"����");
	outtextxy(450, -185, L"wave");
	settextstyle(10, 0, L"����");
	outtextxy(870, 180, L"Version:");
	// ���ƿ̶�
	unsigned short yVertex = 2 * ySegment + 1;
	double yUnit = YLIM / ySegment;
	setbkmode(TRANSPARENT);
	settextcolor(YELLOW);
	settextstyle(15, 0, L"10");
	setlinestyle(PS_DASH, 1);				// ����
	// ˮƽ�̶���
	for (int i = 1; i <= yVertex; ++i)
	{
		// ���� y �̶�ֵ
		double label = YLIM - (i - 1) * yUnit;
		wchar_t* buffer;
		num2WSTR(label, buffer);
		outtextxy(-30, (int)((i - ySegment - 1) * (ROWS / ySegment)) - 10, buffer);
		delete[] buffer;
		buffer = (wchar_t*)NULL;

		// ��������
		line(0, (int)((i - ySegment - 1) * (ROWS / ySegment)), 1000, (int)((i - ySegment - 1) * (ROWS / ySegment)));
	}
	setaspectratio(1, -1);					// �ָ����귽��
	canvas = GetWorkingImage();				// �����ַ
	getimage(&local, -50, -160, 1100, 320);	// ����ֲ�����
}


// ���´�
void DynaWin::UpateWin(double y)	// ���� win
{
	++DynaNum;										// ��Ϣ����
	UpdateAxisX();									// ����AxisX

	if (DynaNum <= xResolution + 1)					// ����δ��
		DynaQue[DynaNum - 1] = y;

	else	// ��������
	{
		for (int i = 0; i <= xResolution - 1; ++i)	// ������
		{
			DynaQue[i] = DynaQue[i + 1];			// ������λ
		}
		DynaQue[xResolution] = y;					// β�������Ԫ��
	}
}

// ���ƴ�
void DynaWin::ShowWin()
{
	// ѡ������
	SetWorkingImage(canvas);

	// ��������	
	putimage(-50, -160, &local);

	// (1) ��ʾ AxisX
	setlinecolor(RED);
	setlinestyle(PS_DASH, 2);
	for (int j = 0; j <= xSegment - 1; ++j)
	{
		// ��������
		line((int)xAxis[j].index, -150, (int)xAxis[j].index, 150);
		// ���Ʊ�ע
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
		setaspectratio(1, -1);						// �ظ�����ϵ
	}

	// (2) ��ʾ DynaQue
	setlinecolor(WHITE);
	setlinestyle(PS_SOLID | PS_ENDCAP_ROUND | PS_JOIN_ROUND, 2);
	if (DynaNum <= xResolution)						// ����δ��
	{
		for (int i = 0; i <= DynaNum - 2; ++i)		// 0 to DynaNum-1 (DynaNum ��)
		{
			line((int)(i * COLS / xResolution), (int)(DynaQue[i] / YLIM * ROWS), (int)((i + 1) * COLS / xResolution), (int)(DynaQue[i + 1] / YLIM * ROWS));
		}
	}
	else	// ��������
	{
		for (int i = 0; i <= xResolution - 1; ++i)	// 0 to xResolution (xResolution + 1 ��) ����ʾȫ�� DynaQue
		{
			line((int)(i * COLS / xResolution), (int)(DynaQue[i] / YLIM * ROWS), (int)((i + 1) * COLS / xResolution), (int)(DynaQue[i + 1] / YLIM * ROWS));
		}
	}
}

// ��������
void DynaWin::UpdateAxisX()
{
	if (DynaNum <= xResolution)										// ����δ��
		for (int i = 0; i <= xSegment - 1; ++i)
		{
			xAxis[i].index = (i + 1) * COLS / xSegment;
			xAxis[i].label = (i + 1) * XLIM / xSegment;
		}
	else	// ��������
	{

		for (int i = 0; i <= xSegment - 1; ++i)						// �����ƶ�
		{
			xAxis[i].index -= COLS / xResolution;
		}
		if (xAxis[0].index <= 0)									// AxisX ��̬����
		{
			int j;
			for (j = 0; j <= xSegment - 2; ++j)						// ���и���
			{
				xAxis[j].index = xAxis[j + 1].index;
				xAxis[j].label = xAxis[j + 1].label;
			}
			xAxis[j].index = xAxis[j - 1].index + COLS / xSegment;	// β�������Ԫ��
			xAxis[j].label = xAxis[j - 1].label + XLIM / xSegment;
		}
	}
}