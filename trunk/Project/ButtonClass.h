#ifndef BUTTON_CLASS_H
#define BUTTON_CLASS_H

#include "vector3D.h"
#include "Definitions.h"
#include "LoadTGA.h"

#pragma once
class ButtonClass
{
private:
	Vector3D areaposX, areaposY, scrResolution, renderposX, renderposY; 

public:
	ButtonClass(void);
	~ButtonClass(void);

	bool buttonhover, buttonclicked, buttonsfx;

	void Set(int x1, int x2, int y1, int y2);
	Vector3D getRegionPosX() { return this->areaposX; }
	Vector3D getRegionPosY() { return this->areaposY; }
	Vector3D getRenderPosX() { return this->renderposX; }
	Vector3D getRenderPosY() { return this->renderposY; }

	void UpdateMouseMove(int x, int y);

	short id;

	TextureImage button[2];
	void Render();


};

#endif
