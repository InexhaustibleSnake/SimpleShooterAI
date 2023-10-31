// The project was made by Alexey Guchmazov for test tasks

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class SIMPLESHOOTER_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	APlayerCharacter();

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Amount);
	void MoveRight(float Amount);

	void Aim();

	void Fire();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UCameraComponent* MainCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aim")
	float AimFOV = 35.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aim")
	float NonAimFOV = 90.0f;
};
