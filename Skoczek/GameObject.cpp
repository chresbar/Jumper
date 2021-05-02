#include "GameObject.h"
#include "TextureMenager.h"

GameObject::GameObject(const char* filename, int objectWidth, int objectHeight, int xPos, int yPos)
{
	texture = TextureMenager::LoadTexture(filename);
	Rec.w = objectWidth;
	Rec.h = objectHeight;
	Rec.x = xPos;
	Rec.y = yPos;
}

GameObject::GameObject(int objectWidth, int objectHeight, int xPos, int yPos): texture(nullptr)
{
	Rec.w = objectWidth;
	Rec.h = objectHeight;
	Rec.x = xPos;
	Rec.y = yPos;
}

GameObject::~GameObject()
{
}

void GameObject::SetTexture(const char* filename)
{
	texture = TextureMenager::LoadTexture(filename);
}

void GameObject::SetPosition(int xPos, int yPos)
{
	Rec.x = xPos;
	Rec.y = yPos;
}

void GameObject::SetSize(int objectWidth, int objectHeight)
{
	Rec.w = objectWidth;
	Rec.h = objectHeight;
}

int GameObject::getWidth() const
{
	return Rec.w;
}

int GameObject::getHeight() const
{
	return Rec.h;
}

int GameObject::getXpos() const
{
	return Rec.x;
}

int GameObject::getYpos() const
{
	return Rec.y;
}

void GameObject::Render() const
{
	SDL_RenderCopy(Game::renderer, texture, nullptr, &Rec);
}

