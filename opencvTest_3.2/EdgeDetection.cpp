#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

//------------------------------------
//	ȫ�ֱ�������
//------------------------------------
// ԭͼ���Ҷ�ͼ��Ŀ��ͼ
Mat g_srcImage, g_grayImage, g_dstImage;

// Canny��Ե�����ر���
Mat g_cannyDetectedEdges;
int g_cannyLowThreshold = 1;  // TrackBarλ�ò���

//------------------------------------
//	ȫ�ֺ�������
//------------------------------------
static void on_Canny(int, void*);  // Canny��Ե��ⴰ�ڹ������Ļص�����

//------------------------------------
//	������
//------------------------------------
int main(int argc, char* argv[])
{
	// �ı�console������ɫ
	system("color 2F");

	// ����ԭͼ
	g_srcImage = imread("1.jpg");
	if (!g_srcImage.data)
	{
		printf("��ȡԭͼ����\n");
		return false;
	}

	// ��ʾԭͼ
	namedWindow("[ԭʼͼ]", CV_WINDOW_NORMAL);
	imshow("[ԭʼͼ]", g_srcImage);

	// ������ src ͬ���ͺʹ�С�ľ��� dst
	g_dstImage.create(g_srcImage.size(), g_srcImage.type());

	// ��ԭͼת��Ϊ�Ҷ�ͼ
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);

	// ������ʾ����
	namedWindow("[Ч��ͼ]Canny��Ե���", WINDOW_AUTOSIZE);

	// ���� trackbar
	createTrackbar("����ֵ��", "[Ч��ͼ]Canny��Ե���", &g_cannyLowThreshold, 120, on_Canny);

	// ���ûص�����
	on_Canny(0, 0);

	// ��ѯ��ȡ������Ϣ��������Q�������˳�
	while((char(waitKey(1))) != 'q') { }

	return 0;
}

//------------------------------------
//	on_Canny()����
//------------------------------------
void on_Canny(int, void*)
{
	// ģ����������
	//blur(g_grayImage, g_cannyDetectedEdges, Size(3, 3));
	GaussianBlur(g_grayImage, g_cannyDetectedEdges, Size(3, 3), 0, 0, BORDER_DEFAULT);  // ��˹ģ������

	// Canny����
	Canny(g_cannyDetectedEdges, g_cannyDetectedEdges, g_cannyLowThreshold, g_cannyLowThreshold * 3, 3);

	// �� dst �ڵ�����Ԫ������Ϊ0
	g_dstImage = Scalar::all(0);

	// ʹ��Canny��������ı�Եͼ g_cannyDetectedEdges ��Ϊ���룬����ԭͼ src ������Ŀ��ͼ dst ��
	g_srcImage.copyTo(g_dstImage, g_cannyDetectedEdges);

	// ��ʾЧ��ͼ
	imshow("[Ч��ͼ]Canny��Ե���", g_dstImage);
}