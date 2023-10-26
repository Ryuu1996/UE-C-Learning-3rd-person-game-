// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class BATTLE_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	// The panel to contain buttons
	UPROPERTY(meta = (BindWidget))
	class UScrollBox* ScrollBox;
public:
	
protected:
private:
public:
	FORCEINLINE UScrollBox* GetUScrollBox() const { return ScrollBox; }
};
