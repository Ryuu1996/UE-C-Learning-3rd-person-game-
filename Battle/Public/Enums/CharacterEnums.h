#pragma once




UENUM(BlueprintType)
enum class ECharacterEquipState : uint8
{
	// Character Unarmed
	Unarmed UMETA(DisplayName = "Unarmed"),
	// Character axe equipped
	AxeEquipped UMETA(DisplayName = "AxeEquipped")
};

