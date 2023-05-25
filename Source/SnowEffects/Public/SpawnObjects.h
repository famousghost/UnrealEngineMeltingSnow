// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "SpawnObjects.generated.h"

class UBoxComponent;

UCLASS()
class SNOWEFFECTS_API ASpawnObjects : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ASpawnObjects();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    UFUNCTION(BlueprintCallable)
        bool SpawnActor(int index);

private:
    UPROPERTY(EditDefaultsOnly)
        UBoxComponent* m_spawnArea;

    UPROPERTY(EditAnywhere)
        TArray<TSubclassOf<AActor>> m_actorsToSpawn;

    UPROPERTY(EditAnywhere)
        int m_amountOfObjects;
};
