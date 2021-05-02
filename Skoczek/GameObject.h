#pragma once
#include <SDL.h>

class GameObject
{
public:
	GameObject(const char* filename, int objectWidth, int objectHeight, int xPos, int yPos);
	GameObject(int objectWidth, int objectHeight, int xPos, int yPos);
	~GameObject();
	void SetTexture(const char* filename);
	void SetPosition(int xPos, int yPos);
	void SetSize(int objectWidth, int objectHeight);
	int getWidth() const;
	int getHeight() const;
	int getXpos() const;
	int getYpos() const;
	virtual void Render() const;
protected:
	SDL_Texture* texture; //wskaŸnik na obiekt przechowuj¹cy jego teksturê 
	SDL_Rect Rec; //obiekt przechowuj¹cy wspó³rzêdne obiektu na ekranie i jego wielkoœæ 
};

