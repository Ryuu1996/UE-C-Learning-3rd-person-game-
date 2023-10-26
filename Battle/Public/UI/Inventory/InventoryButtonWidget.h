// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/InventoryRowBase.h"
#include "InventoryButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class BATTLE_API UInventoryButtonWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	// Button which shows the item name
	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonItem;

	// The image of the item
	UPROPERTY(meta = (BindWidget))
	class UImage* ItemIcon;

	// Text which shows the quantity
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlockQuantity;

	// Text which shows the item name
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlockItemName;

	// Description background
	UPROPERTY(meta = (BindWidget))
	class UImage* DescriptionBackground;

	// The description text
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlockDescription;

	// Button to use the item
	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonUse;

	// Button to drop the item
	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonDrop;

	// Item informations
	struct FInventoryRowBase* InventoryRowBase;

	// Is use & drop button visible
	bool IsUseDropVisible = false;

	// PlayerCharacter pointer
	class APlayerCharacter* PlayerCharacter;

public:
	// Construct
	virtual void NativeConstruct() override;

	// Set the item image of the button
	void SetItemIcon(UTexture2D* Texture2D);

	// Set the item quantity of the button 
	void SetTextBlockQuantity(FText Text);

	// Set the item name of the button
	void SetTextBlockItemName(FText Text);

	// Set the description of the item
	void SetTextBlockDescription(FText Text);

	// When hover over the button, show the description of the item
	void ShowDescription();

	// Hide the description
	void HideDescription();

	// When button clicked, show use & drop button
	void ShowUseDropButton();

	// When button clicked again, hide use & drop button
	void HideUseDropButton();

	// Set the item informations, and initialize button
	void SetInventoryRowBase(FInventoryRowBase* ParaInventoryRowBase, int32 Quantity);
protected:
private:
	// On button hovered
	UFUNCTION()
	void OnButtonHovered();

	// On button unhovered
	UFUNCTION()
	void OnButtonUnhovered();

	// On button clicked
	UFUNCTION()
	void OnButtonClicked();

	// On use button pressed
	UFUNCTION()
	void InventoryUseItem();

	// Use Item
	UFUNCTION()
	void UseItem();
};
