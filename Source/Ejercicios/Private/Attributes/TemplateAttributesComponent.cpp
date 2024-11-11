
#include "Attributes/TemplateAttributesComponent.h"


UTemplateAttributesComponent::UTemplateAttributesComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UTemplateAttributesComponent::SetAttribute(const FName& AttName, float const Value)
{
	if (CheckAttribute(AttName))
	{
		FloatAttributesMap.Find(AttName)->SetValue(Value);
	}
}

bool UTemplateAttributesComponent::CreateAttribute(const FName& AttName, float const Value)
{
	if (CheckAttribute(AttName)) return false;
	
	FloatAttributesMap.Add(AttName, Value);
	return true;
}

float UTemplateAttributesComponent::GetAttributeValue(const FName& AttName) const
{
	if (CheckAttribute(AttName))
	{
		return FloatAttributesMap.Find(AttName)->GetValue();
	}

	return 0.0f;
}

bool UTemplateAttributesComponent::CheckAttribute(const FName& AttName) const
{
	return FloatAttributesMap.Find(AttName) != nullptr;
}

void UTemplateAttributesComponent::BeginPlay()
{
	Super::BeginPlay();

	TArray<FAttributesStructure*> Attributes;
	DefaultValues->GetAllRows<FAttributesStructure>("FAttributesStructure", Attributes);

	for (FAttributesStructure* Attribute : Attributes)
	{
		CreateAttribute(Attribute->AttName, Attribute->DefaultValue);
	}
	
}

void UTemplateAttributesComponent::TickComponent(float DeltaTime, ELevelTick TickType,
												 FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


