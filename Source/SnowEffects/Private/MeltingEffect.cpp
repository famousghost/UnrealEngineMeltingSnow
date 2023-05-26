// Fill out your copyright notice in the Description page of Project Settings.

#include "MeltingEffect.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Materials/Material.h"
#include <Kismet/KismetRenderingLibrary.h>
#include "Materials/MaterialInstanceDynamic.h"
#include "Landscape.h"
#include "Materials/MaterialInstance.h"
#include "Containers/Array.h"

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
        if (m_landscape)
        {
            SetMPCScalarParam(l_mpci, FName("LandscapeHeight"), m_landscape->GetActorLocation().Z);
        }
    }

    ClearTexture(m_meltingTexture);
    ClearTexture(m_meltingTextureBlur);
    ClearTexture(m_displacementTexture);
    ClearTexture(m_displacementTextureGenerated);

    m_deformingSceneCapture2D->TextureTarget = m_displacementTexture;
    m_meltingSceneCapture2D->TextureTarget = m_meltingTexture;

    CreateMaterialInstances();

    SetMaterialTextureIfMaterialExists(m_meltingMaterialDynamicInstance, FName("_MeltingTextureBlur"), m_meltingTextureBlur);
    SetMaterialTextureIfMaterialExists(m_displacementMaterialDynamicInstance, FName("_DisplacementGeneratedTexture"), m_displacementTextureGenerated);
    SetMaterialTextureIfMaterialExists(m_meltingBlurMaterialDynamicInstance, FName("_MeltingTexture"), m_meltingTexture);
    SetMaterialTextureIfMaterialExists(m_displacementGeneratedMaterialDynamicInstance, FName("_DisplacementTexture"), m_displacementTexture);

    m_meltingSceneCapture2D->PostProcessSettings.WeightedBlendables.Array.Add(FWeightedBlendable(1, m_meltingMaterialDynamicInstance));
    m_deformingSceneCapture2D->PostProcessSettings.WeightedBlendables.Array.Add(FWeightedBlendable(1, m_displacementMaterialDynamicInstance));
}

// Called every frame
void AMeltingEffect::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    DrawMaterialToRenderTarget(m_displacementTextureGenerated, m_displacementGeneratedMaterialDynamicInstance);
    DrawMaterialToRenderTarget(m_meltingTextureBlur, m_meltingBlurMaterialDynamicInstance);
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

void AMeltingEffect::DrawMaterialToRenderTarget(UTextureRenderTarget2D* p_texture, UMaterialInstanceDynamic* p_material)
{
    if (p_texture != nullptr && p_material != nullptr)
    {
        UKismetRenderingLibrary::DrawMaterialToRenderTarget(GetWorld(), p_texture, p_material);
    }
}

void AMeltingEffect::CreateMaterialInstances()
{
    m_meltingMaterialDynamicInstance = UMaterialInstanceDynamic::Create(m_meltingMaterial, this);
    m_displacementMaterialDynamicInstance = UMaterialInstanceDynamic::Create(m_displacementMaterial, this);
    m_meltingBlurMaterialDynamicInstance = UMaterialInstanceDynamic::Create(m_meltingBlurMaterial, this);
    m_displacementGeneratedMaterialDynamicInstance = UMaterialInstanceDynamic::Create(m_displacementGeneratedMaterial, this);
}

void AMeltingEffect::SetMaterialTextureIfMaterialExists(UMaterialInstanceDynamic* p_material, const FName& p_name, UTextureRenderTarget2D* p_texture)
{
    if(p_material)
    {
        p_material->SetTextureParameterValue(p_name, p_texture);
    }
}
