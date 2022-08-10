#include "stdafx.h"
#include "Entity.h"

void Entity::initvariables()
{

	this->texture = nullptr;
	this->movementComponent = nullptr;
	this->animationComponent = nullptr;
	this->hitboxComponent = nullptr;
}

Entity::Entity()
{
	this->initvariables();

}

Entity::~Entity()
{
	delete this->movementComponent;
	delete this->animationComponent;
	delete this->hitboxComponent;
}
void Entity::createHitboxComponent(sf::Sprite& sprite, const float offset_x, const float offset_y, float width, float height)
{
	this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}
//Component functions
void Entity::setTexture(sf::Texture& texture)
{
	this->texture = &texture;
	this->sprite.setTexture(texture);

}

void Entity::createMovementComponent(const float maxVelocity, float acceleration, float deceleration)
{
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent( sf::Texture& texture_sheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}


//Functions


const sf::Vector2f& Entity::getPosition() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getPosition();
	return this->sprite.getPosition();
}

const sf::Vector2u Entity::getGridPosition(const unsigned gridSizeU) const
{
	if (this->hitboxComponent)
		return sf::Vector2u(
			static_cast<unsigned>(this->hitboxComponent->getPosition().x)/gridSizeU,
			static_cast<unsigned>(this->hitboxComponent->getPosition().y )/ gridSizeU
		);
	return sf::Vector2u(
		static_cast<unsigned>(this->sprite.getPosition().x) / gridSizeU,
		static_cast<unsigned>(this->sprite.getPosition().y) / gridSizeU
	);
}

const sf::FloatRect Entity::getGlobalBounds() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getGlobalBounds();
	return this->sprite.getGlobalBounds();
}

void Entity::setPosition(const float x, const float y)
{
	if(this->hitboxComponent)
		return this->hitboxComponent->setPosition(x, y);
	else
		this->sprite.setPosition(x,y);
}

void Entity::move(const float dir_x, const float dir_y,const float& dt)
{
	if (this->movementComponent)
		this->movementComponent->move(dir_x, dir_y,dt); //Sets velocity
}

void Entity::stopVelocity()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocity();
}

void Entity::stopVelocityX()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocityX();
}

void Entity::stopVelocityY()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocityY();
}

void Entity::update(const float& dt)
{

}

void Entity::render(sf::RenderTarget& target)
{

}