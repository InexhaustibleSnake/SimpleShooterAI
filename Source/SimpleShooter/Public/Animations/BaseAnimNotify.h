// The project was made by Alexey Guchmazov for test tasks

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "BaseAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotified, USkeletalMeshComponent*);

UCLASS()
class SIMPLESHOOTER_API UBaseAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	FOnNotified OnNotified;
};
