// The project was made by Alexey Guchmazov for test tasks

#include "Character/Components/WeaponComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Character.h"
#include "Animations/ReloadFinishedAnimNotify.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentAmmo = DefaultAmmo;

	InitAnimations();
}

void UWeaponComponent::StartFire()
{
	if (!GetWorld()) return;

	GetWorld()->GetTimerManager().SetTimer(ShootTimer, this, &UWeaponComponent::MakeShot, TimeBetweenShots, true);
	MakeShot();
}

void UWeaponComponent::StopFire()
{
	if (!GetWorld()) return;

	GetWorld()->GetTimerManager().ClearTimer(ShootTimer);
}

void UWeaponComponent::MakeShot()
{
	if (ReloadAnimInProgress) return;

	if (IsAmmoEmpty())
	{
		Reload();
		return;
	}

	FVector TraceStart, TraceEnd;

	if (!GetTraceData(TraceStart, TraceEnd)) return;

	FHitResult HitResult;

	MakeTrace(HitResult, TraceStart, TraceEnd);

	SetAmmoBullets(--CurrentAmmo.Bullets);

	if (HitResult.bBlockingHit)
	{
		MakeDamage(HitResult);
	}
}

bool UWeaponComponent::GetTraceData(FVector& TraceStart, FVector& TraceEnd) 
{
	FRotator TraceRotation;
	if (!GetPlayerViewPoint(TraceStart, TraceRotation)) return false;

	FVector ShootDirection = TraceRotation.Vector();

	TraceEnd = TraceStart + ShootDistance * ShootDirection;

	return true;
}

void UWeaponComponent::MakeTrace(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
	if (!GetWorld()) return;

	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 0.5f);

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionQueryParams);
}

void UWeaponComponent::MakeDamage(const FHitResult& HitResult) const
{
	if (!HitResult.GetActor()) return;
	
	HitResult.GetActor()->TakeDamage(Damage, FDamageEvent{}, GetOwnerController(), GetOwner());
}

void UWeaponComponent::SetAmmoBullets(int32 NewAmmoBullets)
{
	CurrentAmmo.Bullets = FMath::Clamp(NewAmmoBullets, 0, DefaultAmmo.Bullets);

	OnAmmoChanged.Broadcast(CurrentAmmo.Bullets);
}

void UWeaponComponent::SetAmmoClips(int32 NewAmmoClips)
{
	if (DefaultAmmo.Infinite)
	{
		CurrentAmmo.Clips = DefaultAmmo.Clips;
		return;
	}

	CurrentAmmo.Clips = FMath::Clamp(NewAmmoClips, 0, DefaultAmmo.Clips);

	OnClipsChanged.Broadcast(CurrentAmmo.Clips);
}

bool UWeaponComponent::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation)
{
	const auto OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (!OwnerCharacter) return false;

	if (OwnerCharacter->IsPlayerControlled())
	{
		const auto OwnerController = GetOwnerController();
		if (!OwnerController) return false;

		OwnerController->GetPlayerViewPoint(ViewLocation, ViewRotation);
	}
	else
	{
		OwnerCharacter->GetController()->GetActorEyesViewPoint(ViewLocation, ViewRotation);
	}

	return true;
}

void UWeaponComponent::Reload()
{
	if (!CanReload()) return;

	ReloadAnimInProgress = true;

	PlayAnimMontage(ReloadMontage);
}

void UWeaponComponent::PlayAnimMontage(UAnimMontage* MontageToPlay, float PlayRate, FName StartSectionName)
{
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (!OwnerCharacter) return;

	OwnerCharacter->PlayAnimMontage(MontageToPlay, PlayRate, StartSectionName);
}

void UWeaponComponent::InitAnimations()
{
	auto ReloadFinishedNotify = FindNotifyByClass<UReloadFinishedAnimNotify>(ReloadMontage);

	if (ReloadFinishedNotify)
	{
		ReloadFinishedNotify->OnNotified.AddUObject(this, &UWeaponComponent::OnReloadFinished);
	}
}

void UWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (!OwnerCharacter || MeshComponent != OwnerCharacter->GetMesh()) return;

	ReloadAnimInProgress = false;

	SetAmmoClips(--CurrentAmmo.Clips);
	SetAmmoBullets(CurrentAmmo.Bullets = DefaultAmmo.Bullets);
}

AController* UWeaponComponent::GetOwnerController() const
{
	if (!GetOwner()) return false;

	const auto OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) return false;

	return OwnerPawn->GetController();
}
