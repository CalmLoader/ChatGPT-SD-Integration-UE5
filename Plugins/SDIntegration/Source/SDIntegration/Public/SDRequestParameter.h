// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SDRequestParameter.generated.h"


UENUM(BlueprintType)
enum class ESamplerIndex : uint8
{
	Euler_A,
};


/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class SDINTEGRATION_API USDRequestParameter : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(ExposeOnSpawn), Category="BaseParam")
	FString Prompt;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(ExposeOnSpawn), Category="BaseParam")
	FString NegativePrompt;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(ExposeOnSpawn), Category="BaseParam")
	FString SamplerIndex = TEXT("Euler a");
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(ExposeOnSpawn), Category="BaseParam")
	int Steps = 20;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(ExposeOnSpawn), Category="BaseParam")
	int Seed = -1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(ExposeOnSpawn), Category="BaseParam")
	int Width = 512;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(ExposeOnSpawn), Category="BaseParam")
	int Height = 512;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(ExposeOnSpawn), Category="BaseParam")
	int CfgScale = 7;

public:
	UFUNCTION(BlueprintCallable, Category="SDRequest", BlueprintNativeEvent)
	FString ConvertToJsonString();
};
