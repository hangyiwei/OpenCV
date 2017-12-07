
#define _CRT_SECURE_NO_WARNINGS  

#include <iostream>
#include "opencv2/opencv.hpp"
#include <stdio.h>
#include "opencv2/imgproc.hpp"
#include<opencv2\opencv.hpp>

using namespace std;
using namespace cv;



#define NUM 100

int main()

{
	
	
	
	//Rect
	cv::Mat pImg = imread("E:\\Projects\\Project5\\x64\\Release\\lena.jpg");
	cv::Rect rect(180, 200, 200, 200);
	cv::Mat roi = cv::Mat(pImg, rect);
	cv::Mat pImgRect = pImg.clone();
	cv::rectangle(pImgRect, rect, cv::Scalar(0, 255, 0), 2);
	cv::imshow("original image with rectangle ", pImgRect);
	cv::imshow("roi", roi);
	cv::waitKey();


	return 0;
}
