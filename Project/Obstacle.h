#pragma once
#include "Building.h"

class Obstacle : public Building
{
	private:
		float rotationSpeed;
		bool test;
	public:
		TextureImage ObstacleTexture;
		Obstacle(void);
		~Obstacle(void);
		void Init(Vector3D pos);
		void Update();
		void Draw();

		float GetRSpeed();
		void SetRspeed(float rs);
};