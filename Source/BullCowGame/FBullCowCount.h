#pragma once

#include "FBullCowCount.generated.h"

USTRUCT(BlueprintType)
struct FBullCowCount
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int32 Bulls = 0;

	UPROPERTY(EditAnywhere)
	int32 Cows = 0;
};
