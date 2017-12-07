
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
	
	
	
	Mat dst;
	string img_name;

	char m[10];
	char n[10];

	
	for (int c = 1; c <= 100 ; c++)
	{
		for (int a = 1; a <= 2; a++)
		{
			
		
			sprintf_s(m, "%d", c);

			sprintf_s(n, "%d", a);
			string str1(&m[0], &m[strlen(m)]);
			string str2(&n[0], &n[strlen(n)]);
			img_name = "E:\\Photo\\"+ str1 + "-("+str2+")"+".jpg";
		    cout << img_name << endl;
			char c1[100];
			strcpy(c1, img_name.c_str());

		   Mat src_img = imread(img_name);

		   if (src_img.cols >= 1000)
		   {
			   resize(src_img, dst,  Size(1000, 1000 * src_img.rows / src_img.cols));

			   namedWindow("IMG");
			   imshow("IMG", dst);
			   cvSaveImage(c1, &IplImage(dst));
			   waitKey(50);
		   }
		   else
		   {
			   resize(src_img, dst, Size(),1,1);

			   namedWindow("IMG");
			   imshow("IMG", dst);
			   cvSaveImage(c1, &IplImage(dst));
			   waitKey(50);
		   }
		 
		   

		 
		}  
	}
	return 0;
}
