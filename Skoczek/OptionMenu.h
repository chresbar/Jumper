#pragma once
#include "Button.h"
#include "GameObject.h"
#include <utility>

class OptionMenu
{
public:
	OptionMenu(int windowWidth, int windowHeight);
	Button::ButtonTypes WhichButtonWasClicked(int xPos, int yPos);
	void Render() const;
	static const std::pair<int, int> resA;
	static const std::pair<int, int> resB;
	static const std::pair<int, int> resC;
private:
	GameObject* option;
	const char* resolutionBannerTexture = "assets/resolution.png";
	GameObject* selectResolution;
	const char* selectResolutionTexture = "assets/select_resolution.png";
	Button* resolutionA;
	Button* resolutionB;
	Button* resolutionC;
	Button* back;
	std::pair<int, int> resolution;
};

