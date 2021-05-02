#include "OptionMenu.h"

const std::pair<int, int> OptionMenu::resA = std::make_pair(1152, 872);
const std::pair<int, int> OptionMenu::resB = std::make_pair(1024, 768);
const std::pair<int, int> OptionMenu::resC = std::make_pair(800, 600);

OptionMenu::OptionMenu(int windowWidth, int windowHeight): resolution(std::make_pair(windowWidth, windowHeight))
{
	int elementHight = windowHeight / 6;
	int elementYpos = windowHeight / 12;
	option = new GameObject(resolutionBannerTexture, windowHeight, elementHight, windowWidth/8, elementYpos);
	elementYpos += elementHight;
	resolutionA = new Button(Button::ButtonTypes::ResolutionA, windowHeight/2, elementHight, windowWidth/3.2, elementYpos);
	if (resA.first == windowWidth && resA.second == windowHeight)
		selectResolution = new GameObject(selectResolutionTexture, windowHeight / 2, elementHight, windowWidth / 3.2, elementYpos);
	elementYpos += elementHight;
	resolutionB = new Button(Button::ButtonTypes::ResolutionB, windowHeight / 2, elementHight, windowWidth / 3.2, elementYpos);
	if (resB.first == windowWidth && resB.second == windowHeight)
		selectResolution = new GameObject(selectResolutionTexture, windowHeight / 2, elementHight, windowWidth / 3.2, elementYpos);
	elementYpos += elementHight;
	resolutionC = new Button(Button::ButtonTypes::ResolutionC, windowHeight / 2, elementHight, windowWidth / 3.2, elementYpos);
	if (resC.first == windowWidth && resC.second == windowHeight)
		selectResolution = new GameObject(selectResolutionTexture, windowHeight / 2, elementHight, windowWidth / 3.2, elementYpos);
	elementYpos += elementHight;
	back = new Button(Button::ButtonTypes::Back, windowWidth / 4, elementHight, windowHeight/2, elementYpos);
}

Button::ButtonTypes OptionMenu::WhichButtonWasClicked(int xPos, int yPos)
{
	if (resolutionA->IsButtonClicked(xPos, yPos))
		return Button::ButtonTypes(7);
	else if (resolutionB->IsButtonClicked(xPos, yPos))
		return Button::ButtonTypes(8);
	else if (resolutionC->IsButtonClicked(xPos, yPos))
		return Button::ButtonTypes(9);
	else if (back->IsButtonClicked(xPos, yPos))
		return Button::ButtonTypes(6);
	else
		return Button::ButtonTypes(5);
}

void OptionMenu::Render() const
{
	option->Render();
	resolutionA->Render();
	resolutionB->Render();
	resolutionC->Render();
	back->Render();
	selectResolution->Render();
}
