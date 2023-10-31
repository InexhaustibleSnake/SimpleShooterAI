// The project was made by Alexey Guchmazov for test tasks

#include "Character/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/Components/WeaponComponent.h"

APlayerCharacter::APlayerCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());

	MainCamera = CreateDefaultSubobject<UCameraComponent>("MainCamera");
	MainCamera->SetupAttachment(SpringArmComponent);

	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->TargetArmLength = 325.0f;
	SpringArmComponent->SocketOffset.Set(0.0f, 50.0f, 0.0f);

	FVector SpringArmComponentLocation;
	SpringArmComponentLocation.Set(0.0f, 0.0f, 80.0f);

	SpringArmComponent->SetWorldLocation(SpringArmComponentLocation);

	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->CameraLagSpeed = 12.5f;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("MouseX", this, &APlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("MouseY", this, &APlayerCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::StopJumping);

	PlayerInputComponent->BindAction("Aiming", IE_Pressed, this, &APlayerCharacter::Aim);
	PlayerInputComponent->BindAction("Aiming", IE_Released, this, &APlayerCharacter::Aim);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::StopJumping);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::Fire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &UWeaponComponent::StopFire);

	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &UWeaponComponent::Reload);
}

void APlayerCharacter::MoveForward(float Amount)
{
	if (!Controller) return;

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	AddMovementInput(ForwardDirection, Amount);
}

void APlayerCharacter::MoveRight(float Amount)
{
	if (!Controller) return;

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(RightDirection, Amount);
}

void APlayerCharacter::Aim()
{
	Aiming = !Aiming;

	bUseControllerRotationYaw = Aiming;

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = Aiming ? WalkingSpeed : RunningSpeed;
	}

	const auto PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController) return;

	PlayerController->PlayerCameraManager->SetFOV(Aiming ? AimFOV : NonAimFOV);
}

void APlayerCharacter::Fire()
{
	if (!Aiming) return;

	WeaponComponent->StartFire();
}
