#include<iostream>
#include <curl/curl.h>    
#include<string>
#include "windows.h "                      
#include "shellapi.h "
using namespace std;
int main1451(int argc, char* argv[])
{
	CURL *curl = nullptr;
	CURLcode res;
	//��ʼ��curl����
	curl = curl_easy_init();
	if (curl != nullptr)
	{
		//CURLOPT_URL: ����������PHPȡ�ص�URL��ַ
		curl_easy_setopt(curl, CURLOPT_URL, "http://robomaster.kingstudio.top");//curlָ����ַ
		/* example.com is redirected, so we tell libcurl to follow redirection */
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 0L);   //Ϊcurl����ѡ��
		/* Perform the request, res will get the return code */
		res=curl_easy_perform(curl);

		/* Check for errors */
		if (res != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}
		/* always cleanup */
		curl_easy_cleanup(curl);
	}
	system("pause");
	return 0;
}
