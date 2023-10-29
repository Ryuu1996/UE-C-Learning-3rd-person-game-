// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/BaseItem.h"

#include "BaseWeapon.generated.h"

/**
 * 
 */
UCLASS()
class BATTLE_API ABaseWeapon : public ABaseItem
{
	GENERATED_BODY()
private:	
	/********************
	* Data Properties
	********************/
	// Data table for search
	UPROPERTY(EditDefaultsOnly, Category = "TOSET Data")
	class UDataTable* WeaponDataTable;

	// The damage of the weapon
	int32 Damage = 0;

	/********************
	* Hit Trace Properties
	********************/
	UPROPERTY(VisibleDefaultsOnly)
	class USphereComponent* SphereTraceStart;

	UPROPERTY(VisibleDefaultsOnly)
	class USphereComponent* SphereTraceEnd;

	UPROPERTY(EditDefaultsOnly, Category = "TOSET Socket")
	FName EquipSocket = "RightHandSocket";
public:
	ABaseWeapon();
	// Equip weapon
	virtual void EquipWeapon(class ABaseCharacter* Character);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Initialize data
	void InitializeData(FName RowName);

	// Overlap when attacking
	UFUNCTION()
	void AttackOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:
public:
	FORCEINLINE int32 GetDamage() const { return Damage; }

};
