#include <opencv2/opencv.hpp>
#include <opencv2\imgproc\imgproc.hpp> // Gaussian Blur
#include "opencv2\core\core.hpp"        // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2\highgui\highgui.hpp> // OpenCV window I/O
#include <iostream> // for standard I/O
#include <string>   // for strings
#include <iomanip>  // for controlling float print precision
#include <sstream>  // string to number conversion
#include <opencv2/highgui/highgui_c.h>

using namespace std;
using namespace cv;
bool rButtonDown = false;
bool lButtonDown = false;
float varianceSquared = 0;
int scribbleRadius = 10;
const char* imagename = "1.etc"; //�˴�ΪͼƬ·��
Mat DRAWImage = imread(imagename, 1);

static void onMouse(int event, int x, int y, int, void*)
{
	cout << "On Mouse: (" << x << "," << y << ")" << endl;
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		lButtonDown = true;
	}
	else if (event == CV_EVENT_RBUTTONDOWN)
	{
		rButtonDown = true;
	}
	else if (event == CV_EVENT_LBUTTONUP)
	{
		lButtonDown = false;
	}
	else if (event == CV_EVENT_RBUTTONUP)
	{
		rButtonDown = false;
	}
	else if (event == CV_EVENT_MOUSEMOVE)
	{
		if (rButtonDown)
		{
			circle(DRAWImage, Point(x, y), scribbleRadius, CV_RGB(0, 0, 255), -1);
		}
		else if (lButtonDown)
		{
			circle(DRAWImage, Point(x, y), scribbleRadius, CV_RGB(255, 0, 0), -1);
		}
	}
	imshow("draw", DRAWImage);
}

int main(int argc, char* argv[])
{
	

	//���ļ��ж���ͼ��
	Mat img = imread(imagename, 1);

	//�������ͼ��ʧ��
	if (img.empty())
	{
		fprintf(stderr, "Can not load image %s\n", imagename);
		return -1;
	}
	//��ʾͼ��
	namedWindow("ԭͼ��", WINDOW_AUTOSIZE);
	imshow("ԭͼ��", img);

	//��ͼ��ת��ΪCIE-LAB������COLOR_ǰ׺
	Mat LABImage;
	cvtColor(img, LABImage, COLOR_BGR2Lab);    //��ͼ��ת��ΪCIE-LABͼ
	namedWindow("CIE-LAB", WINDOW_AUTOSIZE);
	imshow("CIE-LAB", LABImage);

	//��ͼ��ת��ΪYUV������COLOR_ǰ׺
	Mat YUVImage;
	cvtColor(img, YUVImage, COLOR_BGR2YUV);    //��ͼ��ת��ΪYUVͼ
	namedWindow("YUV", WINDOW_AUTOSIZE);
	imshow("YUV", YUVImage);

	//��ͼ��ת��ΪHSV������COLOR_ǰ׺
	Mat HSVImage;
	cvtColor(img, HSVImage, COLOR_BGR2HSV);    //��ͼ��ת��ΪHSVͼ
	namedWindow("HSV", WINDOW_AUTOSIZE);
	imshow("HSV", HSVImage);

	//Ϳѻ
	namedWindow("draw");
	imshow("draw", DRAWImage);

	setMouseCallback("draw", onMouse, 0);

	//�˺����ȴ�������������s���ͱ���

	char key = waitKey(0);
	if (key == 's') { imwrite("C:\\Users\\11749\\Desktop\\1draw.jpg", DRAWImage); cout << "successed"; }


	//���ͼƬ�Ļ�����Ϣ
	cout << "ԭͼ���Ϊ��" << img.cols << "\t�߶�Ϊ��" << img.rows << "\tͨ����Ϊ��" << img.channels() << endl;

	//��Ƶ
	VideoCapture cap;
	Mat frame,gray;
	frame= cap.open("sp.mp4");
	if (!cap.isOpened())
		printf("open failed");
	Size size = Size(cap.get(CAP_PROP_FRAME_WIDTH), cap.get(CAP_PROP_FRAME_HEIGHT));
	VideoWriter writer;
	writer.open("spcopy.mp4", CAP_OPENCV_MJPEG, 20, size, false);
	if (!writer.isOpened()) {
		printf("failed");
	}
	while (cap.read(frame)) {
		cvtColor(frame,gray, COLOR_BGR2GRAY);
		Canny(gray, gray, 40, 100);
		imshow("gray", gray);
		writer.write(gray);//�ѻҶ�ͼд��ȥ�������д�õ���Ƶ��ԭ��Ƶ�ĻҶ���Ƶ
		waitKey(10);
	}
	waitKey(0);
	cap.release();
	
	return 0;
}
