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

	// Focus on enemy Input Action
	UPROPERTY(EditDefaultsOnly, Category = "TOSET Input")
	class UInputAction* CrouchAction;

	// Focus on enemy Input Action
	UPROPERTY(EditDefaultsOnly, Category = "TOSET Input")
	class UInputAction* PickAction;

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
	// Data table for search
	UPROPERTY(EditDefaultsOnly, Category = "TOSET General")
	class UDataTable* DataTable;

	/********************
	* Character State Properties
	********************/
	// Character Equip State
	ECharacterEquipState CharacterEquipState = ECharacterEquipState::Unarmed;
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

	// Called for Walking input
	void Walk(const FInputActionValue& Value);

	// Called for Walking end
	void WalkEnd();

	// Called for trying to focus or defocus on enemy 
	void TraceToFocusOnEnemy();

	// Focus on enemy
	void FocusOnEnemy();

	// Crouch
	void Crouch();

	// Pick up item
	void PickUp();

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

public:
	// Set Character Equip State
	FORCEINLINE void SetCharacterEquipState(ECharacterEquipState State) { CharacterEquipState = State; }
	FORCEINLINE ECharacterEquipState GetCharacterEquipState() const { return CharacterEquipState; }


};
