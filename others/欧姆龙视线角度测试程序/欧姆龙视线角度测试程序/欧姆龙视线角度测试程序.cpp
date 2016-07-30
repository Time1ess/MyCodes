// 欧姆龙视线角度测试程序.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <opencv2\opencv.hpp>
#include "cvut.h"
#pragma warning(disable:4996)

#ifdef OKAO
#include "OkaoAPI.h"
#include "CommonDef.h"
#include "OkaoDtAPI.h"
#include "OkaoPtAPI.h"
#include "OkaoAgAPI.h"
#include "OkaoGnAPI.h"
#include "OkaoEoAPI.h"//Eye-open Rate Detection
#include "OkaoSmAPI.h"
#include "OkaoFrAPI.h"
#include "OkaoGbAPI.h"
#endif
using namespace std;
using namespace cvut;

int _tmain(int argc, _TCHAR* argv[])
{
	IplImage* LFrame = NULL;
	IplImage* RFrame = NULL;
	CvCapture *Capture2 = cvCreateCameraCapture(0);
	CvCapture *Capture1 = cvCreateCameraCapture(2);

	cvNamedWindow("video-L", 1);
	cvNamedWindow("video-R", 1);
	int i = 0;

	while (1)
	{
		IplImage *Rimage, *Limage;
		cvGrabFrame(Capture2);
		cvGrabFrame(Capture1);
		LFrame = cvRetrieveFrame(Capture2);
		RFrame = cvRetrieveFrame(Capture1);
		if (!LFrame || !RFrame) break;
		Rimage = cvCloneImage(RFrame);
		Limage = cvCloneImage(LFrame);
		if (!LFrame || !RFrame)
		{
			cout << "Failed";
			break;
		}
		cvShowImage("video-L", LFrame);
		cvShowImage("video-R", RFrame);
		char c = cvWaitKey(33);
		if (c == 27)break;
	}
	cvReleaseCapture(&Capture1);
	cvDestroyWindow("video-L");
	cvReleaseCapture(&Capture2);
	cvDestroyWindow("video-R");
	return 0;
}

