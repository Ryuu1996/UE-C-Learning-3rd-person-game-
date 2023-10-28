// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "InputActionValue.h"
#include "Enums/CharacterEnums.h"

#include "PlayerCharacter.generated.h"


/**
 * 
 */
UCLASS()
class BATTLE_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
private:
	/********************
	* General Properties
	********************/
	// Player controller
	APlayerController* PlayerController;

	// Player Animate Instance
	class UPlayerLocomotionAnimInstance* LocomotionAnimInstance;

	/********************
	* Act Input Properties
	********************/
	// Act Input Mapping Context
	UPROPERTY(EditDefaultsOnly, Category = "TOSET Input")
	class UInputMappingContext* ActMappingContext;

	// Look Input Action
	UPROPERTY(EditDefaultsOnly, Category = "TOSET Input")
	class UInputAction* LookAction;

	// Move Input Action
	UPROPERTY(EditDefaultsOnly, Category = "TOSET Input")
	class UInputAction* MoveAction;

	// Jump Input Action
	UPROPERTY(EditDefaultsOnly, Category = "TOSET Input")
	class UInputAction* JumpAction;

	// Walk Input Action
	UPROPERTY(EditDefaultsOnly, Category = "TOSET Input")
	class UInputAction* WalkAction;

	// Focus on enemy Input Action
	UPROPERTY(EditDefaultsOnly, Category = "TOSET Input")
	class UInputAction* FocusAction;

	// Crouch Input Action
	UPROPERTY(EditDefaultsOnly, Category = "TOSET Input")
	class UInputAction* CrouchAction;

	// Pick up items Input Action
	UPROPERTY(EditDefaultsOnly, Category = "TOSET Input")
	class UInputAction* PickAction;

	// Light Attack Input Action
	UPROPERTY(EditDefaultsOnly, Category = "TOSET Input")
	class UInputAction* LightAttackAction;

	// Is character focusing
	bool IsFocusing = false;

	// Hit result while sphere tracing, the pawn to focus
	class ACharacter* FocusCharacter;

	/********************
	* UI Input Properties
	********************/
	// UI Input Mapping Context
	UPROPERTY(EditDefaultsOnly, Category = "TOSET Input")
	class UInputMappingContext* UIMappingContext;

	// Open up Inventory Widget Input
	UPROPERTY(EditDefaultsOnly, Category = "TOSET Input")
	class UInputAction* InventoryAction;


	/********************
	* Camera Properties
	********************/
	// Spring arm
	UPROPERTY(VisibleDefaultsOnly)
	class USpringArmComponent* SpringArm;

	// Follow Camera
	UPROPERTY(VisibleDefaultsOnly)
	class UCameraComponent* FollowCamera;

	/********************
	* UI Properties
	********************/
	UPROPERTY()
	class APlayerHUD* PlayerHUD;

	bool IsInventoryOpening = false;
	/********************
	* Interact Properties
	********************/
	// Hit result while line tracing, the item can interacte with
	class ABaseItem* InteractableItem;

	/********************
	* Data Properties
	********************/
	// Player ID
	UPROPERTY(EditDefaultsOnly, category = "TOSET Data")
	FName ID;

	// Data table for search
	UPROPERTY(EditDefaultsOnly, Category = "TOSET Data")
	class UDataTable* InventoryDataTable;


	/********************
	* Character State Properties
	********************/
	// Character Equip State
	ECharacterEquipState CharacterEquipState = ECharacterEquipState::Unarmed;

	// Character Action State
	ECharacterActionState CharacterActionState = ECharacterActionState::Unoccupied;

	/********************
	* Character Montage Properties
	********************/
	// Light Attack Montage
	UPROPERTY(EditDefaultsOnly, Category = "TOSET Montage")
	UAnimMontage* LightAttackMontage;

	// Light Attack Montage Sections' names
	UPROPERTY(EditDefaultsOnly, Category = "TOSET Montage")
	TArray<FName> LightAttackMontageSections;

	// Light Attack Montage Current Section's Index
	int32 LightAttackMontageIndex = 0;

	// Timer to refresh index to 0 in certain sections
	struct FTimerHandle LightAttackTimer;


public:
	// Sets default values for this character's properties
	APlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/********************
	* UI Functions
	********************/
	// Refresh inventory, use GC, and then add buttons again
	void RefreshInventory();

	// Open inventory
	void OpenInventory();

	// Close inventory
	void CloseInventory();

	// Items' FNames stored
	UPROPERTY(VisibleInstanceOnly)
	TMap<FName, int32> InventoryItems;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/********************
	* Initialize Functions
	********************/
	// Initialize Character properties
	virtual void InitializeCharacterProperties() override;

private:
	/********************
	* Initialize Functions
	********************/
	// Initialize mapping context
	void InitializeMappingContext();

	// Initialize Camera components
	void InitializeCameraComponents();
	
	// Initialize Widgets
	void InitializeWidgets();
	
	/********************
	* Act Input Functions
	********************/
	// Called for looking input
	void Look(const FInputActionValue& Value);

	// Called for Movement input
	void Move(const FInputActionValue& Value);

	// Called for Jump input
	virtual void Jump() override;

	// Called for Walking input
	void Walk(const FInputActionValue& Value);

	// Called for Walking end
	void WalkEnd();

	// Called for trying to focus or defocus on enemy 
	void TraceToFocusOnEnemy();

	// Focus on enemy
	void FocusOnEnemy();

	// Crouch
	virtual void Crouch(bool bClientSimulation) override;

	// Pick up item
	void PickUp();

	// Light Attack
	void LightAttack();

	// Axe Light Attack
	void AxeLightAttack();

	/********************
	* UI Input Functions
	********************/
	// Open or close inventory
	void OpenOrCloseInventory();

	/********************
	* Interact Functions
	********************/
	// Called for trying to interact with items
	void TraceToInteractItem();

	// Highlight Item you want to interact
	void HighlightItem();

	// Unhighlight Item if you are not concentrate on any items
	void UnhighlightItem();

	/********************
	* Montage Functions
	********************/
	// If is occupied
	bool CheckIfOccupied();

	// Reset light attack index to 0
	void ResetLightAttackIndex();
public:
	// Set Character Equip State
	FORCEINLINE void SetCharacterEquipState(ECharacterEquipState State) { CharacterEquipState = State; }

	// Get Character Equip State
	FORCEINLINE ECharacterEquipState GetCharacterEquipState() const { return CharacterEquipState; }

	// Set Character Action State
	FORCEINLINE void SetCharacterActionState(ECharacterActionState State) { CharacterActionState = State; }

};
