// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHUD.h"
#include "UI/HUDWidget.h"
#include "UI/Inventory/InventoryWidget.h"
#include "UI/Inventory/InventoryButtonWidget.h"
#include "Components/ScrollBox.h"
#include "Data/InventoryRowBase.h"


void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();
	InitializeWidgets();
}

void APlayerHUD::RefreshInventory()
{
	if (PlayerController == nullptr) return;
	if (InventoryWidgetClass == nullptr) return;
	InventoryWidget = CreateWidget<UInventoryWidget>(PlayerController, InventoryWidgetClass);
	// GC, don't find better way to delete widgets here
	CollectGarbage(EObjectFlags::RF_NoFlags);
}

void APlayerHUD::AddButtonToInventory(FInventoryRowBase* InventoryRowBase, int32 Quantity)
{
	if (InventoryButtonWidgetClass == nullptr) return;
	UInventoryButtonWidget* InventoryButtonWidget = CreateWidget<UInventoryButtonWidget>(PlayerController, InventoryButtonWidgetClass);
	InventoryButtonWidget->SetInventoryRowBase(InventoryRowBase, Quantity);
	InventoryWidget->GetUScrollBox()->AddChild(InventoryButtonWidget);
}

void APlayerHUD::InitializeWidgets()
{
	UWorld* World = GetWorld();
	if (World == nullptr) return;
	PlayerController = World->GetFirstPlayerController();
	if (PlayerController == nullptr) return;

	if (HUDWidgetClass)
	{
		HUDWidget = CreateWidget<UHUDWidget>(PlayerController, HUDWidgetClass);
		HUDWidget->AddToViewport();
	}
	if (InventoryWidgetClass)
	{
		InventoryWidget = CreateWidget<UInventoryWidget>(PlayerController, InventoryWidgetClass);
	}
}
