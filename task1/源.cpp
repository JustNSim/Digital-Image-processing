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
const char* imagename = "1.etc"; //此处为图片路径
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
	

	//从文件中读入图像
	Mat img = imread(imagename, 1);

	//如果读入图像失败
	if (img.empty())
	{
		fprintf(stderr, "Can not load image %s\n", imagename);
		return -1;
	}
	//显示图像
	namedWindow("原图像", WINDOW_AUTOSIZE);
	imshow("原图像", img);

	//将图像转换为CIE-LAB，采用COLOR_前缀
	Mat LABImage;
	cvtColor(img, LABImage, COLOR_BGR2Lab);    //将图像转换为CIE-LAB图
	namedWindow("CIE-LAB", WINDOW_AUTOSIZE);
	imshow("CIE-LAB", LABImage);

	//将图像转换为YUV，采用COLOR_前缀
	Mat YUVImage;
	cvtColor(img, YUVImage, COLOR_BGR2YUV);    //将图像转换为YUV图
	namedWindow("YUV", WINDOW_AUTOSIZE);
	imshow("YUV", YUVImage);

	//将图像转换为HSV，采用COLOR_前缀
	Mat HSVImage;
	cvtColor(img, HSVImage, COLOR_BGR2HSV);    //将图像转换为HSV图
	namedWindow("HSV", WINDOW_AUTOSIZE);
	imshow("HSV", HSVImage);

	//涂鸦
	namedWindow("draw");
	imshow("draw", DRAWImage);

	setMouseCallback("draw", onMouse, 0);

	//此函数等待按键，按键盘s键就保存

	char key = waitKey(0);
	if (key == 's') { imwrite("C:\\Users\\11749\\Desktop\\1draw.jpg", DRAWImage); cout << "successed"; }


	//输出图片的基本信息
	cout << "原图像宽为：" << img.cols << "\t高度为：" << img.rows << "\t通道数为：" << img.channels() << endl;

	//视频
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
		writer.write(gray);//把灰度图写进去，即最后写好的视频是原视频的灰度视频
		waitKey(10);
	}
	waitKey(0);
	cap.release();
	
	return 0;
}
