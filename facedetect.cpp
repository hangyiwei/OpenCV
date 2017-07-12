#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <thread>
#include <windows.h>
#include <fstream>
#include <mutex>


using namespace std;
using namespace cv;

static void help()
{
	cout << "\nThis program demonstrates the cascade recognizer. Now you can use Haar or LBP features.\n"
		"This classifier can recognize many kinds of rigid objects, once the appropriate classifier is trained.\n"
		"It's most known use is for faces.\n"
		"Usage:\n"
		"./facedetect [--cascade=<cascade_path> this is the primary trained classifier such as frontal face]\n"
		"   [--nested-cascade[=nested_cascade_path this an optional secondary classifier such as eyes]]\n"
		"   [--scale=<image scale greater or equal to 1, try 1.3 for example>]\n"
		"   [--try-flip]\n"
		"   [filename|camera_index]\n\n"
		"see facedetect.cmd for one call:\n"
		"./facedetect --cascade=\"../../data/haarcascades/haarcascade_frontalface_alt.xml\" --nested-cascade=\"../../data/haarcascades/haarcascade_eye_tree_eyeglasses.xml\" --scale=1.3\n\n"
		"During execution:\n\tHit any key to quit.\n"
		"\tUsing OpenCV version " << CV_VERSION << "\n" << endl;
}

void detectAndDraw(Mat& img, CascadeClassifier& cascade,
	CascadeClassifier& nestedCascade,
	double scale, bool tryflip, Rect &point);

string cascadeName;
string nestedCascadeName;

int main(int argc, const char** argv)
{
	Rect point(1, 1, 100, 100);
	VideoCapture capture;
	Mat frame, image;
	string inputName;
	bool tryflip;
	CascadeClassifier cascade, nestedCascade;
	double scale;

	cv::CommandLineParser parser(argc, argv,
		"{help h||}"
		"{cascade|../../data/haarcascades/haarcascade_frontalface_alt.xml|}"
		"{nested-cascade|../../data/haarcascades/haarcascade_eye_tree_eyeglasses.xml|}"
		"{scale|1|}{try-flip||}{@filename||}"
	);
	if (parser.has("help"))
	{
		help();
		return 0;
	}
	cascadeName = parser.get<string>("cascade");
	nestedCascadeName = parser.get<string>("nested-cascade");
	scale = parser.get<double>("scale");
	if (scale < 1)
		scale = 1;
	tryflip = parser.has("try-flip");
	inputName = parser.get<string>("@filename");
	if (!parser.check())
	{
		parser.printErrors();
		return 0;
	}
	if (!nestedCascade.load(nestedCascadeName))
		cerr << "WARNING: Could not load classifier cascade for nested objects" << endl;
	if (!cascade.load(cascadeName))
	{
		cerr << "ERROR: Could not load classifier cascade" << endl;
		help();
		return -1;
	}
	if (inputName.empty() || (isdigit(inputName[0]) && inputName.size() == 1))
	{
		int camera = inputName.empty() ? 0 : inputName[0] - '0';
		if (!capture.open(camera))
			cout << "Capture from camera #" << camera << " didn't work" << endl;
	}
	else if (inputName.size())
	{
		image = imread(inputName, 1);
		if (image.empty())
		{
			if (!capture.open(inputName))
				cout << "Could not read " << inputName << endl;
		}
	}
	else
	{
		image = imread("../data/lena.jpg", 1);
		if (image.empty()) cout << "Couldn't read ../data/lena.jpg" << endl;
	}

	if (capture.isOpened())
	{
		DWORD start;
		DWORD stop;
		
		cout << "Video capturing has been started ..." << endl;
		CreateDirectory("E:\\Projects\\Project1\\0", NULL);
		
	
		char d[100];
		
		char s[100];
		for (int a = 0; a < 1000; a++)
		{
			 start = GetTickCount();
			
          	for (int i = 0; i < 10000; i++)
			{
				stop = GetTickCount();
				DWORD time_passing = (stop - start) / 1000;
				capture >> frame;
				if (frame.empty())
					break;

				Mat frame1 = frame.clone();
				detectAndDraw(frame1, cascade, nestedCascade, scale, tryflip, point);
				Mat imgtem;
				Rect rc(cvPoint(cvRound(point.x*scale), cvRound(point.y*scale)),
					cvPoint(cvRound((point.x + point.width - 1)*scale), cvRound((point.y + point.height - 1)*scale)));  //人脸坐标
				frame1(rc).copyTo(imgtem);
				Mat sa;
				resize(imgtem, sa, Size(1000, 1000));
				//创建文件夹
				cout << time_passing << endl;
				sprintf_s(d, "E:\\Projects\\Project1\\%d", a);
				//图片保存
				sprintf_s(s, "%d.png", i);
				cout << s << endl;
				string str1(&d[0], &d[strlen(d)]);
				string str2(&s[0], &s[strlen(s)]);
				char c1[100];
				string str = str1+ "\\" + str2;
				strcpy(c1, str.c_str());
				cout << c1 << endl;
				cvSaveImage(c1, &IplImage(sa));
		        char c = (char)waitKey(10);
				if (c == 27 || c == 'q' || c == 'Q')
					break;
				if (time_passing >= 25)
				{


					cout << time_passing << "文件夹路径" << d << endl;
					CreateDirectory(d, NULL);
					break;

				}
				else
				{
					cout << "剩余 " <<25-time_passing<<"秒创建新文件夹" << endl;
					//time_passing += time_passing;
				}
				
				
			}

		}
	}
	else
	{
		cout << "Detecting face(s) in " << inputName << endl;
		if (!image.empty())
		{
			detectAndDraw(image, cascade, nestedCascade, scale, tryflip, point);
			waitKey(0);
		}
		else if (!inputName.empty())
		{
			/* assume it is a text file containing the
			list of the image filenames to be processed - one per line */
			FILE* f = fopen(inputName.c_str(), "rt");
			if (f)
			{
				char buf[1000 + 1];
				while (fgets(buf, 1000, f))
				{
					int len = (int)strlen(buf);
					while (len > 0 && isspace(buf[len - 1]))
						len--;
					buf[len] = '\0';
					cout << "file " << buf << endl;
					image = imread(buf, 1);
					if (!image.empty())
					{
						detectAndDraw(image, cascade, nestedCascade, scale, tryflip, point);
						char c = (char)waitKey(0);
						if (c == 27 || c == 'q' || c == 'Q')
							break;
					}
					else
					{
						cerr << "Aw snap, couldn't read image " << buf << endl;
					}
				}
				fclose(f);
			}
		}
	}

	return 0;
}

