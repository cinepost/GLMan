#ifndef NDSPY_H
#define NDSPY_H
/* $Revision: #3 $  (Pixar - RenderMan Division)  $Date: 2014/12/10 $ */
/*
# ------------------------------------------------------------------------------
#
# Copyright (c) 2001-2010 Pixar Animation Studios. All rights reserved.
#
# The information in this file (the "Software") is provided for the
# exclusive use of the software licensees of Pixar.  Licensees have
# the right to incorporate the Software into other products for use
# by other authorized software licensees of Pixar, without fee.
# Except as expressly permitted herein, the Software may not be
# disclosed to third parties, copied or duplicated in any form, in
# whole or in part, without the prior written permission of
# Pixar Animation Studios.
#
# The copyright notices in the Software and this entire statement,
# including the above license grant, this restriction and the
# following disclaimer, must be included in all copies of the
# Software, in whole or in part, and all permitted derivative works of
# the Software, unless such copies or derivative works are solely
# in the form of machine-executable object code generated by a
# source language processor.
#
# PIXAR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
# ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT
# SHALL PIXAR BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES
# OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
# WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
# ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
# SOFTWARE.
#
# Pixar
# 1200 Park Ave
# Emeryville CA 94608
#
# ------------------------------------------------------------------------------
*/

#include "prmanapi.h"
#include "ri.h"

#include <stdio.h>
#include <stdlib.h>

#define PkDspyMaxMsgSize 32760

#define PkDspyServerMsgOpen  (65 + 1)
#define PkDspyServerMsgImage (65 + 2)
#define PkDspyServerMsgData  (65 + 3)
#define PkDspyServerMsgQuery (65 + 4)
#define PkDspyServerMsgClose (65 + 5)
#define PkDspyServerMsgDeepData (65 + 6)
#define PkDspyServerMsgActiveRegion (65 + 7)

/*
PtDspyUnsigned64
PtDspySigned64
*/
typedef double PtDspyFloat64;
typedef float PtDspyFloat32;

#if defined(__mips)
#define PkDspyByteOrderNative	PkDspyByteOrderHiLo
#elif defined(__mips64)
#define PkDspyByteOrderNative	PkDspyByteOrderHiLo
#elif defined(__sparc)
#define PkDspyByteOrderNative	PkDspyByteOrderHiLo
#elif defined(__alpha)
#define PkDspyByteOrderNative	PkDspyByteOrderLoHi
#elif defined(__ppc__)
#define PkDspyByteOrderNative	PkDspyByteOrderHiLo
#else
#define PkDspyByteOrderNative	PkDspyByteOrderLoHi
#endif

typedef unsigned int PtDspyUnsigned32;
typedef int PtDspySigned32;

typedef unsigned short PtDspyUnsigned16;
typedef short PtDspySigned16;

typedef unsigned char PtDspyUnsigned8;
typedef char PtDspySigned8;

typedef PtDspyUnsigned32 PtDspyMsgLen;
typedef PtDspyUnsigned32 PtDspyServerMessage;

#define PkDspyClassFloat 1
#define PkDspyClassInt 2

#define PkDspyNone		0
#define PkDspyFloat32		1
#define PkDspyUnsigned32	2
#define PkDspySigned32		3
#define PkDspyUnsigned16	4
#define PkDspySigned16		5
#define PkDspyUnsigned8		6
#define PkDspySigned8		7
#define PkDspyString		8
#define PkDspyMatrix		9
#define PkDspyArrayBegin	10
#define PkDspyArrayEnd	        11

#define PkDspyMaskType		8191

#define PkDspyMaskOrder (PkDspyByteOrderHiLo | PkDspyByteOrderLoHi)
#define PkDspyShiftOrder	13
#define PkDspyByteOrderHiLo	8192
#define PkDspyByteOrderLoHi	16384


/*
 * PkDspyOpenPortCount controls the number of open display connections are used
 * by netrender/windows - or any process with an "internal" display server. 
 */
#define PkDspyOpenPortCount 1024


