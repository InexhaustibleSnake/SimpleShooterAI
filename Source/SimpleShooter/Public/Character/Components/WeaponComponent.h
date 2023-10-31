// The project was made by Alexey Guchmazov for test tasks

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAmmoChanged, int32, NewAmmo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClipsChanged, int32, NewClips);

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 Bullets = 30;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (EditCondition = "!Infinite"))
	int32 Clips = 3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	bool Infinite = true;
};

class AController;
class UAnimNotify;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIMPLESHOOTER_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponent();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void StartFire();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void StopFire();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Reload();

	UFUNCTION(BlueprintCallable, Category = "Ammo")
	bool IsAmmoEmpty() const { return CurrentAmmo.Bullets == 0; }

	UFUNCTION(BlueprintCallable, Category = "Ammo")
	bool IsAmmoFull() const { return CurrentAmmo.Bullets == DefaultAmmo.Bullets; }

	UFUNCTION(BlueprintCallable, Category = "Ammo")
	bool IsAmmoClipsEmpty() const { return CurrentAmmo.Clips == 0; }

	UFUNCTION(BlueprintCallable, Category = "Ammo")
	FAmmoData GetCurrentAmmoData() const { return CurrentAmmo; }

	UFUNCTION(BlueprintCallable, Category = "Ammo")
	FAmmoData GetDefaultAmmoData() const { return DefaultAmmo; }

	UFUNCTION(BlueprintCallable, Category = "Ammo")
	bool CanReload() const { return !ReloadAnimInProgress && !IsAmmoFull() && !IsAmmoClipsEmpty(); }

	UPROPERTY(BlueprintAssignable, Category = "Ammo")
	FOnAmmoChanged OnAmmoChanged;

	UPROPERTY(BlueprintAssignable, Category = "Ammo")
	FOnClipsChanged OnClipsChanged;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void MakeShot();

	bool GetTraceData(FVector& TraceStart, FVector& TraceEnd);

	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation);

	void MakeTrace(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);

	void MakeDamage(const FHitResult& HitResult) const;

	void SetAmmoBullets(int32 NewAmmoBullets);

	void SetAmmoClips(int32 NewAmmoBullets);

	void OnReloadFinished(USkeletalMeshComponent* MeshComponent);

	void InitAnimations();

	void PlayAnimMontage(UAnimMontage* MontageToPlay, float PlayRate = 1.0f, FName StartSectionName = NAME_None);

	FTransform GetMuzzleWorldTransform() const;

	AController* GetOwnerController() const;

	template<typename T>
	T* FindNotifyByClass(UAnimSequenceBase* Animation);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float ShootDistance = 30000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float Damage = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float TimeBetweenShots = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	bool ReloadAnimInProgress = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FName MuzzleSocketName = "Muzzle";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
	FAmmoData DefaultAmmo;

	UPROPERTY(BlueprintReadOnly, Category = "Ammo")
	FAmmoData CurrentAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* ReloadMontage;

private:
	FTimerHandle ShootTimer;

};

template<typename T>
inline T* UWeaponComponent::FindNotifyByClass(UAnimSequenceBase* Animation)
{
	if (!Animation) return nullptr;

	const auto NotifyEvents = Animation->Notifies;

	for (auto NotifyEvent : NotifyEvents)
	{
		auto AnimNotify = Cast<T>(NotifyEvent.Notify);
		if (AnimNotify)
		{
			return AnimNotify;
		}
	}
	return nullptr;
}
