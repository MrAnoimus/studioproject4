#pragma once

#include "LoadTGA.h"
#include "FreeType.h"

class Choices
{
public:
	Choices(void);
	~Choices(void);

	void Draw(int type);
	int GetNumOfChoice();
	void SetNumOfChoice(int NumOfChoice);

	//texture for choices
	TextureImage ChoiceBG[5];
	TextureImage Choice1[5];
	TextureImage Choice2[5];

	void SetPopup(bool Up);
	void DrawInGameText(std::string Text);
	bool popup;
	//fonts
	freetype::font_data our_font;
private:
	int NumOfChoice;
	bool choice1;
	bool choice2;
	bool selected;

	

};

