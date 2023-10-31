// The project was made by Alexey Guchmazov for test tasks

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAIController.generated.h"

class UAIPerceptionComponent;

UCLASS()
class SIMPLESHOOTER_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

public:
	ABaseAIController();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UAIPerceptionComponent* AIPerceptionComponent;

};
