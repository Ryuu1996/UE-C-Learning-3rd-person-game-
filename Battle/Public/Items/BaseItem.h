// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/ItemInterface.h"

#include "BaseItem.generated.h"


UCLASS()
class BATTLE_API ABaseItem : public AActor, public IItemInterface
{
	GENERATED_BODY()
private:
	// The root component, capsule component
	UPROPERTY(EditDefaultsOnly)
	class UCapsuleComponent* CapsuleComponent;

	// Item Mesh
	UPROPERTY(EditDefaultsOnly, category = "TOSET Mesh")
	class UStaticMeshComponent* ItemMesh;

	//Highlight Mesh, used for highlighting
	UPROPERTY(EditDefaultsOnly, category = "TOSET Mesh")
	class UStaticMeshComponent* HighlightMesh;

	// ID of item, should be the same as Data Table Raw Name
	UPROPERTY(EditDefaultsOnly, category = "TOSET General")
	FName ID;

public:
	// Sets default values for this actor's properties
	ABaseItem();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Initialize mesh components
	void InitializeMesh();

public:
	class UStaticMeshComponent* GetHighlightMesh() const;
	FORCEINLINE FName GetID() const { return ID; }
	FORCEINLINE UStaticMeshComponent* GetStaticMeshComponent() const { return ItemMesh;	}
};
