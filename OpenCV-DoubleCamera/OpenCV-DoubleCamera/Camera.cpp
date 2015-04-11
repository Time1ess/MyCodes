#include <opencv2\opencv.hpp>
#include "cvut.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace cvut;
using namespace std;

enum{L=0,R=1};

//每次按下空格键，左右摄像头分别捕获图像并保存jpg文件，并将路径信息添加至定标所需要路径的文件中

int CapturePhoto()
{
	ofstream L_fout,R_fout;
	L_fout.open("Lcalibdata.txt");
	R_fout.open("Rcalibdata.txt");
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
		if (!LFrame|| !RFrame)
		{
			cout << "Failed";
			break;
		}
		cvShowImage("video-L", LFrame);
		cvShowImage("video-R", RFrame);
		char c = cvWaitKey(33);
		if (c==32)
		{
			i += 1;
			char L_filename[30], R_filename[30];
			sprintf(L_filename, "photo\\L%d.jpg", i);
			sprintf(R_filename, "photo\\R%d.jpg", i);
			cvSaveImage(L_filename, LFrame);
			cvSaveImage(R_filename, RFrame);
			if (i != 1)
			{
				L_fout << endl;
				R_fout << endl;
			}
			L_fout << L_filename;
			R_fout << R_filename;
		}
		if (c == 27)break;
	}
	cvReleaseCapture(&Capture1);
	cvDestroyWindow("video-L");
	cvReleaseCapture(&Capture2);
	cvDestroyWindow("video-R");
	L_fout.close();
	R_fout.close();
	return 0;
}




