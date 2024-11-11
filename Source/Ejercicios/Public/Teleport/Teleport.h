// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Teleport.generated.h"


class UStaticMeshComponent;
class UBoxComponent;
class UNiagaraSystem;


UCLASS()
class EJERCICIOS_API ATeleport : public AActor
{
	GENERATED_BODY()

public:
	ATeleport();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditInstanceOnly, Category = "Teleport")
	ATeleport* DestinationTeleport;

	//Flag to avoid a looping teleport
	bool bTeleportUsed = false;

	FVector GetTeleportLocation() const;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	USceneComponent* TeleportPoint;

	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	USceneComponent* EffectsSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleport")
	USoundBase* Sound;
	
	UPROPERTY(EditAnywhere, Category = "Teleport")
	UStaticMeshComponent* TeleportMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	UBoxComponent* TeleportBoxVolume;

	UPROPERTY(EditAnywhere, Category = "Teleport")
	TSubclassOf<AActor> EnabledClass;

	UPROPERTY(EditAnywhere, Category = "Teleport")
	UNiagaraSystem* TeleportEffect;
	
#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
	void Teleport(AActor* ActorToTeleport);
	
};
