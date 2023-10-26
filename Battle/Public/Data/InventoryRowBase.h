// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/Texture2D.h"
#include "InventoryRowBase.generated.h"

USTRUCT(BlueprintType)
struct FInventoryRowBase : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString Name;

	UPROPERTY(EditAnywhere)
	FString Description;

	UPROPERTY(EditAnywhere)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ClassName;

	UPROPERTY(EditAnywhere)
	int32 StackSize;

	UPROPERTY(EditAnywhere)
	int32 SellValue;
};