typedef struct
{
   char *name;
   unsigned type;
} PtDspyDevFormat;


typedef struct
{
	PtDspyUnsigned32 width;
	PtDspyUnsigned32 height;
	PtDspyFloat32 aspectRatio;
} PtDspySizeInfo;

typedef struct
{
  PtDspyUnsigned8 overwrite;
  PtDspyUnsigned8 interactive;
} PtDspyOverwriteInfo;
typedef struct
{
  PtDspyUnsigned8 redraw;
} PtDspyRedrawInfo;

typedef struct
{
  PtDspyUnsigned8 rewrite;
} PtDspyRewriteInfo;

typedef struct
{
    PtDspySigned32 xmin;
    PtDspySigned32 xmax;
    PtDspySigned32 ymin;
    PtDspySigned32 ymax;
} PtDspyNextDataInfo;

typedef struct {
    PtDspyUnsigned32 x;
    PtDspyUnsigned32 y;
} PtDspyRenderingStartQuery;

typedef struct {
    int canCheckpoint;
} PtDspySupportsCheckpointing;

typedef struct {
    int supportsPointClouds;
} PtDspyPointCloudQuery;

typedef struct {
    int supportsGrids;
} PtDspyGridQuery;

typedef struct {
    int supportsMultiResolution;
} PtDspyMultiResolutionQuery;

typedef struct {
    int zero, one, min, max; 
    float ditheramplitude;
    int driverWantsToQuantize;
} PtDspyQuantizationQuery;

typedef struct {
    PtDspyUnsigned32 peakkB, currentkB; 
} PtMemoryUsageQuery;

typedef struct {
    PtDspyUnsigned32 seconds; 
} PtElapsedTimeQuery;

typedef enum
{
	PkSizeQuery,
	PkOverwriteQuery,
	PkNextDataQuery,
	PkRedrawQuery,
        PkRenderingStartQuery,
        PkSupportsCheckpointing,
	PkPointCloudQuery,
	PkGridQuery,
	PkMultiResolutionQuery,
        PkQuantizationQuery,
        PkMemoryUsageQuery,
        PkElapsedTimeQuery,
} PtDspyQueryType;

typedef enum
{
    	PkDspyGridConnected,
	PkDspyGridLines,
	PkDspyGridPoints
} PtDspyGridStyle;

typedef enum
{
        PkDspyBucketOrderHorizontal = 1,
        PkDspyBucketOrderVertical,
        PkDspyBucketOrderZigZagX,
        PkDspyBucketOrderZigZagY,
        PkDspyBucketOrderSpiral,
        PkDspyBucketOrderSpaceFill,
        PkDspyBucketOrderRandom
} PtDspyBucketOrder;

typedef enum
{
	PkDspyErrorNone = 0,
	PkDspyErrorNoMemory,
	PkDspyErrorUnsupported,
	PkDspyErrorBadParams,
	PkDspyErrorNoResource,
	PkDspyErrorUndefined,
	PkDspyErrorCancel
} PtDspyError;

#define PkDspyFlagsWantsScanLineOrder 1
#define PkDspyFlagsWantsEmptyBuckets 2
#define PkDspyFlagsWantsNullEmptyBuckets 4
typedef struct
{
	int flags;
} PtFlagStuff;

typedef void * PtDspyImageHandle;

typedef void * PtDspyChannel;

typedef void * PtDspyOutput;

typedef struct
{
	PtDspyServerMessage msg;
	PtDspyUnsigned32 id;
	PtDspyUnsigned32 width;
	PtDspyUnsigned32 height;
	PtDspyUnsigned32 formatCount;
} PtDspyMsgOpen;
typedef struct
{
	PtDspyServerMessage msg;
	PtDspyUnsigned32 id;
	PtDspyUnsigned32 width;
	PtDspyUnsigned32 height;
	PtDspyUnsigned32 formatCount;
	PtDspyUnsigned32 paramCount;
} PtDspyMsgAddOutput;

typedef struct
{
	PtDspyServerMessage msg;
	PtDspyUnsigned32 id;
	PtDspyUnsigned32 formatCount;
	PtDspyUnsigned32 paramCount;
} PtDspyMsgImage;

