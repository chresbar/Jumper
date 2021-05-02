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
	SDL_Texture* texture; //wska�nik na obiekt przechowuj�cy jego tekstur� 
	SDL_Rect Rec; //obiekt przechowuj�cy wsp�rz�dne obiektu na ekranie i jego wielko�� 
};

