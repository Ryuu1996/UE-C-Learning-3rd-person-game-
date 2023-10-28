#pragma once



UENUM(BlueprintType)
enum class EItemEquipState : uint8
{
	// Character Unarmed
	Equipped UMETA(DisplayName = "Equipped"),
	// Character axe equipped
	Unequipped UMETA(DisplayName = "Unequipped")
};