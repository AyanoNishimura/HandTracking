// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"	
#include "opencv2/imgproc.hpp"

#include "CoreMinimal.h"

/**
 * 
 */
class cvImageUtils
{
public:
	cvImageUtils();
	~cvImageUtils();
	UTexture2D* Mat2Texture(cv::Mat sourceMt);
	cv::Mat Texture2Mat(UTexture2D* sourceTx);
};
