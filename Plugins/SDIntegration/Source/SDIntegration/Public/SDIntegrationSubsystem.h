// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SDIntegrationSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class SDINTEGRATION_API USDIntegrationSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="SDIntegrationSubsystem")
	void GetRequestChatGPTURL(FString& ChatGPTURL);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="SDIntegrationSubsystem")
	void GetRequestSDURL(FString& SDURL);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="SDIntegrationSubsystem")
	void GetChatGPTKey(FString& Key);

	UFUNCTION(BlueprintCallable, Category="SDIntegrationSubsystem")
	void SetRequestChatGPTURL(FString ChatGPTURL);
	UFUNCTION(BlueprintCallable, Category="SDIntegrationSubsystem")
	void SetRequestSDURL(FString SDURL);
	UFUNCTION(BlueprintCallable, Category="SDIntegrationSubsystem")
	void SetRequestChatGPTKey(FString Key);

	UFUNCTION(BlueprintCallable, Category="SDIntegrationSubsystem")
	void InitializeAllField(FString ChatGPTURL, FString SDURL, FString ChatGPTKey);

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

private:
	UPROPERTY()
	FString MyChatGPTURL;
	UPROPERTY()
	FString MySDURL;
	UPROPERTY()
	FString MyChatGPTKey;
};
