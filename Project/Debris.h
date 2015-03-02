#pragma once
#include "Building.h"
class Debris: public Building
{
	private:
		float rotationSpeed;
		bool test;
	public:
		TextureImage ObstacleTexture;
		Debris(void);
		~Debris(void);
		void Init(Vector3D pos);
		void Update();
		void Draw();

		float GetRSpeed();
		void SetRspeed(float rs);
};

