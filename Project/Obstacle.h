#pragma once
#include "Building.h"

class Obstacle : public Building
{
	private:
		float rotationSpeed;
		bool test;
		bool diff;
	public:
		TextureImage ObstacleTexture;
		TextureImage debrisTexture;
		Obstacle(void);
		~Obstacle(void);
		void Init(Vector3D pos);
		void Update();
		void Draw();

		bool GetDiff();
		float GetRSpeed();

		void SetDiff(bool d);
		void SetRspeed(float rs);


};