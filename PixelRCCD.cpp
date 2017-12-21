#define _CRT_SECURE_NO_WARNINGS  

#include <iostream>
#include "opencv2/opencv.hpp"
#include <stdio.h>
#include "opencv2/imgproc.hpp"
#include<opencv2\opencv.hpp>

using namespace std;
using namespace cv;

//遍历行列，生成像素值

#define NUM 100

//int main()
//
//{
//
//
//
//	//Rect
//	cv::Mat pImg = imread("E:\\Projects\\Project5\\x64\\Release\\lena.jpg");
//	cv::Rect rect(180, 200, 200, 200);
//	cv::Mat roi = cv::Mat(pImg, rect);
//	cv::Mat pImgRect = pImg.clone();
//	cv::rectangle(pImgRect, rect, cv::Scalar(0, 255, 0), 2);
//	cv::imshow("original image with rectangle ", pImgRect);
//	cv::imshow("roi", roi);
//	cv::waitKey();
//
//
//	return 0;
//	}
//}


int main()
{
	Mat m(400, 400, CV_8U, Scalar(0));

	for (int col = 0; col < 400; col++)
	{
		for (int row = 195; row < 205; row++)
		{

			cout << (int)(*(m.data + m.step[0] * row + m.step[1] * col)) << " ==>";
			// 获取第[row,col]个像素点的地址并用*符号解析
			*(m.data + m.step[0] * row + m.step[1] * col) = 255;
			cout << (int)(*(m.data + m.step[0] * row + m.step[1] * col)) << endl;

			cout <<"每一维的大小" << "\t" <<  m.step[0] << "\t" << m.step[1] << endl;
		}
	}
	imshow("canvas", m);
	waitKey();
}
	//cvWaitKey();
	//return 0;
    	
	//	Mat grayim(600, 800, CV_8UC1);
	//	Mat colorim(600, 800, CV_8UC3);
	//	for (int i = 0; i<grayim.rows; i++) {
	//		for (int j = 0; j<grayim.cols; j++) {
	//			grayim.at<uchar>(i, j) = (i + j) % 255;
	//		}
	//	}
	//	for (int i = 0; i<colorim.rows; i++) {
	//		for (int j = 0; j<colorim.cols; j++) {
	//			Vec3b pixel;
	//			pixel[0] = i % 255;
	//			pixel[1] = j % 255;
	//			pixel[2] = 3;
	//			colorim.at<Vec3b>(i, j) = pixel;
	//		}
	//	}
	//	imshow("grayim", grayim);
	//	imshow("colorim", colorim);
	//	waitKey(0);
	//	return 0;
	//
//}




