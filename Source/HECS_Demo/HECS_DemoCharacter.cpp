// Copyright Epic Games, Inc. All Rights Reserved.

#include "HECS_DemoCharacter.h"

#include "ComponentEntryData.h"
#include "ComponentsModule.h"
#include "HECS_DemoProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AHECS_DemoCharacter

AHECS_DemoCharacter::AHECS_DemoCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
}

void AHECS_DemoCharacter::BeginPlay()
{
	UGameInstance* gameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	UHECSSubsystem* hecsSubsystem = gameInstance->GetSubsystem<UHECSSubsystem>();
	ECSWorld = hecsSubsystem->GetECSWorld();

	Super::BeginPlay();
}

//////////////////////////////////////////////////////////////////////////// Input

void AHECS_DemoCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AHECS_DemoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHECS_DemoCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHECS_DemoCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AHECS_DemoCharacter::UpdateEntityInfo()
{
	if(FocusEntity == nullptr)
	{
		return;
	}

	TArray<UComponentEntryData*> data;
	int entityID = FocusEntity->EntityID;
	
	if (ECSWorld->Has<StaticMeshComponent>(entityID))
	{
	    UComponentEntryData* entryData = NewObject<UComponentEntryData>();
	    entryData->ComponentLabel = FText::FromString(TEXT("Static Mesh"));
	    data.Add(entryData);
	}

	if (ECSWorld->Has<CosX>(entityID))
	{
	    UComponentEntryData* entryData = NewObject<UComponentEntryData>();
	    entryData->ComponentLabel = FText::FromString(TEXT("CosX"));
	    data.Add(entryData);
	}

	if (ECSWorld->Has<CosY>(entityID))
	{
	    UComponentEntryData* entryData = NewObject<UComponentEntryData>();
	    entryData->ComponentLabel = FText::FromString(TEXT("CosY"));
	    data.Add(entryData);
	}

	if (ECSWorld->Has<CosZ>(entityID))
	{
	    UComponentEntryData* entryData = NewObject<UComponentEntryData>();
	    entryData->ComponentLabel = FText::FromString(TEXT("CosZ"));
	    data.Add(entryData);
	}

	if (ECSWorld->Has<SinX>(entityID))
	{
	    UComponentEntryData* entryData = NewObject<UComponentEntryData>();
	    entryData->ComponentLabel = FText::FromString(TEXT("SinX"));
	    data.Add(entryData);
	}

	if (ECSWorld->Has<SinY>(entityID))
	{
	    UComponentEntryData* entryData = NewObject<UComponentEntryData>();
	    entryData->ComponentLabel = FText::FromString(TEXT("SinY"));
	    data.Add(entryData);
	}

	if (ECSWorld->Has<SinZ>(entityID))
	{
	    UComponentEntryData* entryData = NewObject<UComponentEntryData>();
	    entryData->ComponentLabel = FText::FromString(TEXT("SinZ"));
	    data.Add(entryData);
	}

	if (ECSWorld->Has<LinearX>(entityID))
	{
	    UComponentEntryData* entryData = NewObject<UComponentEntryData>();
	    entryData->ComponentLabel = FText::FromString(TEXT("LinearX"));
	    data.Add(entryData);
	}

	if (ECSWorld->Has<LinearY>(entityID))
	{
	    UComponentEntryData* entryData = NewObject<UComponentEntryData>();
	    entryData->ComponentLabel = FText::FromString(TEXT("LinearY"));
	    data.Add(entryData);
	}

	if (ECSWorld->Has<LinearZ>(entityID))
	{
	    UComponentEntryData* entryData = NewObject<UComponentEntryData>();
	    entryData->ComponentLabel = FText::FromString(TEXT("LinearZ"));
	    data.Add(entryData);
	}
		
		EntityWidget->EntityNum->SetText(FText::AsNumber(entityID));
		EntityWidget->ComponentList->SetListItems(data);
	}

void AHECS_DemoCharacter::AddOrRemoveCosX()
{
	if(FocusEntity == nullptr) return;
	int entityID = FocusEntity->EntityID;
	AddOrRemove<CosX>(entityID, {FocusEntity->Radius});
	UpdateEntityInfo();
}

void AHECS_DemoCharacter::AddOrRemoveCosY()
{
	if (FocusEntity == nullptr) return;
	int entityID = FocusEntity->EntityID;
	AddOrRemove<CosY>(entityID, {FocusEntity->Radius});
	UpdateEntityInfo();
}

void AHECS_DemoCharacter::AddOrRemoveCosZ()
{
	if (FocusEntity == nullptr) return;
	int entityID = FocusEntity->EntityID;
	AddOrRemove<CosZ>(entityID, {FocusEntity->Radius});
	UpdateEntityInfo();
}

void AHECS_DemoCharacter::AddOrRemoveSinX()
{
	if (FocusEntity == nullptr) return;
	int entityID = FocusEntity->EntityID;
	AddOrRemove<SinX>(entityID, {FocusEntity->Radius});
	UpdateEntityInfo();
}

void AHECS_DemoCharacter::AddOrRemoveSinY()
{
	if (FocusEntity == nullptr) return;
	int entityID = FocusEntity->EntityID;
	AddOrRemove<SinY>(entityID, {FocusEntity->Radius});
	UpdateEntityInfo();
}

void AHECS_DemoCharacter::AddOrRemoveSinZ()
{
	if (FocusEntity == nullptr) return;
	int entityID = FocusEntity->EntityID;
	AddOrRemove<SinZ>(entityID, {FocusEntity->Radius});
	UpdateEntityInfo();
}

void AHECS_DemoCharacter::AddOrRemoveLinearX()
{
	if (FocusEntity == nullptr) return;
	int entityID = FocusEntity->EntityID;
	AddOrRemove<LinearX>(entityID, {FocusEntity->Radius});
	UpdateEntityInfo();
}

void AHECS_DemoCharacter::AddOrRemoveLinearY()
{
	if (FocusEntity == nullptr) return;
	int entityID = FocusEntity->EntityID;
	AddOrRemove<LinearY>(entityID, {FocusEntity->Radius});
	UpdateEntityInfo();
}

void AHECS_DemoCharacter::AddOrRemoveLinearZ()
{
	if (FocusEntity == nullptr) return;
	int entityID = FocusEntity->EntityID;
	AddOrRemove<LinearZ>(entityID, {FocusEntity->Radius});
	UpdateEntityInfo();
}

void AHECS_DemoCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AHECS_DemoCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}