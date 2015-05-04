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
    Eye Open-close Estimation Library API
*/
#pragma warning(disable:4996)
#ifndef OKAOEOAPI_H__
#define OKAOEOAPI_H__

#include    "OkaoAPI.h"

#ifndef OKAO_DEF_HEYEOPEN
#define OKAO_DEF_HEYEOPEN
typedef void *  HEYEOPEN;       /* Eye Open-close Estimation handle */
#endif /* OKAO_DEF_HEYEOPEN */

#ifndef OKAO_DEF_HPTRESULT
#define OKAO_DEF_HPTRESULT
typedef void *  HPTRESULT;      /* Facial Parts Detection result handle */
#endif /* OKAO_DEF_HPTRESULT */

/*----- Open Rate Parts Number -----*/
#define EO_PARTS_LEFTEYE            0x00000001  /* Left Eye */
#define EO_PARTS_RIGHTEYE           0x00000002  /* Right Eye */
#define EO_PARTS_MOUTH              0x00000004  /* Mouth */
#define EO_PARTS_ALL                (EO_PARTS_LEFTEYE | EO_PARTS_RIGHTEYE | EO_PARTS_MOUTH)


/*----- Index of Facial parts -----*/
enum EO_PTPOINT {
    EO_PTPOINT_LEFT_EYE = 0,        /* Center of left eye        */
    EO_PTPOINT_RIGHT_EYE,           /* Center of right eye       */
    EO_PTPOINT_MOUTH,               /* Mouth Center              */
    EO_PTPOINT_LEFT_EYE_IN,         /* Inner corner of left eye  */
    EO_PTPOINT_LEFT_EYE_OUT,        /* Outer corner of left eye  */
    EO_PTPOINT_RIGHT_EYE_IN,        /* Inner corner of right eye */
    EO_PTPOINT_RIGHT_EYE_OUT,       /* Outer corner of right eye */
    EO_PTPOINT_MOUTH_LEFT,          /* Left corner of mouth      */
    EO_PTPOINT_MOUTH_RIGHT,         /* Right corner of mouth     */
    EO_PTPOINT_RESERVE1,            /* Reserve 1                 */
    EO_PTPOINT_RESERVE2,            /* Reserve 2                 */
    EO_PTPOINT_MAX                  /* Number of Facial parts    */
};


#ifdef  __cplusplus
extern "C" {
#endif

/**********************************************************/
/* Get Version                                            */
/**********************************************************/
/* Get Eye Open-close Estimation Library API Version */
OKAO_API INT32 OKAO_GetEoVersion(UINT8 *pucMajor, UINT8 *pucMinor);

/**********************************************************/
/* Create/Delete Handle                                   */
/**********************************************************/
/* Create Eye Open-close Estimation handle */
OKAO_API HEYEOPEN   OKAO_CreateEyeOpen(void);
/* Delete Eye Open-close Estimation handle */
OKAO_API INT32      OKAO_DeleteEyeOpen(HEYEOPEN hEO);

/**********************************************************/
/* Facial Feature Point Setting                           */
/**********************************************************/
/* Set the feature points for Eye Open-close Estimation from PT result handle */
OKAO_API INT32      OKAO_SetEoPoint(HEYEOPEN hEO, HPTRESULT hPtResult);
/* Set the feature points for Eye Open-close Estimation */
OKAO_API INT32      OKAO_SetEoPointFromPosAngle(HEYEOPEN hEO, POINT aptPoint[], INT32 nUpDown, INT32 nLeftRight);

/* Set the Open Rate Part Number in the Eye Open-close Estimation handle */
OKAO_API INT32      OKAO_SetEoParts(HEYEOPEN hEO, UINT32 nParts);
/* Get the Open Rate Part Number from the Eye Open-close Estimation handle */
OKAO_API INT32      OKAO_GetEoParts(HEYEOPEN hEO, UINT32 *pnParts);

/**********************************************************/
/* Eye Open-close Estimation                              */
/**********************************************************/
/* Estimate the eye open-close */
OKAO_API INT32      OKAO_EyeOpen(HEYEOPEN hEO, RAWIMAGE *pImage, INT32 nWidth, INT32 nHeight);

/* Get Left Eye Open Rate */
OKAO_API INT32      OKAO_GetEoLevelL(HEYEOPEN hEO, INT32 *pnEyeOpenLevel);
/* Get Right Eye Open Rate */
OKAO_API INT32      OKAO_GetEoLevelR(HEYEOPEN hEO, INT32 *pnEyeOpenLevel);
/* Get Mouth Open Rate */
OKAO_API INT32      OKAO_GetEoLevelM(HEYEOPEN hEO, INT32 *pnMouthOpenLevel);

#ifdef  __cplusplus
}
#endif


#endif  /* OKAOEOAPI_H__ */
