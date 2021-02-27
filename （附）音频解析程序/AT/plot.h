#include <iostream>
#include <easyx.h>
#include <conio.h>
#include <sstream>
#include <string>

/*************** ���嶯̬ X ����ṹ�� ************************/
struct AxisX {
	double index; // ����
	double label; // ��ǩ
};

/*************** �����ࣺ��̬���� ****************************************************************************/
// ˵������̬����ʵ�ֻ���ʵʱ�źŵ�ԭ����ʵ�ǽ���ǰ�ź����붨������ DynaQue,
//      ����ÿһ֡���л��ƣ����ж��г����ɷֱ��ʾ��������ֱ���Ӧ�� <= COLS
//      ���磺DynaQue[xResolution+1] = {DynaQue[0],DynaQue[1,..,DynaQue[xRelolution]}������ DynaQue[N] Ϊ����ź�
//            ��ô���ڵ����Ϊ��COLS/xResolution
// ��Ȼ X ����Ҳ��Ҫ��̬���£�ͬ������Ҳ�����˶��� xAxis ���������ͬ������
//      ���磺xAxis[xSegment+1] = {xAxis[0],xAxis[1],..,xAxis[xSegment]}������ xAxis[N] ������� AxisX ����
//             ��ô���ڿ̶Ⱦ��룺COLS/xSegment
/***************************************************************************************************************/
class DynaWin {
public:
	DynaWin(double XLIM, double YLIM, unsigned short xSegment, unsigned short ySegment, int xResolution);	// ������
	void UpateWin(double y);	// ���´���
	void ShowWin();				// ���ƴ���
	void InitBackGround();		// ������ʼ������̬���ڣ�

private:
	const int CENTERX = 50;		// ����ԭ��
	const int CENTERY = 200;
	const int ROWS = 150;		// ����߳�
	const int COLS = 1000;

	double XLIM;				// ���� X ������
	double YLIM;				// ���� Y ������
	unsigned short xSegment;	// ��������Ŀ̶�
	unsigned short ySegment;
	int xResolution;			// x��ֱ���(���� Dynaque �ĳ���)
	int DynaNum = 0;			// �Ѷ��źŸ���
	double* DynaQue;			// ʵʱ�źŶ���
	AxisX* xAxis;				// ʵʱ�������
	IMAGE* canvas;				// ��ǰ����
	IMAGE local;				// �ֲ�����

	void UpdateAxisX();			// ��������

};