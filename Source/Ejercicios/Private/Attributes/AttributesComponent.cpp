

#include "Attributes/AttributesComponent.h"


UAttributesComponent::UAttributesComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

bool UAttributesComponent::HasUAttribute(const FName& AttName) const
{
	return UAttributesMap.Find(AttName) != nullptr;
}

void UAttributesComponent::EditUAttribute(const FName& AttName, float const Value)
{
	UAttributesMap.FindRef(AttName)->SetAttValue(Value);
}

void UAttributesComponent::AddUAttribute(const FName& AttName, UAttribute* Att)
{
	if (HasUAttribute(AttName))
	{
		UAttributesMap.Add(AttName, Att);
	}
}

UAttribute* UAttributesComponent::GetUAttribute(const FName& AttName)
{
	return UAttributesMap.FindRef(AttName);
}

void UAttributesComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


void UAttributesComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

