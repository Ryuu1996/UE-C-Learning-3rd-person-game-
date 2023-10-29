// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/BaseWeapon.h"
#include "Characters/BaseCharacter.h"
#include "Data/WeaponRowBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"


ABaseWeapon::ABaseWeapon()
{
	SphereTraceStart = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Trace Start"));
	SphereTraceStart->SetupAttachment(GetRootComponent());
	SphereTraceEnd = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Trace End"));
	SphereTraceEnd->SetupAttachment(GetRootComponent());
	SphereTraceStart->SetCollisionProfileName("Item");
	SphereTraceEnd->SetCollisionProfileName("Item");
}

void ABaseWeapon::EquipWeapon(ABaseCharacter* Character)
{
	SetItemEquipState(EItemEquipState::Equipped);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABaseWeapon::AttackOverlap);
}

void ABaseWeapon::InitializeData(FName ItemID)
{
	FWeaponRowBase* WeaponRowBase = WeaponDataTable->FindRow<FWeaponRowBase>(ItemID, FString(""));
	Damage = WeaponRowBase->Damage;
}

void ABaseWeapon::AttackOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GetOwner() == nullptr) return;
	// Only different camps can attack each other
	FName ThisProfileName = Cast<ABaseCharacter>(GetOwner())->GetCapsuleComponent()->GetCollisionProfileName();
	FName OtherProfileName = Cast<ABaseCharacter>(OtherActor)->GetCapsuleComponent()->GetCollisionProfileName();
	if (ThisProfileName == OtherProfileName) return;
	
	// The HitResult of Overlap is empty, so I have to trace to get the hit position
	FHitResult HitResult;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypeQuery;
	ObjectTypeQuery.Add(ObjectTypeQuery7);
	ObjectTypeQuery.Add(ObjectTypeQuery9);
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	UKismetSystemLibrary::SphereTraceSingleForObjects(
		this,
		SphereTraceStart->GetComponentLocation(),
		SphereTraceEnd->GetComponentLocation(),
		SphereTraceStart->GetScaledSphereRadius(),
		ObjectTypeQuery,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::None,
		HitResult,
		true
	);

	// TODO: GetHit interface


}
