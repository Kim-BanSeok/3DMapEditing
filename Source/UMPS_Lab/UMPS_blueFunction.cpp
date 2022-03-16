// Fill out your copyright notice in the Description page of Project Settings.


#include "UMPS_blueFunction.h"
#include <windows.h>



static int Servo_move;
struct _xyz
{
	float x;
	float y;
	float z;
};
struct _StatePos
{
	int State;
	_xyz Pos;
};
struct _Component
{
	_StatePos m_Compo;
	int SensorCheck;
	int Stay; //PLC_Number || Wroks2_Servo
};
struct __IO_Board
{
	_Component Start_Signal; //MPS �ùķ��̼� ���� ��ȣ
	_Component SUPPLY; //���޽Ǹ���
	_Component DISTRIBUTE; //�й�Ǹ���
	_Component PROCESS; //�����Ǹ���

	_Component STOP_FWD; //������ ����
	_Component STOP_BWD; //������ ����

	_Component EXTRACT; //����Ǹ���


	_Component TRANS; //�̼۽Ǹ���
	_Component TRANS_FWD; //�̼۽Ǹ��� ����
	_Component TRANS_BWD; //�̼۽Ǹ��� ����
	_Component SAVE; //����Ǹ���
	_Component SAVE_FWD; //����Ǹ��� ����
	_Component SAVE_BWD; //����Ǹ��� ����


	_Component DRILL; //�帱
	_Component CONVEYOR; //�����̾�


	_Component VAC_ON; //���� ON
	_Component VAC_OFF; //���� OFF
	_Component SERVO_ON; //Servo ON
	_Component SERVO_FWJOG; // Servo ���� ����
	_Component SERVO_BWJOG; // Servo ���� ����
	_Component Servo_Point; //Servo Motor Move

	_Component SUPPLY_M_Sensor; //���� �Ű��� ����

	_Component DISTRIBUTE_M_Sensor; //�й� �Ű��� ����
	_Component STOP_M_Sensor; //������ �Ű��� ����

	_Component Proximity_Sensor; //��������
	_Component Capacity_Sensor; //�뷮������

	_Component PLC_Check; //PLC ���� ���� 1:Melsec_MCPU, 2:XGK,XGI
	_Component Works2_Servo; //Wroks2 Servo Motor Move
	_Component Servo_Sensor; //Servo Motor Sensor
	_Component Servo_Fin; //Servo Motor ��ġ���� �Ϸ�
	_Component Pulseper3D; //Servo Motor ��ġ���� �Ϸ�
	_Component Share_Check; //�𸮾� �����޸� 1���� ������


	_Component Lamp_R; //Lamp Red
	_Component Lamp_Y; //Lamp Red
	_Component Lamp_G; //Lamp Red

	///////////�ַ����̵� ���////////////////////////
	_Component SUPPLY_FWD; //���޽Ǹ���
	_Component SUPPLY_BWD; //���޽Ǹ���
	_Component DISTRIBUTE_FWD; //�й�Ǹ���
	_Component DISTRIBUTE_BWD; //�й�Ǹ���
	_Component PROCESS_FWD; //�����Ǹ���
	_Component PROCESS_BWD; //�����Ǹ���
	_Component EXTRACT_FWD; //����Ǹ���
	_Component EXTRACT_BWD; //����Ǹ���

	//////C Lab �ǳ� ��� �߰�/////////////
	_Component S_Supply; // ���޽Ǹ��� �ַ����̵� ����
	_Component S_Process; // �����Ǹ��� �ַ����̵� ����
	_Component S_Distribute; // �й�Ǹ��� �ַ����̵� ����
	_Component S_Extract; // ����Ǹ��� �ַ����̵� ����

	_Component C_Magazine_Sensor; // �Ű��� ���� NPN|PNP �Ժ�
	_Component C_Capacity; // �����뷮�� ���� NPN|PNP ����
	_Component C_Proximity; // ������ ���� NPN|PNP ����
	_Component C_Optical; // �� ���� NPN|PNP ����

