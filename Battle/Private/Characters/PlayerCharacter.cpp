// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUDWidget.h"
#include "Components/ProgressBar.h"
#include "UI/PlayerHUD.h"
#include "AnimInstance/PlayerLocomotionAnimInstance.h"
#include "Items/BaseItem.h"
#include "UI/Inventory/InventoryWidget.h"
#include "Data/InventoryRowBase.h"
#include "GameFramework/PlayerController.h"
#include "Engine/EngineTypes.h"
#include "Components/CapsuleComponent.h"
#include "Macros/GeneralMacros.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"


APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	InitializeCameraComponents();
	InitializeCharacterProperties();
	InitializeStimulusSource();
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Trace interactable item
	TraceToInteractItem();

	// Focus on enemy
	if(GetFocusCharacter() != nullptr &&
		GetFocusCharacter()->GetCurrentHP() > 0) 
		FocusOnEnemy();
	
	// Highlight the item to interact
	if (InteractableItem &&
		InteractableItem->GetItemEquipState() == EItemEquipState::Unequipped) 
		HighlightItem();

}

void APlayerCharacter::GetHit_Implementation(const FVector& ImpactPoint)
{
	Super::GetHit_Implementation(ImpactPoint);
	// Access Widgets
	UHUDWidget* HUDWidget = PlayerHUD->GetHUDWidget();
	// Set Widgets in HUD
	HUDWidget->SetProgressBarHPPercent(float(GetCurrentHP()) / float(GetHP()));
	HUDWidget->SetTextBlockHP(GetCurrentHP(), GetHP());

}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	LocomotionAnimInstance = Cast<UPlayerLocomotionAnimInstance>(GetMesh()->GetAnimInstance());
	PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController == nullptr) return;
	InitializeMappingContext();
	InitializeWidgets();
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent == nullptr) return;

	// Looking
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

	// Moving
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

	// Jumping
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

	// Walking
	EnhancedInputComponent->BindAction(WalkAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Walk);
	EnhancedInputComponent->BindAction(WalkAction, ETriggerEvent::Completed, this, &APlayerCharacter::WalkEnd);

	// Focus on enemy
	EnhancedInputComponent->BindAction(FocusAction, ETriggerEvent::Triggered, this, &APlayerCharacter::TraceToFocusOnEnemy);

	// Crouch
	EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Crouch, false);

	// Pick up items
	EnhancedInputComponent->BindAction(PickAction, ETriggerEvent::Triggered, this, &APlayerCharacter::PickUp);

	// Light Attack
	EnhancedInputComponent->BindAction(LightAttackAction, ETriggerEvent::Triggered, this, &APlayerCharacter::LightAttack);

	// Dodge 
	EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Dodge);


	// Open up Inventory Widget
	EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Triggered, this, &APlayerCharacter::OpenOrCloseInventory);

}

