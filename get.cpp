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
	//初始化curl对象
	curl = curl_easy_init();
	if (curl != nullptr)
	{
		//CURLOPT_URL: 这是你想用PHP取回的URL地址
		curl_easy_setopt(curl, CURLOPT_URL, "http://robomaster.kingstudio.top");//curl指向网址
		/* example.com is redirected, so we tell libcurl to follow redirection */
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 0L);   //为curl设置选项
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