	_Component S_Magazine_Sensor_NP; // �Ű��� ���� NPN 0/ PNP 1
	_Component S_Capacity_NP; // �����뷮�� ���� NPN 0/ PNP 1
	_Component S_Proximity_NP; // ������ ���� NPN 0/ PNP 1
	_Component S_Optical_NP; // �� ���� NPN 0/ PNP 1

	_Component S_Magazine_Sensor_Out; // �Ű��� ���� ��� GND 0 / VCC 1
	_Component S_Capacity_Out; // �����뷮�� ���� ��� GND 0 / VCC 1
	_Component S_Proximity_Out; // ������ ���� ��� GND 0 / VCC 1
	_Component S_Optical_Out; // �� ���� ��� GND 0 / VCC 1

	_Component C_Cap_Sen; // �����뷮�� ���� ���� ǰ��
	_Component C_Opt_Color; // �� ���� �� ����
	/////////////////////////////////
};

void  *h_shareMem = NULL;
__IO_Board *S_Data = NULL;

static int Share_C = 0;


//__Data p_Data[10];//0 = Supply

int UUMPS_blueFunction::Memoryshare()
{
	if (Share_C == 0)
	{

		h_shareMem = ::OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, L"UnRealSharedMemory");
		if (h_shareMem == NULL) {
			h_shareMem = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 1, L"UnRealSharedMemory");
			UE_LOG(LogTemp, Warning, TEXT("h_shareMem == NULL"));
			if (h_shareMem) {
				if (S_Data == NULL) {
					S_Data = (__IO_Board *)::MapViewOfFile(h_shareMem, FILE_MAP_ALL_ACCESS, 0, 0, 0);
					UE_LOG(LogTemp, Warning, TEXT("S_Data == NULL"));
				}
				S_Data = (__IO_Board *)::MapViewOfFile(h_shareMem, FILE_MAP_ALL_ACCESS, 0, 0, 0);

			}
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("UnRealSharedMemory  %d"), h_shareMem);
			if (S_Data == NULL) {
				S_Data = (__IO_Board *)::MapViewOfFile(h_shareMem, FILE_MAP_ALL_ACCESS, 0, 0, 0);
				UE_LOG(LogTemp, Warning, TEXT("S_Data == NULL2222"));
			}
			else {

				//S_Data = (__IO_Board *)::MapViewOfFile(h_shareMem, FILE_MAP_ALL_ACCESS, 0, 0, 0);
			}
		}		
	}
	Share_C++;
	
	return Share_C;

}


FVector UUMPS_blueFunction::Servo_Move(int id, FVector m_origin, float Pulseper3D)
{
	static FVector Vec;
	FVector Origin;			
	Servo_move = 0;
	if (id == 0) {
		//Vec.X = m_origin.X;
		//Vec.Y = m_origin.Y;
		Vec.Z = m_origin.Z + (S_Data->Servo_Point.m_Compo.Pos.z/Pulseper3D);
		if (Vec.Z > m_origin.Z)
		{
			Servo_move = 1;
		}
		else if (Vec.Z < m_origin.Z)
		{
			Servo_move = 1;
		}
		else
			Servo_move = 0;
	}
	
	return Vec;
}

int UUMPS_blueFunction::Axis_Move()
{
	return Servo_move;
}

int UUMPS_blueFunction::PLC_Check()
{
	return S_Data->PLC_Check.Stay;
}

int UUMPS_blueFunction::Melsec_Servo()
{
	return S_Data->Works2_Servo.Stay;
}

