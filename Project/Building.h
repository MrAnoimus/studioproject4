#pragma once
#include "LoadTGA.h"
#include "vector3D.h"
#include "Citizen.h"
class Building
{
	enum
	{
		HOUSE = 0,
		BANK,
		FOODSTORE,
		LAST
	}BuildingType;
	private:
		int Size;
		Vector3D Position;
		int Type;
		float Cost;
	public:
		std::vector<Citizen* >CitizenList;

		TextureImage Building1;
		Building(void);
		~Building(void);

		void Init(Vector3D pos);
		void Update();
		void Draw();

		float GetCost();
		int GetType();
		Vector3D GetPosition();

		void SetType(int tp);
		void SetPosition(Vector3D pos);
};

