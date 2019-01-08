// Fill out your copyright notice in the Description page of Project Settings.

#include "cvImageUtils.h"

cvImageUtils::cvImageUtils()
{
}

cvImageUtils::~cvImageUtils()
{
}

UTexture2D* cvImageUtils::Mat2Texture(cv::Mat sourceMt)
{
	int height = sourceMt.size().height;
	int width = sourceMt.size().width;
	UTexture2D* targetTx = UTexture2D::CreateTransient(width, height);
	targetTx->CompressionSettings = TextureCompressionSettings::TC_VectorDisplacementmap;
	targetTx->SRGB = 0;

	void* Data = targetTx->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);

	const uint8 ch = 4;
	int32 DataSize = width * height * ch;
	uint8 *colorData = new uint8[DataSize];

	for (int y = 0, i = 0; y < height; y++) {
		for (int x = 0; x < width; x++, y++) {
			colorData[i * ch + 0] = sourceMt.data[i * 3 + 0];
			colorData[i * ch + 1] = sourceMt.data[i * 3 + 1];
			colorData[i * ch + 2] = sourceMt.data[i * 3 + 2];
		}
	}

	FMemory::Memcpy(Data, colorData, DataSize);
	targetTx->PlatformData->Mips[0].BulkData.Unlock();
	targetTx->UpdateResource();

	return targetTx;
	
	//return UTexture2D::CreateTransient(200, 200);
}

cv::Mat cvImageUtils::Texture2Mat(UTexture2D* sourceTx)
{
	FTexture2DMipMap* srcMipMap = &sourceTx->PlatformData->Mips[0];
	FByteBulkData* RawImageData = &srcMipMap->BulkData;
	FColor* FormatedImageData = static_cast<FColor*>(RawImageData->Lock(LOCK_READ_ONLY));
	
	auto height = srcMipMap->SizeY;
	auto width = srcMipMap->SizeX;
	cv::Mat mat(height, width, CV_8UC3);

	for (int y = 0; y < height; y++) {
		auto ptr = mat.ptr<cv::Vec3b>(y);
		for (int x = 0; x < width; x++) {
			auto color = FormatedImageData[y * width + x];
			ptr[x][0] = color.B;
			ptr[x][1] = color.G;
			ptr[x][2] = color.R;
		}
	}

	RawImageData->Unlock();

	return mat;
}
