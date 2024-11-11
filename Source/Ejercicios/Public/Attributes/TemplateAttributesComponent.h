// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TemplateAttributesComponent.generated.h"


template <typename T>
class EJERCICIOS_API Attribute
{
public:
	
	Attribute(T InValue = NULL)
	{
		Value = InValue;
	}

	T GetValue() const
	{
		return Value;
	}

	T& GetValue()
	{
		return Value;
	}

	void SetValue(T InValue)
	{
		Value = InValue;
	}

private:
	T Value;

};

USTRUCT(BlueprintType)
struct FAttributesStructure : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Example")
	FName AttName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Example")
	float DefaultValue;
	
	FAttributesStructure()
		: AttName(""), DefaultValue(0)
	{}
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EJERCICIOS_API UTemplateAttributesComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTemplateAttributesComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* DefaultValues = nullptr;

	UFUNCTION(BlueprintCallable)
	void SetAttribute(const FName& AttName, float const Value);
	
	UFUNCTION(BlueprintCallable)
	bool CreateAttribute(const FName& AttName, float const Value);

	UFUNCTION(BlueprintCallable)
	float GetAttributeValue(const FName& AttName) const;

	UFUNCTION(BlueprintCallable)
	bool CheckAttribute(const FName& AttName) const;

protected:
	virtual void BeginPlay() override;
	
	TMap<FName, Attribute<float>> FloatAttributesMap;


public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;
};
