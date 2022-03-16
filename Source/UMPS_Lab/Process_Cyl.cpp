// Fill out your copyright notice in the Description page of Project Settings.


#include "Process_Cyl.h"



static int Sensor;
static int Sensor_F;
static int Sensor_B;


// Sets default values
AProcess_Cyl::AProcess_Cyl()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AProcess_Cyl::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProcess_Cyl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector AProcess_Cyl::AProcess_Process(FVector orgin, FVector Postion, int state, float speed)
{
	Sensor = 0;
	FVector v;
	if (state == 0)
	{
		v.X = orgin.X;
		v.Y = orgin.Y;
		v.Z = orgin.Z;
	}
	else if (state == 1)
	{
		v.X = Postion.X ;
		v.Y = Postion.Y;
		v.Z = Postion.Z - speed;
		if (v.Z < orgin.Z - 50)
		{
			v.Z = orgin.Z - 50;
			Sensor = 1;
		}
	}
	else if (state == 2)
	{
		v.X = Postion.X ;
		v.Y = Postion.Y;
		v.Z = Postion.Z + speed;
		if (v.Z > orgin.Z)
		{
			v.Z = orgin.Z;
			Sensor = 2;
		}
	}
	return v;
}

FVector AProcess_Cyl::AProcess_Process_F(FVector orgin, FVector Postion, int state, float speed)
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
		if (v.Z < orgin.Z - 50)
		{
			v.Z = orgin.Z - 50;
			Sensor_F = 1;
		}
	}
	else if (state == 2)
	{
		v.X = Postion.X;
		v.Y = Postion.Y;
		v.Z = Postion.Z;
		if (v.Z < orgin.Z - 49)
		{
			Sensor_F = 1;
		}

	}
	return v;
}

FVector AProcess_Cyl::AProcess_Process_B(FVector orgin, FVector Postion, int state, float speed)
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
		if (v.Z > orgin.Z - 1)
		{
			Sensor_B = 1;
		}

	}
	return v;
}

int AProcess_Cyl::AProcess_Sensor_Check_F()
{
	return Sensor_F;
}

int AProcess_Cyl::AProcess_Sensor_Check_B()
{
	return Sensor_B;
}


int AProcess_Cyl::AProcess_SensorCheck()
{
	return Sensor;
}


int AProcess_Cyl::Close_Sensor()
{
	return 0;

}