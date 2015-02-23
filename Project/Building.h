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
		int Tier;
	public:
		std::vector<Citizen* >CitizenList;
		TextureImage IsBuilding;
		Building(void);
		~Building(void);

		//get
		int GetTier();
		float GetBPercentage();
		int GetSize();
		float GetCost();
		Vector3D GetPosition();
		//set
		void SetTier(int t);
		void SetBPercentage(float pc);
		void SetSize(int size);
		void SetCost(float cost);
		void SetPosition(Vector3D pos);
};

