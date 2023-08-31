// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Interfaces/IHttpRequest.h"
#include "AsyncTaskRequestSDImage.generated.h"

class UTexture2DDynamic;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRequestSDImageDelegate, UTexture2DDynamic*, Texture);

/**
 * 
 */
UCLASS()
class SDINTEGRATION_API UAsyncTaskRequestSDImage : public UBlueprintAsyncActionBase
{
	GENERATED_UCLASS_BODY()
public:
	//http://127.0.0.1:7860/sdapi/v1/txt2img
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true"))
	static UAsyncTaskRequestSDImage* RequestSdImageWithJson(FString URL, FString JsonParam);

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true"))
	static UAsyncTaskRequestSDImage* RequestSdImageWithObject(FString URL, USDRequestParameter* ObjectParam);

public:
	UPROPERTY(BlueprintAssignable)
	FRequestSDImageDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FRequestSDImageDelegate OnFail;

public:
	void Start(FString URL, FString JsonParam);

private:
	void HandleImageRequest(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
};
