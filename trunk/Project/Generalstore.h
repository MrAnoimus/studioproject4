#pragma once
#include "Building.h"

class Generalstore : public Building
{
	private:
		float rotationSpeed;

	public:
		TextureImage GStoreTexture;

		Generalstore(void);
		~Generalstore(void);

		void Init(Vector3D pos);
		void Update();
		void Draw();

		float GetRSpeed();
		void SetRspeed(float rs);
		
};