typedef struct
{
	PtDspyServerMessage msg;
	PtDspyUnsigned32 id;
	PtDspyUnsigned32 xmin;
	PtDspyUnsigned32 xmax;
	PtDspyUnsigned32 ymin;
	PtDspyUnsigned32 ymax;
} PtDspyMsgData;

 typedef struct
{
	PtDspyServerMessage msg;
	PtDspyUnsigned32 id;
	PtDspyUnsigned32 xmin;
	PtDspyUnsigned32 xmax;
	PtDspyUnsigned32 ymin;
	PtDspyUnsigned32 ymax;
 } PtDspyMsgActiveRegion;

typedef struct
{
	PtDspyServerMessage msg;
	PtDspyUnsigned32 id;
	PtDspyUnsigned32 xmin;
	PtDspyUnsigned32 xmax;
	PtDspyUnsigned32 ymin;
	PtDspyUnsigned32 ymax;
	PtDspyUnsigned32 datasize;
} PtDspyMsgDeepData;


typedef struct
{
	PtDspyServerMessage msg;
	PtDspyUnsigned32 id;
	PtDspyQueryType query;
	PtDspyUnsigned32 length;
} PtDspyMsgQuery;

typedef struct
{
	PtDspyServerMessage msg;
	PtDspyUnsigned32 id;
} PtDspyMsgClose;

typedef struct
{
    PtDspySigned8 vtype;
    PtDspySigned8 vcount;
    PtDspySigned8 byteorder;
    PtDspySigned8 XunusedpaddingX;
    PtDspyUnsigned32 nbytes;
    PtDspyUnsigned32 type;
} PtDspyMsgFormat;

typedef struct uparam {
        RtToken         name;
        char            vtype, vcount;
        RtPointer       value;
        int             nbytes;
} UserParameter;


