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
		UNBUILDABLE,
		LAST
	}TileType;
	private:
		bool ModeOn;
		int Type;
		bool Empty;
		bool Selected;
		bool ClickedOn;
		Vector3D Position;
		Vector3D Color;
		float Alpha;
		int Size;
		Building thebuilding; 
		//don't want people to use this two drawing function outside of this class
		void DrawTileOutLine();
		void DrawTile();
	public:
		
		Tile(void);
		~Tile(void);
		TextureImage TileTexture;
		void Init();
		void Update();

		//
		void Draw();

		bool GetModeOn();
		bool IsSelected();
		int GetType();
		bool GetEmpty();
		Vector3D GetPosition();
		Vector3D GetColor();
		bool IsClickedOn();


		void SetModeOn(bool m);
		void SetIsSelected(bool s);
		void SetType(int type);
		void SetEmpty(bool e);
		void SetPosition(Vector3D pos);
		void SetColor(Vector3D c);
		void SetIsClickedOn(bool co);

};

