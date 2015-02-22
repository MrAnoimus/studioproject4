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
		
	public:
		std::vector<Citizen* >CitizenList;
		Building(void);
		~Building(void);

		//get
		float GetBPercentage();
		int GetSize();
		float GetCost();
		Vector3D GetPosition();
		//set
		void SetBPercentage(float pc);
		void SetSize(int size);
		void SetCost(float cost);
		void SetPosition(Vector3D pos);
};

