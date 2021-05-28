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
			cout << "����ͷ��ʧ��" << endl;
			return -1;
		}

		while (1)
		{
			Mat frame;
			video >> frame;
			imshow("frame", frame);
			if (waitKey(20) == 'q')   //��ʱ20ms,��ȡ�û��Ƿ񰴼���������������q�����Ƴ����� 
				break;
		}
		Mat frame;
		video >> frame;
		//���ñ����ʽ
		vector<int>compression_params;
		compression_params.push_back(IMWRITE_PNG_COMPRESSION);
		compression_params.push_back(9);
		bool result = imwrite("D:/opencvpicture/test.png", frame, compression_params);
		if (result)
		{
			cout << "ͼƬ����ɹ�" << endl;
		}
		//�����ά��
		Mat img = imread("D:/opencvpicture/test.png");
		if (img.empty())
		{
			cout << "��ά����Ϣ����" << endl;
			return -1;
		}
		Mat gray, src;
		cvtColor(img, gray, COLOR_BGR2GRAY); //ת��Ϊ�Ҷ�ͼƬ
		QRCodeDetector qrcode;
		string web; //���ն�ά�����ַ
		vector<Point> point; //��ά�붥������
		web = qrcode.detectAndDecode(gray, point, src); //����
		if (web.empty())
		{
			cout << "ʶ��ʧ�� " << endl;
		}
		else
		{
			cout << web << endl; //��ӡ��ַ
		}
		cout << "�Ƿ�������" << endl;
		cin >> x;
	}
	system("pause");
	destroyAllWindows();
	return 0;
}