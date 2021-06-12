// Fill out your copyright notice in the Description page of Project Settings.
/*
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PortalActor.generated.h"

UCLASS()
class MYRPG_API APortalActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
    APortalActor::APortalActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


    //Status of the Portal (being visualized by the player or not)
    UFUNCTION(BlueprintPure, Category = "MYRPG|Portal")
        bool IsActive();

    UFUNCTION(BlueprintCallable, Category = "MYRPG|Portal")
        void SetActive(bool NewActive);

    //Render target to use to display the portal
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MYRPG|Portal")
        void ClearRTT();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MYRPG|Portal")
        void SetRTT(UTexture* RenderTexture);

    UFUNCTION(BlueprintNativeEvent, Category = "MYRPG|Portal")
        void ForceTick();

    //Target of where the portal is looking
    UFUNCTION(BlueprintPure, Category = "MYRPG|Portal")
        AActor* GetTarget();

    UFUNCTION(BlueprintCallable, Category = "MYRPG|Portal")
        void SetTarget(AActor* NewTarget);

    //Helpers
    UFUNCTION(BlueprintCallable, Category = "MYRPG|Portal")
        bool IsPointInFrontOfPortal(FVector Point, FVector PortalLocation, FVector PortalNormal);

    UFUNCTION(BlueprintCallable, Category = "MYRPG|Portal")
        bool IsPointCrossingPortal(FVector Point, FVector PortalLocation, FVector PortalNormal);

    UFUNCTION(BlueprintCallable, Category = "MYRPG|Portal")
        void TeleportActor(AActor* ActorToTeleport);


protected:
    UPROPERTY(BlueprintReadOnly)
        USceneComponent* PortalRootComponent;

private:
    bool bIsActive;

    AActor* Target;

    //Used for Tracking movement of a point
    FVector LastPosition;
    bool    LastInFront;
};

FVector ConvertLocationToActorSpace(FVector Location, AActor* Reference, AActor* Target);
FRotator ConvertRotationToActorSpace(FRotator Rotation, AActor* Reference, AActor* Target);
*/