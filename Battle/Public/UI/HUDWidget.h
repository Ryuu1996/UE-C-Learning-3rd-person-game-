// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class BATTLE_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	// Progress Bar HP
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* ProgressBarHP;

	// Progress Bar STA
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* ProgressBarSTA;

	// Text Block HP
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlockHP;
public:
	void SetProgressBarHPPercent(float Percent);
	void SetProgressBarSTAPercent(float Percent);
	void SetTextBlockHP(int32 HP, int32 MaxHP);
	
protected:
private:


};
