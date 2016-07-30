// fatiguedetect-dlgDlg.cpp : implementation file
//
///////////////////////////////////////////////////////////////////////Basic include
#pragma warning(disable:4996)
#include "stdafx.h"
#include "fatiguedetect-dlg.h"
#include "fatiguedetect-dlgDlg.h"
#include "resource.h"
#include <windows.h>
#include <windowsx.h>
#include <cstring>
#include <cctype>
#include <list>
#include <commctrl.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;
#define LOAD_OMRON
///////////////////////////////////////////////////////////////////////Omron include
#ifdef LOAD_OMRON
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
///////////////////////////////////////////////////////////////////////Defines

#define MAX2 30  //检测累计  30
#define MAX1 30  //鼠标累计  30
#define MAX3 50 //画线
#define MAX4 2 //定位 遍数
#define MAX5 100  //定位累计
#define MAX5_MIN 30	//误差限
#define PI 3.1415
#define FRAME_WIDTH		320
#define FRAME_HEIGHT	240
#define TPL_WIDTH 		16
#define TPL_HEIGHT 		12
#define WIN_WIDTH		TPL_WIDTH * 2
#define WIN_HEIGHT		TPL_HEIGHT * 2
#define TM_THRESHOLD	0.4
#define STAGE_INIT		1
#define STAGE_TRACKING	2
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#define sign(a)             (((a) >=(0)) ? (1) : (-1)) 
#define pow(a)				((a)*(a))
#define POINT_TL(r)		cvPoint(r.x, r.y)
#define POINT_BR(r)		cvPoint(r.x + r.width, r.y + r.height)
#define POINTS(r)		POINT_TL(r), POINT_BR(r)


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CvPoint2D32f CenterGaze;
CvPoint2D32f rCenterGaze;
CvPoint2D32f ScreenLocation[2] = { { 0, 0 }, { 0, 0 } };  //0:左上角;1:右下角
CvPoint2D32f rScreenLocation[2] = { { 0, 0 }, { 0, 0 } }; //同上


double A = GetSystemMetrics(SM_CXSCREEN);   //获取屏幕宽度
double B = GetSystemMetrics(SM_CYSCREEN);	//获取屏幕高度

int WindowPositionFlag = -1;					
int horizontal[MAX5];			//为系统初始化定位视线位置的时候保存水平夹角数据
int vertical[MAX5];			//为系统初始化定位视线位置的时候保存垂直夹角数据

int rHorizontal[MAX5];			//为系统初始化定位视线位置的时候保存水平夹角数据
int rVertical[MAX5];			//为系统初始化定位视线位置的时候保存垂直夹角数据
//////////////////////////////////////////////////////////
struct Angle
{
	INT32 data[MAX2];
	int insert, erase;
};

struct Coordinates
{
	INT32 data[MAX1];
	int insert, erase;
};

int FrameCount = 0;
bool ReadyToEstimation = false;


//////////////////////////////////////////////////////////////////////////


//提供“关于”窗口内容

class CAboutDlg : public CDialog
{
public:
	CAboutDlg():CDialog(CAboutDlg::IDD){};
	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX)   // DDX/DDV support
	{
		CDialog::DoDataExchange(pDX);
	};    
protected:
	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////

//系统初始化

fatiguedetectDlg::fatiguedetectDlg(CWnd* pParent): CDialog(fatiguedetectDlg::IDD, pParent)
												//pParent=NULL
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	flag_CamState = 0;
	isCamOpen = FALSE;
	isRightCamOpen = FALSE;
	ServMainThread = NULL;
	ServMainThread2 = NULL;
	iLEyeOpen = iREyeOpen = 250;//系统初始参数
	iLEyeClose = iREyeClose = 230;
	iThreshold_OpenClose = 50;
	nMaxUserNum = 6; 
	nMaxDataNum = 10;
	flag_faceRecognitionState = 0;
	nRegisteredUserNum = 0; 
	iMaxFaceCount = 1;
	imageNo = 0;
}

//框架调用此函数来改写与确认对话框数据

void fatiguedetectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Text(pDX, IDC_GENDER, eBox_gender);
	//DDX_Text(pDX, IDC_AGE, eBox_age);
	DDX_Control(pDX, IDC_ALL_USER, combo_allUser);
}

//启动消息映射定义

BEGIN_MESSAGE_MAP(fatiguedetectDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN_CAM, &fatiguedetectDlg::OnBnClickedOpenCam)
	ON_BN_CLICKED(IDC_PAUSE, &fatiguedetectDlg::OnBnClickedPause)
	ON_BN_CLICKED(IDC_EXIT, &fatiguedetectDlg::OnBnClickedExit)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_SET, &fatiguedetectDlg::OnBnClickedSet)
	ON_BN_CLICKED(IDC_ADDUSER, &fatiguedetectDlg::OnBnClickedAdduser)
	ON_BN_CLICKED(IDC_MANUAL_SET, &fatiguedetectDlg::OnBnClickedManualSet)
	ON_BN_CLICKED(IDC_REGISTER_FEATURE, &fatiguedetectDlg::OnBnClickedRegisterFeature)
	ON_BN_CLICKED(IDC_PRINT, &fatiguedetectDlg::OnBnClickedPrint)
	ON_EN_CHANGE(IDC_GAZELR, &fatiguedetectDlg::OnEnChangeGazelr)
	ON_EN_CHANGE(IDC_GAZEUD, &fatiguedetectDlg::OnEnChangeGazeud)
	ON_BN_CLICKED(IDC_BUTTON1, &fatiguedetectDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &fatiguedetectDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &fatiguedetectDlg::OnBnClickedButton3)
	ON_STN_CLICKED(IDC_PICTURE, &fatiguedetectDlg::OnStnClickedPicture)
	ON_EN_CHANGE(IDC_EDIT1, &fatiguedetectDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON6, &fatiguedetectDlg::OnBnClickedButton6)
	ON_EN_CHANGE(IDC_LEYE1, &fatiguedetectDlg::OnEnChangeLeye1)
	ON_EN_CHANGE(IDC_REYE1, &fatiguedetectDlg::OnEnChangeReye1)
	ON_EN_CHANGE(IDC_MANUAL_SET, &fatiguedetectDlg::OnEnChangeManualSet)
	ON_EN_CHANGE(IDC_REYE2, &fatiguedetectDlg::OnEnChangeReye2)
	ON_CBN_SELCHANGE(IDC_ALL_USER, &fatiguedetectDlg::OnCbnSelchangeAllUser)
	//ON_STN_CLICKED(IDC_PICTURE2, &fatiguedetectDlg::OnStnClickedPicture2)
END_MESSAGE_MAP()


//对话框初始化函数

BOOL fatiguedetectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	

	return TRUE; 
}

/*截获控制命令，如用户点击控制菜单的按钮或者点击最大化最小化按钮*/

void fatiguedetectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

/*窗口重画函数*/

void fatiguedetectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1)/2;
		int y = (rect.Height() - cyIcon + 1)/2;
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

/*回调函数，供系统调用，不用管*/

HCURSOR fatiguedetectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/*Click OpenCam button*/

void fatiguedetectDlg::OnBnClickedOpenCam()
{

	if (flag_CamState > 0)
		return;
	CRect rect;
	CvFont font;

	rightCamera = cvCreateCameraCapture(1);
	capture = cvCreateCameraCapture(0);/*连接摄像头*/

	/*capture = cvCreateFileCapture("video//tongNa.wmv");*/
	if (!capture||!rightCamera)
	{
		AfxMessageBox("Cannot initialize camera!");
		return;
	}
	/*设置摄像视频尺寸、预设字体*/
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);
	cvSetCaptureProperty(rightCamera, CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
	cvSetCaptureProperty(rightCamera, CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);

	cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 0.4, 0.4, 0, 1, 8);

	cvGrabFrame(rightCamera);
	cvGrabFrame(capture);
	rightFrame = cvRetrieveFrame(rightCamera);
	frame = cvRetrieveFrame(capture);

	pWnd = GetDlgItem(IDC_PICTURE);
	rPWnd = GetDlgItem(IDC_PICTURE2);

	pWnd->GetClientRect(&videoRect);
	rPWnd->GetClientRect(&videoRect);

	pGlobalDC = pWnd->GetDC();
	hGlobalDC = pGlobalDC->GetSafeHdc();
	rPGlobalDC = rPWnd->GetDC();
	rHGlobalDC = rPGlobalDC->GetSafeHdc();


	combo_allUser.Clear();

	isCamOpen = TRUE;
	isRightCamOpen = TRUE;
	CString str1, str2;
	str1.Format("%d", iLEyeOpen);
	str2.Format("%d", iLEyeClose);

	SetDlgItemText(IDC_LEYE1, str1);
	SetDlgItemText(IDC_LEYE2, str2);
	flag_CamState = 1;
#ifdef LOAD_OMRON
	ServMainThread = AfxBeginThread(ComputeThreadProc, (LPVOID)this, THREAD_PRIORITY_NORMAL);
#endif
}

void fatiguedetectDlg::MatrixPreprocessing()
{
}


/*调用欧姆龙库函数测定视线*/

//double XCoordinateCalculation(double gaze,double positiongazeL,double positiongazeR,int distance) 
//{
//	int offset = 0;
//	offset = distance*tan((gaze - (positiongazeL+positiongazeR) / 2) / 180 * PI);
//	return A / 2+offset;
//}

//double YCoordinateCalculation(double gaze, double positiongazeU, int distance)
//{
//	int offset = 0;
//	offset = distance*fabs(tan((gaze -  positiongazeU) / 180 * PI));
//	return 0 + offset;
//}


