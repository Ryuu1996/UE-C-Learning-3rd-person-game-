// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/BaseItem.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"


ABaseItem::ABaseItem()
{
	PrimaryActorTick.bCanEverTick = true;
	InitializeMesh();
}

void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
}


void ABaseItem::InitializeMesh()
{
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	SetRootComponent(CapsuleComponent);
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh Component"));
	ItemMesh->SetupAttachment(GetRootComponent());
	ItemMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// Search my custom object type in Config/DefaultEngine.ini, in this case I want to set it Item
	ItemMesh->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2);

	HighlightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Highlight Mesh Component"));
	HighlightMesh->SetupAttachment(ItemMesh);
	HighlightMesh->SetVisibility(false);
	HighlightMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	HighlightMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UStaticMeshComponent* ABaseItem::GetHighlightMesh() const
{
	return HighlightMesh;
}