void detectAndDraw(Mat& img, CascadeClassifier& cascade,
	CascadeClassifier& nestedCascade,
	double scale, bool tryflip, Rect &point)
{

	double t = 0;
	vector<Rect> faces, faces2;
	const static Scalar colors[] =
	{
		Scalar(255,0,0),
		Scalar(255,128,0),
		Scalar(255,255,0),
		Scalar(0,255,0),
		Scalar(0,128,255),
		Scalar(0,255,255),
		Scalar(0,0,255),
		Scalar(255,0,255)
	};
	Mat gray, smallImg;

	cvtColor(img, gray, COLOR_BGR2GRAY);
	double fx = 1 / scale;
	resize(gray, smallImg, Size(), fx, fx, INTER_LINEAR);
	equalizeHist(smallImg, smallImg);

	t = (double)getTickCount();
	cascade.detectMultiScale(smallImg, faces,
		1.1, 2, 0
		//|CASCADE_FIND_BIGGEST_OBJECT
		//|CASCADE_DO_ROUGH_SEARCH
		| CASCADE_SCALE_IMAGE,
		Size(30, 30));
	if (tryflip)
	{
		flip(smallImg, smallImg, 1);
		cascade.detectMultiScale(smallImg, faces2,
			1.1, 2, 0
			//|CASCADE_FIND_BIGGEST_OBJECT
			//|CASCADE_DO_ROUGH_SEARCH
			| CASCADE_SCALE_IMAGE,
			Size(30, 30));
		for (vector<Rect>::const_iterator r = faces2.begin(); r != faces2.end(); ++r)
		{
			faces.push_back(Rect(smallImg.cols - r->x - r->width, r->y, r->width, r->height));
		}
	}
	t = (double)getTickCount() - t;
	printf("detection time = %g ms\n", t * 1000 / getTickFrequency());

	for (size_t i = 0; i < faces.size(); i++)
	{

		Rect r = faces[i];
		point = r;
		//Mat smallImgROI;
		/*vector<Rect> nestedObjects;
		Point center;
		*/Scalar color = colors[i % 8];
		int radius;

		double aspect_ratio = (double)r.width / r.height;
		//if (0.75 < aspect_ratio && aspect_ratio < 1.3)
		//{
		//	center.x = cvRound((r.x + r.width*0.5)*scale);
		//	center.y = cvRound((r.y + r.height*0.5)*scale);
		//	radius = cvRound((r.width + r.height)*0.25*scale);
		//	circle(img, center, radius, color, 3, 8, 0);
		//}
		//else
		rectangle(img, cvPoint(cvRound(r.x*scale), cvRound(r.y*scale)),
			cvPoint(cvRound((r.x + r.width - 1)*scale), cvRound((r.y + r.height - 1)*scale)),
			color, 3, 8, 0);
		//if (nestedCascade.empty())
		//	continue;
		//smallImgROI = smallImg(r);
		//nestedCascade.detectMultiScale(smallImgROI, nestedObjects,
		//	1.1, 2, 0
		//	//|CASCADE_FIND_BIGGEST_OBJECT
		//	//|CASCADE_DO_ROUGH_SEARCH
		//	//|CASCADE_DO_CANNY_PRUNING
		//	| CASCADE_SCALE_IMAGE,
		//	Size(30, 30));
		//for (size_t j = 0; j < nestedObjects.size(); j++)
		//{
		//	Rect nr = nestedObjects[j];
		//	center.x = cvRound((r.x + nr.x + nr.width*0.5)*scale);
		//	center.y = cvRound((r.y + nr.y + nr.height*0.5)*scale);
		//	radius = cvRound((nr.width + nr.height)*0.25*scale);
		//	circle(img, center, radius, color, 3, 8, 0);
		//}
	}
	imshow("result", img);
}