#ifdef LOAD_OMRON
UINT fatiguedetectDlg::ComputeThreadProc(LPVOID pParam)
{
	double VerticalGaze = 0, HorizontalGaze = 0;  /*每次累计的平均的 垂直值和水平值*/
	double rVerticalGaze = 0, rHorizontalGaze = 0;  /*每次累计的平均的 垂直值和水平值*/
	double minx = 10000, maxx = -10000;
	double miny = 10000, maxy = -10000;

	double rMinx = 10000, rMaxx = -10000;
	double rMiny = 10000, rMaxy = -10000;

	double TotalXOf30fps0 = 0, TotalYOf30fps0 = 0;	/*最近30次坐标数值的总和*/
	double rTotalXOf30fps0 = 0, rTotalYOf30fps0 = 0;	/*最近30次坐标数值的总和*/

	double HorizontalCoordinate = 0, VerticalCoordinate = 0;	/*最近30次坐标数值的平均值*/
	double OldHorizontalCoordinate = 0, OldVerticalCoordinate = 0;	/*上一次30次坐标数值的平均值*/
//	double HorizontalLocationLeft, HorizontalLocationRight, VerticalLocationLeft = -30, VerticalLocationRight = 30;
//	double rHorizontalLocationLeft, rHorizontalLocationRight, rVerticalLocationLeft = -30, rVerticalLocationRight = 30;

	int MouseControlCode = 0;//鼠标控制
	int t_ce = 0;
	int stay = 0;	//是否维持坐标状态。0:不维持;1:维持;
	int a_num = 0, b_num = 0, c_num = 0;  //a左击，b右击,c双击

	int distance = 0;
	int rdistance = 0;

	//gaze队列
	Angle GazeHangleData = { { 0 }, 0, 0 }; //水平
	Angle GazeVangleData = { { 0 }, 0, 0 }; //垂直

	Angle rGazeHangleData = { { 0 }, 0, 0 }; //水平
	Angle rGazeVangleData = { { 0 }, 0, 0 }; //垂直


	GazeHangleData.erase = 0; GazeHangleData.insert = 0;
	GazeVangleData.erase = 0; GazeVangleData.insert = 0;

	rGazeHangleData.erase = 0; rGazeHangleData.insert = 0;
	rGazeVangleData.erase = 0; rGazeVangleData.insert = 0;

	double TotalHAngleOf30fps = 0; //INT32
	double TotalVAngleOf30fps = 0; //INT32

	double rTotalHAngleOf30fps = 0; //INT32
	double rTotalVAngleOf30fps = 0; //INT32

	//坐标（x,y）队列
	Coordinates GazeXData = { { 0 }, 0, 0 };
	Coordinates GazeYData = { { 0 }, 0, 0 };
	double TotalXOf30fps = 0; //INT32
	double TotalYOf30fps = 0; //INT32
	GazeXData.erase = 0; GazeXData.insert = 0;
	GazeYData.erase = 0; GazeYData.insert = 0;

	IplImage* img = cvLoadImage("d:\\1.jpg");
	cvNamedWindow("exp", 0);  //创建窗口
	cvShowImage("exp", img);    //窗口中显示图像

	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	fatiguedetectDlg * pointer;
	pointer = (fatiguedetectDlg *)pParam;
	CRect rect,rRect;
	CDC *pDC,*rPDC;
	HDC hDC,rHDC;

	pointer->pWnd->GetClientRect(&rect);
	pDC = pointer->pWnd->GetDC();
	hDC = pDC->GetSafeHdc();

	pointer->rPWnd->GetClientRect(&rRect);
	rPDC = pointer->rPWnd->GetDC();
	rHDC = rPDC->GetSafeHdc();

	int iLReady, iRReady;
	iLReady = iRReady = 0;

	double X0, Y0;
	double rX0, rY0;

	//IplImage* pCurFrame;
	BYTE *pImgData;//存放帧图像像素数据
	BYTE *pRImgData;
	CString strTemp1, strTemp2, strTemp3;

	RAWIMAGE r, g, b;
	int iBytePerLine;
	int width, height;//frame宽度，高度

	int iTemp1, iTemp2, iTemp3, iTemp4, iTemp5;//临时变量
	int i, j;//循环变量

	vector<INT32>vLEye, vREye, vAge;
	vector<INT32>rVLEye, rVREye, rVAge;
	INT32 totalSmile, totalREye, totalLEye, totalAge;
	INT32 rTotalSmile, rTotalREye, rTotalLEye, rTotalAge;
	totalSmile = totalREye = totalLEye = totalAge = 0;
	rTotalSmile = rTotalREye = rTotalLEye = rTotalAge = 0;
	//脸部检测相关变量定义
	INT32 FunctionReturnCode, rFunctionReturnCode;  /* Return code */
	INT32 FaceCount = 0, rFaceCount = 0;               /* The number of detected face */

	INT32 LeftEyeOpenLevel, RightEyeOpenLevel;
	INT32 rLeftEyeOpenLevel, rRightEyeOpenLevel;

	INT32 SmileDegree, SmileDetectConfidence;//smile degree, 
	INT32 rSmileDegree, rSmileDetectConfidence;//smile degree, 
	FACEINFO info,rInfo;                  /* Detection Result */

	//////////////////////////////////////////////////////////////
	INT32 pnGazeLeftRight, pnGazeUpDown;//gaze
	INT32 rPnGazeLeftRight, rPnGazeUpDown;//gaze

	/////////////////////////////////////////////////////////////

	INT32 anConf[PT_POINT_KIND_MAX];
	POINT aptPoint[PT_POINT_KIND_MAX];
	INT32 rAnConf[PT_POINT_KIND_MAX];
	POINT rAptPoint[PT_POINT_KIND_MAX];



	vector<FACEINFO>vInfo;//存放每张脸的坐标数据

	INT32 Age;
	INT32 Confidence;
	INT32 rAge;
	INT32 rConfidence;

	INT32 FetureSimilarityTemp1, FetureSimilarityTemp2;
	//data num of current user

	INT32 Gender;
	INT32 rGender;
	//INT32 Confidence;

	RAWIMAGE *pGray = NULL;         /* Raw image data (gray) */
	RAWIMAGE *rPGray = NULL;
	const INT32 PictureWidth = 320;       /* Image width */
	const INT32 PictureHeight = 240;      /* Image height */

	char pStr[2048];                /* String Buffer for logging output */
//********************************************************************************************************************
//识别器声明
	//人脸检测
	HDETECTION FaceDetect = NULL;   
	HDETECTION rFaceDetect = NULL;
	HDTRESULT FaceDetectResult = NULL;    
	HDTRESULT rFaceDetectResult = NULL;

	//脸部器官检测
	HPOINTER FacePartsDetect = NULL;   
	HPOINTER rFacePartsDetect = NULL;
	HPTRESULT FacePartsDetectResult = NULL;   
	HPTRESULT rFacePartsDetectResult = NULL;

	//人脸识别		
	HFEATURE FaceFeature = NULL;
	HFEATURE rFaceFeature = NULL;
	HALBUM FaceFeatureAlbum = NULL;
	HALBUM rFaceFeatureAlbum = NULL;

	//人眼张开程度检测
	HEYEOPEN EyeOpenDetect = NULL;
	HEYEOPEN rEyeOpenDetect = NULL;


	//人眼视线
	HGAZEBLINK EyeGazeBlinkDetect = NULL;
	HGAZEBLINK rEyeGazeBlinkDetect = NULL;
	HGBRESULT EyeGazeBlinkDetectResult = NULL;
	HGBRESULT rEyeGazeBlinkDetectResult = NULL;

	//微笑程度检测
	HSMILE SmileDetect = NULL;
	HSMILE rSmileDetect = NULL;
	HSMRESULT SmileDetectResult = NULL;
	HSMRESULT rSmileDetectResult = NULL;

	//年龄估计
	HAGE AgeDetect = NULL;        
	HAGE rAgeDetect = NULL;
	HAGRESULT AgeDetectResult = NULL;     
	HAGRESULT rAgeDetectResult = NULL;

	//性别估计
	HGENDER GenderDetect = NULL;        
	HGENDER rGenderDetect = NULL;
	HGNRESULT GenderDetectResult = NULL;    
	HGNRESULT rGenderDetectResult = NULL;
//识别器声明完成

//初始化过程
	
	for (i = 0; i < 10; i++)   //进行10次面部识别器创建尝试
	{
		FaceDetect = OKAO_CreateDetection();
		if (FaceDetect != NULL)
			break;
	}
	if (i == 10)   //面部识别器创建失败
	{
		AfxMessageBox("Creating Face Detection handle failed"); return 0;
	}

	for (i = 0; i < 10; i++)   //进行10次面部识别器创建尝试
	{
		rFaceDetect = OKAO_CreateDetection();
		if (rFaceDetect != NULL)
			break;
	}
	if (i == 10)   //面部识别器创建失败
	{
		AfxMessageBox("Creating Face Detection handle failed"); return 0;
	}

	for (i = 0; i < 10; i++)  //进行10次面部识别结果管理器创建尝试
	{
		FaceDetectResult = OKAO_CreateDtResult(pointer->iMaxFaceCount, 0);
		if (FaceDetectResult != NULL)
			break;
	}
	if (i == 10)  //面部识别结果管理器创建失败
	{
		AfxMessageBox("Creating Face Detection result handle failed"); return 0;
	}

	for (i = 0; i < 10; i++)  //进行10次面部识别结果管理器创建尝试
	{
		rFaceDetectResult = OKAO_CreateDtResult(pointer->iMaxFaceCount, 0);
		if (rFaceDetectResult != NULL)
			break;
	}
	if (i == 10)  //面部识别结果管理器创建失败
	{
		AfxMessageBox("Creating Face Detection result handle failed"); return 0;
	}

	OKAO_SetDtMode(FaceDetect, DT_MODE_DEFAULT);  //设置面部识别模式
	OKAO_SetDtFaceSizeRange(FaceDetect, 60, 220);   //设置识别器所能识别的最小和最大脸部大小

	OKAO_SetDtMode(rFaceDetect, DT_MODE_DEFAULT);  //设置面部识别模式
	OKAO_SetDtFaceSizeRange(rFaceDetect, 60, 220);   //设置识别器所能识别的最小和最大脸部大小


	
	for (i = 0; i < 10; i++)    //进行10次脸部器官识别器创建尝试
	{
		FacePartsDetect = OKAO_PT_CreateHandle();
		if (FacePartsDetect != NULL)
			break;
	}
	if (i == 10)      //面部器官识别器创建失败
	{
		AfxMessageBox("Creating Facial Parts Detection handle failed"); return 0;
	}

	for (i = 0; i < 10; i++)    //进行10次脸部器官识别器创建尝试
	{
		rFacePartsDetect = OKAO_PT_CreateHandle();
		if (rFacePartsDetect != NULL)
			break;
	}

	if (i == 10)      //面部器官识别器创建失败
	{
		AfxMessageBox("Creating Facial Parts Detection handle failed"); return 0;
	}

	for (i = 0; i < 10; i++)    //进行10次脸部器官识别结果管理器创建尝试
	{
		FacePartsDetectResult = OKAO_PT_CreateResultHandle();
		if (FacePartsDetectResult != NULL)
			break;
	}
	if (i == 10)    //面部器官识别结果管理器创建失败
	{
		AfxMessageBox("Creating Facial Parts Detection result handle failed"); return 0;
	}

	for (i = 0; i < 10; i++)    //进行10次脸部器官识别结果管理器创建尝试
	{
		rFacePartsDetectResult = OKAO_PT_CreateResultHandle();
		if (rFacePartsDetectResult != NULL)
			break;
	}
	if (i == 10)    //面部器官识别结果管理器创建失败
	{
		AfxMessageBox("Creating Facial Parts Detection result handle failed"); return 0;
	}


	for (i = 0; i < 10; i++)     	//进行10次人脸特征识别器创建尝试
	{
		FaceFeature = OKAO_FR_CreateFeatureHandle();
		if (FaceFeature != NULL)
			break;
	}
	if (i == 10)      //人脸特征识别器创建失败
	{
		AfxMessageBox("Creating Face recognition handle failed"); return 0;
	}

	for (i = 0; i < 10; i++)     	//进行10次人脸特征识别器创建尝试
	{
		rFaceFeature = OKAO_FR_CreateFeatureHandle();
		if (rFaceFeature != NULL)
			break;
	}
	if (i == 10)      //人脸特征识别器创建失败
	{
		AfxMessageBox("Creating Face recognition handle failed"); return 0;
	}


	for (i = 0; i < 10; i++)    //按照预设的参数进行人脸特征识别相簿的创建尝试,最大用户人数6,每人最大特征数10
	{
		FaceFeatureAlbum = OKAO_FR_CreateAlbumHandle(pointer->nMaxUserNum, pointer->nMaxDataNum);//maxUserNum=6,maxDataNumPerUser=10
		if (FaceFeatureAlbum != NULL)
			break;
	}
	if (i == 10)    //特征相簿创建失败
	{
		AfxMessageBox("Creating Album handle failed"); return 0;
	}


	for (i = 0; i < 10; i++)    //按照预设的参数进行人脸特征识别相簿的创建尝试,最大用户人数6,每人最大特征数10
	{
		rFaceFeatureAlbum = OKAO_FR_CreateAlbumHandle(pointer->nMaxUserNum, pointer->nMaxDataNum);//maxUserNum=6,maxDataNumPerUser=10
		if (rFaceFeatureAlbum != NULL)
			break;
	}
	if (i == 10)    //特征相簿创建失败
	{
		AfxMessageBox("Creating Album handle failed"); return 0;
	}


	
	for (i = 0; i < 10; i++)     //进行10次睁眼识别器的创建尝试
	{
		EyeOpenDetect = OKAO_CreateEyeOpen();
		if (EyeOpenDetect != NULL)
			break;
	}
	if (i == 10)    //睁眼识别器创建失败
	{
		AfxMessageBox("Creating Eye Open-close Estimation handle failed"); return 0;
	}

	for (i = 0; i < 10; i++)     //进行10次睁眼识别器的创建尝试
	{
		rEyeOpenDetect = OKAO_CreateEyeOpen();
		if (rEyeOpenDetect != NULL)
			break;
	}
	if (i == 10)    //睁眼识别器创建失败
	{
		AfxMessageBox("Creating Eye Open-close Estimation handle failed"); return 0;
	}

	for (i = 0; i < 10; i++)    //进行10次视线识别器的创建尝试
	{
		EyeGazeBlinkDetect = OKAO_GB_CreateHandle();
		if (EyeGazeBlinkDetect != NULL)
			break;
	}
	if (i == 10)      //视线识别器创建失败
	{
		AfxMessageBox("Creating Creates Gaze and Blink Estimation handle failed"); return 0;
	}

	for (i = 0; i < 10; i++)    //进行10次视线识别器的创建尝试
	{
		rEyeGazeBlinkDetect = OKAO_GB_CreateHandle();
		if (rEyeGazeBlinkDetect != NULL)
			break;
	}
	if (i == 10)      //视线识别器创建失败
	{
		AfxMessageBox("Creating Creates Gaze and Blink Estimation handle failed"); return 0;
	}

	for (i = 0; i < 10; i++)     //进行10次视线识别结果管理器的创建尝试
	{
		EyeGazeBlinkDetectResult = OKAO_GB_CreateResultHandle();
		if (EyeGazeBlinkDetectResult != NULL)
			break;
	}
	if (i == 10)     //视线识别结果管理器创建失败
	{
		AfxMessageBox("Creates Gaze and Blink Estimation Result handle failed"); return 0;
	}

	for (i = 0; i < 10; i++)     //进行10次视线识别结果管理器的创建尝试
	{
		rEyeGazeBlinkDetectResult = OKAO_GB_CreateResultHandle();
		if (rEyeGazeBlinkDetectResult != NULL)
			break;
	}
	if (i == 10)     //视线识别结果管理器创建失败
	{
		AfxMessageBox("Creates Gaze and Blink Estimation Result handle failed"); return 0;
	}
	
	for (i = 0; i < 10; i++)    //进行10次微笑识别器的创建尝试
	{
		SmileDetect = OKAO_SM_CreateHandle();
		if (SmileDetect != NULL)
			break;
	}
	if (i == 10)     //微笑识别器创建失败
	{
		AfxMessageBox("Creating Smile Degree Estimation handle failed"); return 0;
	}

	for (i = 0; i < 10; i++)    //进行10次微笑识别器的创建尝试
	{
		rSmileDetect = OKAO_SM_CreateHandle();
		if (rSmileDetect != NULL)
			break;
	}
	if (i == 10)     //微笑识别器创建失败
	{
		AfxMessageBox("Creating Smile Degree Estimation handle failed"); return 0;
	}

	for (i = 0; i < 10; i++)     //进行10次微笑识别结果管理器的创建尝试
	{
		SmileDetectResult = OKAO_SM_CreateResultHandle();
		if (SmileDetectResult != NULL)
			break;
	}
	if (i == 10)     //微笑识别结果管理器创建失败
	{
		AfxMessageBox("Creating Smile Degree Estimation result handle failed"); return 0;
	}

	for (i = 0; i < 10; i++)     //进行10次微笑识别结果管理器的创建尝试
	{
		rSmileDetectResult = OKAO_SM_CreateResultHandle();
		if (rSmileDetectResult != NULL)
			break;
	}
	if (i == 10)     //微笑识别结果管理器创建失败
	{
		AfxMessageBox("Creating Smile Degree Estimation result handle failed"); return 0;
	}


	for (i = 0; i < 10; i++)     //进行10次年龄识别器的创建尝试
	{
		AgeDetect = OKAO_AG_CreateHandle();
		if (AgeDetect != NULL)
			break;
	}
	if (i == 10)      //年龄识别器创建失败
	{
		AfxMessageBox("Creating Age Estimation handle failed"); return 0;
	}

	for (i = 0; i < 10; i++)     //进行10次年龄识别器的创建尝试
	{
		rAgeDetect = OKAO_AG_CreateHandle();
		if (rAgeDetect != NULL)
			break;
	}
	if (i == 10)      //年龄识别器创建失败
	{
		AfxMessageBox("Creating Age Estimation handle failed"); return 0;
	}

	for (i = 0; i < 10; i++)    //进行10次年龄识别结果管理器的创建尝试
	{
		AgeDetectResult = OKAO_AG_CreateResultHandle();
		if (AgeDetectResult != NULL)
			break;
	}
	if (i == 10)    //年龄识别结果管理器创建失败
	{
		AfxMessageBox("Creating Age Estimation result handle failed"); return 0;
	}

	for (i = 0; i < 10; i++)    //进行10次年龄识别结果管理器的创建尝试
	{
		rAgeDetectResult = OKAO_AG_CreateResultHandle();
		if (rAgeDetectResult != NULL)
			break;
	}
	if (i == 10)    //年龄识别结果管理器创建失败
	{
		AfxMessageBox("Creating Age Estimation result handle failed"); return 0;
	}

	for (i = 0; i < 10; i++)    //进行10次性别识别器的创建尝试
	{
		GenderDetect = OKAO_GN_CreateHandle();
		if (GenderDetect != NULL)
			break;
	}
	if (i == 10)    //性别识别器创建失败
	{
		AfxMessageBox("Creating Gender Estimation handle failed"); return 0;
	}

	for (i = 0; i < 10; i++)    //进行10次性别识别器的创建尝试
	{
		rGenderDetect = OKAO_GN_CreateHandle();
		if (rGenderDetect != NULL)
			break;
	}
	if (i == 10)    //性别识别器创建失败
	{
		AfxMessageBox("Creating Gender Estimation handle failed"); return 0;
	}

	for (i = 0; i < 10; i++)    //进行10次性别识别结果管理器的创建尝试
	{
		GenderDetectResult = OKAO_GN_CreateResultHandle();
		if (GenderDetectResult != NULL)
			break;
	}
	if (i == 10)    //性别识别结果管理器创建失败
	{
		AfxMessageBox("Creating Gender Estimation result handle failed"); return 0;
	}

	for (i = 0; i < 10; i++)    //进行10次性别识别结果管理器的创建尝试
	{
		rGenderDetectResult = OKAO_GN_CreateResultHandle();
		if (rGenderDetectResult != NULL)
			break;
	}
	if (i == 10)    //性别识别结果管理器创建失败
	{
		AfxMessageBox("Creating Gender Estimation result handle failed"); return 0;
	}

//初始化完成
//********************************************************************************************************************


	int framenum = 0;

	width = pointer->frame->width;   //宽度
	height = pointer->frame->height;    //高度
	iBytePerLine = pointer->frame->widthStep;
	CPen pen_male, pen_female, pen_noGender, pen_open;

	pen_male.CreatePen(PS_SOLID, 1, RGB(20, 20, 255));//创建画笔
	pen_female.CreatePen(PS_SOLID, 1, RGB(255, 20, 20));//
	pen_noGender.CreatePen(PS_SOLID, 1, RGB(255, 255, 20));//
	pen_open.CreatePen(PS_SOLID, 1, RGB(20, 255, 20));//


	char cGender;

	int state_lEye, state_rEye;//0:合上,1:半开,2:睁开
	int rState_lEye, rState_rEye;//0:合上,1:半开,2:睁开
	CString sSmile, sAge, sUser;
	CString LeftEyeState, RightEyeState;
	CString rLeftEyeState, rRightEyeState;

	POINT mouthPoint_l, mouthPoint_c, mouthPoint_r, mouthPoint_t;
	POINT startPoint_smile, endPoint_smile;
	POINT rMouthPoint_l, rMouthPoint_c, rMouthPoint_r, rMouthPoint_t;
	POINT rStartPoint_smile, rEndPoint_smile;


	RECT rect_face, rect_lEye, rect_rEye;//面部、左右眼矩形
	RECT rRect_face, rRect_lEye, rRect_rEye;

	RECT rect_smile;   //笑容矩形
	RECT rRect_smile;

	pGray = (RAWIMAGE *)malloc(PictureWidth * PictureHeight * sizeof(RAWIMAGE));   //为图片申请内存
	rPGray = (RAWIMAGE *)malloc(PictureWidth * PictureHeight * sizeof(RAWIMAGE));
	memset(pStr, 0, sizeof(pStr));    //内存初始化
	pDC->SetBkMode(TRANSPARENT);     //取消输出字符串或图形的背景色
	pDC->SetTextColor(RGB(255, 0, 0));   //设置文字颜色
	while (pointer->isCamOpen)    //当摄像头启动时进行
	{
	//	pointer->frame = cvQueryFrame(pointer->capture);  //捕获图像

		cvGrabFrame(pointer->rightCamera);
		cvGrabFrame(pointer->capture);
		pointer->rightFrame = cvRetrieveFrame(pointer->rightCamera);
		pointer->frame = cvRetrieveFrame(pointer->capture);

		if (pointer->frame->origin == 1)		//将图像原点转换至左上
		{
			cvFlip(pointer->frame, NULL, 0);
			cvFlip(pointer->rightFrame, NULL, 0);
		}
	
		//获取灰度图像
		pImgData = (BYTE*)pointer->frame->imageData;
		pRImgData = (BYTE*)pointer->rightFrame->imageData;

		if (pointer->frame->nChannels == 1)//灰度图像
		{
			for (i = 0; i < PictureHeight; i++)
			{
				for (j = 0; j < PictureWidth; j++)
				{
					pGray[i*PictureWidth + j] = pImgData[i*iBytePerLine + j];
					rPGray[i*PictureWidth + j] = pRImgData[i*iBytePerLine + j];
				}
			}
		}
		else if (pointer->frame->nChannels == 3)//彩色图像
		{
			for (i = 0; i < PictureHeight; i++)
			{
				for (j = 0; j < PictureWidth; j++)
				{
					int ColorTemp = i*iBytePerLine + j * 3;
					r = pImgData[ColorTemp + 2];
					g = pImgData[ColorTemp + 1];
					b = pImgData[ColorTemp];
					pGray[i*PictureWidth + j] = RAWIMAGE(r*0.30 + g*0.59 + b*0.11);
					r = pRImgData[ColorTemp + 2];
					g = pRImgData[ColorTemp + 1];
					b = pRImgData[ColorTemp];
					rPGray[i*PictureWidth + j] = RAWIMAGE(r*0.30 + g*0.59 + b*0.11);
				}
			}
		}
		else
		{
			AfxMessageBox("Image Format error");
			break;
		}

		if (pGray == NULL||rPGray==NULL)
			continue;
		//获取灰度图像成功
		//启动面部识别
		FunctionReturnCode = OKAO_Detection(FaceDetect, pGray, PictureWidth, PictureHeight, ACCURACY_NORMAL, FaceDetectResult);
		rFunctionReturnCode = OKAO_Detection(rFaceDetect, rPGray, PictureWidth, PictureHeight, ACCURACY_NORMAL, rFaceDetectResult);

		if (FunctionReturnCode != OKAO_NORMAL || rFunctionReturnCode != OKAO_NORMAL)
			continue;   //识别失败,重新捕获图像识别

		//获取面部识别数量
		FunctionReturnCode = OKAO_GetDtFaceCount(FaceDetectResult, &FaceCount);
		rFunctionReturnCode = OKAO_GetDtFaceCount(rFaceDetectResult, &rFaceCount);

		if (FaceCount != rFaceCount)
			continue;

		if (FunctionReturnCode != OKAO_NORMAL || rFunctionReturnCode != OKAO_NORMAL)
			continue;   //识别失败,重新捕获图像识别

		//如果当前图像上只识别到了一张脸
		if (FaceCount < 1)
		{
			pointer->cimg.CopyOf(pointer->frame);
			pointer->cimg.DrawToHDC(hDC, &rect);

			pointer->cimg.CopyOf(pointer->rightFrame);
			pointer->cimg.DrawToHDC(rHDC, &rect);
			continue;   //在用户窗口区输出,并进行下一次识别
		}
		else
		{   
			FunctionReturnCode = OKAO_GetDtFaceInfo(FaceDetectResult, 0, &info);//获取识别到的面部朝向、特征等信息
			rFunctionReturnCode = OKAO_GetDtFaceInfo(rFaceDetectResult, 0, &rInfo);

			if (FunctionReturnCode != OKAO_NORMAL || rFunctionReturnCode != OKAO_NORMAL)
				continue;   //识别失败,重新捕获图像识别
			if (info.ptLeftTop.x > 0 && info.ptRightBottom.x<320 && info.ptLeftTop.y>0 && info.ptRightBottom.y < 240)
			{              //如果识别结果合法,则为面部矩形设置参数以待输出
				rect_face.top = info.ptLeftTop.y;
				rect_face.bottom = info.ptRightBottom.y;
				rect_face.left = info.ptLeftTop.x;
				rect_face.right = info.ptRightBottom.x;
			}
			else
				continue;

			if (rInfo.ptLeftTop.x > 0 && rInfo.ptRightBottom.x<320 && rInfo.ptLeftTop.y>0 && rInfo.ptRightBottom.y < 240)
			{              //如果识别结果合法,则为面部矩形设置参数以待输出
				rRect_face.top = rInfo.ptLeftTop.y;
				rRect_face.bottom = rInfo.ptRightBottom.y;
				rRect_face.left = rInfo.ptLeftTop.x;
				rRect_face.right = rInfo.ptRightBottom.x;
			}
			else
				continue;

			//下面进行面部细节识别
			iTemp1 = 0;
			//通过识别到的面部结果设置面部位置
			FunctionReturnCode = OKAO_PT_SetPositionFromHandle(FacePartsDetect, FaceDetectResult, 0);
			rFunctionReturnCode = OKAO_PT_SetPositionFromHandle(rFacePartsDetect, rFaceDetectResult, 0);
			if (FunctionReturnCode == OKAO_NORMAL&&rFunctionReturnCode == OKAO_NORMAL)
			{					//执行面部细节识别
				FunctionReturnCode = OKAO_PT_DetectPoint(FacePartsDetect, pGray, PictureWidth, PictureHeight, FacePartsDetectResult);
				rFunctionReturnCode = OKAO_PT_DetectPoint(rFacePartsDetect, rPGray, PictureWidth, PictureHeight, rFacePartsDetectResult);

				if (FunctionReturnCode == OKAO_NORMAL&&rFunctionReturnCode == OKAO_NORMAL)
				{				//获取面部细节结果
					FunctionReturnCode = OKAO_PT_GetResult(FacePartsDetectResult, PT_POINT_KIND_MAX, aptPoint, anConf);
					rFunctionReturnCode = OKAO_PT_GetResult(rFacePartsDetectResult, PT_POINT_KIND_MAX, rAptPoint, rAnConf);

					if (FunctionReturnCode == OKAO_NORMAL&&rFunctionReturnCode == OKAO_NORMAL)
					{
						iTemp1 = 1;
					}
				}
			}
			if (iTemp1 == 0)//面部细节识别失败
			{
				pointer->cimg.CopyOf(pointer->frame);
				pointer->cimg.DrawToHDC(hDC, &rect);
				pDC->SelectObject(&pen_noGender);
				pDC->MoveTo(rect_face.left, rect_face.top);  //移动到某点
				pDC->LineTo(rect_face.right, rect_face.top);   //画线
				pDC->LineTo(rect_face.right, rect_face.bottom);
				pDC->LineTo(rect_face.left, rect_face.bottom);
				pDC->LineTo(rect_face.left, rect_face.top);     //完成矩形的绘制

				pointer->cimg.CopyOf(pointer->rightFrame);
				pointer->cimg.DrawToHDC(rHDC, &rRect);
				rPDC->SelectObject(&pen_noGender);
				rPDC->MoveTo(rRect_face.left, rRect_face.top);  //移动到某点
				rPDC->LineTo(rRect_face.right, rRect_face.top);   //画线
				rPDC->LineTo(rRect_face.right, rRect_face.bottom);
				rPDC->LineTo(rRect_face.left, rRect_face.bottom);
				rPDC->LineTo(rRect_face.left, rRect_face.top);     //完成矩形的绘制

				continue;   //执行下一张图片的捕获
			}
			//面部细节识别成功
			mouthPoint_l = aptPoint[PT_POINT_MOUTH_LEFT];    //嘴的左角坐标
			mouthPoint_r = aptPoint[PT_POINT_MOUTH_RIGHT];     //嘴的右角坐标
			mouthPoint_c = aptPoint[PT_POINT_MOUTH];    //嘴的中部坐标
			mouthPoint_t = aptPoint[PT_POINT_MOUTH_UP];    //嘴的上部坐标

			rMouthPoint_l = rAptPoint[PT_POINT_MOUTH_LEFT];    //嘴的左角坐标
			rMouthPoint_r = rAptPoint[PT_POINT_MOUTH_RIGHT];     //嘴的右角坐标
			rMouthPoint_c = rAptPoint[PT_POINT_MOUTH];    //嘴的中部坐标
			rMouthPoint_t = rAptPoint[PT_POINT_MOUTH_UP];    //嘴的上部坐标


			//睁眼程度测试
			//通过识别到的面部细节为睁眼程度测试设置识别特征点
			FunctionReturnCode = OKAO_SetEoPoint(EyeOpenDetect, FacePartsDetectResult);
			rFunctionReturnCode = OKAO_SetEoPoint(rEyeOpenDetect, rFacePartsDetectResult);
			if (FunctionReturnCode == OKAO_NORMAL&&rFunctionReturnCode == OKAO_NORMAL)
			{		//通过睁眼识别器设置指定部分开合程度
				FunctionReturnCode = OKAO_SetEoParts(EyeOpenDetect, EO_PARTS_LEFTEYE | EO_PARTS_RIGHTEYE);
				rFunctionReturnCode = OKAO_SetEoParts(rEyeOpenDetect, EO_PARTS_LEFTEYE | EO_PARTS_RIGHTEYE);
				if (FunctionReturnCode == OKAO_NORMAL&&rFunctionReturnCode == OKAO_NORMAL)
				{			//判断眼睛开合
					FunctionReturnCode = OKAO_EyeOpen(EyeOpenDetect, pGray, PictureWidth, PictureHeight);
					rFunctionReturnCode = OKAO_EyeOpen(rEyeOpenDetect, rPGray, PictureWidth, PictureHeight);
					if (FunctionReturnCode == OKAO_NORMAL&&rFunctionReturnCode == OKAO_NORMAL)
					{		
						if ((OKAO_GetEoLevelL(EyeOpenDetect, &LeftEyeOpenLevel) == OKAO_NORMAL) //获取左眼开合程度
							&& (OKAO_GetEoLevelR(EyeOpenDetect, &RightEyeOpenLevel) == OKAO_NORMAL)
							&& (OKAO_GetEoLevelL(rEyeOpenDetect, &rLeftEyeOpenLevel) == OKAO_NORMAL)
							&& (OKAO_GetEoLevelR(rEyeOpenDetect, &rRightEyeOpenLevel) == OKAO_NORMAL))//获取右眼开合程度
						{	//两只眼睛都获取成功
							if (pointer->flag_CamState == 1)//检测摄像头状态,处于面部识别状态
							{
								//将最新的左眼开合程度放入vector数组最前面
								vLEye.insert(vLEye.begin(), LeftEyeOpenLevel);
								rVLEye.insert(rVLEye.begin(), rLeftEyeOpenLevel);

								totalLEye += LeftEyeOpenLevel;
								rTotalLEye += rLeftEyeOpenLevel;
								//右眼同理
								vREye.insert(vREye.begin(), RightEyeOpenLevel);
								rVREye.insert(rVREye.begin(), rRightEyeOpenLevel);

								totalREye += RightEyeOpenLevel;
								rTotalREye += rRightEyeOpenLevel;

								iTemp3 = vLEye.size();
								if (iTemp3 > 10)  //如果vector数组中获取了10个以上的数据
								{
									//删去最末端的一个数据,同时从total变量中减去该值
									totalLEye = totalLEye - vLEye.back();
									totalREye = totalREye - vREye.back();

									vLEye.pop_back();
									vREye.pop_back();
									iTemp3--;
								}

								//获取vector数组中所有元素的平均值
								iTemp1 = totalLEye / iTemp3;
								iTemp2 = totalREye / iTemp3;

								
								if (iTemp2 <= pointer->iREyeClose)//右眼闭合
								{
									state_rEye = 0;		//标志位记录闭合状态
									RightEyeState = "Close";
								}
								else if (iTemp2 <= pointer->iREyeOpen) //右眼半开
								{
									state_rEye = 1;
									RightEyeState = "Half-Open";
								}
								else    //右眼睁开
								{
									state_rEye = 2;
									RightEyeState = "Open";
								}
								
								//左眼同理

								if (iTemp1 <= pointer->iLEyeClose)
								{
									state_lEye = 0;
									LeftEyeState = "Close";
								}
								else if (iTemp1 <= pointer->iLEyeOpen)
								{
									state_lEye = 1;
									LeftEyeState = "Half-Open";
								}
								else
								{
									state_lEye = 2;
									LeftEyeState = "Open";
								}

								iTemp3 = rVLEye.size();
								if (iTemp3 > 10)  //如果vector数组中获取了10个以上的数据
								{
									//删去最末端的一个数据,同时从total变量中减去该值
									rTotalLEye = rTotalLEye - rVLEye.back();
									rTotalREye = rTotalREye - rVREye.back();

									rVLEye.pop_back();
									rVREye.pop_back();
									iTemp3--;
								}


								//获取vector数组中所有元素的平均值
								iTemp1 = rTotalLEye / iTemp3;
								iTemp2 = rTotalREye / iTemp3;


								if (iTemp2 <= pointer->iREyeClose)//右眼闭合
								{
									rState_rEye = 0;		//标志位记录闭合状态
									rRightEyeState = "Close";
								}
								else if (iTemp2 <= pointer->iREyeOpen) //右眼半开
								{
									rState_rEye = 1;
									rRightEyeState = "Half-Open";
								}
								else    //右眼睁开
								{
									rState_rEye = 2;
									rRightEyeState = "Open";
								}

								//左眼同理

								if (iTemp1 <= pointer->iLEyeClose)
								{
									rState_lEye = 0;
									rLeftEyeState = "Close";
								}
								else if (iTemp1 <= pointer->iLEyeOpen)
								{
									rState_lEye = 1;
									rLeftEyeState = "Half-Open";
								}
								else
								{
									rState_lEye = 2;
									rLeftEyeState = "Open";
								}
							}
							else if (pointer->flag_CamState == 2)//处于修正状态
							{
								iLReady = 0;
								vLEye.clear();
								totalLEye = 0;
								rVLEye.clear();
								rTotalLEye = 0;

								iRReady = 0;
								vREye.clear();
								totalREye = 0;
								rVREye.clear();
								rTotalREye = 0;

								pointer->flag_CamState = 3;  //调整为修正中态
							}

							//记录若干帧数值，然后取平均值，将平均值向下延伸若干数值，作为最小睁眼率
							if (pointer->flag_CamState == 3)//参数测试状态
							{
								if (iLReady == 0)//左眼还未到稳定状态
								{
									vLEye.push_back(LeftEyeOpenLevel);
									totalLEye += LeftEyeOpenLevel;

									rVLEye.push_back(rLeftEyeOpenLevel);
									rTotalLEye += rLeftEyeOpenLevel;

									if (vLEye.size() >= 60 && rVLEye.size() >= 60)   //当获取到了60张图片的数据时进行下一步
									{
											pointer->iLEyeOpen = (totalLEye + rTotalLEye) / (vLEye.size() + rVLEye.size()) - 50;
											pointer->iLEyeClose = pointer->iLEyeOpen - 40;
											iLReady = 1;    //左眼完成校准
									}
								}

								if (iRReady == 0)//右眼同上
								{
									vREye.push_back(RightEyeOpenLevel);
									totalREye += RightEyeOpenLevel;

									rVREye.push_back(rRightEyeOpenLevel);
									rTotalREye += rRightEyeOpenLevel;

									if (vREye.size() >= 60 && rVREye.size() >= 60)
									{
											pointer->iREyeOpen = (totalREye+rTotalREye) / (vREye.size()+rVREye.size()) - 50;
											pointer->iREyeClose = pointer->iREyeOpen - 40;
											iRReady = 1;    
									}
								}
								if ((iLReady == 1) && (iRReady == 1))//左右眼都完成了校准
								{
									pointer->flag_CamState = 1;   //切换回面部识别状态

									//数据清空,重置
									vLEye.clear();
									totalLEye = 0;
									vREye.clear();
									totalREye = 0;

									rVLEye.clear();
									rTotalLEye = 0;
									rVREye.clear();
									rTotalREye = 0;

									//将开合率设置给多个控件,具体作用不明
									pointer->SetDlgItemInt(IDC_LEYE1, pointer->iLEyeOpen);
									pointer->SetDlgItemInt(IDC_LEYE2, pointer->iLEyeClose);
									pointer->SetDlgItemInt(IDC_REYE1, pointer->iREyeOpen);
									pointer->SetDlgItemInt(IDC_REYE2, pointer->iREyeClose);
									AfxMessageBox("Testing success!");
								}
							}
						}
					}
				}
			}

			//将左眼用矩形标识出来			
			iTemp4 = min(aptPoint[PT_POINT_LEFT_EYE_OUT].y, aptPoint[PT_POINT_LEFT_EYE_IN].y);//左眼内径高度
			iTemp5 = max(aptPoint[PT_POINT_LEFT_EYE_OUT].y, aptPoint[PT_POINT_LEFT_EYE_IN].y);//左眼外径高度
			iTemp4 -= 10;  //容差调整
			iTemp5 += 5;
			//矩形参数初始化
			rect_lEye.top = iTemp4;
			rect_lEye.bottom = iTemp5;
			rect_lEye.left = aptPoint[PT_POINT_LEFT_EYE_OUT].x - 5;
			rect_lEye.right = aptPoint[PT_POINT_LEFT_EYE_IN].x + 3;

			//r左眼
			iTemp4 = min(rAptPoint[PT_POINT_LEFT_EYE_OUT].y, rAptPoint[PT_POINT_LEFT_EYE_IN].y);//左眼内径高度
			iTemp5 = max(rAptPoint[PT_POINT_LEFT_EYE_OUT].y, rAptPoint[PT_POINT_LEFT_EYE_IN].y);//左眼外径高度
			iTemp4 -= 10;  //容差调整
			iTemp5 += 5;
			//矩形参数初始化
			rRect_lEye.top = iTemp4;
			rRect_lEye.bottom = iTemp5;
			rRect_lEye.left = rAptPoint[PT_POINT_LEFT_EYE_OUT].x - 5;
			rRect_lEye.right = rAptPoint[PT_POINT_LEFT_EYE_IN].x + 3;


			//右眼同上				
			iTemp4 = min(aptPoint[PT_POINT_RIGHT_EYE_OUT].y, aptPoint[PT_POINT_RIGHT_EYE_IN].y);
			iTemp5 = max(aptPoint[PT_POINT_RIGHT_EYE_OUT].y, aptPoint[PT_POINT_RIGHT_EYE_IN].y);
			iTemp4 -= 10;
			iTemp5 += 5;
			rect_rEye.top = iTemp4;
			rect_rEye.bottom = iTemp5;
			rect_rEye.left = aptPoint[PT_POINT_RIGHT_EYE_IN].x - 3;
			rect_rEye.right = aptPoint[PT_POINT_RIGHT_EYE_OUT].x + 5;

			//r右眼
			iTemp4 = min(rAptPoint[PT_POINT_RIGHT_EYE_OUT].y, rAptPoint[PT_POINT_RIGHT_EYE_IN].y);
			iTemp5 = max(rAptPoint[PT_POINT_RIGHT_EYE_OUT].y, rAptPoint[PT_POINT_RIGHT_EYE_IN].y);
			iTemp4 -= 10;
			iTemp5 += 5;
			rRect_rEye.top = iTemp4;
			rRect_rEye.bottom = iTemp5;
			rRect_rEye.left = rAptPoint[PT_POINT_RIGHT_EYE_IN].x - 3;
			rRect_rEye.right = rAptPoint[PT_POINT_RIGHT_EYE_OUT].x + 5;



			//面部特征识别
			FunctionReturnCode = 0;
			rFunctionReturnCode = 0;
			strTemp1 = "";
			if (pointer->nRegisteredUserNum > 0)// 已经被保存的用户数量大于0
				//从面部器官识别结果提取面部特征
			{
				FunctionReturnCode = OKAO_FR_ExtractFeatureFromPtHdl(FaceFeature, pGray, PictureWidth, PictureHeight, FacePartsDetectResult);
				rFunctionReturnCode = OKAO_FR_ExtractFeatureFromPtHdl(rFaceFeature, rPGray, PictureWidth, PictureHeight, rFacePartsDetectResult);
			}
			
			if (FunctionReturnCode == OKAO_NORMAL&&rFunctionReturnCode == OKAO_NORMAL)  //如果提取正常完成
			{
				INT32 similarity = 0;

				FetureSimilarityTemp1 = 0; 
				j = 0; 
				FetureSimilarityTemp2 = 0;
				for (i = 0; i<pointer->nRegisteredUserNum; i++)
				{
					OKAO_FR_Verify(FaceFeature, FaceFeatureAlbum, i, &FetureSimilarityTemp1);//将面部特征识别结果与相簿中的数据进行匹配
					
					if (FetureSimilarityTemp1 > FetureSimilarityTemp2)		//如果当前特征相似度大于之前相似度，则进行替换
					{
						FetureSimilarityTemp2 = FetureSimilarityTemp1; 
						j = i;
						if (FetureSimilarityTemp1 > 900)break;//如果相似度大于90%,则匹配成功
					}
				}

				similarity += FetureSimilarityTemp2;

				FetureSimilarityTemp1 = 0;
				j = 0;
				FetureSimilarityTemp2 = 0;
				for (i = 0; i<pointer->nRegisteredUserNum; i++)
				{
					OKAO_FR_Verify(FaceFeature,rFaceFeatureAlbum, i, &FetureSimilarityTemp1);//将面部特征识别结果与相簿中的数据进行匹配

					if (FetureSimilarityTemp1 > FetureSimilarityTemp2)		//如果当前特征相似度大于之前相似度，则进行替换
					{
						FetureSimilarityTemp2 = FetureSimilarityTemp1;
						j = i;
						if (FetureSimilarityTemp1 > 900)break;//如果相似度大于90%,则匹配成功
					}
				}

				similarity += FetureSimilarityTemp2;
				similarity /= 2;

				if (similarity > 700)//相似度大于70%，认为匹配成功
				{
					strTemp1 = pointer->pStrUserList[j];	//提取匹配成功的用户名称
				}
			}

			sUser = strTemp1;  //如果面部特征识别成功则为特征匹配的用户名称，否则为空

			//添加用户信息
			if (pointer->flag_faceRecognitionState == 2)//人脸信息注册
			{
				if (pointer->nRegisteredUserNum == 0) //如果数据库中没有注册信息,则使用捕获的图像以及识别的面部器官进行识别
				{
					FunctionReturnCode = OKAO_FR_ExtractFeatureFromPtHdl(FaceFeature, pGray, PictureWidth, PictureHeight, FacePartsDetectResult);
					rFunctionReturnCode = OKAO_FR_ExtractFeatureFromPtHdl(rFaceFeature, rPGray, PictureWidth, PictureHeight, rFacePartsDetectResult);
				}
				if (FunctionReturnCode == OKAO_NORMAL&&rFunctionReturnCode == OKAO_NORMAL)	//如果特征提取成功
				{
							//将特征数据注册到面部特征识别管理器中
					OKAO_FR_RegisterData(FaceFeatureAlbum, FaceFeature, pointer->nRegisteredUserNum, pointer->nCurDataNum);
					OKAO_FR_RegisterData(rFaceFeatureAlbum, rFaceFeature, pointer->nRegisteredUserNum, pointer->nCurDataNum);

					pointer->nCurDataNum++;   //改变当前注册特征数
					pointer->flag_faceRecognitionState = 1;    //进入正常识别状态
					if (pointer->nCurDataNum < pointer->nMaxDataNum)	//如果注册特征数量未达到最大值
					{
						strTemp1.Format("%d/10", pointer->nCurDataNum + 1);	//设置当前注册特征数量
						pointer->GetDlgItem(IDC_FEATURE_NUM)->SetWindowText(strTemp1);	//显示当前注册特征数量
					}
					else
					{
						pointer->OnBnClickedAdduser();	//调用添加用户按钮的点击函数
					}
				}
			}


			//使用面部器官识别结果为微笑程度识别器设置特征点
			FunctionReturnCode = OKAO_SM_SetPointFromHandle(SmileDetect, FacePartsDetectResult);
			rFunctionReturnCode = OKAO_SM_SetPointFromHandle(rSmileDetect, rFacePartsDetectResult);
			strTemp1 = "";
			if (FunctionReturnCode == OKAO_NORMAL&&rFunctionReturnCode == OKAO_NORMAL)	//设置特征点成功
			{
				FunctionReturnCode = OKAO_SM_Estimate(SmileDetect, pGray, PictureWidth, PictureHeight, SmileDetectResult);	//识别微笑程度，保存至微笑识别结果管理器中
				rFunctionReturnCode = OKAO_SM_Estimate(rSmileDetect, rPGray, PictureWidth, PictureHeight, rSmileDetectResult);	//识别微笑程度，保存至微笑识别结果管理器中

				if (FunctionReturnCode == OKAO_NORMAL&&rFunctionReturnCode == OKAO_NORMAL)		//识别微笑程度成功
				{
					FunctionReturnCode = OKAO_SM_GetResult(SmileDetectResult, &SmileDegree, &SmileDetectConfidence);//获取微笑程度识别结果，以及其可信度
					rFunctionReturnCode = OKAO_SM_GetResult(rSmileDetectResult, &rSmileDegree, &rSmileDetectConfidence);//获取微笑程度识别结果，以及其可信度

					if (FunctionReturnCode == OKAO_NORMAL&&rFunctionReturnCode == OKAO_NORMAL)		//获取结果成功
					{
						if (SmileDegree <= 20)		//如果微笑程度没有达到阈值
							rect_smile.top = -1;
						else
						{
							startPoint_smile.y = (mouthPoint_l.y + mouthPoint_r.y) / 2;		//设置微笑开始纵坐标
							startPoint_smile.x = mouthPoint_l.x;			//设置微笑开始横坐标
							endPoint_smile.y = startPoint_smile.y;			//设置微笑结束纵坐标

							iTemp2 = (mouthPoint_r.x - mouthPoint_l.x) / 4;	//取嘴部宽度的1/4
							//笑容矩形参数初始化
							rect_smile.top = startPoint_smile.y - iTemp2;
							rect_smile.bottom = startPoint_smile.y + iTemp2;
							rect_smile.left = mouthPoint_l.x;
							rect_smile.right = mouthPoint_r.x;
							//*************************************************************************************************
							if (SmileDegree <= 45)		//如果微笑程度小于45，设置微笑结束横坐标
								endPoint_smile.x = mouthPoint_r.x;	
							else
								endPoint_smile.x = mouthPoint_l.x;
						}

						if (rSmileDegree <= 20)		//如果微笑程度没有达到阈值
							rRect_smile.top = -1;
						else
						{
							rStartPoint_smile.y = (rMouthPoint_l.y + rMouthPoint_r.y) / 2;		//设置微笑开始纵坐标
							rStartPoint_smile.x = rMouthPoint_l.x;			//设置微笑开始横坐标
							rEndPoint_smile.y = rStartPoint_smile.y;			//设置微笑结束纵坐标

							iTemp2 = (rMouthPoint_r.x - rMouthPoint_l.x) / 4;	//取嘴部宽度的1/4
							//笑容矩形参数初始化
							rRect_smile.top = rStartPoint_smile.y - iTemp2;
							rRect_smile.bottom = rStartPoint_smile.y + iTemp2;
							rRect_smile.left = rMouthPoint_l.x;
							rRect_smile.right = rMouthPoint_r.x;
							//*************************************************************************************************
							if (rSmileDegree <= 45)		//如果微笑程度小于45，设置微笑结束横坐标
								rEndPoint_smile.x = rMouthPoint_r.x;
							else
								rEndPoint_smile.x = rMouthPoint_l.x;
						}
					}
				}
			}

			// 年龄识别器
			strTemp1 = "";
			//使用面部器官识别结果为年龄识别器设置特征点
			FunctionReturnCode = OKAO_AG_SetPointFromHandle(AgeDetect, FacePartsDetectResult);
			rFunctionReturnCode = OKAO_AG_SetPointFromHandle(rAgeDetect, rFacePartsDetectResult);
			if (FunctionReturnCode == OKAO_NORMAL&&rFunctionReturnCode == OKAO_NORMAL)		//设置特征点成功
			{
				FunctionReturnCode = OKAO_AG_Estimate(AgeDetect, pGray, PictureWidth, PictureHeight, AgeDetectResult);	//年龄识别
				rFunctionReturnCode = OKAO_AG_Estimate(rAgeDetect, rPGray, PictureWidth, PictureHeight, rAgeDetectResult);	//年龄识别

				if (FunctionReturnCode == OKAO_NORMAL&&rFunctionReturnCode == OKAO_NORMAL)	//识别年龄成功
				{
					FunctionReturnCode = OKAO_AG_GetResult(AgeDetectResult, &Age, &Confidence);//获取年龄识别结果以及可信度
					rFunctionReturnCode = OKAO_AG_GetResult(rAgeDetectResult, &rAge, &rConfidence);//获取年龄识别结果以及可信度

					if (FunctionReturnCode == OKAO_NORMAL&&rFunctionReturnCode == OKAO_NORMAL)	//获取结果成功
					{
						Age -= 2;	
						Age = (Age + rAge - 4) / 2;
						//根据年龄设置字符串
						if (Age < 12)strTemp1 = "儿童";
						else if (Age < 20)strTemp1 = "少年";
						else if (Age < 34)strTemp1 = "青年";
						else if (Age < 50)strTemp1 = "中年";
						else strTemp1 = "老年";
					}
				}
			}
			sAge = strTemp1;

			//性别识别器
			cGender = 0;
			//使用面部器官识别结果为性别识别器设置特征点
			FunctionReturnCode = OKAO_GN_SetPointFromHandle(GenderDetect, FacePartsDetectResult);
			rFunctionReturnCode = OKAO_GN_SetPointFromHandle(rGenderDetect, rFacePartsDetectResult);
			if (FunctionReturnCode == OKAO_NORMAL&&rFunctionReturnCode == OKAO_NORMAL)		//设置特征点成功
			{
				FunctionReturnCode = OKAO_GN_Estimate(GenderDetect, pGray, PictureWidth, PictureHeight, GenderDetectResult);//性别识别
				rFunctionReturnCode = OKAO_GN_Estimate(rGenderDetect, rPGray, PictureWidth, PictureHeight, rGenderDetectResult);//性别识别

				if (FunctionReturnCode == OKAO_NORMAL&&rFunctionReturnCode == OKAO_NORMAL)	//识别性别成功
				{
					FunctionReturnCode = OKAO_GN_GetResult(GenderDetectResult, &Gender, &Confidence);//获取性别识别结果以及可信度
					rFunctionReturnCode = OKAO_GN_GetResult(rGenderDetectResult, &rGender, &rConfidence);//获取性别识别结果以及可信度

					if (FunctionReturnCode == OKAO_NORMAL&&rFunctionReturnCode == OKAO_NORMAL)	//获取结果成功
					{
						if (Gender == GN_ESTIMATION_MALE&&rGender==GN_ESTIMATION_MALE)
							cGender = 1;
						else if (Gender == rGender)
							cGender = 2;
						else
							continue;
					}
				}
			}
			//画面输出到显示装置
			pointer->cimg.CopyOf(pointer->frame);
			pointer->cimg.DrawToHDC(hDC, &rect);

			pointer->cimg.CopyOf(pointer->rightFrame);
			pointer->cimg.DrawToHDC(rHDC, &rRect);

			//脸部矩形绘制，男女分别用不同颜色笔
			if (cGender == 1)
			{
				pDC->SelectObject(&pen_male); //男，蓝色
				rPDC->SelectObject(&pen_male); //男，蓝色
			}
			else if (cGender == 2)
			{
				pDC->SelectObject(&pen_female); //女，红色
				rPDC->SelectObject(&pen_female); //女，红色
			}
			else
			{
				pDC->SelectObject(&pen_noGender);  //无性别，黄色
				rPDC->SelectObject(&pen_noGender);  //无性别，黄色
			}

			//绘制操作
			pDC->MoveTo(rect_face.left, rect_face.top);
			pDC->LineTo(rect_face.right, rect_face.top);
			pDC->LineTo(rect_face.right, rect_face.bottom);
			pDC->LineTo(rect_face.left, rect_face.bottom);
			pDC->LineTo(rect_face.left, rect_face.top);

			rPDC->MoveTo(rRect_face.left, rRect_face.top);
			rPDC->LineTo(rRect_face.right, rRect_face.top);
			rPDC->LineTo(rRect_face.right, rRect_face.bottom);
			rPDC->LineTo(rRect_face.left, rRect_face.bottom);
			rPDC->LineTo(rRect_face.left, rRect_face.top);

			//左眼矩形绘制，不同开合状态使用不同颜色
			if (state_lEye == 0)
			{
				pDC->SelectObject(&pen_female);	//闭合，红色
				rPDC->SelectObject(&pen_female);	//闭合，红色
			}
			else if (state_lEye == 1)
			{
				pDC->SelectObject(&pen_noGender);	//半开，黄色
				rPDC->SelectObject(&pen_noGender);	//半开，黄色
			}
			else
			{
				pDC->SelectObject(&pen_open);		//睁开，绿色
				rPDC->SelectObject(&pen_open);		//睁开，绿色
			}
			
			//绘制操作
			pDC->MoveTo(rect_lEye.left, rect_lEye.top);
			pDC->LineTo(rect_lEye.right, rect_lEye.top);
			pDC->LineTo(rect_lEye.right, rect_lEye.bottom);
			pDC->LineTo(rect_lEye.left, rect_lEye.bottom);
			pDC->LineTo(rect_lEye.left, rect_lEye.top);

			rPDC->MoveTo(rRect_lEye.left, rRect_lEye.top);
			rPDC->LineTo(rRect_lEye.right, rRect_lEye.top);
			rPDC->LineTo(rRect_lEye.right, rRect_lEye.bottom);
			rPDC->LineTo(rRect_lEye.left, rRect_lEye.bottom);
			rPDC->LineTo(rRect_lEye.left, rRect_lEye.top);

			//如果左右眼开合状态不一致,使用另一种颜色绘制，否则使用同一种颜色
			if (state_rEye != state_lEye)
			{
				if (state_rEye == 0)
				{
					pDC->SelectObject(&pen_female);
					rPDC->SelectObject(&pen_female);
				}
				else if (state_rEye == 1)
				{
					pDC->SelectObject(&pen_noGender);
					rPDC->SelectObject(&pen_noGender);
				}
				else
				{
					pDC->SelectObject(&pen_open);
					rPDC->SelectObject(&pen_open);
				}
			}

			//绘制操作
			pDC->MoveTo(rect_rEye.left, rect_rEye.top);
			pDC->LineTo(rect_rEye.right, rect_rEye.top);
			pDC->LineTo(rect_rEye.right, rect_rEye.bottom);
			pDC->LineTo(rect_rEye.left, rect_rEye.bottom);
			pDC->LineTo(rect_rEye.left, rect_rEye.top);

			rPDC->MoveTo(rRect_rEye.left, rRect_rEye.top);
			rPDC->LineTo(rRect_rEye.right, rRect_rEye.top);
			rPDC->LineTo(rRect_rEye.right, rRect_rEye.bottom);
			rPDC->LineTo(rRect_rEye.left, rRect_rEye.bottom);
			rPDC->LineTo(rRect_rEye.left, rRect_rEye.top);

			//如果有笑容被检测到
			if (rect_smile.top > -1)
			{
				pDC->SelectObject(&pen_female);
				pDC->MoveTo(startPoint_smile);
				pDC->Arc(&rect_smile, startPoint_smile, endPoint_smile);//在笑容矩形框内画弧线标识笑容
			}

			if (rRect_smile.top > -1)
			{
				rPDC->SelectObject(&pen_female);
				rPDC->MoveTo(rStartPoint_smile);
				rPDC->Arc(&rRect_smile, rStartPoint_smile, rEndPoint_smile);//在笑容矩形框内画弧线标识笑容
			}

			//向窗口显示区域写入字符串
			pDC->TextOut(rect_face.left, rect_face.top, sAge);	//年龄
			pDC->TextOut(rect_face.left, rect_face.bottom - 20, sUser);	//当前用户名称
			pDC->TextOut(rect_face.right, rect_face.bottom, " ");	//空


			rPDC->TextOut(rRect_face.left, rRect_face.top, sAge);	//年龄
			rPDC->TextOut(rRect_face.left, rRect_face.bottom - 20, sUser);	//当前用户名称
			rPDC->TextOut(rRect_face.right, rRect_face.bottom, " ");	//空
//***********************************************************************************************************************************
//***********************************************************************************************************************************
//***********************************************************************************************************************************
	//Work Start
			
			//视线识别器
			//使用面部器官识别结果为视线识别器设置特征点
			FunctionReturnCode = OKAO_GB_SetPointFromHandle(EyeGazeBlinkDetect, FacePartsDetectResult);
			rFunctionReturnCode = OKAO_GB_SetPointFromHandle(rEyeGazeBlinkDetect, rFacePartsDetectResult);
			strTemp1 = "";
			if (FunctionReturnCode == OKAO_NORMAL&&rFunctionReturnCode == OKAO_NORMAL)	//设置特征点成功
			{
				//执行视线测定
				FunctionReturnCode = OKAO_GB_Estimate(EyeGazeBlinkDetect, pGray, PictureWidth, PictureHeight, EyeGazeBlinkDetectResult);
				rFunctionReturnCode = OKAO_GB_Estimate(rEyeGazeBlinkDetect, rPGray, PictureWidth, PictureHeight, rEyeGazeBlinkDetectResult);

				if (FunctionReturnCode == OKAO_NORMAL&&FunctionReturnCode == OKAO_NORMAL)	//测定成功
				{
					//获取视线测定结果
					FunctionReturnCode = OKAO_GB_GetGazeDirection(EyeGazeBlinkDetectResult, &pnGazeLeftRight, &pnGazeUpDown);   
					rFunctionReturnCode = OKAO_GB_GetGazeDirection(rEyeGazeBlinkDetectResult, &rPnGazeLeftRight, &rPnGazeUpDown);

					if (FunctionReturnCode == OKAO_NORMAL&&rFunctionReturnCode == OKAO_NORMAL)	//获取结果成功
					{
						//测试阶段
						/*pointer->framecnt++;*/
						HorizontalGaze = pnGazeLeftRight; //获取视线水平夹角值
						VerticalGaze = pnGazeUpDown; //获取视线垂夹角值

						rHorizontalGaze = rPnGazeLeftRight; //获取视线水平夹角值
						rVerticalGaze = rPnGazeUpDown; //获取视线垂夹角值
						//标定
						char c;
						//if (pointer->framecnt < 500)
						//{
						//	ofstream fout, rfout;
						//	fout.open("d:\\Ans.txt", ios::app);
						//	rfout.open("d:\\rAns.txt", ios::app);
						//	fout << int(HorizontalGaze) << endl;
						//	rfout << int(rHorizontalGaze) << endl;
						//	fout.close();
						//	rfout.close();
						//}
						//在LoopTime值大于100的时候才进行以下内容
						if (!ReadyToEstimation)
						{
							//移动定位窗口
							if (FrameCount%MAX5 == 0)
							{
								if (WindowPositionFlag == -1)
								{
									cvMoveWindow("exp", 0, 0);  //将exp窗口移动到左上角
									WindowPositionFlag = 0;
								}
								else if (WindowPositionFlag == 0)
								{

									cvMoveWindow("exp", int(A - 117), int(B - 87));  //将exp窗口移动到右下角
									WindowPositionFlag = 1;
								}
							}
							//移动完毕

						//	//****后期优化校准流程
							if (FrameCount == 0)
							{
								c = cvWaitKey(0);	//等待按下一个键，画面停止
							}
							if (c == 32)	//当按下空格键
							{
								if (FrameCount < MAX5)  //获取累计直到82个水平夹角值、垂直夹角值数据
								{
									horizontal[FrameCount] = int(HorizontalGaze);
									vertical[FrameCount] = int(VerticalGaze);

									rHorizontal[FrameCount] = int(rHorizontalGaze);
									rVertical[FrameCount] = int(rVerticalGaze);

									FrameCount++;
								}

								if (FrameCount == MAX5)	//当累计得到足够多的数据以后
								{
									//清空计数器
									FrameCount = 0;
									c = 0;

									//选择排序
									//将horizontal数组递增排列
									for (int i = 0; i < MAX5 - 1; i++)
									{
										int k = i;
										for (int j = i + 1; j < MAX5; j++)
										{
											if (horizontal[j] < horizontal[k])
												k = j;
										}
										if (k != i)
										{
											int temp = horizontal[k];
											horizontal[k] = horizontal[i];
											horizontal[i] = temp;
										}
									}

									for (int i = 0; i < MAX5 - 1; i++)
									{
										int k = i;
										for (int j = i + 1; j < MAX5; j++)
										{
											if (rHorizontal[j] < rHorizontal[k])
												k = j;
										}
										if (k != i)
										{
											int temp = rHorizontal[k];
											rHorizontal[k] = rHorizontal[i];
											rHorizontal[i] = temp;
										}
									}

									//对vertical数组递增排序
									for (int i = 0; i < MAX5 - 1; i++)
									{
										int	k = i;
										for (int j = i + 1; j < MAX5; j++)
										{
											if (vertical[j] < vertical[k])
												k = j;
										}
										if (k != i)
										{
											int temp = vertical[k];
											vertical[k] = vertical[i];
											vertical[i] = temp;
										}
									}

									for (int i = 0; i < MAX5 - 1; i++)
									{
										int	k = i;
										for (int j = i + 1; j < MAX5; j++)
										{
											if (rVertical[j] < rVertical[k])
												k = j;
										}
										if (k != i)
										{
											int temp = rVertical[k];
											rVertical[k] = rVertical[i];
											rVertical[i] = temp;
										}
									}

									double AverageHorizontal = 0, AverageVertical = 0;
									double rAverageHorizontal = 0, rAverageVertical = 0;

									for (int i = MAX5_MIN; i < MAX5 - MAX5_MIN; i++) //从第23个元素开始取值，一共取40个，求平均值
									{	
										//取值去掉了两头的，也就是较大和较小的，提升精度
										AverageHorizontal = AverageHorizontal + horizontal[i];
										AverageVertical = AverageVertical + vertical[i];

										rAverageHorizontal = rAverageHorizontal + rHorizontal[i];
										rAverageVertical = rAverageVertical + rVertical[i];
									}

									AverageHorizontal = AverageHorizontal / (MAX5-2*MAX5_MIN);
									AverageVertical = AverageVertical / (MAX5 - 2 * MAX5_MIN);

									rAverageHorizontal = rAverageHorizontal / (MAX5 - 2 * MAX5_MIN);
									rAverageVertical = rAverageVertical / (MAX5 - 2 * MAX5_MIN);

									//通过对观察左下、右下位置视线的测定，确定视野范围
									//当前WindowPositionFlag-1的值为现有视线测定数据所对应的窗口位置
									if (WindowPositionFlag == 0)
									{
										ScreenLocation[WindowPositionFlag].x = float(AverageHorizontal);
										ScreenLocation[WindowPositionFlag].y = float(AverageVertical);

										rScreenLocation[WindowPositionFlag].x = float(rAverageHorizontal);
										rScreenLocation[WindowPositionFlag].y = float(rAverageVertical);
									}
									if (WindowPositionFlag == 1)
									{
										ScreenLocation[WindowPositionFlag].x = float(AverageHorizontal);
										ScreenLocation[WindowPositionFlag].y = float(AverageVertical);

										rScreenLocation[WindowPositionFlag].x = float(rAverageHorizontal);
										rScreenLocation[WindowPositionFlag].y = float(rAverageVertical);
										cvDestroyWindow("exp");

										X0 = A*tan(ScreenLocation[0].x*PI / 180.0) / (tan(ScreenLocation[0].x*PI / 180.0) - tan(ScreenLocation[1].x*PI / 180.0));
										Y0 = B*tan(ScreenLocation[0].y*PI / 180.0) / (tan(ScreenLocation[0].y*PI / 180.0) - tan(ScreenLocation[1].y*PI / 180.0));

										rX0 = A*tan(rScreenLocation[0].x*PI / 180.0) / (tan(rScreenLocation[0].x*PI / 180.0) - tan(rScreenLocation[1].x*PI / 180.0));
										rY0 = B*tan(rScreenLocation[0].y*PI / 180.0) / (tan(rScreenLocation[0].y*PI / 180.0) - tan(rScreenLocation[1].y*PI / 180.0));


//										distance = A / 2 / tan((fabs(ScreenLocation[0].x) + fabs(ScreenLocation[1].x)) / 360 * PI);
//										rdistance = A / 2 / tan((fabs(rScreenLocation[0].x) + fabs(rScreenLocation[1].x)) / 360 * PI);
										/*distance = distance / 2 + (B / 2 / tan(fabs(fabs(ScreenLocation[1].y) - fabs(ScreenLocation[0].y))) +
											B / 2 / tan(fabs(fabs(rScreenLocation[1].y) - fabs(rScreenLocation[0].y))))/2;*/
										ReadyToEstimation = true;
										::ShowWindow(AfxGetMainWnd()->m_hWnd,SW_SHOWMINIMIZED);
										
									}
								}
							}
						}
						else
						{
							GazeHangleData.data[GazeHangleData.insert] = INT32(HorizontalGaze); //水平视线夹角值，数组保存最新的30次数据，GazeHangleData.insert保存下一次数据应存放位置
							GazeHangleData.insert = (GazeHangleData.insert + 1) % MAX2;
							TotalHAngleOf30fps += GazeHangleData.data[(GazeHangleData.insert - 1 + MAX2) % MAX2];//累积所有水平数据

							rGazeHangleData.data[rGazeHangleData.insert] = INT32(rHorizontalGaze); //水平视线夹角值，数组保存最新的30次数据，GazeHangleData.insert保存下一次数据应存放位置
							rGazeHangleData.insert = (rGazeHangleData.insert + 1) % MAX2;
							rTotalHAngleOf30fps += rGazeHangleData.data[(rGazeHangleData.insert - 1 + MAX2) % MAX2];//累积所有水平数据


							GazeVangleData.data[GazeVangleData.insert] = INT32(VerticalGaze); //垂直视线夹角值，同上
							GazeVangleData.insert = (GazeVangleData.insert + 1) % MAX2;
							TotalVAngleOf30fps = TotalVAngleOf30fps + GazeVangleData.data[(GazeVangleData.insert - 1 + MAX2) % MAX2];

							rGazeVangleData.data[rGazeVangleData.insert] = INT32(rVerticalGaze); //垂直视线夹角值，同上
							rGazeVangleData.insert = (rGazeVangleData.insert + 1) % MAX2;
							rTotalVAngleOf30fps += rGazeVangleData.data[(rGazeVangleData.insert - 1 + MAX2) % MAX2];


							if ((GazeHangleData.insert == GazeHangleData.erase))  //每积累到30次数据，进行以下操作
							{

								HorizontalGaze = TotalHAngleOf30fps / MAX2;//计算水平视线平均值
								VerticalGaze = TotalVAngleOf30fps / MAX2;//计算垂直视线平均值

								rHorizontalGaze = rTotalHAngleOf30fps / MAX2;//计算水平视线平均值
								rVerticalGaze = rTotalVAngleOf30fps / MAX2;//计算垂直视线平均值

								double hor, ver;  //坐标
								double rHor, rVer;

								//将视线夹角转化坐标
								//hor = XCoordinateCalculation(HorizontalGaze, ScreenLocation[0].x,ScreenLocation[1].x, distance);
								//ver = YCoordinateCalculation(VerticalGaze, ScreenLocation[0].y, distance);

								hor = X0*(1.0 - (tan(HorizontalGaze*PI / 180.0) / tan(ScreenLocation[0].x*PI / 180.0)));
								ver = Y0*(1.0 - (tan(VerticalGaze*PI / 180.0) / tan(ScreenLocation[0].y*PI / 180.0)));

								//rHor = XCoordinateCalculation(rHorizontalGaze, rScreenLocation[0].x,rScreenLocation[1].x, rdistance);
								//rVer = YCoordinateCalculation(rVerticalGaze, rScreenLocation[0].y, rdistance);

								rHor = rX0*(1.0 - (tan(rHorizontalGaze*PI / 180.0) / tan(rScreenLocation[0].x*PI / 180.0)));
								rVer = rY0*(1.0 - (tan(rVerticalGaze*PI / 180.0) / tan(rScreenLocation[0].y*PI / 180.0)));

								GazeXData.data[GazeXData.insert] = INT32((rHor+hor)/2); //保存最新的30次水平坐标值
								GazeXData.insert = (GazeXData.insert + 1) % MAX1;
								TotalXOf30fps = TotalXOf30fps + GazeXData.data[(GazeXData.insert - 1 + MAX1) % MAX1];  //计算到当前次的总和

								GazeYData.data[GazeYData.insert] = INT32((rVer+ver)/2); //保存最新的30次垂直坐标值
								GazeYData.insert = (GazeYData.insert + 1) % MAX1;
								TotalYOf30fps = TotalYOf30fps + GazeYData.data[(GazeYData.insert - 1 + MAX1) % MAX1];

								char* buf = new char[255];
								HWND hwndPointNow = NULL;
								hwndPointNow = ::GetForegroundWindow();  //返回前台窗口的句柄
								::GetClassName(hwndPointNow, buf, 255);
								CString str1;
								str1.Format("%s", buf);
								pointer->SetDlgItemText(IDC_GAZELR, str1);
								//根据到现在的情况，每进行一次坐标数据的收集
								//需要进行30次视线角度数据的收集
								//考虑是否有必要改进

								if ((GazeXData.insert == GazeXData.erase))	//积累到30次视线坐标数据
								{
									HorizontalCoordinate = TotalXOf30fps / MAX1;  //水平坐标
									VerticalCoordinate = TotalYOf30fps / MAX1;	 //垂直坐标
									
									//完成鼠标的移动与控制
									if (strcmp(buf, "OpusApp") == 0 || strcmp(buf, "classFoxitReader") == 0 || strcmp(buf, "XLMAIN") == 0 || strcmp(buf, "WordPadClass") == 0 || strcmp(buf, "KK_Frame") == 0)
									{
										//如果是以上软件
										if (OldHorizontalCoordinate > 1200 && OldVerticalCoordinate<100)
										{
											if (SmileDegree>15)//点击操作
											{
												stay++;
												//将鼠标移动到指定位置
												SetCursorPos(int(OldHorizontalCoordinate), int(OldVerticalCoordinate));
												if (MouseControlCode == 30)
												{
													//执行左键单击操作
													mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
												}
												if (MouseControlCode == 60)
												{
													//执行左键双击操作
													mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
													mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
													MouseControlCode = 0;
												}
												MouseControlCode++;
											}
											else//位移操作
											{
												MouseControlCode = 0;
												//如果新坐标和旧坐标相差在300像素以内，维持原位置，否则移动到新坐标
												if ((sqrt(pow(OldHorizontalCoordinate - HorizontalCoordinate) + pow(OldVerticalCoordinate - VerticalCoordinate))) < 300)
													SetCursorPos(int(OldHorizontalCoordinate), int(OldVerticalCoordinate));
												else
													SetCursorPos(int(HorizontalCoordinate), int(VerticalCoordinate));
												OldHorizontalCoordinate = HorizontalCoordinate;  ////用新值替代旧值
												OldVerticalCoordinate = VerticalCoordinate;
											}

										}
										else
										{
											OldHorizontalCoordinate = HorizontalCoordinate;  //用新值替代旧值
											OldVerticalCoordinate = VerticalCoordinate;
										}

										if (strcmp(buf, "KK_Frame") == 0)//如果KK_Frame软件

											//看图软件的切换图片、放大、缩小图片功能实现

										{
											if (OldHorizontalCoordinate > 1000 && OldVerticalCoordinate<100)
											{
											}
											else if (OldHorizontalCoordinate>1150)//水平看向最右边
											{
												if (stay == 0)//不维持坐标状态
												{
													//合成一次击键事件
													keybd_event(39, 0, 0, 0);	//模拟按下向右键
													keybd_event(39, 0, KEYEVENTF_KEYUP, 0);	//模拟松开向右键
													stay = 1;	//维持坐标状态
												}

											}
											else if (OldHorizontalCoordinate < 150)//水平看向最左边
											{
												if (stay == 0)
												{
													keybd_event(37, 0, 0, 0);	//模拟按下向左键
													keybd_event(37, 0, KEYEVENTF_KEYUP, 0);//模拟松开向左键
													stay = 1;	//维持坐标状态
												}
											}
											else if (OldVerticalCoordinate < 20)//垂直看向最上边
											{
												if (stay == 0)
												{
													keybd_event(38, 0, 0, 0);	//模拟按下向上键
													keybd_event(38, 0, KEYEVENTF_KEYUP, 0);//模拟松开向上键
													stay = 1;	//维持坐标状态
												}
											}
											else if (OldVerticalCoordinate > B - 20)//垂直看向最下边
											{
												if (stay == 0)
												{
													keybd_event(40, 0, 0, 0);//模拟按下向下键
													keybd_event(40, 0, KEYEVENTF_KEYUP, 0);//模拟松开向下键
													stay = 1;	//维持坐标状态
												}

											}
											else
												stay = 0;//不维持坐标状态
										}


										else
											//滑轮动作模拟

										{
											if (OldHorizontalCoordinate > 1000 && OldVerticalCoordinate < 100)
											{
											}
											else if ((OldVerticalCoordinate < 100) && (OldHorizontalCoordinate < 300))
											{
												//模拟滑轮向远处快速滑动
												mouse_event(MOUSEEVENTF_WHEEL, 0, 0, 20, 0);
											}
											else if ((OldVerticalCoordinate<100) && (OldHorizontalCoordinate>300) && (OldHorizontalCoordinate<1000))
											{
												//模拟滑轮向远处中速滑动
												mouse_event(MOUSEEVENTF_WHEEL, 0, 0, 15, 0);
											}
											else if ((OldVerticalCoordinate>700) && (OldHorizontalCoordinate<300))
											{
												//模拟滑轮向近处快速移动
												mouse_event(MOUSEEVENTF_WHEEL, 0, 0, -20, 0);
											}
											else if ((OldVerticalCoordinate>700) && (OldHorizontalCoordinate > 300) && (OldHorizontalCoordinate < 1000))
											{
												//模拟滑轮向近处中速移动
												mouse_event(MOUSEEVENTF_WHEEL, 0, 0, -15, 0);
											}

										}
									}


									else if (strcmp(buf, "CWmpControlCntr") == 0 || strcmp(buf, "WMPTransition") == 0)
									{
										//	如果是以上软件
										if (OldHorizontalCoordinate > 1200 && OldVerticalCoordinate<100)
										{
											if (SmileDegree>15)//微笑模拟鼠标点击
											{
												stay++;
												SetCursorPos(int(OldHorizontalCoordinate), int(OldVerticalCoordinate));
												if (MouseControlCode == 30)
												{
													mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
												}
												if (MouseControlCode == 60)
												{
													mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
													mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
													MouseControlCode = 0;
												}
												MouseControlCode++;
											}

											else//位移操作
											{
												MouseControlCode = 0;
												if ((sqrt(pow(OldHorizontalCoordinate - HorizontalCoordinate) + pow(OldVerticalCoordinate - VerticalCoordinate))) < 300)
													SetCursorPos(int(OldHorizontalCoordinate), int(OldVerticalCoordinate));
												else
													SetCursorPos(int(HorizontalCoordinate), int(VerticalCoordinate));
												OldHorizontalCoordinate = HorizontalCoordinate;  ////用新值替代旧值
												OldVerticalCoordinate = VerticalCoordinate;
											}

										}
										else
										{
											OldHorizontalCoordinate = HorizontalCoordinate;  //旧值
											OldVerticalCoordinate = VerticalCoordinate;
										}
									}

									else   //如果不是以上软件
									{
										if (SmileDegree > 15)//微笑模拟鼠标点击
										{
											stay++;
											SetCursorPos(int(OldHorizontalCoordinate), int(OldVerticalCoordinate));
											if (MouseControlCode == 30)
											{
												mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
											}
											if (MouseControlCode == 60)
											{
												mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
												mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
												MouseControlCode = 0;
											}
											MouseControlCode++;
										}

										else//位移操作
										{
											MouseControlCode = 0;
											if ((sqrt(pow(OldHorizontalCoordinate - HorizontalCoordinate) + pow(OldVerticalCoordinate - VerticalCoordinate))) < 300)
												SetCursorPos(int(OldHorizontalCoordinate), int(OldVerticalCoordinate));
											else
												SetCursorPos(int(HorizontalCoordinate), int(VerticalCoordinate));
											OldHorizontalCoordinate = HorizontalCoordinate;  ////用新值替代旧值
											OldVerticalCoordinate = VerticalCoordinate;
										}

									}

									//删除最旧的坐标数据
									TotalXOf30fps = TotalXOf30fps - GazeXData.data[GazeXData.erase];
									GazeXData.erase = (GazeXData.erase + 1) % MAX1;
									TotalYOf30fps = TotalYOf30fps - GazeYData.data[GazeYData.erase];
									GazeYData.erase = (GazeYData.erase + 1) % MAX1;
								}

								//删除最旧的夹角数据
								TotalHAngleOf30fps = TotalHAngleOf30fps - GazeHangleData.data[GazeHangleData.erase];
								GazeHangleData.erase = (GazeHangleData.erase + 1) % MAX2;
								TotalVAngleOf30fps = TotalVAngleOf30fps - GazeVangleData.data[GazeVangleData.erase];
								GazeVangleData.erase = (GazeVangleData.erase + 1) % MAX2;

								rTotalHAngleOf30fps = rTotalHAngleOf30fps - rGazeHangleData.data[rGazeHangleData.erase];
								rGazeHangleData.erase = (rGazeHangleData.erase + 1) % MAX2;
								rTotalVAngleOf30fps = rTotalVAngleOf30fps - rGazeVangleData.data[rGazeVangleData.erase];
								rGazeVangleData.erase = (rGazeVangleData.erase + 1) % MAX2;
							}
						}
						CString  str2, str3;
						//str1.Format("%s", ReadyToEstimation ? "Ready" : "Preparing");
						//str1.Format("%.2f/%.2f/%d", A, B, distance);
						str2.Format("%.2f", HorizontalCoordinate);
						str3.Format("%.2f", VerticalCoordinate);
						/*pointer->SetDlgItemText(IDC_GAZELR, str1);*/
						pointer->SetDlgItemText(IDC_GAZEUD, str2);
						pointer->SetDlgItemText(IDC_EDIT1, str3);
						//在LoopTime值大于100的时候才进行以上内容

						//将LoopTime值、TotalXOf30fps0、TotalYOf30fps0值设置到对话框文本
					}
				}

			}

			//Work End
//******************************************************************************************************
//******************************************************************************************************
//******************************************************************************************************
		}

	}

	//摄像头关闭后，退出循环，执行识别器销毁操作

	if (AgeDetect != NULL)
		OKAO_AG_DeleteHandle(AgeDetect);	//销毁年龄识别器

	if (rAgeDetect != NULL)
		OKAO_AG_DeleteHandle(rAgeDetect);	//销毁年龄识别器

	if (AgeDetectResult != NULL)
		OKAO_AG_DeleteResultHandle(AgeDetectResult);	//销毁年龄识别结果管理器

	if (rAgeDetectResult != NULL)
		OKAO_AG_DeleteResultHandle(rAgeDetectResult);	//销毁年龄识别结果管理器

	if (GenderDetect != NULL)
		OKAO_GN_DeleteHandle(GenderDetect);  	//销毁性别识别器

	if (rGenderDetect != NULL)
		OKAO_GN_DeleteHandle(rGenderDetect);  	//销毁性别识别器

	if (GenderDetectResult != NULL)
		OKAO_GN_DeleteResultHandle(GenderDetectResult);  	//销毁性别识别结果识别器

	if (rGenderDetectResult != NULL)
		OKAO_GN_DeleteResultHandle(rGenderDetectResult);  	//销毁性别识别结果识别器

	if (EyeGazeBlinkDetectResult != NULL)
		OKAO_GB_DeleteResultHandle(EyeGazeBlinkDetectResult);  	//销毁视线识别结果管理器

	if (rEyeGazeBlinkDetectResult != NULL)
		OKAO_GB_DeleteResultHandle(rEyeGazeBlinkDetectResult);  	//销毁视线识别结果管理器

	if (EyeGazeBlinkDetect != NULL)
		OKAO_GB_DeleteHandle(EyeGazeBlinkDetect);  	//销毁视线识别器

	if (rEyeGazeBlinkDetect != NULL)
		OKAO_GB_DeleteHandle(rEyeGazeBlinkDetect);  	//销毁视线识别器

	if (EyeOpenDetect != NULL)
		OKAO_DeleteEyeOpen(EyeOpenDetect);  	//销毁睁眼识别器

	if (rEyeOpenDetect != NULL)
		OKAO_DeleteEyeOpen(rEyeOpenDetect);  	//销毁睁眼识别器

	if (SmileDetect != NULL)
		OKAO_SM_DeleteHandle(SmileDetect);  	//销毁微笑识别器

	if (rSmileDetect != NULL)
		OKAO_SM_DeleteHandle(rSmileDetect);  	//销毁微笑识别器

	if (SmileDetectResult != NULL)
		OKAO_SM_DeleteResultHandle(SmileDetectResult);  	//销毁微笑识别结果管理器

	if (rSmileDetectResult != NULL)
		OKAO_SM_DeleteResultHandle(rSmileDetectResult);  	//销毁微笑识别结果管理器

	if (FaceFeatureAlbum != NULL)
		OKAO_FR_DeleteAlbumHandle(FaceFeatureAlbum);  	//销毁面部特征识别结果管理器

	if (rFaceFeatureAlbum != NULL)
		OKAO_FR_DeleteAlbumHandle(rFaceFeatureAlbum);  	//销毁面部特征识别结果管理器

	if (FaceFeature != NULL)
		OKAO_FR_DeleteFeatureHandle(FaceFeature);  	//销毁面部特征识别器

	if (rFaceFeature != NULL)
		OKAO_FR_DeleteFeatureHandle(rFaceFeature);  	//销毁面部特征识别器

	if (FacePartsDetect != NULL)
		OKAO_PT_DeleteHandle(FacePartsDetect);  	//销毁面部器官识别器

	if (rFacePartsDetect != NULL)
		OKAO_PT_DeleteHandle(rFacePartsDetect);  	//销毁面部器官识别器

	if (FacePartsDetectResult != NULL)
		OKAO_PT_DeleteResultHandle(FacePartsDetectResult);  	//销毁面部结果识别结果管理器

	if (rFacePartsDetectResult != NULL)
		OKAO_PT_DeleteResultHandle(rFacePartsDetectResult);  	//销毁面部结果识别结果管理器

	if (FaceDetect != NULL)
		OKAO_DeleteDetection(FaceDetect);  	//销毁面部识别器

	if (rFaceDetect != NULL)
		OKAO_DeleteDetection(rFaceDetect);  	//销毁面部识别器

	if (FaceDetectResult != NULL)
		OKAO_DeleteDtResult(FaceDetectResult);  	//销毁面部识别结果管理器

	if (rFaceDetectResult != NULL)
		OKAO_DeleteDtResult(rFaceDetectResult);  	//销毁面部识别结果管理器

	//销毁所有画笔对象
	pen_male.DeleteObject();
	pen_female.DeleteObject();
	pen_noGender.DeleteObject();
	pen_open.DeleteObject();
	//释放为保存捕获的图像申请的内存
	free(pGray);
	free(rPGray);
	return 0;
}

