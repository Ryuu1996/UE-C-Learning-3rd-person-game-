// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UHUDWidget::SetProgressBarHPPercent(float Percent)
{
	if (ProgressBarHP) ProgressBarHP->SetPercent(Percent);
}

void UHUDWidget::SetProgressBarSTAPercent(float Percent)
{
	if (ProgressBarSTA) ProgressBarSTA->SetPercent(Percent);
}

void UHUDWidget::SetTextBlockHP(int32 CurrentHP, int32 MaxHP)
{
	if (TextBlockHP)
	{
		const FString String = FString::Printf(TEXT("%d / %d"), CurrentHP, MaxHP);
		const FText Text = FText::FromString(String);
		TextBlockHP->SetText(Text);
	}
}
