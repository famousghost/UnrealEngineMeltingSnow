// Fill out your copyright notice in the Description page of Project Settings.

#include "MeltingEffect.h"

// Sets default values
AMeltingEffect::AMeltingEffect()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    m_meltingSceneCapture2D = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("MeltingSceneCapture"));
    m_deformingSceneCapture2D = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("DeformingSceneCapture"));
    RootComponent = CreateDefaultSubobject<USceneComponent>("DefaultSceneRoot");
    m_meltingSceneCapture2D->SetupAttachment(RootComponent);
    m_deformingSceneCapture2D->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMeltingEffect::BeginPlay()
{
    Super::BeginPlay();
    m_meltingSceneCapture2D->OrthoWidth = m_fieldSize;
    m_deformingSceneCapture2D->OrthoWidth = m_fieldSize;
}

// Called every frame
void AMeltingEffect::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}