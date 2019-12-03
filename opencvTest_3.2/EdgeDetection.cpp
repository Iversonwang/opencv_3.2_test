#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

//------------------------------------
//	全局变量声明
//------------------------------------
// 原图，灰度图，目标图
Mat g_srcImage, g_grayImage, g_dstImage;

// Canny边缘检测相关变量
Mat g_cannyDetectedEdges;
int g_cannyLowThreshold = 1;  // TrackBar位置参数

//------------------------------------
//	全局函数声明
//------------------------------------
static void on_Canny(int, void*);  // Canny边缘检测窗口滚动条的回调函数

//------------------------------------
//	主函数
//------------------------------------
int main(int argc, char* argv[])
{
	// 改变console字体颜色
	system("color 2F");

	// 载入原图
	g_srcImage = imread("1.jpg");
	if (!g_srcImage.data)
	{
		printf("读取原图错误！\n");
		return false;
	}

	// 显示原图
	namedWindow("[原始图]", CV_WINDOW_NORMAL);
	imshow("[原始图]", g_srcImage);

	// 创建与 src 同类型和大小的矩阵 dst
	g_dstImage.create(g_srcImage.size(), g_srcImage.type());

	// 将原图转换为灰度图
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);

	// 创建显示窗口
	namedWindow("[效果图]Canny边缘检测", WINDOW_AUTOSIZE);

	// 创建 trackbar
	createTrackbar("参数值：", "[效果图]Canny边缘检测", &g_cannyLowThreshold, 120, on_Canny);

	// 调用回调函数
	on_Canny(0, 0);

	// 轮询获取按键信息，若按下Q，程序退出
	while((char(waitKey(1))) != 'q') { }

	return 0;
}

//------------------------------------
//	on_Canny()函数
//------------------------------------
void on_Canny(int, void*)
{
	// 模糊函数降噪
	//blur(g_grayImage, g_cannyDetectedEdges, Size(3, 3));
	GaussianBlur(g_grayImage, g_cannyDetectedEdges, Size(3, 3), 0, 0, BORDER_DEFAULT);  // 高斯模糊处理

	// Canny算子
	Canny(g_cannyDetectedEdges, g_cannyDetectedEdges, g_cannyLowThreshold, g_cannyLowThreshold * 3, 3);

	// 把 dst 内的所有元素设置为0
	g_dstImage = Scalar::all(0);

	// 使用Canny算子输出的边缘图 g_cannyDetectedEdges 作为掩码，来将原图 src 拷贝到目标图 dst 中
	g_srcImage.copyTo(g_dstImage, g_cannyDetectedEdges);

	// 显示效果图
	imshow("[效果图]Canny边缘检测", g_dstImage);
}