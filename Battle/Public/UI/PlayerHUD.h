// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class BATTLE_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
private:
	/********************
	* Initialize
	********************/
	class APlayerController* PlayerController;

	/********************
	* HUD
	********************/
	// Use TSubclassOf to access blueprint class
	UPROPERTY(EditDefaultsOnly, Category = "TOSET UI")
	TSubclassOf<class UHUDWidget> HUDWidgetClass;

	// HUD Widget
	UPROPERTY();
	class UHUDWidget* HUDWidget;

	/********************
	* Inventory
	********************/
	// Use TSubclassOf to access blueprint class
	UPROPERTY(EditDefaultsOnly, Category = "TOSET UI")
	TSubclassOf<class UInventoryWidget> InventoryWidgetClass;

	// Inventory Widget
	UPROPERTY()
	class UInventoryWidget* InventoryWidget;

	// Use TSubclassOf to access blueprint class
	UPROPERTY(EditDefaultsOnly, Category = "TOSET UI")
	TSubclassOf<class UInventoryButtonWidget> InventoryButtonWidgetClass;

public:
	// Recreate Inventory widget, and GC
	void RefreshInventory();

	// Add Inventory item button
	void AddButtonToInventory(struct FInventoryRowBase* InventoryRowBase, int32 Quantity);
protected:
	// Begin Play
	virtual void BeginPlay() override;
private:
	// Initialize Widgets
	void InitializeWidgets();
public:
	FORCEINLINE UHUDWidget* GetHUDWidget() const { return HUDWidget; }
	FORCEINLINE UInventoryWidget* GetInventoryWidget() const { return InventoryWidget; }
};
