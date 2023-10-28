// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"


#include "AttributeRowBase.generated.h"


USTRUCT(BlueprintType)
struct FAttributeRowBase : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString Name;

	UPROPERTY(EditAnywhere)
	int32 HP;

	UPROPERTY(EditAnywhere)
	int32 Stamina;

};