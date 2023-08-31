// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncTaskRequestChatGPT.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRequestChatGPTDelegate, FString, Result);

/**
 * 
 */
UCLASS()
class SDINTEGRATION_API UAsyncTaskRequestChatGPT : public UBlueprintAsyncActionBase
{
	GENERATED_UCLASS_BODY()
public:
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true"))
	static UAsyncTaskRequestChatGPT* AsyncTaskRequestChatGPT(FString Content);

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true"))
	static UAsyncTaskRequestChatGPT* AsyncTaskRequestChatGPTWithKey(FString Content, FString Key);

public:
	UPROPERTY(BlueprintAssignable)
	FRequestChatGPTDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FRequestChatGPTDelegate OnProgress;

	UPROPERTY(BlueprintAssignable)
	FRequestChatGPTDelegate OnFail;

	void Start(FString Content, FString Key);

private:
	void HandleProgress(FHttpRequestPtr Request, int32 BytesSent, int32 BytesReceived);
	void HandleChatGPTRequest(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
};
