#pragma once
#include "Building.h"

class House : public Building
{
	private:
		std::string	Owner;
		float rotationSpeed;
	public:
		TextureImage IsBuilding;
		TextureImage HouseTexture;
		House(void);
		~House(void);

		void Init(Vector3D pos);
		void Update();
		void DrawBuildingbar();
		void Draw();

		//get
		std::string GetOwner();
		//set
		void SetOwner(std::string name);
};