#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Ends here
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Click Set button

void fatiguedetectDlg::OnBnClickedSet()
{
	if (flag_CamState == 0)return;
	//isCamOpen = FALSE;
	AfxMessageBox("Please look at the video for about 5 seconds");
	flag_CamState = 2;
}

//Click Pause/Continue button

void fatiguedetectDlg::OnBnClickedPause()
{
	if (flag_CamState == 0)
		return;
	if (isCamOpen)
	{
		isCamOpen = FALSE;
		GetDlgItem(IDC_PAUSE)->SetWindowText(_T("Continue"));
		ServMainThread->SuspendThread();
	}
	else
	{
		isCamOpen = TRUE;
		GetDlgItem(IDC_PAUSE)->SetWindowText(_T("Pause"));
		ServMainThread->ResumeThread();
	}
}

//Click Exit button

void fatiguedetectDlg::OnBnClickedExit()
{
	isCamOpen = FALSE;
//	if (flag_CamState > 0&&ServMainThread != NULL)
//		TerminateThread(ServMainThread->m_hThread, 0);
	::CloseWindow(AfxGetMainWnd()->m_hWnd);//window minimize
	AfxGetMainWnd()->SendMessage(WM_CLOSE);
}

//Respond to WM_CLOSE message

void fatiguedetectDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	cvDestroyAllWindows();
	if (flag_CamState > 0&&capture)
		cvReleaseCapture(&capture);
	CDialog::OnClose();
}

