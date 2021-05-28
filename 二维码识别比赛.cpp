#include<iostream>
#include<opencv.hpp>
#include<vector>   
#include<string>

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
	int x = 1;
	while (x)
	{
		VideoCapture video(0);
		if (!video.isOpened())
		{
			cout << "摄像头打开失败" << endl;
			return -1;
		}

		while (1)
		{
			Mat frame;
			video >> frame;
			imshow("frame", frame);
			if (waitKey(20) == 'q')   //延时20ms,获取用户是否按键的情况，如果按下q，会推出程序 
				break;
		}
		Mat frame;
		video >> frame;
		//配置保存格式
		vector<int>compression_params;
		compression_params.push_back(IMWRITE_PNG_COMPRESSION);
		compression_params.push_back(9);
		bool result = imwrite("D:/opencvpicture/test.png", frame, compression_params);
		if (result)
		{
			cout << "图片保存成功" << endl;
		}
		//解码二维码
		Mat img = imread("D:/opencvpicture/test.png");
		if (img.empty())
		{
			cout << "二维码信息错误" << endl;
			return -1;
		}
		Mat gray, src;
		cvtColor(img, gray, COLOR_BGR2GRAY); //转换为灰度图片
		QRCodeDetector qrcode;
		string web; //接收二维码的网址
		vector<Point> point; //二维码顶点坐标
		web = qrcode.detectAndDecode(gray, point, src); //解码
		if (web.empty())
		{
			cout << "识别失败 " << endl;
		}
		else
		{
			cout << web << endl; //打印网址
		}
		cout << "是否继续检测" << endl;
		cin >> x;
	}
	system("pause");
	destroyAllWindows();
	return 0;
}