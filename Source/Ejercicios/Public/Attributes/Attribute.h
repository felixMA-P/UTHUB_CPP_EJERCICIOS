
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Attribute.generated.h"

UCLASS()
class EJERCICIOS_API UAttribute : public UObject
{
	GENERATED_BODY()

	float AttValue;

public:
	UAttribute(){};

	UAttribute(const float InValue)
	{
		AttValue = InValue;
	}

	inline float SetAttValue(float const NewValue) { return AttValue = NewValue; }

	inline float GetAttValue() const { return AttValue; }
};
