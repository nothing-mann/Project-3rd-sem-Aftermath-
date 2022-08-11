#include "stdafx.h"
#include "Player.h"
//Initializer functions
void Player::initVariables()
{
	this->attacking = false;
}

void Player::initComponents()
{

}
//Constructors Destructors
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();
	

	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 10.f, 5.f, 44.f, 54.f);
	this->createMovementComponent(200.f, 1500.f, 900.f);
	this->createAnimationComponent( texture_sheet);
	this->createAttributeComponent(1);

	this->animationComponent->addAnimation("IDLE", 15.f, 0, 0, 8, 0, 64, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 1.f, 0, 1, 3, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 1.f, 4, 1, 7, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 1.f, 8, 1, 11, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_UP", 1.f, 12, 1, 15, 1, 64, 64);
	this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 1, 2, 64, 64);

}

Player::~Player()
{

}


//Accesors
AttributeComponent* Player::getAttributeComponent()
{
	return this->attributeComponent;
}




//Functions
void Player::loseHP(const int hp)
{
	this->attributeComponent->hp -= hp;
	if (this->attributeComponent->hp < 0)
		this->attributeComponent->hp = 0;
}

void Player::gainHP(const int hp)
{
	this->attributeComponent->hp += hp;
	if (this->attributeComponent->hp > this->attributeComponent->hpMax)
		this->attributeComponent->hp = this->attributeComponent->hpMax;
}

void Player::loseEXP(const int exp)
{
	this->attributeComponent->exp -= exp;
	if (this->attributeComponent->exp < 0)
		this->attributeComponent->exp = 0;
}

void Player::gainEXP(const int exp)
{
	this->attributeComponent->gainExp(exp);
}


void Player::updateAttack() //Change it to attack once it is done
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		//this->attacking = true;

	}
}

void Player::updateAnimation(const float& dt)
{
	if (this->attacking)
	{
		//Set origin depending on direction
		if (this->sprite.getScale().x > 0.f) //Facing right
		{
			this->sprite.setOrigin(0.f, -4.f);
		}
		else //Facing left
		{
			this->sprite.setOrigin(30.f, -4.f);
		}
		//Animate and check for animation and
		if (this->animationComponent->play("ATTACK", dt, true)) //When attacking feature is added set the priority animation true to the attack animation
		{
			this->attacking = false;

			if (this->sprite.getScale().x > 0.f) //Facing right
			{
				this->sprite.setOrigin(0.f, 0.f);
			}
			else //Facing left
			{
				this->sprite.setOrigin(30.f, 0.f);
			}
		}
		//if (this->animationComponent->isDone("JUMP"))

	}
	if (this->movementComponent->getState(IDLE))
		this->animationComponent->play("IDLE", dt);
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		
		this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
}
void Player::update(const float& dt)
{
	//if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	//	this->attributeComponent->gainExp(20);
	////this->attributeComponent->update();
	//system("cls");
	//std::cout << this->attributeComponent->debugPrint() << "\n";

	this->movementComponent->update(dt);

	this->updateAttack();

	this->updateAnimation(dt);

	this->hitboxComponent->update();
}

void Player::render(sf::RenderTarget& target, const bool show_hitbox)
{
	target.draw(this->sprite);

	if(show_hitbox)
		this->hitboxComponent->render(target);
}
