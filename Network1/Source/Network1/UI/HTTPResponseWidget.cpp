// Fill out your copyright notice in the Description page of Project Settings.


#include "HTTPResponseWidget.h"

#include "Components/CircularThrobber.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBoxSlot.h"

void UHTTPResponseWidget::AddUser(int32 UserId, FString Username)
{
	UTextBlock* TextBlock = NewObject<UTextBlock>();

	const FString Text = FString::Printf(TEXT("#%i Username: %s"), UserId, *Username);

	TextBlock->SetText(FText::FromString(Text));

	UserListBox->AddChild(TextBlock);
}

void UHTTPResponseWidget::ClearUserList()
{
	UserListBox->ClearChildren();
}

void UHTTPResponseWidget::ShowError(int32 ErrorCode, FString ErrorMessage)
{
	ClearUserList();

	UTextBlock* TextBlock = NewObject<UTextBlock>();

	const FString Text = FString::Printf(TEXT("ErrorCode: %i Message: %s"), ErrorCode, *ErrorMessage);

	TextBlock->SetColorAndOpacity(FLinearColor(1.f, 0.f, 0.f, 1.f));
	TextBlock->SetText(FText::FromString(Text));

	UserListBox->AddChild(TextBlock);

}

void UHTTPResponseWidget::ShowLoading(bool bIsLoading)
{
	ClearUserList();
	if(bIsLoading)
	{
		UCircularThrobber* LoadingIcon = NewObject<UCircularThrobber>();
		UPanelSlot* PanelSlot = UserListBox->AddChild(LoadingIcon);
		if(PanelSlot)
		{
			UVerticalBoxSlot* VerticalSlot = Cast<UVerticalBoxSlot>(PanelSlot);
			if(VerticalSlot)
			{
				VerticalSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
			}
		}
	}
}