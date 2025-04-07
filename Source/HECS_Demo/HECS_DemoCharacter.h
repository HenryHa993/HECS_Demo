// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EntityBase.h"
#include "EntityInfoWidget.h"
#include "HECS.h"
#include "HECSSubsystem.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Logging/LogMacros.h"
#include "HECS_DemoCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AHECS_DemoCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;
	
	HECS::World* ECSWorld;
	
public:
	UPROPERTY(BlueprintReadWrite)
	UEntityInfoWidget* EntityWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AEntityBase* FocusEntity = nullptr;
	
public:
	AHECS_DemoCharacter();

protected:
	virtual void BeginPlay() override;

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

protected:
	// APawn interface
	virtual void NotifyControllerChanged() override;
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

private:
	template <class T>
	void AddOrRemove(unsigned entity, T value = T())
	{
		if(ECSWorld->Has<T>(entity))
		{
			ECSWorld->Remove<T>(entity);
			return;
		}
		ECSWorld->Add<T>(entity, value);
	}

public:
	UFUNCTION(BlueprintCallable)
	void UpdateEntityInfo();

	UFUNCTION(BlueprintCallable)
	void AddOrRemoveCosX();

	UFUNCTION(BlueprintCallable)
	void AddOrRemoveCosY();

	UFUNCTION(BlueprintCallable)
	void AddOrRemoveCosZ();

	UFUNCTION(BlueprintCallable)
	void AddOrRemoveSinX();

	UFUNCTION(BlueprintCallable)
	void AddOrRemoveSinY();

	UFUNCTION(BlueprintCallable)
	void AddOrRemoveSinZ();

	UFUNCTION(BlueprintCallable)
	void AddOrRemoveLinearX();

	UFUNCTION(BlueprintCallable)
	void AddOrRemoveLinearY();

	UFUNCTION(BlueprintCallable)
	void AddOrRemoveLinearZ();

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	
};

