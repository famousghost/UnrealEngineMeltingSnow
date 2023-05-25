// Fill out your copyright notice in the Description page of Project Settings.

#include "MeltingEffect.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Materials/Material.h"
#include <Kismet/KismetRenderingLibrary.h>
#include <Components/SceneCaptureComponent2D.h>


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
    const float l_correctOrthographicSize = m_fieldSize * 2.0f;
    m_meltingSceneCapture2D->OrthoWidth = l_correctOrthographicSize;
    m_deformingSceneCapture2D->OrthoWidth = l_correctOrthographicSize;

    UMaterialParameterCollectionInstance* l_mpci = GetWorld()->GetParameterCollectionInstance(Cast<UMaterialParameterCollection>(m_collectionParam));
    if (l_mpci)
    {
        SetMPCScalarParam(l_mpci, FName("OrthographicSize"), l_correctOrthographicSize);
        SetMPCVectorParam(l_mpci, FName("Offset"), GetActorLocation());
        SetMPCScalarParam(l_mpci, FName("MaxSnowHeight"), m_maxSnowHeight);
        if(m_landscape)
        {
            SetMPCScalarParam(l_mpci, FName("LandscapeHeight"), m_landscape->GetActorLocation().Z);
        }
    }

    ClearTexture(m_displacementTexture);
    ClearTexture(m_displacementTextureGenerated);
    ClearTexture(m_meltingTexture);
    ClearTexture(m_meltingTextureBlur);
}

// Called every frame
void AMeltingEffect::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    DrawMaterialToRenderTarget(m_displacementTextureGenerated, m_displacementMaterial);
    DrawMaterialToRenderTarget(m_meltingTextureBlur, m_meltingMaterial);
    
}

void AMeltingEffect::SetMPCScalarParam(UMaterialParameterCollectionInstance* p_mpci, const FName& p_name, int p_value, bool p_debug)
{
    if (!p_debug)
    {
        p_mpci->SetScalarParameterValue(p_name, p_value);
        return;
    }
    if (p_mpci->SetScalarParameterValue(p_name, p_value))
    {
        if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString(TEXT("Added: " + p_name.ToString())));
    }
}

void AMeltingEffect::SetMPCVectorParam(UMaterialParameterCollectionInstance* p_mpci, const FName& p_name, const FVector& p_value, bool p_debug)
{
    if (!p_debug)
    {
        p_mpci->SetVectorParameterValue(p_name, p_value);
        return;
    }
    if (p_mpci->SetVectorParameterValue(p_name, p_value))
    {
        if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString(TEXT("Added: " + p_name.ToString())));
    }
}

void AMeltingEffect::ClearTexture(UTextureRenderTarget2D* p_texture)
{
    if (p_texture)
    {
        UKismetRenderingLibrary::ClearRenderTarget2D(GetWorld(), p_texture, FLinearColor::Black);
    }
}

void AMeltingEffect::DrawMaterialToRenderTarget(UTextureRenderTarget2D* p_texture, UMaterial* p_material)
{

    if(p_texture != nullptr && p_material != nullptr)
    {
        UKismetRenderingLibrary::DrawMaterialToRenderTarget(GetWorld(), p_texture, p_material);
    }
}