//Click Adduser button

void fatiguedetectDlg::OnBnClickedAdduser()
{
	if (flag_CamState == 0)
		return;

	if (GetDlgItem(IDC_ADDUSER)->IsWindowEnabled())//增加用户
	{
		if (nRegisteredUserNum == nMaxUserNum)
		{
			AfxMessageBox("The number of registered user have reached the upper limit.");
			return;
		}
		nCurDataNum = 0;   
		GetDlgItem(IDC_ADDUSER)->SetWindowText(_T("OK"));
		GetDlgItem(IDC_REGISTER_FEATURE)->EnableWindow(TRUE);
		GetDlgItem(IDC_ADDUSER)->EnableWindow(FALSE);
	}
	else//用户特征注册完毕
	{
		flag_faceRecognitionState = 1;
		CString str1;
		GetDlgItemText(IDC_ALL_USER, str1);
		str1.Trim();//移除字符串两侧的空白字符或其他预定义字符
		if (str1.IsEmpty())//未输入用户名
		{
			MessageBox("Please input the user name.");
			flag_faceRecognitionState = 0;
			return;
		}
		else//判断输入用户名是否重复
		{
			for (int i = 0; i < nRegisteredUserNum; i++)
			{
				if (pStrUserList[i].Compare(str1) == 0)
				{
					MessageBox("It is a existent user name,please input another one.");
					flag_faceRecognitionState = 0;
					return;
				}
			}
		}
		pStrUserList[nRegisteredUserNum] = str1;
		combo_allUser.AddString(_T(str1));
		nRegisteredUserNum++;
		GetDlgItem(IDC_ADDUSER)->SetWindowText(_T("Add user"));
		GetDlgItem(IDC_ADDUSER)->EnableWindow(TRUE);
		GetDlgItem(IDC_REGISTER_FEATURE)->EnableWindow(FALSE);
		GetDlgItem(IDC_FEATURE_NUM)->SetWindowText(_T(" "));
		SetDlgItemText(IDC_ALL_USER, "");
	}
}

