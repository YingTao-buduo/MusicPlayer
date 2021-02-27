#include <iostream>
#include <easyx.h>
#include <conio.h>
#include <sstream>
#include <string>

/*************** 定义动态 X 坐标结构体 ************************/
struct AxisX {
	double index; // 坐标
	double label; // 标签
};

/*************** 定义类：动态窗口 ****************************************************************************/
// 说明：动态窗口实现绘制实时信号的原理，其实是将当前信号送入定长队列 DynaQue,
//      并在每一帧进行绘制，其中队列长度由分辨率决定。最大分辨率应该 <= COLS
//      例如：DynaQue[xResolution+1] = {DynaQue[0],DynaQue[1,..,DynaQue[xRelolution]}，其中 DynaQue[N] 为最近信号
//            那么相邻点距离为：COLS/xResolution
// 当然 X 坐标也需要动态更新，同理类中也定义了队列 xAxis 对坐标进行同步更新
//      例如：xAxis[xSegment+1] = {xAxis[0],xAxis[1],..,xAxis[xSegment]}，其中 xAxis[N] 保存的是 AxisX 数据
//             那么相邻刻度距离：COLS/xSegment
/***************************************************************************************************************/
class DynaWin {
public:
	DynaWin(double XLIM, double YLIM, unsigned short xSegment, unsigned short ySegment, int xResolution);	// 构造器
	void UpateWin(double y);	// 更新窗口
	void ShowWin();				// 绘制窗口
	void InitBackGround();		// 背景初始化（静态窗口）

private:
	const int CENTERX = 50;		// 定义原点
	const int CENTERY = 200;
	const int ROWS = 150;		// 定义边长
	const int COLS = 1000;

	double XLIM;				// 定义 X 轴区间
	double YLIM;				// 定义 Y 轴区间
	unsigned short xSegment;	// 定义坐标的刻度
	unsigned short ySegment;
	int xResolution;			// x轴分辨率(决定 Dynaque 的长度)
	int DynaNum = 0;			// 已读信号个数
	double* DynaQue;			// 实时信号队列
	AxisX* xAxis;				// 实时坐标队列
	IMAGE* canvas;				// 当前画布
	IMAGE local;				// 局部背景

	void UpdateAxisX();			// 更新坐标

};