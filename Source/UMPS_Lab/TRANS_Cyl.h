// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TRANS_Cyl.generated.h"

UCLASS()
class UMPS_LAB_API ATRANS_Cyl : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATRANS_Cyl();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;	

	UFUNCTION(BlueprintCallable, Category = "MPS_TRANS")
		static FVector ATRANS_Process_F(FVector orgin, FVector Postion, int state, float speed);

	UFUNCTION(BlueprintCallable, Category = "MPS_TRANS")
		static FVector ATRANS_Process_B(FVector orgin, FVector Postion, int state, float speed);

	UFUNCTION(BlueprintCallable, Category = "MPS_TRANS")
		static FVector AServo_Process(FVector orgin, FVector Postion, int state, int plc, float speed);

	UFUNCTION(BlueprintCallable, Category = "MPS_TRANS")
		static int ATRANS_Sensor_Check_F();

	UFUNCTION(BlueprintCallable, Category = "MPS_TRANS")
		static int ATRANS_Sensor_Check_B();

	UFUNCTION(BlueprintCallable, Category = "MPS_TRANS")
		static int Servo_Sensor();

	UFUNCTION(BlueprintCallable, Category = "MPS_TRANS")
		static int Axis_Wroks2();

	UFUNCTION(BlueprintCallable, Category = "MPS_TRANS")
		static int Servo_Fin_Sensor();

	UFUNCTION(BlueprintCallable, Category = "MPS_TRANS")
		static int Close_Sensor();

};
