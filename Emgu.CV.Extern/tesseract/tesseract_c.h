//----------------------------------------------------------------------------
//
//  Copyright (C) 2004-2016 by EMGU Corporation. All rights reserved.
//
//----------------------------------------------------------------------------

#pragma once
#ifndef EMGU_TESSERACT_C_H
#define EMGU_TESSERACT_C_H

#if (_MSC_VER >= 1200)          
typedef __int64 INT64;
typedef unsigned __int64 UINT64;
#endif

#include "opencv2/core/core.hpp"
#include "opencv2/core/core_c.h"
#include "stdio.h"
#include "baseapi.h"
#include "allheaders.h"

class EmguTesseract: public tesseract::TessBaseAPI
{
public:
   int GetTextLength(int* blob_count)
   {
      return TextLength(blob_count);
   }

   int GetImageHeight()
   {
      int left, top, width, height, imageWidth, imageHeight;
      thresholder_->GetImageSizes(&left, &top, &width, &height,
                             &imageWidth, &imageHeight);
      return imageHeight;
   }

   int TesseractExtractResult(char** text,
      int** lengths,
      float** costs,
      int** x0,
      int** y0,
      int** x1,
      int** y1)
   {
      return tesseract::TessBaseAPI::TesseractExtractResult(text, lengths, costs, x0, y0, x1, y1, page_res_);
   }
};

struct TesseractResult
{
   int length;
   float cost;
   CvRect region;
};

CVAPI(const char*) TesseractGetVersion();

CVAPI(EmguTesseract*) TessBaseAPICreate();

CVAPI(int) TessBaseAPIInit(EmguTesseract* ocr, const char* dataPath, const char* language, int mode);

CVAPI(void) TessBaseAPIRelease(EmguTesseract** ocr);

//CVAPI(void) TessBaseAPIRecognizeImage(EmguTesseract* ocr, IplImage* image);

CVAPI(void) TessBaseAPIRecognizeArray(EmguTesseract* ocr, cv::_InputArray* mat);

CVAPI(void) TessBaseAPIGetUTF8Text(EmguTesseract* ocr, std::vector<unsigned char>* vectorOfByte);

CVAPI(void) TessBaseAPIGetHOCRText(EmguTesseract* ocr, int pageNumber, std::vector<unsigned char>* vectorOfByte);

CVAPI(void) TessBaseAPIExtractResult(EmguTesseract* ocr, std::vector<unsigned char>* charSeq, std::vector<TesseractResult>* resultSeq);

CVAPI(bool) TessBaseAPISetVariable(EmguTesseract* ocr, const char* varName, const char* value);

CVAPI(void) TessBaseAPISetPageSegMode(EmguTesseract* ocr, tesseract::PageSegMode mode);

CVAPI(tesseract::PageSegMode) TessBaseAPIGetPageSegMode(EmguTesseract* ocr);

CVAPI(int) TessBaseAPIGetOpenCLDevice(EmguTesseract* ocr, void **device);

CVAPI(tesseract::PageIterator*) TessBaseAPIAnalyseLayout(EmguTesseract* ocr, bool mergeSimilarWords);

CVAPI(void) TessPageIteratorGetOrientation(tesseract::PageIterator* iterator, tesseract::Orientation* orientation, tesseract::WritingDirection* writingDirection, tesseract::TextlineOrder* order, float* deskewAngle);

CVAPI(void) TessPageIteratorRelease(tesseract::PageIterator** iterator);

CVAPI(bool) TessPageIteratorGetBaseLine(
   tesseract::PageIterator* iterator,
   tesseract::PageIteratorLevel level,
   int* x1, int* y1, int* x2, int* y2);

CVAPI(int) TessBaseAPIIsValidWord(EmguTesseract* ocr, char* word);

CVAPI(Pix*) leptCreatePixFromMat(cv::Mat* m);
#endif
