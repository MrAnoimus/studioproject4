#pragma once
#include "vector3D.h"
#include "LoadTGA.h"
class GaugeBar
{
	private:
		Vector3D Position;
		float Percentage;
		float Height;
		Vector3D Color;
		bool Active;
		bool done;
	public:
		GaugeBar(void);
		~GaugeBar(void);
		void init(float r,float g,float b,Vector3D pos);
		void draw();
		void update();
		//get
		bool getdone();
		Vector3D getPos();
		Vector3D getColor();
		float getPercentage();
		bool getActive();
		//set
		void setDone(bool d);
		void setActive(bool at);
		void setPos(Vector3D newpos);
		void setColor(Vector3D Color);
		void setPercentage(float Percentage);
};

