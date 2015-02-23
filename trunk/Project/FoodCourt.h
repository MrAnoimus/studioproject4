#pragma once
#include "Building.h"

class FoodCourt : public Building
{
	private:
		float rotationSpeed;
	public:
		TextureImage FoodCourtTexture;
		FoodCourt(void);
		~FoodCourt(void);

		void Init(Vector3D pos);
		void Update();
		void DrawBuildingbar();
		void Draw();
};

