// Fill out your copyright notice in the Description page of Project Settings.


#include "SDRequestParameter.h"
#include "Json.h"

FString USDRequestParameter::ConvertToJsonString_Implementation()
{
	TSharedPtr<FJsonObject> ObjectJson = MakeShareable(new FJsonObject);
	ObjectJson->SetStringField(TEXT("prompt"), Prompt);
	ObjectJson->SetStringField(TEXT("negative_prompt"), NegativePrompt);
	ObjectJson->SetStringField(TEXT("sampler_index"), SamplerIndex);
	ObjectJson->SetNumberField(TEXT("steps"), Steps);
	ObjectJson->SetNumberField(TEXT("seed"), Seed);
	ObjectJson->SetNumberField(TEXT("width"), Width);
	ObjectJson->SetNumberField(TEXT("height"), Height);
	ObjectJson->SetNumberField(TEXT("cfg_scale"), CfgScale);
	FString OutputString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(ObjectJson.ToSharedRef(), Writer);
	OutputString = OutputString.Replace(TEXT("\n"), TEXT(""));
	OutputString = OutputString.Replace(TEXT("\r"), TEXT(""));
	OutputString = OutputString.Replace(TEXT("\t"), TEXT(""));
	return OutputString;
}
