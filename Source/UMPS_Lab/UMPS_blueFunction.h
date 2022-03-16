// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UMPS_blueFunction.generated.h"

/**
 *
 */
UCLASS()
class UMPS_LAB_API UUMPS_blueFunction : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()



public:


	UFUNCTION(BlueprintCallable, Category = "UMPS_Lab")
		static int Memoryshare();

	UFUNCTION(BlueprintCallable, Category = "UMPS_Lab")
		static FVector Servo_Move(int id, FVector m_origin, float Pulseper3D);

	UFUNCTION(BlueprintCallable, Category = "UMPS_Lab")
		static int Memory_Num(int Number);

	UFUNCTION(BlueprintCallable, Category = "UMPS_Lab")
		static int PLC_Check();

	UFUNCTION(BlueprintCallable, Category = "UMPS_Lab")
		static int Melsec_Servo();

	UFUNCTION(BlueprintCallable, Category = "UMPS_Lab")
		static int MPS_Signal();

	UFUNCTION(BlueprintCallable, Category = "MPS_TRANS")
		static int Axis_Move();

	UFUNCTION(BlueprintCallable, Category = "UMPS_Lab")
		static void Senser_Check(int Comp, int Sensor);

	UFUNCTION(BlueprintCallable, Category = "UMPS_Lab")
		static void Memory_Clear();

	UFUNCTION(BlueprintCallable, Category = "UMPS_Lab")
		static int LED_Red();

	UFUNCTION(BlueprintCallable, Category = "UMPS_Lab")
		static int LED_Yellow();

	UFUNCTION(BlueprintCallable, Category = "UMPS_Lab")
		static int LED_Green();

	UFUNCTION(BlueprintCallable, Category = "Widget_Control")
		static int Component_Check_On(int a, int Check);

	UFUNCTION(BlueprintCallable, Category = "Widget_Control")
		static int Speed_Check_On(int a, int Check);

	UFUNCTION(BlueprintCallable, Category = "Widget_Control")
		static int Window_Check_On(int a, int Check);

	UFUNCTION(BlueprintCallable, Category = "Widget_Control")
		static int Share_Check();

	UFUNCTION(BlueprintCallable, Category = "Widget_Control")
		static int Magazin_Check_On(int a, int Check);
	
};