void calib(int LR)
{
	ifstream fin;
	ofstream fout,fout1;
	if (LR == L)
	{
		fin.open("Lcalibdata.txt"); /* 定标所用图像文件的路径 */
		fout.open("Lcaliberation_result.txt");  /* 保存定标结果的文件 */
		fout1.open("LXYZ.txt");
	}
	else
	{
		fin.open("Rcalibdata.txt"); /* 定标所用图像文件的路径 */
		fout.open("Rcaliberation_result.txt");  /* 保存定标结果的文件 */
		fout1.open("RXYZ.txt");
	}

	/************************************************************************
	读取每一幅图像，从中提取出角点，然后对角点进行亚像素精确化
	*************************************************************************/

	cout << "开始提取角点………………\n";

	int image_count = 0;  /* 图像数量 */
	CvSize image_size;  /* 图像的尺寸 */

	CvSize board_size = cvSize(4, 6);    /* 定标板上每行、列的角点数 */

	CvPoint2D32f* image_points_buf = new CvPoint2D32f[board_size.width*board_size.height];   /* 缓存每幅图像上检测到的角点 */
	Seq<CvPoint2D32f> image_points_seq;  /* 保存检测到的所有角点 */

	string filename;

	int count = -1;//用于存储角点个数。 所有变量定义后必须初始化，这是一个编程优良习惯

	while (getline(fin, filename))
	{
		image_count++;
		/************************************************************************/
		/* 用于观察检验输出                                                                  */
		cout << "image_count = " << image_count << endl;

		/************************************************************************/


		/************************************************************************/
		/* 输出检验*/
		cout << "-->count = " << count;
		/************************************************************************/


		Image<uchar> view(filename);

		if (image_count == 1)
		{
			image_size.width = view.size().width;
			image_size.height = view.size().height;
			/************************************************************************/
			/*                                                                      */
			cout << "image_size.width = " << image_size.width << endl;
			cout << "image_size.height = " << image_size.height << endl;

			/************************************************************************/
		}

		/* 提取角点 */

		if (0 == cvFindChessboardCorners(view.cvimage, board_size,
			image_points_buf, &count, CV_CALIB_CB_ADAPTIVE_THRESH))
		{
			/************************************************************************/
			/*                                                                      */
			cout << endl << "board_size.height=" << board_size.height << endl << "count=" << count << endl;
			/************************************************************************/
			cout << "can not find chessboard corners!\n";
			exit(1);
		}
		else
		{
			Image<uchar> view_gray(view.size(), 8, 1);
			rgb2gray(view, view_gray);

			/* 亚像素精确化 */

			cvFindCornerSubPix(view_gray.cvimage, image_points_buf, count, cvSize(11, 11),
				cvSize(-1, -1), cvTermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));//对粗提取的角点进行精确化
			image_points_seq.push_back(image_points_buf, count);

			/* 在图像上显示角点位置 */

			cvDrawChessboardCorners(view.cvimage, board_size, image_points_buf, count, 1);//用于在图片中标记角点
			view.show("calib");//显示图片
			cvWaitKey(500);//用于暂停，单位是毫秒
			view.close();
		}
	}

	fin.close();

	/************************************************************************/
	/*
	//以下是利用包装后的数据结构（seq类）进行操作，比基于openCV的数据结构更方便，结构清晰。
	*/
	int total = image_points_seq.length();
	cout << "total = " << total << endl;

	for (int ii = 0; ii<total; ii++)
	{
		if (0 == ii % 24)// 24 是每幅图片的角点个数。此判断语句是为了输出 图片号，便于控制台观看 
		{
			int i = -1;
			i = ii / 24;

			int j = i + 1;
			cout << "--> 第 " << j << "图片的数据 --> : " << endl;


		}


		if (0 == ii % 3)	// 此判断语句，格式化输出，便于控制台查看
		{
			cout << endl;
		}
		else
		{
			cout.width(10);
		}

		//输出所有的角点

		cout << " -->" << image_points_seq[ii].x;
		cout << " -->" << image_points_seq[ii].y;

	}


	/************************************************************************/


	delete[]image_points_buf;
	cout << "角点提取完成！\n";

	/************************************************************************
	摄像机定标
	*************************************************************************/

	cout << "开始定标………………";

	/*棋盘三维信息*/

	CvSize square_size = cvSize(10, 10);  /* 实际测量得到的定标板上每个棋盘格的大小 */
	Matrix<double> object_points(1, board_size.width*board_size.height*image_count, 3); /* 保存定标板上角点的三维坐标 */
	Matrix<double> image_points(1, image_points_seq.cvseq->total, 2); /* 保存提取的所有角点 */
	Matrix<int> point_counts(1, image_count, 1); /* 每幅图像中角点的数量 */

	/*内外参数*/

	Matrix<double> intrinsic_matrix(3, 3, 1); /* 摄像机内参数矩阵 */
	Matrix<double> distortion_coeffs(1, 4, 1); /* 摄像机的4个畸变系数：k1,k2,p1,p2 */
	Matrix<double> rotation_vectors(1, image_count, 3); /* 每幅图像的旋转向量 */
	Matrix<double> translation_vectors(1, image_count, 3); /* 每幅图像的平移向量 */


	/* 初始化定标板上角点的三维坐标 */

	int i, j, t;

	for (t = 0; t<image_count; t++) {
		for (i = 0; i<board_size.height; i++) {
			for (j = 0; j<board_size.width; j++) {
				/* 假设定标板放在世界坐标系中z=0的平面上 */
				object_points(0, t*board_size.height*board_size.width + i*board_size.width + j, 0) = i*square_size.width;  //x
				object_points(0, t*board_size.height*board_size.width + i*board_size.width + j, 1) = j*square_size.height;  //y
				object_points(0, t*board_size.height*board_size.width + i*board_size.width + j, 2) = 0;   //z
				fout1 << "X:  "<<i*square_size.width << "   Y:  " << j*square_size.height << endl;
			}
		}
	}

	/* 将角点的存储结构转换成矩阵形式 */

	for (i = 0; i<image_points_seq.cvseq->total; i++) {
		image_points(0, i, 0) = image_points_seq[i].x;
		image_points(0, i, 1) = image_points_seq[i].y;
	}

	/* 初始化每幅图像中的角点数量，这里我们假设每幅图像中都可以看到完整的定标板 */

	for (i = 0; i<image_count; i++)
		point_counts(0, i) = board_size.width*board_size.height;

	/* 开始定标 */

	cvCalibrateCamera2(object_points.cvmat,
		image_points.cvmat,
		point_counts.cvmat,
		image_size,
		intrinsic_matrix.cvmat,
		distortion_coeffs.cvmat,
		rotation_vectors.cvmat,
		translation_vectors.cvmat,
		0);
	cout << "定标完成！\n";

	/************************************************************************
	对定标结果进行评价
	*************************************************************************/

	cout << "开始评价定标结果………………\n";

	double total_err = 0.0; /* 所有图像的平均误差的总和 */
	double err = 0.0; /* 每幅图像的平均误差 */
	Matrix<double> image_points2(1, point_counts(0, 0, 0), 2); /* 保存重新计算得到的投影点 */

	cout << "\t每幅图像的定标误差：\n";
	fout << "每幅图像的定标误差：\n";

	for (i = 0; i<image_count; i++) {
		/* 通过得到的摄像机内外参数，对空间的三维点进行重新投影计算，得到新的投影点 */
		cvProjectPoints2(object_points.get_cols(i*point_counts(0, 0, 0), (i + 1)*point_counts(0, 0, 0) - 1).cvmat,
			rotation_vectors.get_col(i).cvmat,
			translation_vectors.get_col(i).cvmat,
			intrinsic_matrix.cvmat,
			distortion_coeffs.cvmat,
			image_points2.cvmat,
			0, 0, 0, 0);
		/* 计算新的投影点和旧的投影点之间的误差*/
		err = cvNorm(image_points.get_cols(i*point_counts(0, 0, 0), (i + 1)*point_counts(0, 0, 0) - 1).cvmat,
			image_points2.cvmat,
			CV_L1);
		total_err += err /= point_counts(0, 0, 0);
		cout << "\t\t第" << i + 1 << "幅图像的平均误差：" << err << "像素" << '\n';
		fout << "\t第" << i + 1 << "幅图像的平均误差：" << err << "像素" << '\n';
	}

	cout << "\t总体平均误差：" << total_err / image_count << "像素" << '\n';
	fout << "总体平均误差：" << total_err / image_count << "像素" << '\n' << '\n';
	cout << "评价完成！\n";

	/************************************************************************
	保存定标结果
	*************************************************************************/

	cout << "开始保存定标结果………………";

	Matrix<double> rotation_vector(3, 1); /* 保存每幅图像的旋转向量 */
	Matrix<double> rotation_matrix(3, 3); /* 保存每幅图像的旋转矩阵 */

	fout << "相机内参数矩阵：\n";
	fout << intrinsic_matrix << '\n';
	fout << "畸变系数：\n";
	fout << distortion_coeffs << '\n';

	for (i = 0; i<image_count; i++)
	{
		fout << "第" << i + 1 << "幅图像的旋转向量：\n";
		fout << rotation_vectors.get_col(i);

		/* 对旋转向量进行存储格式转换 */

		for (j = 0; j<3; j++)
		{
			rotation_vector(j, 0, 0) = rotation_vectors(0, i, j);
		}

		/* 将旋转向量转换为相对应的旋转矩阵 */

		cvRodrigues2(rotation_vector.cvmat, rotation_matrix.cvmat);

		fout << "第" << i + 1 << "幅图像的旋转矩阵：\n";
		fout << rotation_matrix;

		fout << "第" << i + 1 << "幅图像的平移向量：\n";
		fout << translation_vectors.get_col(i) << '\n';

	}
	fout.close();
	fout1.close();
	cout << "完成保存\n";
}


int main()
{
	CapturePhoto();
	calib(L);
	calib(R);
	return 0;
}

