#pragma once
class CResource
{

private:
	int NumOfFood;
	float NumOfMoney;
	int NumOfManPower;
	int NumOfCitizen;
public:

	int GetFood();
	float GetMoney();
	int GetManPower();
	int GetCitizen();

	void SetFood(int NewFood);
	void SetMoney(float NewMoney);
	void SetManpower(int NewManPower);
	void SetCitizen(int NewCitizen);

	CResource(void);
	~CResource(void);
};

