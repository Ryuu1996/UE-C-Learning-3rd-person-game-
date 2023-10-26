#pragma once




UENUM(BlueprintType)
enum class ECharacterEquipState : uint8
{
	// Character Unarmed
	Unarmed UMETA(DisplayName = "Unarmed"),
	// Character axe equipped
	AxeEquipped UMETA(DisplayName = "AxeEquipped")
};

UENUM(BlueprintType)
enum class ECharacterActionState : uint8
{
	// Currently no action
	Unoccupied UMETA(DisplayName = "Unoccupied"),
	// Currently doing action
	Occupied UMETA(DisplayName = "Occupied")
};