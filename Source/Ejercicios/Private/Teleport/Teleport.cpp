// Fill out your copyright notice in the Description page of Project Settings.


#include "Ejercicios/Public/Teleport/Teleport.h"
#include "Components/BoxComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"


ATeleport::ATeleport()
{
	PrimaryActorTick.bCanEverTick = true;

	TeleportMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TeleportMesh"));
	RootComponent = TeleportMesh;

	TeleportBoxVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxVolume"));
	TeleportBoxVolume->SetupAttachment(RootComponent);

	TeleportPoint = CreateDefaultSubobject<USceneComponent>(TEXT("TeleportPoint"));
	TeleportPoint->SetupAttachment(RootComponent);
	
	EffectsSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("EffectsSpawnPoint"));
	EffectsSpawnPoint->SetupAttachment(RootComponent);
	
}

void ATeleport::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


FVector ATeleport::GetTeleportLocation() const
{
	return TeleportPoint->GetComponentLocation();
}

void ATeleport::BeginPlay()
{
	Super::BeginPlay();

	//Set the overlaps events in the box volume
	TeleportBoxVolume->OnComponentBeginOverlap.AddDynamic(this,&ATeleport::OverlapBegin);
	TeleportBoxVolume->OnComponentEndOverlap.AddDynamic(this,&ATeleport::OverlapEnd);
	
	
}

void ATeleport::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!DestinationTeleport) return;
	
	//If we just have Been Teleported we dont want to teleport
	if (DestinationTeleport->bTeleportUsed)
	{
		if (TeleportEffect)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, TeleportEffect, EffectsSpawnPoint->GetComponentLocation());
		}
		return;
	}
	//If it isnt in the list of actors, it cant teleport
	if (OtherActor->StaticClass() == EnabledClass) return;
	
	Teleport(OtherActor);
	
}

void ATeleport::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//if it isnt the desired class we dont want to do nothing
	if (OtherActor->StaticClass() == EnabledClass) return;
	
	if (DestinationTeleport->bTeleportUsed)
	{
		DestinationTeleport->bTeleportUsed = false;
	}
}

#if WITH_EDITOR
void ATeleport::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName& PropertyName = PropertyChangedEvent.GetPropertyName();

	if (PropertyName.IsEqual(GET_MEMBER_NAME_CHECKED(ATeleport, DestinationTeleport)))
	{
		DestinationTeleport->DestinationTeleport = this;
	}
	
}
#endif

void ATeleport::Teleport(AActor* ActorToTeleport)
{
	//Spawn de emmiter effect if exist
	if (TeleportEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			this,
			TeleportEffect,
			EffectsSpawnPoint->GetComponentLocation(), FRotator::ZeroRotator, FVector(1), true);
	}

	//Play sound if its set
	if (Sound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, Sound, EffectsSpawnPoint->GetComponentLocation(), FRotator::ZeroRotator, 0.3);
	}
	
	bTeleportUsed = true;
	ActorToTeleport->SetActorLocation(DestinationTeleport->TeleportPoint->GetComponentLocation());
}
