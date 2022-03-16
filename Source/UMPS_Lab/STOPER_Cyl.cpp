// Fill out your copyright notice in the Description page of Project Settings.


#include "STOPER_Cyl.h"

static int Sensor_F;
static int Sensor_B;

// Sets default values
ASTOPER_Cyl::ASTOPER_Cyl()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASTOPER_Cyl::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASTOPER_Cyl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


FVector ASTOPER_Cyl::AStoper_Process_F(FVector orgin, FVector Postion, int state, float speed)
{
	Sensor_F = 0;
	FVector v;
	if (state == 0)
	{
		v.X = orgin.X;
		v.Y = orgin.Y;
		v.Z = orgin.Z;
	}
	else if (state == 1)
	{
		v.X = Postion.X;
		v.Y = Postion.Y;
		v.Z = Postion.Z - speed;
		if (v.Z < orgin.Z - 102)
		{
			v.Z = orgin.Z - 102;
			Sensor_F = 1;
		}
	}
	else if (state == 2)
	{
		v.X = Postion.X;
		v.Y = Postion.Y;
		v.Z = Postion.Z;
		if (v.Z < orgin.Z - 101)
		{
			Sensor_F = 1;
		}
		
	}
	return v;
}

FVector ASTOPER_Cyl::AStoper_Process_B(FVector orgin, FVector Postion, int state, float speed)
{
	Sensor_B = 0;
	FVector v;
	if (state == 0)
	{
		v.X = orgin.X;
		v.Y = orgin.Y;
		v.Z = orgin.Z;
	}
	else if (state == 1)
	{
		v.X = Postion.X;
		v.Y = Postion.Y;
		v.Z = Postion.Z + speed;
		if (v.Z > orgin.Z)
		{
			v.Z = orgin.Z;
			Sensor_B = 1;
		}
	}
	else if (state == 2)
	{
		v.X = Postion.X;
		v.Y = Postion.Y;
		v.Z = Postion.Z;
		if (v.Z > orgin.Z-1)
		{			
			Sensor_B = 1;
		}
		
	}
	return v;
}

int ASTOPER_Cyl::AStoper_Sensor_Check_F()
{
	return Sensor_F;
}

int ASTOPER_Cyl::AStoper_Sensor_Check_B()
{
	return Sensor_B;
}


int ASTOPER_Cyl::Close_Sensor()
{
	return 0;

}
