#pragma once

#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "AttributeComponent.h"

//Entity will be the base class for any type of characters we have
class Entity
{
private:
	void initvariables();

protected:
	sf::Texture* texture; // We will not create individual for all the components because loading texture takes a lot of space and time too
	sf::Sprite sprite;

	HitboxComponent* hitboxComponent;
	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;
	AttributeComponent* attributeComponent;
public:
	Entity();
	virtual ~Entity();

	//Component functions
	void createHitboxComponent(sf::Sprite& sprite, const float offset_x, const float offset_y, float width, float height);
	void setTexture(sf::Texture& texture);
	void createMovementComponent(const float maxVelocity, float acceleration, float deceleration);
	void createAnimationComponent(sf::Texture& texture_sheet);
	void createAttributeComponent(const unsigned level);

	
	//Accessors

	virtual const sf::Vector2f& getPosition() const;
	virtual const sf::Vector2i getGridPosition(const int gridSizeI) const;
	virtual const sf::FloatRect getGlobalBounds() const;
	virtual const sf::FloatRect getNextPositionBounds(const float& dt) const;

	//Modifiers
	virtual void setPosition(const float x, const float y);

	//Functions
	virtual void move(const float dir_x, const float dir_y, const float& dt);
	virtual void stopVelocity();
	virtual void stopVelocityX();
	virtual void stopVelocityY();

	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget& target, const bool show_hitbox) = 0;
};