//Click RegisterFeature button

void fatiguedetectDlg::OnBnClickedRegisterFeature()
{
	if (nCurDataNum < nMaxDataNum)
		flag_faceRecognitionState = 2;//触发人脸特征记录
}

//Click ManualSet button

void fatiguedetectDlg::OnBnClickedManualSet()
{
	CvVideoWriter* videoWriter;
	IplImage *pFrame;
	CvCapture *pCapture;
	CWnd *wnd;
	CvvImage img;
	CRect rect;
	CDC *pDC;                  //*************************************************************************??
	HDC hDC;                   //*************************************************************************??

	//设置摄像视频尺寸
	pCapture = cvCaptureFromCAM(0);//连接0号摄像头
	cvSetCaptureProperty(pCapture, CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
	cvSetCaptureProperty(pCapture, CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);  
	wnd = GetDlgItem(IDC_PICTURE);
	wnd->GetClientRect(&rect);
	pDC = wnd->GetDC();
	hDC = pDC->GetSafeHdc();
	videoWriter = cvCreateVideoWriter("test2.avi", CV_FOURCC('X', 'V', 'I', 'D'), 30, cvSize(320, 240), 1);

	int i = 0;
	do
	{
		pFrame = cvQueryFrame(pCapture);   //通过摄像头捕获图像
		cvWriteFrame(videoWriter, pFrame);    //将图像写入视频文件
		img.CopyOf(pFrame);               
		img.DrawToHDC(hDC, &rect);         
	} while (++i < 900);
	cvReleaseVideoWriter(&videoWriter);
	MessageBox("Video Recording Complete");
	return;
}

//Click Print button

void fatiguedetectDlg::OnBnClickedPrint()
{
	char c[4];
	string str1;
	itoa(imageNo, c, 10);
	str1 = "picture\\";
	str1 += c;
	str1 += ".jpg";
	cvSaveImage(str1.c_str(), frame);
}

//Click Button1            //********************************************************************************??

void fatiguedetectDlg::OnBnClickedButton1()
{
	STARTUPINFO si;
	memset(&si, 0, sizeof(STARTUPINFO));//初始化si在内存块中的值（详见memset函数）
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_SHOW;
	PROCESS_INFORMATION pi;
	if (!CreateProcess(TEXT("D://OPENCV//欧姆龙//player//Release//player.exe"), NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		cout << "Create Fail!" << endl;
		exit(1);
	}
}

//Click Button2            //********************************************************************************??

void fatiguedetectDlg::OnBnClickedButton2()
{
	ShellExecute(NULL, "explore", "D:\\OPENCV\\欧姆龙\\PHOTO", NULL, NULL, SW_SHOWNORMAL);
}

//Click Button3            //********************************************************************************??

void fatiguedetectDlg::OnBnClickedButton3()
{
	ShellExecute(NULL, "explore", "D:\\OPENCV\\欧姆龙\\BOOK", NULL, NULL, SW_SHOWNORMAL);
}

//Click Button6            //********************************************************************************??

void fatiguedetectDlg::OnBnClickedButton6()
{
	cvMoveWindow("exp", int(A / 2 - 50), int(B / 2 - 50));  //左上角
	cvDestroyWindow("exp");
	WindowPositionFlag = 0;
	FrameCount = 0;
#ifdef LOAD_OMRON
	ServMainThread = AfxBeginThread(ComputeThreadProc, (LPVOID)this, THREAD_PRIORITY_NORMAL);
#endif
}


//UNUSED

void fatiguedetectDlg::OnStnClickedPicture()
{
	// TODO: 在此添加控件通知处理程序代码
}

//UNUSED

void fatiguedetectDlg::OnEnChangeGazelr()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

//UNUSED

void fatiguedetectDlg::OnEnChangeGazeud()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

//UNUSED

void fatiguedetectDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void fatiguedetectDlg::OnEnChangeLeye1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void fatiguedetectDlg::OnEnChangeReye1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void fatiguedetectDlg::OnEnChangeManualSet()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void fatiguedetectDlg::OnEnChangeReye2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void fatiguedetectDlg::OnCbnSelchangeAllUser()
{
	// TODO:  在此添加控件通知处理程序代码
}


void fatiguedetectDlg::OnStnClickedPicture2()
{
	// TODO:  在此添加控件通知处理程序代码
}
