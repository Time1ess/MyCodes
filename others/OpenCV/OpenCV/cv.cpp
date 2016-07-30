#include <cv.h>
#include <highgui.h>
using namespace std;
int main()
{
	IplImage *origin;
	origin = cvLoadImage("D:\\MathorCup\\origin.bmp",1);//Í¼Æ¬Â·¾¶
	IplImage *gussian = cvLoadImage("D:\\MathorCup\\origin.bmp", 1);
	cvZero(gussian);
	CvRNG rng = cvRNG(-1);
	cvRandArr(&rng, gussian, CV_RAND_NORMAL, cvScalarAll(15), cvScalarAll(15));

	cvAdd(origin, gussian, gussian);
	cvSaveImage("gaussian.bmp", gussian);

	cvNamedWindow("origin", 1);
	cvShowImage("origin", origin);
	cvNamedWindow("gussian", 1);
	cvShowImage("gussian", gussian);
	cvWaitKey(0);
	cvDestroyWindow("origin");
	cvDestroyWindow("gussian");
	cvReleaseImage(&origin);
	cvReleaseImage(&gussian);
	return 0;
}