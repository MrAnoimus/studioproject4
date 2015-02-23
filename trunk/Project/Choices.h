#pragma once

#include "LoadTGA.h"
#include "FreeType.h"

class Choices
{
public:
	Choices(void);
	~Choices(void);

	void Draw();
	int GetNumOfChoice();
	void SetNumOfChoice(int NumOfChoice);

	//texture for choices
	TextureImage ChoiceBG;
	TextureImage CheapTree;
	TextureImage ExpensiveTree;

	void SetPopup(bool Up);
	void DrawInGameText(std::string Text);

	//fonts
	freetype::font_data our_font;
private:
	int NumOfChoice;
	bool choice1;
	bool choice2;
	bool selected;

	bool popup;

};

