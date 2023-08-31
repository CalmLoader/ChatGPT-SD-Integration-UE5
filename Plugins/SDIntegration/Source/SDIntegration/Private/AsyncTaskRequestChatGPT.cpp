// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncTaskRequestChatGPT.h"
#include "Interfaces/IHttpResponse.h"
#include "HttpModule.h"
#include "SDIntegrationSubsystem.h"


UAsyncTaskRequestChatGPT::UAsyncTaskRequestChatGPT(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	if (HasAnyFlags(RF_ClassDefaultObject) == false)
	{
		AddToRoot();
	}
}

UAsyncTaskRequestChatGPT* UAsyncTaskRequestChatGPT::AsyncTaskRequestChatGPT(FString Content)
{
	check(GWorld);
	USDIntegrationSubsystem* SDIntegrationSubsystem = GWorld->GetGameInstance()->GetSubsystem<
		USDIntegrationSubsystem>();
	check(SDIntegrationSubsystem);
	FString Key;
	SDIntegrationSubsystem->GetChatGPTKey(Key);
	return AsyncTaskRequestChatGPTWithKey(Content, Key);
}

UAsyncTaskRequestChatGPT* UAsyncTaskRequestChatGPT::AsyncTaskRequestChatGPTWithKey(FString Content, FString Key)
{
	UAsyncTaskRequestChatGPT* RequestChatGPTTask = NewObject<UAsyncTaskRequestChatGPT>();
	RequestChatGPTTask->Start(Content, Key);
	return RequestChatGPTTask;
}

void UAsyncTaskRequestChatGPT::Start(FString Content, FString Key)
{
#if !UE_SERVER
	TSharedPtr<FJsonObject> HeaderObjectJson = MakeShareable(new FJsonObject);
	TSharedPtr<FJsonObject> ModelObjectJson = MakeShareable(new FJsonObject);
	ModelObjectJson->SetStringField(TEXT("id"), TEXT("gpt-3.5-turbo"));
	ModelObjectJson->SetStringField(TEXT("name"), TEXT("GPT-3.5"));
	ModelObjectJson->SetNumberField(TEXT("maxLength"), 12000);
	ModelObjectJson->SetNumberField(TEXT("tokenLimit"), 4000);
	HeaderObjectJson->SetObjectField(TEXT("model"), ModelObjectJson);

	TArray<TSharedPtr<FJsonValue>> JsonArray;

	TSharedPtr<FJsonObject> OneTempJsonObject = MakeShareable(new FJsonObject);
	OneTempJsonObject->SetStringField(TEXT("role"), TEXT("user"));
	OneTempJsonObject->SetStringField(TEXT("content"), Content);
	TSharedPtr<FJsonValue> FirstJsonValue = MakeShareable(new FJsonValueObject(OneTempJsonObject));
	JsonArray.Add(FirstJsonValue);
	HeaderObjectJson->SetArrayField(TEXT("messages"), JsonArray);

	HeaderObjectJson->SetStringField(TEXT("key"), Key);
	HeaderObjectJson->SetStringField(
		TEXT("prompt"),
		TEXT(
			"You are ChatGPT, a large language model trained by OpenAI. Follow the user's instructions carefully. Respond using markdown."));
	HeaderObjectJson->SetNumberField(TEXT("temperature"), 1);

	FString HeaderString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&HeaderString);
	FJsonSerializer::Serialize(HeaderObjectJson.ToSharedRef(), Writer);
	HeaderString = HeaderString.Replace(TEXT("\n"), TEXT(""));
	HeaderString = HeaderString.Replace(TEXT("\r"), TEXT(""));
	HeaderString = HeaderString.Replace(TEXT("\t"), TEXT(""));

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	FString URL;
	check(GWorld);
	USDIntegrationSubsystem* SDIntegrationSubsystem = GWorld->GetGameInstance()->GetSubsystem<
		USDIntegrationSubsystem>();
	check(SDIntegrationSubsystem);
	SDIntegrationSubsystem->GetRequestChatGPTURL(URL);
	HttpRequest->SetURL(URL);
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json; charset=utf-8"));
	HttpRequest->SetHeader(
		TEXT("User-Agent"),
		TEXT(
			"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.0.0 Safari/537.36"));
	HttpRequest->SetVerb(TEXT("POST"));


	HttpRequest->SetContentAsString(HeaderString);
	HttpRequest->OnRequestProgress().BindUObject(this, &UAsyncTaskRequestChatGPT::HandleProgress);
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UAsyncTaskRequestChatGPT::HandleChatGPTRequest);
	HttpRequest->ProcessRequest();
#else
	RemoveFromRoot();
#endif
}

void UAsyncTaskRequestChatGPT::HandleChatGPTRequest(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse,
                                                    bool bSucceeded)
{
#if !UE_SERVER
	RemoveFromRoot();
	if (bSucceeded && HttpResponse.IsValid() && HttpResponse->GetContentLength() > 0)
	{
		UE_LOG(LogTemp, Log, TEXT("UAsyncTaskRequestChatGPT:%s"), *HttpResponse->GetContentAsString());
		OnSuccess.Broadcast(HttpResponse->GetContentAsString());
		return;
	}
	OnFail.Broadcast(TEXT(""));
#endif
}

void UAsyncTaskRequestChatGPT::HandleProgress(FHttpRequestPtr Request, int32 BytesSent, int32 BytesReceived)
{
	UE_LOG(LogTemp, Log, TEXT("HandleProgress:%s"), *Request->GetResponse()->GetContentAsString());
	OnProgress.Broadcast(Request->GetResponse()->GetContentAsString());
}
