// The project was made by Alexey Guchmazov for test tasks

#include "AI/BaseEnemy.h"
#include "AI/BaseAIController.h"
#include "Perception/AIPerceptionComponent.h"

ABaseEnemy::ABaseEnemy()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ABaseAIController::StaticClass();
}
