// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"	
#include "opencv2/imgproc.hpp"

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TrackingUtils.generated.h"

/**
 * 
 */
UCLASS()
class REALSENSESAMPLES_API UTrackingUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable, Category = "Camera Tracking")
	static UTexture2D* HandTracking(UTexture2D* sourceTx);
	
};
