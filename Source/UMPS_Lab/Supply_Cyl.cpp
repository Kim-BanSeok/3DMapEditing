// Fill out your copyright notice in the Description page of Project Settings.


#include "Supply_Cyl.h"
#include "UMPS_blueFunction.h"




static int Sensor;

static int Sensor_F;
static int Sensor_B;

// Sets default values
ASupply_Cyl::ASupply_Cyl()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASupply_Cyl::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASupply_Cyl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASupply_Cyl::ASupply_Process(FVector orgin, FVector Postion, int state, float speed)
{
	
	FVector v;
	Sensor = 0;
	if (state == 0)
	{
		v.X = orgin.X;
		v.Y = orgin.Y;
		v.Z = orgin.Z;
	}
	else if (state == 1)
	{
		v.X = Postion.X;
		v.Y = Postion.Y + speed;
		v.Z = Postion.Z;
		if (v.Y > orgin.Y + 250)
		{
			v.Y = orgin.Y + 250;
			Sensor = 1;
		}
	}
	else if (state == 2)
	{
		v.X = Postion.X;
		v.Y = Postion.Y - speed;
		v.Z = Postion.Z;
		if (v.Y < orgin.Y)
		{
			v.Y = orgin.Y;
			Sensor = 2;
		}
	}
	return v;
}

FVector ASupply_Cyl::ASupply_Process_F(FVector orgin, FVector Postion, int state, float speed)
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
		v.Y = Postion.Y + speed;
		v.Z = Postion.Z ;
		if (v.Y > orgin.Y + 250)
		{
			v.Y = orgin.Y + 250;
			Sensor_F = 1;
		}
	}
	else if (state == 2)
	{
		v.X = Postion.X;
		v.Y = Postion.Y;
		v.Z = Postion.Z;
		if (v.Y > orgin.Y + 249)
		{
			Sensor_F = 1;
		}

	}
	return v;
}

FVector ASupply_Cyl::ASupply_Process_B(FVector orgin, FVector Postion, int state, float speed)
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
		v.Y = Postion.Y - speed;
		v.Z = Postion.Z ;
		if (v.Y < orgin.Y)
		{
			v.Y = orgin.Y;
			Sensor_B = 1;
		}
	}
	else if (state == 2)
	{
		v.X = Postion.X;
		v.Y = Postion.Y;
		v.Z = Postion.Z;
		if (v.Y < orgin.Y + 1)
		{
			Sensor_B = 1;
		}

	}
	return v;
}

int ASupply_Cyl::ASupply_Sensor_Check_F()
{
	return Sensor_F;
}

int ASupply_Cyl::ASupply_Sensor_Check_B()
{
	return Sensor_B;
}

int ASupply_Cyl::ASupply_SensorCheck()
{
	return Sensor;
}

FVector ASupply_Cyl::Close_Position(FVector Origin)
{
	FVector Position;
	Position = Origin;

	return Position;
	
}

int ASupply_Cyl::Close_Sensor()
{
	return 0;

}
