// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Enemy/HealthWidgetComponent.h"
#include "UI/Enemy/EnemyHealthBarWidget.h"
#include "Components/ProgressBar.h"

void UHealthWidgetComponent::SetProgressBarHealth(float Percent)
{
	if (EnemyHealthBarWidget == nullptr)
	{
		EnemyHealthBarWidget = Cast<UEnemyHealthBarWidget>(GetUserWidgetObject());
	}
	EnemyHealthBarWidget->GetHealthBar()->SetPercent(Percent);
}
