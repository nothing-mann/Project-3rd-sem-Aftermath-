#include "stdafx.h"
#include "EnemySpawnerTile.h"

EnemySpawnerTile::EnemySpawnerTile(int grid_x, int grid_y, float gridSizef,
	sf::Texture& texture, const sf::IntRect& tex_rect,
	 int enemy_type, int enemy_amount, sf::Int32 enemy_time_to_spawn, float enemy_max_distance)
	:Tile(TileTypes::ENEMYSPAWNER, grid_x, grid_y, gridSizef, texture, tex_rect, false)
{

	this->enemyType = enemy_type;
	this->enemyAmount = enemy_amount;
	this->enemyCounter = 0;
	this->enemySpawnTimer.restart();
	this->enemyTimeToSpawn = enemy_time_to_spawn;
	this->enemyMaxDistance = enemy_max_distance;

	this->spawned = false;
}

EnemySpawnerTile::~EnemySpawnerTile()
{
}

const std::string EnemySpawnerTile::getAsString() const
{
	std::stringstream ss;

	/*
	x, y, z (done in tilemap save)
	type,
	rect x, rect y,
	enemy type,
	enemy amount,
	enemy time to spawn,
	enemy max distance
	*/
	ss << this->type << " " << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " " << this->enemyType << " " << this->enemyAmount << " " << this->enemyTimeToSpawn << " " << this->enemyMaxDistance;
	std::cout << ss.str() << "\n";
	return ss.str();
}

const bool& EnemySpawnerTile::getSpawned() const
{
	return this->spawned;
}

const int& EnemySpawnerTile::getEnemyAmount() const
{
	return this->enemyAmount;
}

const int& EnemySpawnerTile::getEnemyCounter() const
{
	return this->enemyCounter;
}


//Functions

void EnemySpawnerTile::setSpawned(const bool spawned)
{
	this->spawned = spawned;
	this->enemySpawnTimer.restart();
}

const bool EnemySpawnerTile::canSpawn() const
{
	if (this->enemySpawnTimer.getElapsedTime().asSeconds() >= this->enemyTimeToSpawn)
	{
		return true;
	}
	return false;
}

void EnemySpawnerTile::increaseEnemyCounter()
{
	if (this->enemyCounter > this->enemyAmount)
		this->enemyCounter = this->enemyAmount;
	else
		++this->enemyCounter;
}

void EnemySpawnerTile::decreaseEnemyCounter()
{
	if (this->enemyCounter < 0)
		this->enemyCounter = 0;
	else
		--this->enemyCounter;
}

void EnemySpawnerTile::update()
{
	if (this->canSpawn())
		this->spawned = false;

}

void EnemySpawnerTile::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f player_position)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", player_position);
		target.draw(this->shape, shader);
	}
	else
	{
		target.draw(this->shape);
	}
}
