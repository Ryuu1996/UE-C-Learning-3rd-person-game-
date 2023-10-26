// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/InventoryButtonWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Characters/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/ItemInterface.h"

void UInventoryButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	HideDescription();
	HideUseDropButton();
	ButtonItem->OnHovered.AddDynamic(this, &UInventoryButtonWidget::OnButtonHovered);
	ButtonItem->OnUnhovered.AddDynamic(this, &UInventoryButtonWidget::OnButtonUnhovered);
	ButtonItem->OnClicked.AddDynamic(this, &UInventoryButtonWidget::OnButtonClicked);
	ButtonUse->OnClicked.AddDynamic(this, &UInventoryButtonWidget::InventoryUseItem);
}

void UInventoryButtonWidget::SetItemIcon(UTexture2D* Texture2D)
{
	ItemIcon->SetBrushFromTexture(Texture2D, true);
}

void UInventoryButtonWidget::SetTextBlockQuantity(FText Text)
{
	TextBlockQuantity->SetText(Text);
}

void UInventoryButtonWidget::SetTextBlockItemName(FText Text)
{
	TextBlockItemName->SetText(Text);
}

void UInventoryButtonWidget::SetTextBlockDescription(FText Text)
{
	TextBlockDescription->SetText(Text);
}

void UInventoryButtonWidget::ShowDescription()
{
	TextBlockItemName->SetVisibility(ESlateVisibility::Hidden);
	DescriptionBackground->SetVisibility(ESlateVisibility::Visible);
	TextBlockDescription->SetVisibility(ESlateVisibility::Visible);
}

void UInventoryButtonWidget::HideDescription()
{
	TextBlockItemName->SetVisibility(ESlateVisibility::Visible);
	DescriptionBackground->SetVisibility(ESlateVisibility::Hidden);
	TextBlockDescription->SetVisibility(ESlateVisibility::Hidden);
}

void UInventoryButtonWidget::ShowUseDropButton()
{
	ButtonUse->SetVisibility(ESlateVisibility::Visible);
	ButtonDrop->SetVisibility(ESlateVisibility::Visible);
}

void UInventoryButtonWidget::HideUseDropButton()
{
	ButtonUse->SetVisibility(ESlateVisibility::Hidden);
	ButtonDrop->SetVisibility(ESlateVisibility::Hidden);
}

void UInventoryButtonWidget::SetInventoryRowBase(FInventoryRowBase* ParaInventoryRowBase, int32 Quantity)
{
	InventoryRowBase = ParaInventoryRowBase;
	SetTextBlockItemName(FText::FromString(InventoryRowBase->Name));
	SetTextBlockQuantity(FText::FromString(FString::FromInt(Quantity)));
	SetItemIcon(InventoryRowBase->Icon);
	SetTextBlockDescription(FText::FromString(InventoryRowBase->Description));
}

void UInventoryButtonWidget::OnButtonHovered()
{
	ShowDescription();
}

void UInventoryButtonWidget::OnButtonUnhovered()
{
	HideDescription();
}

void UInventoryButtonWidget::OnButtonClicked()
{
	switch (IsUseDropVisible)
	{
	case true:
		HideUseDropButton();
		IsUseDropVisible = false;
		break;
	case false:
		ShowUseDropButton();
		IsUseDropVisible = true;
		break;
	}
}

void UInventoryButtonWidget::InventoryUseItem()
{
	FName ID = FName(InventoryRowBase->Name);
	PlayerCharacter->InventoryItems[ID]--;
	if (PlayerCharacter->InventoryItems[ID] <= 0)
	{
		PlayerCharacter->InventoryItems.Remove(ID);
	}
	PlayerCharacter->CloseInventory();
	PlayerCharacter->OpenInventory();
	HideUseDropButton();
	UseItem();
}

void UInventoryButtonWidget::UseItem()
{
	AActor* ActorToUse = GetWorld()->SpawnActor(InventoryRowBase->ClassName);
	IItemInterface* ItemInterface = Cast<IItemInterface>(ActorToUse);
	if (ItemInterface)
	{
		ItemInterface->Execute_UseItem(ActorToUse);
	}
}

