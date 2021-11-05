// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "HTTPResponseWidget.generated.h"




UCLASS(Blueprintable)
class NETWORK1_API UHTTPResponseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void AddUser(int32 UserId, FString Username);

	UFUNCTION(BlueprintCallable)
	void ClearUserList();

	UFUNCTION(BlueprintCallable)
	void ShowLoading(bool bIsLoading);

	UFUNCTION(BlueprintCallable)
	void ShowError(int32 ErrorCode, FString ErrorMessage);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UVerticalBox* UserListBox;
};
