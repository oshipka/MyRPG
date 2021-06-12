// Fill out your copyright notice in the Description page of Project Settings.

/*
#include "PortalActor.h"
#include "MyPlayerCharacter.h"
#include "MyPlayerController.h"

// Sets default values
APortalActor::APortalActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    bIsActive = false;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    RootComponent->Mobility = EComponentMobility::Static;

    PortalRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("PortalRootComponent"));
    PortalRootComponent->SetupAttachment(GetRootComponent());
    PortalRootComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    PortalRootComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
    PortalRootComponent->Mobility = EComponentMobility::Movable;

}

// Called when the game starts or when spawned
void APortalActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APortalActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool APortalActor::IsActive()
{
    return bIsActive;
}

void APortalActor::SetActive(bool NewActive)
{
    bIsActive = NewActive;
}

void APortalActor::ClearRTT_Implementation()
{

}

void APortalActor::SetRTT_Implementation(UTexture* RenderTexture)
{

}

void APortalActor::ForceTick_Implementation()
{

}

AActor* APortalActor::GetTarget()
{
    return Target;
}

void APortalActor::SetTarget(AActor* NewTarget)
{
    Target = NewTarget;
}

bool APortalActor::IsPointInFrontOfPortal(FVector Point, FVector PortalLocation, FVector PortalNormal)
{
    FPlane PortalPlane = FPlane(PortalLocation, PortalNormal);
    float PortalDot = PortalPlane.PlaneDot(Point);

    //If < 0 means we are behind the Plane
    //See : http://api.unrealengine.com/INT/API/Runtime/Core/Math/FPlane/PlaneDot/index.html
    return (PortalDot >= 0);
}

bool APortalActor::IsPointCrossingPortal(FVector Point, FVector PortalLocation, FVector PortalNormal)
{
    FVector IntersectionPoint;
    FPlane PortalPlane = FPlane(PortalLocation, PortalNormal);
    float PortalDot = PortalPlane.PlaneDot(Point);
    bool IsCrossing = false;
    bool IsInFront = PortalDot >= 0;

    bool IsIntersect = FMath::SegmentPlaneIntersection(LastPosition,
        Point,
        PortalPlane,
        IntersectionPoint);

    // Did we intersect the portal since last Location ?
    // If yes, check the direction : crossing forward means we were in front and now at the back
    // If we crossed backward, ignore it (similar to Prey 2006)
    if (IsIntersect && !IsInFront && LastInFront)
    {
        IsCrossing = true;
    }

    // Store values for next check
    LastInFront = IsInFront;
    LastPosition = Point;

    return IsCrossing;
}

void APortalActor::TeleportActor(AActor* ActorToTeleport)
{
    if (ActorToTeleport == nullptr || Target == nullptr)
    {
        return;
    }

    //-------------------------------
    //Retrieve and save Player Velocity
    //(from the Movement Component)
    //-------------------------------
    FVector SavedVelocity = FVector::ZeroVector;
    AMyPlayerCharacter* EC = nullptr;

    if (ActorToTeleport->IsA(AMyPlayerCharacter::StaticClass()))
    {
        EC = Cast<AMyPlayerCharacter>(ActorToTeleport);

        SavedVelocity = EC->GetCharMovementComponent()->GetCurrentVelocity();
    }

    //-------------------------------
    //Compute and apply new location
    //-------------------------------
    FHitResult HitResult;
    FVector NewLocation = ConvertLocationToActorSpace(ActorToTeleport->GetActorLocation(),
        this,
        Target);

    ActorToTeleport->SetActorLocation(NewLocation,
        false,
        &HitResult,
        ETeleportType::TeleportPhysics);

    //-------------------------------
    //Compute and apply new rotation
    //-------------------------------
    FRotator NewRotation = ConvertRotationToActorSpace(ActorToTeleport->GetActorRotation(),
        this,
        Target);

    //Apply new rotation
    ActorToTeleport->SetActorRotation(NewRotation);

    //-------------------------------
    //If we are teleporting a character we need to
    //update its controller as well and reapply its velocity
    //-------------------------------
    if (ActorToTeleport->IsA(AMyPlayerCharacter::StaticClass()))
    {
        //Update Controller
        AMyPlayerController* EPC = EC->GetPlayerController();

        if (EPC != nullptr)
        {
            NewRotation = UTool::ConvertRotationToActorSpace(EPC->GetControlRotation(),
                this,
                Target);

            EPC->SetControlRotation(NewRotation);
        }

        //Reapply Velocity (Need to reorient direction into local space of Portal)
        {
            FVector Dots;
            Dots.X = FVector::DotProduct(SavedVelocity, GetActorForwardVector());
            Dots.Y = FVector::DotProduct(SavedVelocity, GetActorRightVector());
            Dots.Z = FVector::DotProduct(SavedVelocity, GetActorUpVector());

            FVector NewVelocity = Dots.X * Target->GetActorForwardVector()
                + Dots.Y * Target->GetActorRightVector()
                + Dots.Z * Target->GetActorUpVector();

            EC->GetCharMovementComponent()->Velocity = NewVelocity;
        }
    }

    //Cleanup Teleport
    LastPosition = NewLocation;
}







FVector ConvertLocationToActorSpace(FVector Location, AActor* Reference, AActor* Target)
{
    if (Reference == nullptr || Target == nullptr)
    {
        return FVector::ZeroVector;
    }

    FVector Direction = Location - Reference->GetActorLocation();
    FVector TargetLocation = Target->GetActorLocation();

    FVector Dots;
    Dots.X = FVector::DotProduct(Direction, Reference->GetActorForwardVector());
    Dots.Y = FVector::DotProduct(Direction, Reference->GetActorRightVector());
    Dots.Z = FVector::DotProduct(Direction, Reference->GetActorUpVector());

    FVector NewDirection = Dots.X * Target->GetActorForwardVector()
        + Dots.Y * Target->GetActorRightVector()
        + Dots.Z * Target->GetActorUpVector();

    return TargetLocation + NewDirection;
}

FRotator ConvertRotationToActorSpace(FRotator Rotation, AActor* Reference, AActor* Target)
{
    if (Reference == nullptr || Target == nullptr)
    {
        return FRotator::ZeroRotator;
    }

    FTransform SourceTransform = Reference->GetActorTransform();
    FTransform TargetTransform = Target->GetActorTransform();
    FQuat QuatRotation = FQuat(Rotation);

    FQuat LocalQuat = SourceTransform.GetRotation().Inverse() * QuatRotation;
    FQuat NewWorldQuat = TargetTransform.GetRotation() * LocalQuat;

    return NewWorldQuat.Rotator();
}*/