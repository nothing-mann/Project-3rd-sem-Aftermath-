#pragma once

enum TileTypes {DEFAULT = 0, DAMAGING, DOODAD};

class Tile
{
private:
protected:
	sf::Sprite shape;
	bool collision;
	short type;
public:
	Tile();
	Tile(int grid_x, int grid_y, float gridSizef, sf::Texture& texture, const sf::IntRect& tex_rect, bool collision = false, short type = TileTypes::DEFAULT);
	virtual ~Tile();
	
	//Accessors
	const short& getType() const; 
	
	
	//Functions
	const bool& getCollision() const;
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;

	const bool intersects(const sf::FloatRect bounds) const;
	const std::string getAsString() const;
	
	void update();
	void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f playerPosition = sf::Vector2f());
};

