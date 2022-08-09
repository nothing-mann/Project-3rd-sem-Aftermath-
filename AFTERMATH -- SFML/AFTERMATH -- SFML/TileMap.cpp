#include "stdafx.h"
#include "TileMap.h"

void TileMap::clear()
{
	for (size_t x = 0; x < this->maxSizeWorldGrid.x; x++)
	{
		for (size_t y = 0; y < this->maxSizeWorldGrid.y; y++)
		{
			for (size_t z = 0; z < this->layers; z++)
			{
				delete this->map[x][y][z];
				this->map[x][y][z] = NULL;
			}
			this->map[x][y].clear();
		}
		this->map[x].clear();
	}
	this->map.clear();

	//std::cout << this->map.size() << "\n";
}

TileMap::TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file)
{
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSizeWorldGrid.x = width;
	this->maxSizeWorldGrid.y = height;
	this->maxSizeWorldF.x = static_cast<float>(width) * gridSize;
	this->maxSizeWorldF.y = static_cast<float>(height) * gridSize;
	this->layers = 1;
	this->textureFile = texture_file;

	this->map.resize(this->maxSizeWorldGrid.x, std::vector<std::vector<Tile*> >());
	for (size_t x = 0; x < this->maxSizeWorldGrid.x; x++)
	{

		for (size_t y = 0; y < this->maxSizeWorldGrid.y; y++)
		{
			this->map[x].resize(this->maxSizeWorldGrid.y, std::vector<Tile*>());

			for (size_t z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, nullptr);
			}
		}
	}
	this->tileTextureSheet.loadFromFile("Resources/Images/Tiles/tilesheet1.png");

	this->collisionBox.setSize(sf::Vector2f(gridSize, gridSize));
	this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
	this->collisionBox.setOutlineColor(sf::Color::Red);
	this->collisionBox.setOutlineThickness(1.f);
}


TileMap::~TileMap()
{
	this->clear();
}


//Accessors
const sf::Texture* TileMap::getTileSheet() const
{
	return &this->tileTextureSheet;
}

//Functions
void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& tex_rect, const bool& collision, const short& type)
{
	//take three indices from the mouse position in the grid and add a tile to that position if the internal tilemap array allows it
	if (x < this->maxSizeWorldGrid.x && x >= 0 && y < this->maxSizeWorldGrid.y && y >= 0 && z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] == nullptr) //Adds something if it is actually null
		{
			//Ok to add tile
			this->map[x][y][z] = new Tile(x , y , this->gridSizeF, this->tileTextureSheet, tex_rect, collision, type);
			std::cout << "DEBUG: ADDED TILE!" << "\n";
		}

	}
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
	//take three indices from the mouse position in the grid and remove a tile to that position if the internal tilemap array allows it
	if (x < this->maxSizeWorldGrid.x && x >= 0 && y < this->maxSizeWorldGrid.y && y >= 0 && z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] != nullptr) //Adds something if it is actually null
		{
			//Ok to remove tile
			delete this->map[x][y][z];
			this->map[x][y][z] = nullptr;   //Very IMPORTANT to Set this to NULL POINTER
			std::cout << "Debug: Removed a tile" << "\n";
		}

	}
}

void TileMap::saveToFile(const std::string file_name)
{
	/* saves the entire tilemap to a textfile.
	Format:
	Basic:
	Size x y
	gridSize
	layers
	texturefile

	All tiles:
	gridPos x y layer, Texture rect x y, collision, type
	*/
	std::ofstream out_file;
	out_file.open(file_name);
	if (out_file.is_open())
	{
		out_file << this->maxSizeWorldGrid.x << " " << this->maxSizeWorldGrid.y << "\n"
			<< this->gridSizeU << "\n"
			<< this->layers << "\n"
			<< this->textureFile << "\n";
		for (size_t x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			for (size_t y = 0; y < this->maxSizeWorldGrid.y; y++)
			{
				for (size_t z = 0; z < this->layers; z++)
				{
					
					if(this->map[x][y][z])
						out_file << x << " " << y << " " << z << " " << this->map[x][y][z]->getAsString() << " "; //MAKE SURE THE LAST SPACE IS NOT SAVED
				}
			}
		}
		
	}
	else
	{
		std::cout << "Error::tilemap::could not save to filename:" << file_name << "\n";
	}
	out_file.close();
}

void TileMap::loadFromFile(const std::string file_name)
{
	std::ifstream in_file;
	in_file.open(file_name);
	if (in_file.is_open())
	{
		sf::Vector2u size;
		unsigned gridSizeU = 0;
		unsigned layers = 0;
		std::string texture_file = "";
		unsigned x = 0;
		unsigned y = 0;
		unsigned z = 0;
		unsigned trX = 0;
		unsigned trY = 0;
		bool collision = false;
		short type = 0;

		//Basics
		in_file >> size.x >> size.y >> gridSizeU >> layers >> texture_file;
		

		//Tiles
		this->gridSizeF = static_cast<float>(gridSizeU);
		this->gridSizeU = gridSizeU;
		this->maxSizeWorldGrid.x = size.x;
		this->maxSizeWorldGrid.y = size.y;
		this->layers = layers;
		this->textureFile = texture_file;

		this->clear();

		this->map.resize(this->maxSizeWorldGrid.x, std::vector<std::vector<Tile*> >());
		for (size_t x = 0; x < this->maxSizeWorldGrid.x; x++)
		{

			for (size_t y = 0; y < this->maxSizeWorldGrid.y; y++)
			{
				this->map[x].resize(this->maxSizeWorldGrid.y, std::vector<Tile*>());

				for (size_t z = 0; z < this->layers; z++)
				{
					this->map[x][y].resize(this->layers, nullptr);
				}
			}
		}
		this->tileTextureSheet.loadFromFile(texture_file);

		//Load all tiles
		while (in_file >> x >> y >> z >> trX >> trY >> collision >> type)
		{
			this->map[x][y][z] = new Tile(x, y, this->gridSizeF, this->tileTextureSheet, sf::IntRect(trX, trY, this->gridSizeU, this->gridSizeU), collision, type);
		}
	}
	else
	{
		std::cout << "Error::tilemap::could not load from file:: filename:" << file_name << "\n";
	}
	in_file.close();
}

void TileMap::updateCollision(Entity* entity)
{
	//WORLD BOUNDS
	if (entity->getPosition().x < 0.f)
		entity->setPosition(0.f, entity->getPosition().y);
	else if (entity->getPosition().x > this->maxSizeWorldF.x)
		entity->setPosition(this->maxSizeWorldF.x, entity->getPosition().y);

	if (entity->getPosition().y < 0.f)
		entity->setPosition( entity->getPosition().x, 0.f);
	else if (entity->getPosition().y > this->maxSizeWorldF.y)
		entity->setPosition( entity->getPosition().x, this->maxSizeWorldF.y );

	//TILES
}

void TileMap::update()
{
}

void TileMap::render(sf::RenderTarget& target, Entity* entity)
{
	for (auto& x : this->map)
	{
		for (auto& y : x)
		{
			for (auto* z : y)
			{
				if (z != nullptr)
				{
					z->render(target);
					if (z->getCollision())
					{
						this->collisionBox.setPosition(z->getPosition());
						target.draw(this->collisionBox);
					}
				}
			}
		}
	}
}
