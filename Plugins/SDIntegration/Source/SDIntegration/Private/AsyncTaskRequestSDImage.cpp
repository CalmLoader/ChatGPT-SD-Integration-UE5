// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncTaskRequestSDImage.h"
#include "HttpModule.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "SDRequestParameter.h"
#include "Engine/Texture2DDynamic.h"
#include "Interfaces/IHttpResponse.h"

UAsyncTaskRequestSDImage::UAsyncTaskRequestSDImage(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	if (HasAnyFlags(RF_ClassDefaultObject) == false)
	{
		AddToRoot();
	}
}

UAsyncTaskRequestSDImage* UAsyncTaskRequestSDImage::RequestSdImageWithJson(FString URL, FString JsonParam)
{
	UAsyncTaskRequestSDImage* RequestSDTask = NewObject<UAsyncTaskRequestSDImage>();
	RequestSDTask->Start(URL, JsonParam);
	return RequestSDTask;
}

UAsyncTaskRequestSDImage* UAsyncTaskRequestSDImage::RequestSdImageWithObject(
	FString URL, USDRequestParameter* ObjectParam)
{
	return RequestSdImageWithJson(URL, ObjectParam->ConvertToJsonString());
}

void UAsyncTaskRequestSDImage::Start(FString URL, FString JsonParam)
{
#if !UE_SERVER
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(URL);
	// FString JsonStr = "{\"prompt\": \"a beautiful girl\",\"negative_prompt\": \"\",\"sampler_index\": \"Euler a\",\"seed\": 3,\"steps\": 20,\"width\": 512,\"height\": 512,\"cfg_scale\": 7}";
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json; charset=utf-8"));
	HttpRequest->SetVerb(TEXT("POST"));
	HttpRequest->SetContentAsString(JsonParam);
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UAsyncTaskRequestSDImage::HandleImageRequest);
	HttpRequest->ProcessRequest();
#else
	RemoveFromRoot();
#endif
}

void UAsyncTaskRequestSDImage::HandleImageRequest(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse,
                                                  bool bSucceeded)
{
#if !UE_SERVER
	RemoveFromRoot();
	if (bSucceeded && HttpResponse.IsValid() && HttpResponse->GetResponseCode() == 200 && HttpResponse->
		GetContentLength() > 0)
	{
		FString JsonStr = HttpResponse->GetContentAsString();
		TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonStr);
		TSharedPtr<FJsonValue> CurrentJsonValue;
		FJsonSerializer::Deserialize(JsonReader, CurrentJsonValue);
		TArray<TSharedPtr<FJsonValue>> ImageJsonObjectArray = CurrentJsonValue->AsObject()->GetArrayField(
			TEXT("images"));

		IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(
			FName("ImageWrapper"));
		TSharedPtr<IImageWrapper> ImageWrappers[3] =
		{
			ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG),
			ImageWrapperModule.CreateImageWrapper(EImageFormat::JPEG),
			ImageWrapperModule.CreateImageWrapper(EImageFormat::BMP),
		};

		for (int j = 0; j < ImageJsonObjectArray.Num(); j++)
		{
			auto CurrentImage = ImageJsonObjectArray[j]->AsString();
			TArray<uint8> CurrentImageBytes;
			FBase64::Decode(CurrentImage, CurrentImageBytes);
			for (auto ImageWrapper : ImageWrappers)
			{
				if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(
					CurrentImageBytes.GetData(), CurrentImageBytes.GetAllocatedSize()))
				{
					TArray64<uint8> RawData;
					const ERGBFormat InFormat = ERGBFormat::BGRA;
					if (ImageWrapper->GetRaw(InFormat, 8, RawData))
					{
						if (UTexture2DDynamic* Texture = UTexture2DDynamic::Create(
							ImageWrapper->GetWidth(), ImageWrapper->GetHeight()))
						{
							Texture->SRGB = true;
							Texture->UpdateResource();

							FTexture2DDynamicResource* TextureResource = static_cast<FTexture2DDynamicResource*>(Texture
								->GetResource());
							if (TextureResource)
							{
								ENQUEUE_RENDER_COMMAND(FWriteRawDataToTexture)(
									[TextureResource, RawData = MoveTemp(RawData)](FRHICommandListImmediate& RHICmdList)
									{
										TextureResource->WriteRawToTexture_RenderThread(RawData);
									});
							}
							OnSuccess.Broadcast(Texture);
							return;
						}
					}
				}
			}
		}
	}
	OnFail.Broadcast(nullptr);
#endif
}
