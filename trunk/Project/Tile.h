#pragma once
#include "vector3D.h"
#include "LoadTGA.h"
#include "Building.h"

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
		bool Selected;
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
		void Draw();
		Vector3D GetCenterPoint(void);

		bool IsSelected();
		int GetType();
		bool GetEmpty();
		Vector3D GetPosition();
		Vector3D GetColor();

		void SetIsSelected(bool s);
		void SetType(int type);
		void SetEmpty(bool e);
		void SetPosition(Vector3D pos);
		void SetColor(Vector3D c);

};

