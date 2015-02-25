#pragma once
#include "vector3D.h"
#include "LoadTGA.h"
#include "House.h"
#include "FoodCourt.h"
#include "Generalstore.h"
#include "Obstacle.h"

class Tile
{
	enum
	{
		HOUSE = 0,
		FCOURT,
		GSTORE,
		UNBUILDABLE,
		LAST
	}TileType;
	private:
		GaugeBar myGaugeBar;
		bool startbuild;
		bool startdestory;
		bool ModeOn;
		int Type;
		bool Empty;
		bool Selected;
		bool ClickedOn;
		Vector3D Position;
		Vector3D Color;
		float Alpha;
		int Size;
		//building stuff
		int Btype;
		
		//don't want people to use this two drawing function outside of this class
		void DrawTileOutLine();
		void DrawTile();
	public:
		House myHouse;
		FoodCourt myFCourt;
		Generalstore myGstore;
		Obstacle myObstacle;

		Tile(void);
		~Tile(void);
		TextureImage TileTexture;
		void Init();
		void Update();

		//
		void Draw();

		//Getter
		int GetBtype();
		bool GetModeOn();
		bool IsSelected();
		int GetType();
		bool GetEmpty();
		Vector3D GetPosition();
		Vector3D GetColor();
		bool IsClickedOn();

		//Setter
		void SetSize(int sz);
		void SetBtype(int t);
		void SetModeOn(bool m);
		void SetIsSelected(bool s);
		void SetType(int type);
		void SetEmpty(bool e);
		void SetPosition(Vector3D pos);
		void SetColor(Vector3D c);
		void SetIsClickedOn(bool co);


};

