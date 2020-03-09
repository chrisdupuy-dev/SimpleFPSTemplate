// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"

class UPawnSensingComponent;
class ATargetPoint;

UENUM(BlueprintType)
enum class EAIState : uint8
{
	Idle,
	Suspicious,
	Alerted
};

UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category  = "Components")
	UPawnSensingComponent* PawnSensingComponent;

	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);

	UFUNCTION()
	void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);

	UPROPERTY(EditInstanceOnly, Category = "AI")
	TArray<ATargetPoint*> PatrolPath;

	UPROPERTY(BlueprintReadOnly, Category = "AI")
	ATargetPoint* CurrentTargetLocation;

	int32 PatrolPathCurrentIndex = 0;
	
	FRotator OriginalRotation;

	UFUNCTION()
	void ResetOrientation();

	FTimerHandle TimerHandle_ResetOrientation;

	UPROPERTY(ReplicatedUsing=OnRep_GuardState, BlueprintReadOnly, Category = "AI")
	EAIState GuardState;

	UFUNCTION()
	void OnRep_GuardState();
	
	void SetGuardState(EAIState NewState);

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void OnStateChanged(EAIState NewState);

	UFUNCTION(BlueprintCallable, Category = "AI")
	void OnCurrentTargetLocationReached();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
