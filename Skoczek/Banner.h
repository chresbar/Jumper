#pragma once
#include "GameObject.h"
class Banner: public GameObject
{
public:
	enum class BannerType {Lose, Win};
	Banner(BannerType type, int width, int length);
	bool wasBannerClicked(int xPos, int yPos) const;
private:
	const char* loseSprite = "assets/lose.png";
	const char* winSprite = "assets/win.png";
};

