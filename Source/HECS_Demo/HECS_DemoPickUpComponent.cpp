// Copyright Epic Games, Inc. All Rights Reserved.

#include "HECS_DemoPickUpComponent.h"

UHECS_DemoPickUpComponent::UHECS_DemoPickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void UHECS_DemoPickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UHECS_DemoPickUpComponent::OnSphereBeginOverlap);
}

void UHECS_DemoPickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	AHECS_DemoCharacter* Character = Cast<AHECS_DemoCharacter>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
