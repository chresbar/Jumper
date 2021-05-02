#include "Button.h"

Button::Button(ButtonTypes buttonType, int objectWidth, int objectHeight, int xPos, int yPos): GameObject(objectWidth, objectHeight, xPos, yPos)
{
	switch (buttonType)
	{
	case Button::ButtonTypes::Start:
		this->SetTexture(startButton);
		break;
	case Button::ButtonTypes::Option:
		this->SetTexture(optionButton);
		break;
	case Button::ButtonTypes::Quit:
		this->SetTexture(quitButton);
		break;
	case Button::ButtonTypes::White:
		this->SetTexture(whiteButton);
		break;
	case Button::ButtonTypes::Black:
		this->SetTexture(blackButton);
		break;
	case Button::ButtonTypes::Back:
		this->SetTexture(backButton);
		break;
	case Button::ButtonTypes::ResolutionA:
		this->SetTexture(resolutionA);
		break;
	case Button::ButtonTypes::ResolutionB:
		this->SetTexture(resolutionB);
		break;
	case Button::ButtonTypes::ResolutionC:
		this->SetTexture(resolutionC);
		break;
	default:
		break;
	}
}

Button::~Button()
{
}

bool Button::IsButtonClicked(int xPos, int yPos)
{
	if (xPos >= Rec.x && xPos < Rec.x + Rec.w)
	{
		if (yPos >= Rec.y && yPos < Rec.y + Rec.h)
			return true;
		else
			return false;
	}	
	else
		return false;
}
