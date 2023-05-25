// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "MeltingEffect.generated.h"

class USceneCaptureComponent2D;
class UMaterialParameterCollection;
class FName;
class UMaterialParameterCollectionInstance;
class UTextureRenderTarget2D;
class UMaterial;

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

    UPROPERTY(EditAnywhere)
        UMaterialParameterCollection* m_collectionParam;

public:
    UFUNCTION()
        void SetMPCScalarParam(UMaterialParameterCollectionInstance* p_mpci, const FName& p_name, int p_value, bool p_debug = false);
    UFUNCTION()
        void SetMPCVectorParam(UMaterialParameterCollectionInstance* p_mpci, const FName& p_name, const FVector& p_value, bool p_debug = false);

    UFUNCTION()
        void ClearTexture(UTextureRenderTarget2D* p_texture);

    UFUNCTION()
        void DrawMaterialToRenderTarget(UTextureRenderTarget2D* p_texture, UMaterial* p_material);

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        float m_fieldSize;
private:


    UPROPERTY(EditAnywhere)
        float m_maxSnowHeight;

    UPROPERTY(EditAnywhere)
        AActor* m_landscape;

    UPROPERTY(EditAnywhere)
        UTextureRenderTarget2D* m_displacementTexture;

    UPROPERTY(EditAnywhere)
        UTextureRenderTarget2D* m_displacementTextureGenerated;

    UPROPERTY(EditAnywhere)
        UTextureRenderTarget2D* m_meltingTexture;

    UPROPERTY(EditAnywhere)
        UTextureRenderTarget2D* m_meltingTextureBlur;

    UPROPERTY(EditAnywhere)
        UMaterial* m_displacementMaterial;

    UPROPERTY(EditAnywhere)
        UMaterial* m_meltingMaterial;
};
