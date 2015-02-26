#pragma once
#include "Building.h"
#include "Citizen.h"
class House : public Building
{
	private:
		std::string	Owner;
		float rotationSpeed;
		bool deleted;
	public:
		
		TextureImage HouseTexture;
		House(void);
		~House(void);

		void Init(Vector3D pos);
		void Update();
		void Draw();

		//get
		std::string GetOwner();
		float GetRSpeed();
		bool GetDeleted();
		//set
		void SetOwner(std::string name);
		void SetRspeed(float rs);
		void SetDeleted(bool d);
};

