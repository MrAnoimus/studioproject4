#pragma once
#include "vector3D.h"
#include "LoadTGA.h"

class Tile
{
	enum
	{
		GRASS = 0,
		SOIL,
		ROCK,
		BAD,
		LAST
	}TileType;
	private:
		int Type;
		bool Empty;
		Vector3D Position;
		Vector3D Color;
		float Alpha;
		int Size;
	public:
		
		Tile(void);
		~Tile(void);
		TextureImage TileTexture;
		void Init();
		void Update();
		void Draw(float x , float y);
		Vector3D GetCenterPoint(void);
		int GetType();
		bool GetEmpty();
		Vector3D GetPosition();
		Vector3D GetColor();

		void SetType(int type);
		void SetEmpty(bool e);
		void SetPosition(Vector3D pos);
		void SetColor(Vector3D c);

};

