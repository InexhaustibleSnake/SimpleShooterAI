// The project was made by Alexey Guchmazov for test tasks

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "BaseEnemy.generated.h"

class UAIPerceptionComponent;

UCLASS()
class SIMPLESHOOTER_API ABaseEnemy : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ABaseEnemy();

};
