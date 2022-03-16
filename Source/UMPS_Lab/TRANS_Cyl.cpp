// Fill out your copyright notice in the Description page of Project Settings.


#include "TRANS_Cyl.h"


static int Sensor_F;
static int Sensor_B;
static int m_Servo_Sensor;
static int Servo_Fin;
static int Servo_move;
// Sets default values
ATRANS_Cyl::ATRANS_Cyl()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATRANS_Cyl::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATRANS_Cyl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ATRANS_Cyl::ATRANS_Process_F(FVector orgin, FVector Postion, int state, float speed)
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
		v.Y = Postion.Y - speed;
		v.Z = Postion.Z;
		if (v.Y < orgin.Y - 440)
		{
			v.Y = orgin.Y - 440;
			Sensor_F = 1;
		}
	}
	else if (state == 2)
	{
		
		v.X = Postion.X;
		v.Y = Postion.Y;
		v.Z = Postion.Z;
		if (v.Y < orgin.Y - 440)
		{
			Sensor_F = 1;
		}
		
	}
	
	return v;
}

FVector ATRANS_Cyl::ATRANS_Process_B(FVector orgin, FVector Postion, int state, float speed)
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
		v.Y = Postion.Y + speed;
		v.Z = Postion.Z;
		if (v.Y > orgin.Y)
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
		if (v.Y > orgin.Y - 1)
		{
			Sensor_B = 1;
		}
	}
	return v;
}

FVector ATRANS_Cyl::AServo_Process(FVector orgin, FVector Postion, int state, int plc, float speed)
{
	static FVector v;
	static int Witich;
	Servo_move = 0;
	if (plc == 1)
	{
		v = Postion;
		if (state == 1)
		{
			Witich = 460;			
		}
		else if (state == 2)
		{
			Witich = 370;
		}
		else if (state == 3)
		{
			Witich = 245;
		}
		else if (state == 4)
		{
			Witich = 130;
		}
		else
		{
			Witich = 0;
		}
		if (v.Z > orgin.Z - Witich && v.Z > orgin.Z - 460)
		{
			v.Z = v.Z - speed;
			Servo_move = 1;
		}
		else if (v.Z < orgin.Z - Witich && v.Z < orgin.Z)
		{
			v.Z = v.Z + speed;
			Servo_move = 2;
		}

		if (v.Z == orgin.Z - Witich)
		{
			Servo_Fin = 1;
		}
		else
		{
			Servo_Fin = 0;
		}

		if (v.Z <= orgin.Z - 459)
		{
			m_Servo_Sensor = 1;
		}
		else if (v.Z == orgin.Z - 20)
		{
			m_Servo_Sensor = 2;
		}
		else if (v.Z >= orgin.Z)
		{
			m_Servo_Sensor = 3;
		}
		else
		{
			m_Servo_Sensor = 0;
		}
	}
	else if (plc == 2)
	{
		v.X = Postion.X;
		v.Y = Postion.Y;
		v.Z = Postion.Z;

		if (v.Z > orgin.Z)
		{
			v.Z = orgin.Z;
		}
		if (v.Z < orgin.Z - 460)
		{
			v.Z = orgin.Z - 460;
		}

		if (v.Z <= orgin.Z - 459)
		{
			m_Servo_Sensor = 1;
		}
		else if (v.Z == orgin.Z - 20)
		{
			m_Servo_Sensor = 2;
		}
		else if (v.Z >= orgin.Z)
		{
			m_Servo_Sensor = 3;
		}
		else
		{
			m_Servo_Sensor = 0;
		}
	
	}	
	return v;
}

int ATRANS_Cyl::Axis_Wroks2()
{
	return Servo_move;
}

int ATRANS_Cyl::ATRANS_Sensor_Check_F()
{
	return Sensor_F;
}

int ATRANS_Cyl::ATRANS_Sensor_Check_B()
{
	return Sensor_B;
}

int ATRANS_Cyl::Servo_Sensor()
{
	return m_Servo_Sensor;
}

int ATRANS_Cyl::Servo_Fin_Sensor()
{
	return Servo_Fin;
}

int ATRANS_Cyl::Close_Sensor()
{
	return 0;

}
