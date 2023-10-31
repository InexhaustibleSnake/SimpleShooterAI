// The project was made by Alexey Guchmazov for test tasks

#include "AI/BaseAIController.h"
#include "Perception/AIPerceptionComponent.h"

ABaseAIController::ABaseAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerceptionComponent");
	SetPerceptionComponent(*AIPerceptionComponent);
}
