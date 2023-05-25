// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnObjects.h"

// Sets default values
ASpawnObjects::ASpawnObjects()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    m_spawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));

    RootComponent = m_spawnArea;
}

// Called when the game starts or when spawned
void ASpawnObjects::BeginPlay()
{
    Super::BeginPlay();

    for (int i = 0; i < m_amountOfObjects; ++i)
    {
        int index = FMath::FRandRange(0, m_actorsToSpawn.Num());

        if (!SpawnActor(index))
        {
            break;
        }
    }
}

void ASpawnObjects::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
    GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

// Called every frame
void ASpawnObjects::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

bool ASpawnObjects::SpawnActor(int index)
{
    if (m_actorsToSpawn.Num() != 0)
    {
        // Calculate the extents of the box
        if (m_spawnArea)
        {
            FBoxSphereBounds l_boxBounds = m_spawnArea->CalcBounds(GetActorTransform());

            FVector l_spawnLocation = l_boxBounds.Origin;
            l_spawnLocation.X += -l_boxBounds.BoxExtent.X + 2 * l_boxBounds.BoxExtent.X * FMath::FRand();
            l_spawnLocation.Y += -l_boxBounds.BoxExtent.Y + 2 * l_boxBounds.BoxExtent.Y * FMath::FRand();
            l_spawnLocation.Z += -l_boxBounds.BoxExtent.Z + 2 * l_boxBounds.BoxExtent.Z * FMath::FRand();

            GetWorld()->SpawnActor(m_actorsToSpawn[index], &l_spawnLocation);
            return true;
        }
    }
    return false;
}