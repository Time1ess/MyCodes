/*-------------------------------------------------------------------*/
/*  Copyright(C) 2003-2011 by OMRON Corporation                      */
/*  All Rights Reserved.                                             */
/*                                                                   */
/*   This source code is the Confidential and Proprietary Property   */
/*   of OMRON Corporation.  Any unauthorized use, reproduction or    */
/*   transfer of this software is strictly prohibited.               */
/*                                                                   */
/*-------------------------------------------------------------------*/
/* 
    Gender Estimation Library API
*/
#pragma warning(disable:4996)
#ifndef OKAOGNAPI_H__
#define OKAOGNAPI_H__

#define OKAO_API
#include    "OkaoDef.h"

#ifndef OKAO_DEF_HGENDER
#define OKAO_DEF_HGENDER
typedef void *  HGENDER;        /* Gender Estimation handle */
#endif /* OKAO_DEF_HGENDER */

#ifndef OKAO_DEF_HGNRESULT
#define OKAO_DEF_HGNRESULT
typedef void *  HGNRESULT;      /* Gender Estimation handle */
#endif /* OKAO_DEF_HGNRESULT */

#ifndef OKAO_DEF_HPTRESULT
#define OKAO_DEF_HPTRESULT
typedef void *  HPTRESULT;      /* Facial Parts Detection result handle */
#endif /* OKAO_DEF_HPTRESULT */


/*----- Index of Facial parts -----*/
enum GN_PTPOINT {
    GN_PTPOINT_LEFT_EYE_IN = 0,     /* Left eye inside        */
    GN_PTPOINT_LEFT_EYE_OUT,        /* Left eye outside       */
    GN_PTPOINT_RIGHT_EYE_IN,        /* Right eye inside       */
    GN_PTPOINT_RIGHT_EYE_OUT,       /* Right eye outside      */
    GN_PTPOINT_MOUTH_LEFT,          /* Mouth left             */
    GN_PTPOINT_MOUTH_RIGHT,         /* Mouth right            */
    GN_PTPOINT_MAX                  /* Number of Facial parts */
};

/*----- Index of Gender Estimation Feature Points -----*/
enum GN_FEATURE_POINT {
    GN_FEATURE_LEFT_EYE = 0,        /* Left eye center          */
    GN_FEATURE_RIGHT_EYE,           /* Right eye center         */
    GN_FEATURE_MOUTH,               /* Mouth center             */
    GN_FEATURE_FACE_CENTER,         /* Face center              */
    GN_FEATURE_MAX                  /* Number of Feature points */
};

/*----- Estimation gender value -----*/
enum GN_ESTIMATION_VALUE {
    GN_ESTIMATION_FEMALE = 0,       /* Female */
    GN_ESTIMATION_MALE,             /* Male */
    GN_ESTIMATION_MAX               /* Number of Gender */
};

#ifdef  __cplusplus
extern "C" {
#endif

/**********************************************************/
/* Get Version                                            */
/**********************************************************/
/*----- Gender Estimation Library API Version -----*/
OKAO_API INT32 OKAO_GN_GetVersion(UINT8 *pbyMajor, UINT8 *pbyMinor);

/**********************************************************/
/* Create/Delete Handle                                   */
/**********************************************************/
/* Create Gender Estimation handle */
OKAO_API HGENDER    OKAO_GN_CreateHandle(void);

/* Delete Gender Estimation handle */
OKAO_API INT32      OKAO_GN_DeleteHandle(HGENDER hGN);

/* Create Gender Estimation result handle */
OKAO_API HGNRESULT  OKAO_GN_CreateResultHandle(void);

/* Delete Gender Estimation result handle */
OKAO_API INT32      OKAO_GN_DeleteResultHandle(HGNRESULT hGnResult);

/**********************************************************/
/* Facial Feature Point Setting                           */
/**********************************************************/
/* Set the feature points for Gender Estimation */
OKAO_API INT32      OKAO_GN_SetPoint(HGENDER hGN, INT32 nPointNum, POINT aptPoint[], INT32 anConfidence[], INT32 nUpDown, INT32 nLeftRight);

/* Set the feature points for Gender Estimation from PT result handle*/
OKAO_API INT32      OKAO_GN_SetPointFromHandle(HGENDER hGN, HPTRESULT hPtResult);

/**********************************************************/
/* Gender Estimation                                      */
/**********************************************************/
/* Estimate the Gender */
OKAO_API INT32      OKAO_GN_Estimate(HGENDER hGN, RAWIMAGE *pImage, INT32 nWidth, INT32 nHeight, HGNRESULT hGnResult);

/**********************************************************/
/* Gender Estimation Result                               */
/**********************************************************/
/* Get the estimated facial gender and its confidence level */
OKAO_API INT32      OKAO_GN_GetResult(HGNRESULT hGnResult, INT32 *pnGender, INT32 *pnConfidence);

/* Get the estimated part-gender and its confidence level arrays */
OKAO_API INT32      OKAO_GN_GetPartsResult(HGNRESULT hGnResult, INT32 nPartsNum, INT32 anPartsGender[], INT32 anPartsConfidence[]);

/* Integrate a series of results and get a facial gender and its confidence level */
OKAO_API INT32      OKAO_GN_GetIntegratedResult(INT32 nResultNum, HGNRESULT hGnResult[], INT32 *pnGender, INT32 *pnConfidence);

#ifdef  __cplusplus
}
#endif

#endif  /* OKAOGNAPI_H__ */
