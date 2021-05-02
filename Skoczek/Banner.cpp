#include "Banner.h"

Banner::Banner(BannerType type, int width, int length) : GameObject(width / 2, length / 6, width / 4 , length / 2.4)
{
	switch (type)
	{
	case Banner::BannerType::Lose:
		this->SetTexture(loseSprite);
		break;
	case Banner::BannerType::Win:
		this->SetTexture(winSprite);
		break;
	default:
		break;
	}
}

bool Banner::wasBannerClicked(int xPos, int yPos) const
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
