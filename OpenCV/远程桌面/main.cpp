#include <cv.h>
#include <highgui.h>
#include <string.h>
#include "cv.h"
#include "cxcore.h"
#include <iostream>
#include <fstream>
#include "cvaux.h"
#include "screenCapture.h"
using namespace std;

int main()
{
	IplImage* origin = cvLoadImage("D:\\MathorCup\\gaussian_1.bmp", 0);
	cvNamedWindow("origin", 1);
	cvShowImage("origin", origin);
	cvWaitKey(0);
	return 0;
}