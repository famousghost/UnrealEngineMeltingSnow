// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/SceneCaptureComponent2D.h>
#include "MeltingEffect.generated.h"

UCLASS()
class SNOWEFFECTS_API AMeltingEffect : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AMeltingEffect();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

public:
    UPROPERTY(EditDefaultsOnly)
        USceneCaptureComponent2D* m_meltingSceneCapture2D;
    UPROPERTY(EditDefaultsOnly)
        USceneCaptureComponent2D* m_deformingSceneCapture2D;

private:
    UPROPERTY(EditAnywhere)
        float m_fieldSize;

    UPROPERTY(EditAnywhere)
        float m_maxSnowSize;
};
