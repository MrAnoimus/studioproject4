#pragma once
#include "vector3D.h"
#include "TextureImage.h"

class GaugeBar
{
	private:
		Vector3D Position;
		float Percentage;
		float Height;
		Vector3D Color;
		bool Active;
	public:
		TextureImage outline;
		GaugeBar(void);
		~GaugeBar(void);
		void init(float r,float g,float b);
		void draw();
		void update(Vector3D pos,float p,int posy);
		//get
		Vector3D getPos();
		Vector3D getColor();
		float getPercentage();
		bool getActive();
		//set
		void setPos(Vector3D newpos);
		void setColor(Vector3D Color);
		void setPercentage(float Percentage);
};

