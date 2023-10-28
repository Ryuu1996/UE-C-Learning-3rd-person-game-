// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyHealthBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class BATTLE_API UEnemyHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;
public:
	FORCEINLINE UProgressBar* GetHealthBar() const { return HealthBar; }
};
