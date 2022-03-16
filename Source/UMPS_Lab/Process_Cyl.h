// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Process_Cyl.generated.h"

UCLASS()
class UMPS_LAB_API AProcess_Cyl : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProcess_Cyl();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "MPS_Process")
		static FVector AProcess_Process(FVector orgin, FVector Postion, int state, float speed);

	UFUNCTION(BlueprintCallable, Category = "MPS_Process")
		static FVector AProcess_Process_F(FVector orgin, FVector Postion, int state, float speed);

	UFUNCTION(BlueprintCallable, Category = "MPS_Process")
		static FVector AProcess_Process_B(FVector orgin, FVector Postion, int state, float speed);

	UFUNCTION(BlueprintCallable, Category = "MPS_Process")
		static int AProcess_Sensor_Check_F();

	UFUNCTION(BlueprintCallable, Category = "MPS_Process")
		static int AProcess_Sensor_Check_B();

	UFUNCTION(BlueprintCallable, Category = "MPS_Process")
		static int AProcess_SensorCheck();

	UFUNCTION(BlueprintCallable, Category = "MPS_Process")
		static int Close_Sensor();

};
