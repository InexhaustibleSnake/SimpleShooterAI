// The project was made by Alexey Guchmazov for test tasks

#include "Animations/BaseAnimNotify.h"

void UBaseAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	OnNotified.Broadcast(MeshComp);

	Super::Notify(MeshComp, Animation, EventReference);
}
