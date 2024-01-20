#include "Entity.h"


Entity::Entity(Texture2D texture, Rectangle source, Rectangle destination, Vector2 position, float rotation) 
	: texture(texture), source(source), destination(destination), position(position), rotation(rotation)
{

}

Entity::Entity()
{
	//default
}

void Entity::Draw() {
	DrawTexturePro(texture, source, destination, position, rotation, WHITE);
}