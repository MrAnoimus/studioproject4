#pragma once
#include "LoadTGA.h"
#include "vector3D.h"

class Building
{
	private:
		int Size;
		Vector3D Position;
	public:
		TextureImage Building1;
		Building(void);
		~Building(void);

		void Init(Vector3D pos);
		void Update();
		void Draw();

		Vector3D GetPosition();
		void SetPosition(Vector3D pos);
};

