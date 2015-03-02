#pragma once
#include "LoadTGA.h"
#include "vector3D.h"
#include "GaugeBar.h"
#include "Citizen.h"

class Building
{
	private:
		Vector3D Position;
		float Cost;
		float BuildPercentage;
		float speed;
		int Size;
		float MaintenanceFee;
		float Earnings;
		int Tier;
		float Alpha;
	public:
		
		TextureImage IsBuilding;
		TextureImage IsDestructing;

		Building(void);
		~Building(void);

		void DrawBuildingbar(float r);
		void DrawDestructing(float r);
		//get
		float GetMaintenanceFee();
		float GetEarnings();
		float GetAlpha();
		int GetTier();
		float GetBPercentage();
		int GetSize();
		float GetCost();
		Vector3D GetPosition();
		//set
		void SetMaintenanceFee(float fee);
		void SetEarnings(float earn);
		void SetAlpha(float a);
		void SetTier(int t);
		void SetBPercentage(float pc);
		void SetSize(int size);
		void SetCost(float cost);
		void SetPosition(Vector3D pos);
};

