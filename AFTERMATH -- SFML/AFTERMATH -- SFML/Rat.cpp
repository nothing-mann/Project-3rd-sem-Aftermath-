#include "stdafx.h"
#include "Rat.h"


//Initializer functions
void Rat::initVariables()
{
}

void Rat::initAnimations()
{
	this->animationComponent->addAnimation("IDLE", 2.5f, 0, 0, 3, 0, 60, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 5.f, 0, 1, 3, 1, 60, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 5.f, 0, 2, 3, 2, 60, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 5.f, 0, 3, 3, 3, 60, 64);
	this->animationComponent->addAnimation("WALK_UP", 5.f, 0, 4, 3, 4, 60, 64);
	this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 1, 2, 60, 64);

}

void Rat::initGUI()
{
	this->hpBar.setFillColor(sf::Color::Red);
	this->hpBar.setSize(sf::Vector2f(60.f, 10.f));
	this->hpBar.setPosition(sf::Vector2f(this->sprite.getPosition()));
}

void Rat::initAI()
{
	
}

//Constructor/ destructor
Rat::Rat(float x, float y, sf::Texture& texture_sheet, EnemySpawnerTile& enemy_spawner_tile, Entity& player)
	:Enemy(enemy_spawner_tile)
{
	this->initVariables();
	this->initGUI();
	this->createHitboxComponent(this->sprite, 13.f, 39.f, 30.f, 30.f);
	this->createMovementComponent(50.f, 1600.f, 1000.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(1);

	this->generateAttributes(this->attributeComponent->level);
	this->setPosition(x, y);

	this->initAnimations();

	this->follow = new AIFollow(*this, player);

}

Rat::~Rat()
{
	delete this->follow;
}


//Functions
void Rat::updateAnimation(const float& dt)
{

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

void Rat::update(const float& dt, sf::Vector2f& mouse_pos_view)
{
	//if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	//	this->attributeComponent->gainExp(20);
	////this->attributeComponent->update();
	//system("cls");
	//std::cout << this->attributeComponent->debugPrint() << "\n";

	this->movementComponent->update(dt);


	//Updates the gui......Remove this
	this->hpBar.setSize(sf::Vector2f(60.f * (static_cast<float>(this->attributeComponent->hp)/this->attributeComponent->hpMax), 10.f));
	this->hpBar.setPosition(sf::Vector2f(this->sprite.getPosition()));
	//this->updateAttack();

	this->updateAnimation(dt);

	this->hitboxComponent->update();

	this->follow->update(dt);
}

void Rat::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", light_position);
		target.draw(this->sprite, shader);

	}
	else
	{
		target.draw(this->sprite);

	}
	target.draw(this->hpBar);


	if (show_hitbox)
		this->hitboxComponent->render(target);
}

