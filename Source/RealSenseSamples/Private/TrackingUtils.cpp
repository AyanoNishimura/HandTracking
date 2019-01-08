// Fill out your copyright notice in the Description page of Project Settings.

#include "TrackingUtils.h"
#include "cvImageUtils.h"


UTexture2D* UTrackingUtils::HandTracking(UTexture2D* sourceTx)
{
	UTexture2D* targetTx;
	cv::Mat sourceMt;
	cvImageUtils *imgUtil = new cvImageUtils();

	sourceMt = imgUtil->Texture2Mat(sourceTx);
	targetTx = imgUtil->Mat2Texture(sourceMt);
	return sourceTx;
}