#ifdef __cplusplus
extern "C" {
#endif

typedef PtDspyError
	(*PtDspyOpenFuncPtr)(PtDspyImageHandle * image,
		const char *drivername,
		const char *filename,
		int width,
		int height,
		int paramCount,
		const UserParameter *parameters,
		int iFormatCount,
		PtDspyDevFormat *format,
		PtFlagStuff *flagstuff);

typedef PtDspyError
	(*PtDspyWriteFuncPtr)(PtDspyImageHandle image,
		int xmin,
		int xmax_plus_one,
		int ymin,
		int ymax_plus_one,
		int entrysize,
		const unsigned char *data);

typedef PtDspyError
	(*PtDspyDeepWriteFuncPtr)(PtDspyImageHandle image,
		int xmin,
		int xmax_plus_one,
		int ymin,
		int ymax_plus_one,
		char *data,
                int datasize,
		PtDspyUnsigned32 *pixeloffsets,
		PtDspyUnsigned32 *pixelsizes);

typedef PtDspyError
	(*PtDspyActiveRegionFuncPtr)(PtDspyImageHandle image,
		int xmin,
		int xmax_plus_one,
		int ymin,
                int ymax_plus_one);

typedef PtDspyError
	(*PtDspyCloseFuncPtr)(PtDspyImageHandle);

typedef PtDspyError
	(*PtDspyFlushFuncPtr)(PtDspyImageHandle);

typedef PtDspyError
	(*PtDspyReopenFuncPtr)(PtDspyImageHandle image,
		const char *drivername,
		const char *filename,
		int width,
		int height,
		int paramCount,
		const UserParameter *parameters,
		int iFormatCount,
		PtDspyDevFormat *format,
		PtFlagStuff *flagstuff);

typedef PtDspyError
	(*PtDspyDelayCloseFuncPtr)(PtDspyImageHandle);

typedef PtDspyError
	(*PtDspyQueryFuncPtr)(PtDspyImageHandle,
	   PtDspyQueryType,
	   int ,
	   void *);

typedef enum
{
    k_PtDriverUnknownVersion = 0,
    k_PtDriverCurrentVersion = 1
} PtDriverVersion;

typedef struct
{
    int Version;
    PtDspyOpenFuncPtr pOpen;
    PtDspyWriteFuncPtr pWrite;
    PtDspyCloseFuncPtr pClose;
    PtDspyQueryFuncPtr pQuery;
    PtDspyActiveRegionFuncPtr pActiveRegion;
} PtDspyDriverFunctionTable;


PRMANAPI void
DspyMemReverseCopy(unsigned char *t, const unsigned char *s, int len);

PRMANAPI void
DspyMemReverse(unsigned char *t, int len);

PRMANAPI PtDspyError
DspyFindStringInParamList(const char *string,
	char **result,
	int paramCount,
	const UserParameter *parameters);

PRMANAPI PtDspyError
DspyFindMatrixInParamList(const char *string,
	float *result,
	int paramCount,
	const UserParameter *parameters);

PRMANAPI PtDspyError
DspyFindFloatInParamList(const char *string,
	float *result,
	int paramCount,
	const UserParameter *parameters);

PRMANAPI PtDspyError
DspyFindFloatsInParamList(const char *string,
	int *resultCount,
	float *result,
	int paramCount,
	const UserParameter *parameters);

PRMANAPI PtDspyError
DspyFindIntInParamList(const char *string,
	int *result,
	int paramCount,
	const UserParameter *parameters);

PRMANAPI PtDspyError
DspyFindIntsInParamList(const char *string,
	int *resultCount,
	int *result,
	int paramCount,
	const UserParameter *parameters);

PRMANAPI PtDspyError
DspyReorderFormatting(int formatCount,
	PtDspyDevFormat *format,
	int outFormatCount,
	const PtDspyDevFormat *outFormat);

PRMANAPI void
DspyError(const char *module, const char *fmt, ...);

PRMANAPI PtDspyError
DspyRegisterDriver(const char *name,
                   const PtDspyOpenFuncPtr pOpen,
                   const PtDspyWriteFuncPtr pWrite,
                   const PtDspyCloseFuncPtr pClose,
                   const PtDspyQueryFuncPtr pQuery);

PRMANAPI PtDspyError
DspyRegisterDriverTable(const char *name,
                        const PtDspyDriverFunctionTable *pTable);

PRMANAPI int
DspyGetNumberOfHosts();

PRMANEXPORT PtDspyError
DspyImageOpen(PtDspyImageHandle * image,
		const char *drivername,
		const char *filename,
		int width,
		int height,
		int paramCount,
		const UserParameter *parameters,
		int iFormatCount,
		PtDspyDevFormat *format,
		PtFlagStuff *flagstuff);

PRMANEXPORT PtDspyError
DspyImageData(PtDspyImageHandle image,
		int xmin,
		int xmax,
		int ymin,
		int ymax,
		int entrysize,
		const unsigned char *data);

PRMANEXPORT PtDspyError
DspyImageActiveRegion(PtDspyImageHandle image,
                      int xmin,
                      int xmax,
                      int ymin,
                      int ymax );
 
PRMANEXPORT PtDspyError
DspyImageClose(PtDspyImageHandle);

PRMANEXPORT  PtDspyError
DspyImageReopen(PtDspyImageHandle image,
		const char *drivername,
		const char *filename,
		int width,
		int height,
		int paramCount,
		const UserParameter *parameters,
		int iFormatCount,
		PtDspyDevFormat *format,
		PtFlagStuff *flagstuff);

PRMANEXPORT PtDspyError
DspyImageDelayClose(PtDspyImageHandle);

PRMANEXPORT PtDspyError
DspyImageQuery(PtDspyImageHandle,
	   PtDspyQueryType,
	   int ,
	   void *);

PRMANEXPORT PtDspyError
DspyImageDeepData(PtDspyImageHandle pvImage,
		  int xmin, int xmax, int ymin, int ymax,
		  char *data,int datasize,
		  int *pixeloffsets,
		  int *pixelsizes);

#ifdef __cplusplus
}
#endif

#endif /* ndef NDSPY_H */

