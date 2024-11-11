
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Attribute.h"
#include "AttributesComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EJERCICIOS_API UAttributesComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAttributesComponent();

	// UAttribute

	UFUNCTION(Category="Attributes")
	bool HasUAttribute(const FName& AttName) const;

	UFUNCTION(Category="Attributes")
	void EditUAttribute(const FName& AttName, float Value);

	UFUNCTION(Category="Attributes")
	void AddUAttribute(const FName& AttName, UAttribute* Att);

	UFUNCTION(Category="Attributes")
	UAttribute* GetUAttribute(const FName& AttName);

	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TMap<FName, UAttribute*> UAttributesMap;


public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
