#pragma once
#include "Building.h"
class Shelter : public Building
{
	private:
		float rotationSpeed;
	public:
		TextureImage ShelterTexture;
		Shelter(void);
		~Shelter(void);

		void Init(Vector3D pos);
		void Update();
		void Draw();

		//get
		float GetRSpeed();
		//set
		void SetRspeed(float rs);
};

