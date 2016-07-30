#include <cv.h>
#include <highgui.h>
#include <string.h>
#include "cv.h"
#include "cxcore.h"
#include <iostream>
#include <fstream>
#include "cvaux.h"
using namespace std;
int main()
{
	IplImage* origin = cvLoadImage("D:\\MathorCup\\gaussian_1.bmp", 0);
	cvNamedWindow("origin", 1);
	cvShowImage("origin", origin);
	CvMat* U = cvCreateMat(origin->height, origin->height, CV_8UC1);
	CvMat* V = cvCreateMat(origin->width, origin->width, CV_8UC1);

	CvMat* T = cvCreateMat(origin->height, origin->width, CV_8UC1);

	
	ofstream fout;
	fout.open("mat.txt");

	for (int i = 0; i < origin->height; i++)
	{
		for (int j = 0; j < origin->width; j++)
		{
			fout << int(origin->imageData[i*origin->height + j]) << " ";
		}
		cout << endl;
	}
	fout.close();
	cvNamedWindow("origin", 1);
	cvShowImage("origin", origin);
//	cvWaitKey(0);
	cvReleaseImage(&origin);
	return 0;
}