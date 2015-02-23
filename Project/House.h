#pragma once
#include "Building.h"

class House : public Building
{
	private:
		std::string	Owner;
		float rotationSpeed;
	public:
		TextureImage HouseTexture;
		House(void);
		~House(void);

		void Init(Vector3D pos);
		void Update();
		void Draw();

		//get
		std::string GetOwner();
		float GetRSpeed();
		//set
		void SetOwner(std::string name);
		void SetRspeed(float rs);
};

