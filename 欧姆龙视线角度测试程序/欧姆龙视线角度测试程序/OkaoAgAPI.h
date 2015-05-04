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
    Age Estimation Library API
*/
#pragma warning(disable:4996)
#ifndef OKAOAGAPI_H__
#define OKAOAGAPI_H__

#define OKAO_API
#include    "OkaoDef.h"

#ifndef OKAO_DEF_HAGE
#define OKAO_DEF_HAGE
typedef void *  HAGE;           /* Age Estimation handle */
#endif /* OKAO_DEF_HAGE */

#ifndef OAKO_DEF_HAGRESULT
#define OKAO_DEF_HAGRESULT
typedef void *  HAGRESULT;      /* Age Estimation result handle */
#endif /* OKAO_DEF_HAGRESULT */

#ifndef OKAO_DEF_HPTRESULT
#define OKAO_DEF_HPTRESULT
typedef void *  HPTRESULT;      /* Facial Parts Detection result handle */
#endif /* OKAO_DEF_HPTRESULT */


/*----- Index of Facial parts -----*/
enum AG_PTPOINT {
    AG_PTPOINT_LEFT_EYE_IN = 0,     /* Left eye inside        */
    AG_PTPOINT_LEFT_EYE_OUT,        /* Left eye outside       */
    AG_PTPOINT_RIGHT_EYE_IN,        /* Right eye inside       */
    AG_PTPOINT_RIGHT_EYE_OUT,       /* Right eye outside      */
    AG_PTPOINT_MOUTH_LEFT,          /* Mouth left             */
    AG_PTPOINT_MOUTH_RIGHT,         /* Mouth right            */
    AG_PTPOINT_MAX                  /* Number of Facial parts */
};

/*----- Index of Age Estimation Feature Points -----*/
enum AG_FEATURE_POINT {
    AG_FEATURE_LEFT_EYE = 0,        /* Left eye center          */
    AG_FEATURE_RIGHT_EYE,           /* Right eye center         */
    AG_FEATURE_MOUTH,               /* Mouth center             */
    AG_FEATURE_FACE_CENTER,         /* Face center              */
    AG_FEATURE_LEFT_CHEEK,          /* Left cheek               */
    AG_FEATURE_RIGHT_CHEEK,         /* Right cheek              */
    AG_FEATURE_BROWS_CENTER,        /* Between the eyebrows     */
    AG_FEATURE_MAX                  /* Number of Feature points */
};


#ifdef  __cplusplus
extern "C" {
#endif

/**********************************************************/
/* Get Version                                            */
/**********************************************************/
/*----- Get Age Estimation Library API Version -----*/
OKAO_API INT32 OKAO_AG_GetVersion(UINT8 *pbyMajor, UINT8 *pbyMinor);

/**********************************************************/
/* Create/Delete Handle                                   */
/**********************************************************/
/* Create Age Estimation handle */
OKAO_API HAGE       OKAO_AG_CreateHandle(void);

/* Delete Age Estimation handle */
OKAO_API INT32      OKAO_AG_DeleteHandle(HAGE hAG);

/* Create Age Estimation result handle */
OKAO_API HAGRESULT  OKAO_AG_CreateResultHandle(void);

/* Delete Age Estimation result handle */
OKAO_API INT32      OKAO_AG_DeleteResultHandle(HAGRESULT hAgResult);

/**********************************************************/
/* Facial Feature Point Setting                           */
/**********************************************************/
/* Set the feature points for Age Estimation */
OKAO_API INT32      OKAO_AG_SetPoint(HAGE hAG, INT32 nPointNum, POINT aptPoint[], INT32 anConfidence[], INT32 nUpDown, INT32 nLeftRight);

/* Set the feature points for Age Estimation from PT result handle */
OKAO_API INT32      OKAO_AG_SetPointFromHandle(HAGE hAG, HPTRESULT hPtResult);

/**********************************************************/
/* Age Estimation                                         */
/**********************************************************/
/* Estimate the Age */
OKAO_API INT32      OKAO_AG_Estimate(HAGE hAG, RAWIMAGE *pImage, INT32 nWidth, INT32 nHeight, HAGRESULT hAgResult);

/**********************************************************/
/* Age Estimation Result                                  */
/**********************************************************/
/* Get the estimated facial age and its confidence level */
OKAO_API INT32      OKAO_AG_GetResult(HAGRESULT hAgResult, INT32 *pnAge, INT32 *pnConfidence);

/* Get the estimated part-age and its confidence level arrays */
OKAO_API INT32      OKAO_AG_GetPartsResult(HAGRESULT hAgResult, INT32 nPartsNum, INT32 anPartsAge[], INT32 anPartsConfidence[]);

/* Integrate a series of results and get a facial age and its confidence level */
OKAO_API INT32      OKAO_AG_GetIntegratedResult(INT32 nResultNum, HAGRESULT hAgResult[], INT32 *pnAge, INT32 *pnConfidence);

#ifdef  __cplusplus
}
#endif


#endif  /* OKAOAGAPI_H__ */
