// The project was made by Alexey Guchmazov for test tasks

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UHealthComponent;
class UWeaponComponent;

UCLASS()
class SIMPLESHOOTER_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();

	UFUNCTION(BlueprintCallable, Category = "Aim")
	bool IsAiming() const { return Aiming; }

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnDeath();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetMovementDirection() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UWeaponComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float RunningSpeed = 600.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float WalkingSpeed = 300.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Aim")
	bool Aiming = false;

};
