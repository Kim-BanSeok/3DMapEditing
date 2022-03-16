// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EXTRACT_Cyl.generated.h"

UCLASS()
class UMPS_LAB_API AEXTRACT_Cyl : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEXTRACT_Cyl();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "MPS_EXTRACT")
		static FVector AExtract_Process(FVector orgin, FVector Postion, int state, float speed);

	UFUNCTION(BlueprintCallable, Category = "MPS_EXTRACT")
		static FVector AExtract_Process_F(FVector orgin, FVector Postion, int state, float speed);

	UFUNCTION(BlueprintCallable, Category = "MPS_EXTRACT")
		static FVector AExtract_Process_B(FVector orgin, FVector Postion, int state, float speed);

	UFUNCTION(BlueprintCallable, Category = "MPS_EXTRACT")
		static int AExtract_Sensor_Check_F();

	UFUNCTION(BlueprintCallable, Category = "MPS_EXTRACT")
		static int AExtract_Sensor_Check_B();

	UFUNCTION(BlueprintCallable, Category = "MPS_EXTRACT")
		static int AExtract_SensorCheck();

	UFUNCTION(BlueprintCallable, Category = "MPS_EXTRACT")
		static int Close_Sensor();

};
