#pragma once
class CResource
{

private:
	static int NumOfFood;
	static float NumOfMoney;
	static int NumOfManPower;
	static int NumOfCitizen;
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

