#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include<string>

using namespace cv;
using namespace std;
//绘制轮廓函数
void drawapp(Mat result, Mat img2)
{
	for (int i = 0; i < result.rows; i++)
	{
		//最后一个坐标点与第一个坐标点连接
		if (i == result.rows - 1)
		{
			Vec2i point1 = result.at<Vec2i>(i);
			Vec2i point2 = result.at<Vec2i>(0);
			line(img2, point1, point2, Scalar(0, 0, 255), 2, 8, 0);
			break;
		}
		Vec2i point1 = result.at<Vec2i>(i);
		Vec2i point2 = result.at<Vec2i>(i + 1);
		line(img2, point1, point2, Scalar(0, 0, 255), 2, 8, 0);
	}
}

int main111111(int argc, const char *argv[])
{
    int x = 1;
	while (x)
	{

		//!!!!
		int champion;
		std::cout << "选择检测模式" << endl;
		std::cin >> champion;
		////调用摄像头
		VideoCapture video(1);
		if (!video.isOpened())
		{
			std::cout << "摄像头打开失败" << endl;
			return -1;
		}
		////实时显示摄像头
		while (1)
		{
			Mat frame;
			video >> frame;
			cv::imshow("frame", frame);
			if (cv::waitKey(20) == 'q')   //延时20ms,获取用户是否按键的情况，如果按下q，会推出程序 
				break;                //在20ms时间内，如果有按键则会返回键的ASCII值
		}
		Mat frame;
		video >> frame;
		vector<int>compression_params;
		compression_params.push_back(IMWRITE_PNG_COMPRESSION);
		compression_params.push_back(9);
		bool result = imwrite("D:/opencvpicture/9999.png", frame, compression_params);
		if (result)
		{
			std::cout << "图片保存成功" << endl;
		}
		video.release();
		

		Mat img = imread("D:/opencvpicture/9999.png");
		if (img.empty()) 
		{ 
			std::cout << "请确认图像文件名称是否正确" << endl;	
		    return -1;
		}
		int  triangle = 0;
		int  rectangle = 0;
		int  poly = 0;
		int  star = 0;
		int  circlen = 0;
		Mat gray;
		Mat lubo;
		//中值滤波
		//medianBlur(img, lubo, 3);x
		//转灰度
		cvtColor(img, gray, COLOR_BGR2GRAY);
		GaussianBlur(gray, lubo, Size(9, 9), 2, 2);//高斯滤波
		cv::imshow("lubo", lubo);

		// 边缘检测
		Mat canny;
		Canny(lubo, canny, 80, 160, 3, false);
		//二值化图像
		threshold(lubo, canny, 170, 255, THRESH_BINARY);
		cv::imshow("canny", canny);

	switch (champion)
	{ 
		case 1:	
		{
			// 轮廓发现与绘制
			vector<vector<Point>> contours;
			vector<Vec4i> hierarchy;
			findContours(canny, contours, hierarchy, 0, 2, Point());
			//第二个参数：contours，定义为“vector<vector<Point>> contours”，
			//是一个向量，并且是一个双重向量，向量
			//内每个元素保存了一组由连续的Point点构成的点的集合的向量，每一组Point点集就是一个轮廓

			//绘制多边形
			for (int t = 0; t < contours.size(); t++)
			{	//利用轮廓数进行循环标准
				//进一步降噪，将面积小于400的去掉
				double area = contourArea(contours[t]);
				if (area < 400)   continue;
			   //用最小外接矩形求取轮廓中心
				RotatedRect rrect = minAreaRect(contours[t]);
				Point2f center = rrect.center;

				Mat result;
				approxPolyDP(contours[t], result, 4, true);  //多边形拟合
				drawapp(result, img);
				std::cout << "corners : " << result.rows << endl;
				//判断形状和绘制轮廓
				if (result.rows == 3)
				{
					triangle++;
				}
				if (result.rows == 4)
				{
					rectangle++;
				}
				if (result.rows >= 5 && result.rows <= 6)
				{
					poly++;
				}
				if (result.rows > 8)
				{
					star++;
				}
			}
			break;
		}
		case 2:	
		{
			vector<Vec3f> circles;
			double dp = 2;        //原图分辨率和累加器分辨率的比值
			double minDist = 50;  //两个圆心之间的最小距离
			double	param1 = 100;  //Canny边缘检测的较大阈值
			double	param2 = 50;  //累加器阈值 最小投票数，越小，越多假的圆被检测出来
			int min_radius = 0;  //圆形半径的最小值
			int max_radius = 150;  //圆形半径的最大值
			HoughCircles(canny, circles, HOUGH_GRADIENT, dp, minDist, param1, param2,
				min_radius, max_radius);
			for (size_t i = 0; i < circles.size(); i++)
			{
				circlen++;
				//读取圆心
				Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
				//读取半径
				int radius = cvRound(circles[i][2]);
				//绘制圆心
				circle(img, center, 3, Scalar(0, 255, 0), -1, 8, 0);
				//绘制圆
				circle(img, center, radius, Scalar(0, 0, 255), 3, 8, 0);
			}
			break;

		}
	}
		//三角形
		string a = "triangle:";
		string b = to_string(triangle);
		string c = a + b;
		//矩形
		string d = "rectangle";
		string e = to_string(rectangle);
		string f = d + e;
		//五边形
		string g = "poly";
		string h = to_string(poly);
		string i = g + h;
		//星
		string j = "star";
		string k = to_string(star);
		string l = j + k;
		//圆
		string m = "circle";
		string n = to_string(circlen);
		string o = m + n;
		if (triangle > 0)
		{
			putText(img, c, Point(50, 50), 0, 1, Scalar(0, 255, 0), 5, 8);
		}
		if (rectangle > 0)
		{
			putText(img, f, Point(100, 100), 0, 1, Scalar(0, 255, 0), 5, 8);
		}
		if (poly > 0)
		{
			putText(img, i, Point(150,150), 0, 1, Scalar(0, 255, 0), 5, 8);
		}
		if (star > 0)
		{
			putText(img, l, Point(200, 200), 0, 1, Scalar(0, 255, 0), 5, 8);
		}
		if (circlen > 0)
		{
			putText(img, o, Point(250,250), 0, 1, Scalar(0, 255, 0), 5, 8);
		}
		namedWindow("result", WINDOW_FREERATIO);
		cv::imshow("result", img);
		cv::waitKey(0);
		//destroyAllWindows();
		video.release();
		std::cout << "是否继续检测" << endl;
		std::cin >> x;
	}
	return 0;
}