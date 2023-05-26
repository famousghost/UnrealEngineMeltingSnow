// Fill out your copyright notice in the Description page of Project Settings.

#include "RVTSnowyTerrain.h"
#include "Components/RuntimeVirtualTextureComponent.h"
#include "Math/BoxSphereBounds.h"

// Sets default values
ARVTSnowyTerrain::ARVTSnowyTerrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_runtimeVirtualTexture = CreateDefaultSubobject<URuntimeVirtualTextureComponent>(TEXT("VirtualTextureComponent"));
	RootComponent = m_runtimeVirtualTexture;;
}

// Called when the game starts or when spawned
void ARVTSnowyTerrain::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARVTSnowyTerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(m_runtimeVirtualTexture)
	{
		m_runtimeVirtualTexture->Invalidate(FBoxSphereBounds(FVector::ZeroVector, FVector::ZeroVector, 99999.0f));
	}

}