int UUMPS_blueFunction::Memory_Num(int Number)
{
	int For_Back;; //��.���� ����

	/////////////////���޽Ǹ���////////////////////
	if (Number == 0) {
		if (S_Data->S_Supply.m_Compo.State == 0) ////���
		{
			if (S_Data->SUPPLY.m_Compo.State == 0) {

				For_Back = 0;

			}
			else if (S_Data->SUPPLY.m_Compo.State == 1) {

				For_Back = 1;

			}
			else if (S_Data->SUPPLY.m_Compo.State == 2) {

				For_Back = 2;

			}
		}
	}
	if (Number == 1) {
		if (S_Data->S_Supply.m_Compo.State == 1) //���
		{
			if (S_Data->SUPPLY_FWD.m_Compo.State == 0) {

				For_Back = 0;

			}
			else if (S_Data->SUPPLY_FWD.m_Compo.State == 1) {

				For_Back = 1;

			}
			else if (S_Data->SUPPLY_FWD.m_Compo.State == 2) {

				For_Back = 2;

			}
		}
	}
	if (Number == 2) {
		if (S_Data->S_Supply.m_Compo.State == 1) //���
		{
			if (S_Data->SUPPLY_BWD.m_Compo.State == 0) {

				For_Back = 0;

			}
			else if (S_Data->SUPPLY_BWD.m_Compo.State == 1) {

				For_Back = 1;

			}
			else if (S_Data->SUPPLY_BWD.m_Compo.State == 2) {

				For_Back = 2;

			}
		}
	}	
	////////////////////////////////////////////////////////

	/////////////////�����Ǹ���////////////////////
	if (Number == 3) {
		if (S_Data->S_Process.m_Compo.State == 0) ////���
		{
			if (S_Data->PROCESS.m_Compo.State == 0) {

				For_Back = 0;

			}
			else if (S_Data->PROCESS.m_Compo.State == 1) {

				For_Back = 1;

			}
			else if (S_Data->PROCESS.m_Compo.State == 2) {

				For_Back = 2;

			}
		}
	}
	if (Number == 4) {
		if (S_Data->S_Process.m_Compo.State == 1) //���
		{
			if (S_Data->PROCESS_FWD.m_Compo.State == 0) {

				For_Back = 0;

			}
			else if (S_Data->PROCESS_FWD.m_Compo.State == 1) {

				For_Back = 1;

			}
			else if (S_Data->PROCESS_FWD.m_Compo.State == 2) {

				For_Back = 2;

			}
		}
	}
	if (Number == 5) {
		if (S_Data->S_Process.m_Compo.State == 1) //���
		{
			if (S_Data->PROCESS_BWD.m_Compo.State == 0) {

				For_Back = 0;

			}
			else if (S_Data->PROCESS_BWD.m_Compo.State == 1) {

				For_Back = 1;

			}
			else if (S_Data->PROCESS_BWD.m_Compo.State == 2) {

				For_Back = 2;

			}
		}
	}
	////////////////////////////////////////////////////////


	/////////////////�й�Ǹ���////////////////////
	if (Number == 6) {
		if (S_Data->S_Distribute.m_Compo.State == 0) ////���
		{
			if (S_Data->DISTRIBUTE.m_Compo.State == 0) {

				For_Back = 0;

			}
			else if (S_Data->DISTRIBUTE.m_Compo.State == 1) {

				For_Back = 1;

			}
			else if (S_Data->DISTRIBUTE.m_Compo.State == 2) {

				For_Back = 2;

			}
		}
	}
	if (Number == 7) {
		if (S_Data->S_Distribute.m_Compo.State == 1) //���
		{
			if (S_Data->DISTRIBUTE_FWD.m_Compo.State == 0) {

				For_Back = 0;

			}
			else if (S_Data->DISTRIBUTE_FWD.m_Compo.State == 1) {

				For_Back = 1;

			}
			else if (S_Data->DISTRIBUTE_FWD.m_Compo.State == 2) {

				For_Back = 2;

			}
		}
	}
	if (Number == 8) {
		if (S_Data->S_Distribute.m_Compo.State == 1) //���
		{
			if (S_Data->DISTRIBUTE_BWD.m_Compo.State == 0) {

				For_Back = 0;

			}
			else if (S_Data->DISTRIBUTE_BWD.m_Compo.State == 1) {

				For_Back = 1;

			}
			else if (S_Data->DISTRIBUTE_BWD.m_Compo.State == 2) {

				For_Back = 2;

			}
		}
	}
	////////////////////////////////////////////////////////


	


	/////////////////����Ǹ���////////////////////
	if (Number == 9) {
		if (S_Data->S_Extract.m_Compo.State == 0) ////���
		{
			if (S_Data->EXTRACT.m_Compo.State == 0) {

				For_Back = 0;

			}
			else if (S_Data->EXTRACT.m_Compo.State == 1) {

				For_Back = 1;

			}
			else if (S_Data->EXTRACT.m_Compo.State == 2) {

				For_Back = 2;

			}
		}
	}
	if (Number == 10) {
		if (S_Data->S_Extract.m_Compo.State == 1) //���
		{
			if (S_Data->EXTRACT_FWD.m_Compo.State == 0) {

				For_Back = 0;

			}
			else if (S_Data->EXTRACT_FWD.m_Compo.State == 1) {

				For_Back = 1;

			}
			else if (S_Data->EXTRACT_FWD.m_Compo.State == 2) {

				For_Back = 2;

			}
		}
	}
	if (Number == 11) {
		if (S_Data->S_Extract.m_Compo.State == 1) //���
		{
			if (S_Data->EXTRACT_BWD.m_Compo.State == 0) {

				For_Back = 0;

			}
			else if (S_Data->EXTRACT_BWD.m_Compo.State == 1) {

				For_Back = 1;

			}
			else if (S_Data->EXTRACT_BWD.m_Compo.State == 2) {

				For_Back = 2;

			}
		}
	}
	////////////////////////////////////////////////////////

	

	////////////���////���///������
	if (Number == 100)//���޼ַ����̵�
		For_Back = S_Data->S_Supply.m_Compo.State; 
	if (Number == 101)//�����ַ����̵�
		For_Back = S_Data->S_Process.m_Compo.State;
	if (Number == 102)//�й�ַ����̵�
		For_Back = S_Data->S_Distribute.m_Compo.State;
	if (Number == 103)//����ַ����̵�
		For_Back = S_Data->S_Extract.m_Compo.State;
	///////////////////////////////////////
	////////////Lamp///////////////////
	if (Number == 104)
		For_Back = S_Data->Lamp_R.m_Compo.State;
	if (Number == 105)
		For_Back = S_Data->Lamp_Y.m_Compo.State;
	if (Number == 106)
		For_Back = S_Data->Lamp_G.m_Compo.State;
	if (Number == 107)
		For_Back = S_Data->CONVEYOR.m_Compo.State;
	if (Number == 108)
		For_Back = S_Data->DRILL.m_Compo.State;
	/////////����//////////////////////////////
	if (Number == 109)
		For_Back = S_Data->S_Magazine_Sensor_NP.m_Compo.State;
	if (Number == 110)
		For_Back = S_Data->S_Capacity_NP.m_Compo.State;
	if (Number == 111)
		For_Back = S_Data->S_Proximity_NP.m_Compo.State;
	if (Number == 112)
		For_Back = S_Data->S_Optical_NP.m_Compo.State;
	if (Number == 113)
		For_Back = S_Data->C_Cap_Sen.m_Compo.State;
	if (Number == 114)
		For_Back = S_Data->C_Opt_Color.m_Compo.State;
	////////////////////
	return For_Back;
}
void UUMPS_blueFunction::Senser_Check(int Comp, int Sensor)
{
	if (S_Data->Start_Signal.m_Compo.State)
	{
		////////////���޽Ǹ���///////////////
		if (Comp == 0)//��� ���޽Ǹ���
		{
			S_Data->SUPPLY.SensorCheck = Sensor;
		}
		else if (Comp == 1)//��� ���޽Ǹ��� ����
		{
			S_Data->SUPPLY_FWD.SensorCheck = Sensor;
		}
		else if (Comp == 2)//��� ���޽Ǹ��� ����
		{
			S_Data->SUPPLY_BWD.SensorCheck = Sensor;
		}
		///////////////////////////////


		////////////�����Ǹ���///////////////
		if (Comp == 3)//��� �����Ǹ���
		{
			S_Data->PROCESS.SensorCheck = Sensor;
		}
		else if (Comp == 4)//��� �����Ǹ��� ����
		{
			S_Data->PROCESS_FWD.SensorCheck = Sensor;
		}
		else if (Comp == 5)//��� �����Ǹ��� ����
		{
			S_Data->PROCESS_BWD.SensorCheck = Sensor;
		}
		///////////////////////////////

		////////////�й�Ǹ���///////////////
		if (Comp == 6)//��� �й�Ǹ���
		{
			S_Data->DISTRIBUTE.SensorCheck = Sensor;
		}
		else if (Comp == 7)//��� �й�Ǹ��� ����
		{
			S_Data->DISTRIBUTE_FWD.SensorCheck = Sensor;
		}
		else if (Comp == 8)//��� �й�Ǹ��� ����
		{
			S_Data->DISTRIBUTE_BWD.SensorCheck = Sensor;
		}
		///////////////////////////////


		////////////����Ǹ���///////////////
		if (Comp == 9)//��� ����Ǹ���
		{
			S_Data->EXTRACT.SensorCheck = Sensor;
		}
		else if (Comp == 10)//��� ����Ǹ��� ����
		{
			S_Data->EXTRACT_FWD.SensorCheck = Sensor;
		}
		else if (Comp == 11)//��� ����Ǹ��� ����
		{
			S_Data->EXTRACT_BWD.SensorCheck = Sensor;
		}
		///////////////////////////////

		////////////���޸Ű��� ����///////////////
		if (Comp == 12)//NPN��		
		{			
			S_Data->S_Magazine_Sensor_Out.SensorCheck = Sensor; // NPN 1 / PNP 2 / NONE 0
		}
		//else if (Comp == 13)//PNP��
		//{
		//	S_Data->S_Magazine_Sensor_P.SensorCheck = Sensor;
		//}		
		///////////////////////////////

		////////////�����뷮�� ����///////////////
		if (Comp == 14)//NPN��
		{
			S_Data->S_Capacity_Out.SensorCheck = Sensor;
		}
		//else if (Comp == 15)//PNP��
		//{
		//	S_Data->S_Capacity_P.SensorCheck = Sensor;
		//}
		///////////////////////////////

		////////////������ ����///////////////
		if (Comp == 16)//NPN��
		{
			S_Data->S_Proximity_Out.SensorCheck = Sensor;
		}
		//else if (Comp == 17)//PNP��
		//{
		//	S_Data->S_Proximity_P.SensorCheck = Sensor;
		//}
		///////////////////////////////

		////////////�� ����///////////////
		if (Comp == 18)//NPN��
		{
			S_Data->S_Optical_Out.SensorCheck = Sensor;
		}
		//else if (Comp == 19)//PNP��
		//{
		//	S_Data->S_Optical_P.SensorCheck = Sensor;
		//}
		///////////////////////////////
		
		
	}
	else
	{
		S_Data->SUPPLY.SensorCheck = Sensor;
		S_Data->DISTRIBUTE.SensorCheck = Sensor;
		S_Data->DRILL.SensorCheck = Sensor;
		S_Data->EXTRACT.SensorCheck = Sensor;
		S_Data->STOP_FWD.SensorCheck = Sensor;
		S_Data->STOP_BWD.SensorCheck = Sensor;
		S_Data->TRANS_FWD.SensorCheck = Sensor;
		S_Data->TRANS_BWD.SensorCheck = Sensor;
		S_Data->SAVE_FWD.SensorCheck = Sensor;
		S_Data->SAVE_BWD.SensorCheck = Sensor;
		S_Data->DISTRIBUTE_M_Sensor.SensorCheck = Sensor;
		S_Data->SUPPLY_M_Sensor.SensorCheck = Sensor;
		S_Data->STOP_M_Sensor.SensorCheck = Sensor;
		S_Data->STOP_FWD.SensorCheck = Sensor;
		S_Data->Proximity_Sensor.SensorCheck = Sensor;
		S_Data->Capacity_Sensor.SensorCheck = Sensor;
		S_Data->STOP_BWD.SensorCheck = Sensor;
		S_Data->PROCESS.SensorCheck = Sensor;
		S_Data->SAVE_FWD.SensorCheck = Sensor;
		S_Data->SAVE_BWD.SensorCheck = Sensor;
		S_Data->TRANS_FWD.SensorCheck = Sensor;
		S_Data->TRANS_BWD.SensorCheck = Sensor;
		S_Data->Servo_Sensor.SensorCheck = Sensor;
		S_Data->Servo_Fin.SensorCheck = Sensor;





		////////////���޽Ǹ���///////////////
		S_Data->SUPPLY.SensorCheck = Sensor;
		S_Data->SUPPLY_FWD.SensorCheck = Sensor;
		S_Data->SUPPLY_BWD.SensorCheck = Sensor;
		////////////�����Ǹ���///////////////
		S_Data->PROCESS.SensorCheck = Sensor;
		S_Data->PROCESS_FWD.SensorCheck = Sensor;
		S_Data->PROCESS_BWD.SensorCheck = Sensor;
		////////////�й�Ǹ���///////////////
		S_Data->DISTRIBUTE.SensorCheck = Sensor;
		S_Data->DISTRIBUTE_FWD.SensorCheck = Sensor;
		S_Data->DISTRIBUTE_BWD.SensorCheck = Sensor;
		////////////����Ǹ���///////////////
		S_Data->EXTRACT.SensorCheck = Sensor;
		S_Data->EXTRACT_FWD.SensorCheck = Sensor;
		S_Data->EXTRACT_BWD.SensorCheck = Sensor;
		////////////���޸Ű��� ����///////////////
		S_Data->S_Magazine_Sensor_Out.SensorCheck = Sensor;
		////////////�����뷮�� ����///////////////
		S_Data->S_Capacity_Out.SensorCheck = Sensor;
		////////////������ ����///////////////
		S_Data->S_Proximity_Out.SensorCheck = Sensor;
		////////////�� ����///////////////
		S_Data->S_Optical_Out.SensorCheck = Sensor;
	}
	
}