void APlayerCharacter::InitializeCharacterProperties()
{
	GetCapsuleComponent()->SetCollisionProfileName(ALLY_PROFILENAME);
	// Don't rotate when the controller rotates. Let that just affect the camera
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void APlayerCharacter::InitializeMappingContext()
{
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (Subsystem == nullptr) return;
	Subsystem->AddMappingContext(ActMappingContext, 1);
	Subsystem->AddMappingContext(UIMappingContext, 0);
}

void APlayerCharacter::InitializeCameraComponents()
{
	// Create a spring arm (pulls in towards the player if there is a collision)
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 250.f; // The camera follows at this distance behind the character
	SpringArm->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	SpringArm->AddRelativeLocation(FVector(0.f, 0.f, 95.f));
	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
	FollowCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

void APlayerCharacter::InitializeWidgets()
{
	PlayerHUD = Cast<APlayerHUD>(PlayerController->GetHUD());
	if (PlayerHUD == nullptr) return;

	// Access Widgets
	UHUDWidget* HUDWidget = PlayerHUD->GetHUDWidget();
	UInventoryWidget* InventoryWidget = PlayerHUD->GetInventoryWidget();
	if (HUDWidget == nullptr) return;
	// Inilialize Widgets in HUD
	HUDWidget->SetProgressBarHPPercent(1.f);
	HUDWidget->SetProgressBarSTAPercent(1.f);
	HUDWidget->SetTextBlockHP(GetCurrentHP(), GetHP());
}

void APlayerCharacter::InitializeStimulusSource()
{
	StimulusSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
	if (StimulusSource == nullptr) return;
	StimulusSource->RegisterForSense(TSubclassOf<UAISense_Sight>()); //UAISense_Sight::StaticClass()
	StimulusSource->RegisterWithPerceptionSystem();
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	if (Controller == nullptr) return;
	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(-LookAxisVector.Y);
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	// Check if character is occupied
	if (CheckIfOccupied()) return;
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller == nullptr) return;
	// find out which way is forward
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	// get right vector
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// add movement
	AddMovementInput(ForwardDirection, MovementVector.X);
	AddMovementInput(RightDirection, MovementVector.Y);
}

void APlayerCharacter::Jump()
{
	if (CheckIfOccupied()) return;
	Super::Jump();
}

void APlayerCharacter::Walk(const FInputActionValue& Value)
{
	if (CheckIfOccupied()) return;
	if (LocomotionAnimInstance == nullptr) return;
	if (LocomotionAnimInstance->GetIsCrouching() == false)
	{
		GetCharacterMovement()->MaxWalkSpeed = 350.f;
	}
}

void APlayerCharacter::WalkEnd()
{
	if (LocomotionAnimInstance == nullptr) return;
	CheckIfOccupied();
	if (LocomotionAnimInstance->GetIsCrouching() == false)
	{
		GetCharacterMovement()->MaxWalkSpeed = 700.f;
	}
}

void APlayerCharacter::TraceToFocusOnEnemy()
{
	const FVector StartLocation = FollowCamera->K2_GetComponentLocation();
	const FVector EndLocation = FollowCamera->GetForwardVector().GetSafeNormal2D() * 4000 + StartLocation;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypeQuery;
	ObjectTypeQuery.Add(ObjectTypeQuery7);
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	FHitResult HitResult;
	switch (IsFocusing)
	{
	case true:
		IsFocusing = false;
		SetFocusCharacter(nullptr);
		break;
	case false:
		UKismetSystemLibrary::SphereTraceSingleForObjects(
			this,
			StartLocation,
			EndLocation,
			500.f,
			ObjectTypeQuery,
			false,
			ActorsToIgnore,
			EDrawDebugTrace::None,
			HitResult,
			true
		);
		SetFocusCharacter(Cast<ABaseCharacter>(HitResult.GetActor()));
		if(GetFocusCharacter()) IsFocusing = true;
		break;
	}
}

void APlayerCharacter::Crouch(bool bClientSimulation = false)
{
	if (CheckIfOccupied()) return;
	if (LocomotionAnimInstance == nullptr) return;
	switch (LocomotionAnimInstance->GetIsCrouching())
	{
	case true:
		LocomotionAnimInstance->SetIsCrouching(false);
		GetCharacterMovement()->MaxWalkSpeed = 700.f;
		break;
	case false:
		LocomotionAnimInstance->SetIsCrouching(true);
		GetCharacterMovement()->MaxWalkSpeed = 200.f;
		break;
	}
}

void APlayerCharacter::PickUp()
{
	if (InteractableItem == nullptr) return;
	if (InteractableItem->GetItemEquipState() == EItemEquipState::Equipped) return;
	FName ItemID = InteractableItem->GetID();
	if (InventoryItems.Contains(ItemID))
	{
		InventoryItems[ItemID]++;
	}
	else
	{
		InventoryItems.Add(ItemID, 1);
	}
	if (IsInventoryOpening)
	{
		CloseInventory();
		OpenInventory();
	}
	InteractableItem->K2_DestroyActor();
}

void APlayerCharacter::LightAttack()
{
	if (CheckIfOccupied()) return;
	switch(CharacterEquipState)
	{
	case ECharacterEquipState::Unarmed:
		return;
	case ECharacterEquipState::AxeEquipped:
		AxeLightAttack();
		break;
	}
}

void APlayerCharacter::AxeLightAttack()
{
	if (LocomotionAnimInstance == nullptr) return;
	if (GetLightAttackMontage() == nullptr) return;
	if (GetLightAttackMontageSections().Num() <= 0) return;
	// Reset timer in several seconds if player not attack again
	GetWorld()->GetTimerManager().SetTimer(GetLightAttackTimer(), this, &APlayerCharacter::ResetLightAttackIndex, 1.f, false, 1.5f);
	LocomotionAnimInstance->Montage_Play(GetLightAttackMontage(), 1.4f);
	int32 CurrentIndex = GetLightAttackMontageIndex() % GetLightAttackMontageSections().Num();
	LocomotionAnimInstance->Montage_JumpToSection(GetLightAttackMontageSections()[CurrentIndex]);
	SetLightAttackMontageIndex(GetLightAttackMontageIndex() + 1);
}

void APlayerCharacter::Dodge()
{
	if (CheckIfOccupied()) return;
	if (LocomotionAnimInstance->GetIsFalling()) return;

	if (LocomotionAnimInstance == nullptr) return;
	if (GetLightAttackMontage() == nullptr) return;
	if (GetLightAttackMontageSections().Num() <= 0) return;

	FName Section;
	float Speed = LocomotionAnimInstance->GetCharacterSpeed();
	float Direction = LocomotionAnimInstance->GetCharacterDirection();

	// Jump Back
	if (Speed == 0.f)
		Section = GetDodgeMontageSections()[4];
	// Roll Forward
	else if (Direction <= 45 && Direction >= -45)
		Section = GetDodgeMontageSections()[0];
	// Roll Back
	else if (Direction <= -135 || Direction >= 135)
		Section = GetDodgeMontageSections()[1];
	// Roll Left
	else if (Direction <= -45 && Direction >= -135)
		Section = GetDodgeMontageSections()[2];
	// Roll Right
	else if (Direction <= 135 && Direction >= 45)
		Section = GetDodgeMontageSections()[3];


	LocomotionAnimInstance->Montage_Play(GetDodgeMontage(), 1.3f);
	LocomotionAnimInstance->Montage_JumpToSection(Section);
}

void APlayerCharacter::OpenOrCloseInventory()
{
	switch (IsInventoryOpening)
	{
	case true:
		CloseInventory();
		break;
	case false:
		OpenInventory();
		break;
	}
}

void APlayerCharacter::OpenInventory()
{
	FInputModeGameAndUI InputModeGameAndUI;
	IsInventoryOpening = true;
	RefreshInventory();
	PlayerController->bShowMouseCursor = true;
	PlayerController->SetInputMode(InputModeGameAndUI);
	PlayerHUD->GetInventoryWidget()->AddToViewport();
}

void APlayerCharacter::CloseInventory()
{
	FInputModeGameOnly inputModeGameOnly;
	IsInventoryOpening = false;
	PlayerController->bShowMouseCursor = false;
	PlayerController->SetInputMode(inputModeGameOnly);
	PlayerHUD->GetInventoryWidget()->RemoveFromParent();
}

void APlayerCharacter::TraceToInteractItem()
{
	const FVector StartLocation = FollowCamera->K2_GetComponentLocation();
	const FVector EndLocation = FollowCamera->GetForwardVector() * 500 + StartLocation;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypeQuery;
	ObjectTypeQuery.Add(ObjectTypeQuery8);
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	FHitResult HitResult;
	UKismetSystemLibrary::SphereTraceSingleForObjects(
		this,
		StartLocation,
		EndLocation,
		10.f,
		ObjectTypeQuery,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::None,
		HitResult,
		true
	);
	// Reset highlight mesh
	if (HitResult.GetActor() == nullptr)
	{
		UnhighlightItem();
	}
	// Set interactable item
	InteractableItem = Cast<ABaseItem>(HitResult.GetActor());
}

void APlayerCharacter::HighlightItem()
{
	if (InteractableItem->GetHighlightMesh())
	{
		InteractableItem->GetHighlightMesh()->SetVisibility(true);
	}
}

void APlayerCharacter::UnhighlightItem()
{
	if (InteractableItem == nullptr) return;
	if (InteractableItem->GetHighlightMesh())
	{
		InteractableItem->GetHighlightMesh()->SetVisibility(false);
	}
}

bool APlayerCharacter::CheckIfOccupied()
{
	if (GetCharacterActionState() != ECharacterActionState::Occupied)
	{
		LocomotionAnimInstance->StopAllMontages(0.1);
		return false;
	}
	else return true;
}

void APlayerCharacter::ResetLightAttackIndex()
{
	SetLightAttackMontageIndex(0);
}

void APlayerCharacter::RefreshInventory()
{
	PlayerHUD->RefreshInventory();
	for (auto& Item : InventoryItems)
	{
		FInventoryRowBase* InventoryRow = InventoryDataTable->FindRow<FInventoryRowBase>(Item.Key, FString(""));
		PlayerHUD->AddButtonToInventory(InventoryRow, Item.Value);
	}
}

