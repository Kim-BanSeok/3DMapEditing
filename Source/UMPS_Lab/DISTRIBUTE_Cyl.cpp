// Fill out your copyright notice in the Description page of Project Settings.


#include "DISTRIBUTE_Cyl.h"



static int Sensor;

static int Sensor_F;
static int Sensor_B;

// Sets default values
ADISTRIBUTE_Cyl::ADISTRIBUTE_Cyl()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADISTRIBUTE_Cyl::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADISTRIBUTE_Cyl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ADISTRIBUTE_Cyl::ADistribute_Process(FVector orgin, FVector Postion, int state, float speed)
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
		v.X = Postion.X - speed;
		v.Y = Postion.Y ;
		v.Z = Postion.Z;
		if (v.X < orgin.X - 390)
		{
			v.X = orgin.X - 390;
			Sensor = 1;
		}
	}
	else if (state == 2)
	{
		v.X = Postion.X + speed;
		v.Y = Postion.Y ;
		v.Z = Postion.Z;
		if (v.X > orgin.X)
		{
			v.X = orgin.X;
			Sensor = 2;
		}
	}
	return v;
}

FVector ADISTRIBUTE_Cyl::ADistribute_Process_F(FVector orgin, FVector Postion, int state, float speed)
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
		v.X = Postion.X - speed;
		v.Y = Postion.Y;
		v.Z = Postion.Z;
		if (v.X < orgin.X - 390)
		{
			v.X = orgin.X - 390;
			Sensor_F = 1;
		}
	}
	else if (state == 2)
	{
		v.X = Postion.X;
		v.Y = Postion.Y;
		v.Z = Postion.Z;
		if (v.X < orgin.X - 389)
		{
			Sensor_F = 1;
		}

	}
	return v;
}

FVector ADISTRIBUTE_Cyl::ADistribute_Process_B(FVector orgin, FVector Postion, int state, float speed)
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
		v.X = Postion.X + speed;
		v.Y = Postion.Y;
		v.Z = Postion.Z;
		if (v.X > orgin.X)
		{
			v.X = orgin.X;
			Sensor_B = 1;
		}
	}
	else if (state == 2)
	{
		v.X = Postion.X;
		v.Y = Postion.Y;
		v.Z = Postion.Z;
		if (v.X > orgin.X -1)
		{
			Sensor_B = 1;
		}

	}
	return v;
}

int ADISTRIBUTE_Cyl::ADistribute_Sensor_Check_F()
{
	return Sensor_F;
}

int ADISTRIBUTE_Cyl::ADistribute_Sensor_Check_B()
{
	return Sensor_B;
}

int ADISTRIBUTE_Cyl::ADistribute_SensorCheck()
{
	return Sensor;
}

int ADISTRIBUTE_Cyl::Close_Sensor()
{
	return 0;

}