int UUMPS_blueFunction::MPS_Signal()
{ 
	if (S_Data->Start_Signal.m_Compo.State)
	{
		return S_Data->Start_Signal.m_Compo.State;
	}
	return 0;

}

void UUMPS_blueFunction::Memory_Clear()
{

	if (S_Data != NULL)::UnmapViewOfFile(S_Data);
	if (h_shareMem != NULL)::CloseHandle(h_shareMem);

	S_Data = NULL;
	h_shareMem = NULL;

	Share_C = 0;

}

int UUMPS_blueFunction::Component_Check_On(int a, int Check)
{
	static int check2 = 0;
	if (a == 0)
	{
		return check2;
	}
	else if (a == 1)
	{
		check2 = Check;
		return check2;
	}

	return 0;
}

int UUMPS_blueFunction::Speed_Check_On(int a, int Check)
{
	static int check2 = 0;
	if (a == 0)
	{
		return check2;
	}
	else if (a == 1)
	{
		check2 = Check;
		return check2;
	}

	return 0;
}

int UUMPS_blueFunction::Window_Check_On(int a, int Check)
{
	static int check2 = 0;
	if (a == 0)
	{
		return check2;
	}
	else if (a == 1)
	{
		check2 = Check;
		return check2;
	}

	return 0;
}

int UUMPS_blueFunction::Share_Check()
{
	

	return Share_C;
}

int UUMPS_blueFunction::Magazin_Check_On(int a, int Check)
{
	static int check2 = 0;
	if (a == 0)
	{
		return check2;
	}
	else if (a == 1)
	{
		check2 = Check;
		return check2;
	}

	return 0;
}

int UUMPS_blueFunction::LED_Red()
{
	return S_Data->Lamp_R.m_Compo.State;
}
int UUMPS_blueFunction::LED_Yellow()
{
	return S_Data->Lamp_Y.m_Compo.State;
}
int UUMPS_blueFunction::LED_Green()
{
	return S_Data->Lamp_G.m_Compo.State;
}