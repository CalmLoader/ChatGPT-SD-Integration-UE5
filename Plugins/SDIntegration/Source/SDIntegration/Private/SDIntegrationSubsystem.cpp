// Fill out your copyright notice in the Description page of Project Settings.


#include "SDIntegrationSubsystem.h"

void USDIntegrationSubsystem::GetRequestChatGPTURL(FString& ChatGPTURL)
{
	ChatGPTURL = MyChatGPTURL;
}

void USDIntegrationSubsystem::GetRequestSDURL(FString& SDURL)
{
	SDURL = MySDURL;
}

void USDIntegrationSubsystem::GetChatGPTKey(FString& Key)
{
	Key = MyChatGPTKey;
}

void USDIntegrationSubsystem::SetRequestChatGPTURL(FString ChatGPTURL)
{
	MyChatGPTURL = ChatGPTURL;
}

void USDIntegrationSubsystem::SetRequestSDURL(FString SDURL)
{
	MySDURL = SDURL;
}

void USDIntegrationSubsystem::SetRequestChatGPTKey(FString Key)
{
	MyChatGPTKey = Key;
}

void USDIntegrationSubsystem::InitializeAllField(FString ChatGPTURL, FString SDURL, FString ChatGPTKey)
{
	MyChatGPTURL = ChatGPTURL;
	MySDURL = SDURL;
	MyChatGPTKey = ChatGPTKey;
}

void USDIntegrationSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	//!!!!此处ChatGPTKey需要替换为可用的Key
	this->InitializeAllField(TEXT("https://yourbecbt.top/api/chat"), TEXT("http://127.0.0.1:7860/sdapi/v1/txt2img"),
	                         TEXT("xxxxxx"));
}
