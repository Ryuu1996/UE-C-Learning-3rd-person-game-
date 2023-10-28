// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "HealthWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class BATTLE_API UHealthWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
private:
	UPROPERTY()
	class UEnemyHealthBarWidget* EnemyHealthBarWidget;

public:
	FORCEINLINE UEnemyHealthBarWidget* GetEnemyHealthBarWidget() const { return EnemyHealthBarWidget; }
	void SetProgressBarHealth(float Percent);
};
