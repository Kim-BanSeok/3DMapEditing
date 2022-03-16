// Fill out your copyright notice in the Description page of Project Settings.


#include "Save_Cyl.h"


static int Sensor_F;
static int Sensor_B;
// Sets default values
ASave_Cyl::ASave_Cyl()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASave_Cyl::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASave_Cyl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASave_Cyl::ASave_Process_F(FVector orgin, FVector Postion, int state, float speed)
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
		if (v.X < orgin.X - 148)
		{
			v.X = orgin.X - 148;
			Sensor_F = 1;
		}
	}
	else if (state == 2)
	{		
		
		v.X = Postion.X;
		v.Y = Postion.Y;
		v.Z = Postion.Z;
		if (v.X < orgin.X - 147)
		{
			Sensor_F = 1;
		}
	}
	return v;
}

FVector ASave_Cyl::ASave_Process_B(FVector orgin, FVector Postion, int state, float speed)
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
		if (v.X > orgin.X - 1)
		{
			Sensor_B = 1;
		}
	}
	return v;
}

int ASave_Cyl::ASave_Sensor_Check_F()
{
	return Sensor_F;
}

int ASave_Cyl::ASave_Sensor_Check_B()
{
	return Sensor_B;
}

int ASave_Cyl::Close_Sensor()
{
	return 0;

}