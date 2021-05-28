#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include<string>

using namespace cv;
using namespace std;
//������������
void drawapp(Mat result, Mat img2)
{
	for (int i = 0; i < result.rows; i++)
	{
		//���һ����������һ�����������
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
		std::cout << "ѡ����ģʽ" << endl;
		std::cin >> champion;
		////��������ͷ
		VideoCapture video(1);
		if (!video.isOpened())
		{
			std::cout << "����ͷ��ʧ��" << endl;
			return -1;
		}
		////ʵʱ��ʾ����ͷ
		while (1)
		{
			Mat frame;
			video >> frame;
			cv::imshow("frame", frame);
			if (cv::waitKey(20) == 'q')   //��ʱ20ms,��ȡ�û��Ƿ񰴼���������������q�����Ƴ����� 
				break;                //��20msʱ���ڣ�����а�����᷵�ؼ���ASCIIֵ
		}
		Mat frame;
		video >> frame;
		vector<int>compression_params;
		compression_params.push_back(IMWRITE_PNG_COMPRESSION);
		compression_params.push_back(9);
		bool result = imwrite("D:/opencvpicture/9999.png", frame, compression_params);
		if (result)
		{
			std::cout << "ͼƬ����ɹ�" << endl;
		}
		video.release();
		

		Mat img = imread("D:/opencvpicture/9999.png");
		if (img.empty()) 
		{ 
			std::cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;	
		    return -1;
		}
		int  triangle = 0;
		int  rectangle = 0;
		int  poly = 0;
		int  star = 0;
		int  circlen = 0;
		Mat gray;
		Mat lubo;
		//��ֵ�˲�
		//medianBlur(img, lubo, 3);x
		//ת�Ҷ�
		cvtColor(img, gray, COLOR_BGR2GRAY);
		GaussianBlur(gray, lubo, Size(9, 9), 2, 2);//��˹�˲�
		cv::imshow("lubo", lubo);

		// ��Ե���
		Mat canny;
		Canny(lubo, canny, 80, 160, 3, false);
		//��ֵ��ͼ��
		threshold(lubo, canny, 170, 255, THRESH_BINARY);
		cv::imshow("canny", canny);

	switch (champion)
	{ 
		case 1:	
		{
			// �������������
			vector<vector<Point>> contours;
			vector<Vec4i> hierarchy;
			findContours(canny, contours, hierarchy, 0, 2, Point());
			//�ڶ���������contours������Ϊ��vector<vector<Point>> contours����
			//��һ��������������һ��˫������������
			//��ÿ��Ԫ�ر�����һ����������Point�㹹�ɵĵ�ļ��ϵ�������ÿһ��Point�㼯����һ������

			//���ƶ����
			for (int t = 0; t < contours.size(); t++)
			{	//��������������ѭ����׼
				//��һ�����룬�����С��400��ȥ��
				double area = contourArea(contours[t]);
				if (area < 400)   continue;
			   //����С��Ӿ�����ȡ��������
				RotatedRect rrect = minAreaRect(contours[t]);
				Point2f center = rrect.center;

				Mat result;
				approxPolyDP(contours[t], result, 4, true);  //��������
				drawapp(result, img);
				std::cout << "corners : " << result.rows << endl;
				//�ж���״�ͻ�������
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
			double dp = 2;        //ԭͼ�ֱ��ʺ��ۼ����ֱ��ʵı�ֵ
			double minDist = 50;  //����Բ��֮�����С����
			double	param1 = 100;  //Canny��Ե���Ľϴ���ֵ
			double	param2 = 50;  //�ۼ�����ֵ ��СͶƱ����ԽС��Խ��ٵ�Բ��������
			int min_radius = 0;  //Բ�ΰ뾶����Сֵ
			int max_radius = 150;  //Բ�ΰ뾶�����ֵ
			HoughCircles(canny, circles, HOUGH_GRADIENT, dp, minDist, param1, param2,
				min_radius, max_radius);
			for (size_t i = 0; i < circles.size(); i++)
			{
				circlen++;
				//��ȡԲ��
				Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
				//��ȡ�뾶
				int radius = cvRound(circles[i][2]);
				//����Բ��
				circle(img, center, 3, Scalar(0, 255, 0), -1, 8, 0);
				//����Բ
				circle(img, center, radius, Scalar(0, 0, 255), 3, 8, 0);
			}
			break;

		}
	}
		//������
		string a = "triangle:";
		string b = to_string(triangle);
		string c = a + b;
		//����
		string d = "rectangle";
		string e = to_string(rectangle);
		string f = d + e;
		//�����
		string g = "poly";
		string h = to_string(poly);
		string i = g + h;
		//��
		string j = "star";
		string k = to_string(star);
		string l = j + k;
		//Բ
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
		std::cout << "�Ƿ�������" << endl;
		std::cin >> x;
	}
	return 0;
}