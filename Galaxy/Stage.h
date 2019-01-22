#pragma once

#include"TileArr.h"

class Stage
{
private:
	float dtMultiplier;
	unsigned long stageSizeX;
	unsigned long stageSizeY;
	TileArr <TileArr<Tile> > tiles;
	TileArr <TileArr<Tile> > backgroundTiles;
	TileArr <TileArr<EnemySpawner> > enemySpawners;

	float scrollSpeed;

	int backgroundIndex;
	RectangleShape background;
	dArr<RectangleShape> backgrounds;

	//Optimization
	int fromCol, toCol;
	int fromRow, toRow;

public:
	Stage(unsigned long sizeX, unsigned long sizeY);
	virtual ~Stage();

	//Accessors
	inline int getSizeX()const { return this->stageSizeX; }
	inline int getSizeY()const { return this->stageSizeY; }
	inline float getScrollSpeed()const { return this->scrollSpeed; }
	TileArr< TileArr<Tile> >& getTiles() { return this->tiles; }
	TileArr< TileArr<EnemySpawner> >& getEnemySpawners() { return this->enemySpawners; }

	//Modifiers
	void setBackground(const int index, const int width, const int height);
	void setBackgroundSize(float width, float height);
	
	//Functions
	void addTile(const Tile tile, unsigned row, unsigned col, int type);
	void removeTile(unsigned row, unsigned col, bool background);
	void addEnemySpawner(const EnemySpawner es, unsigned row, unsigned col);
	void removeEnemySpawner(unsigned row, unsigned col);
	void reset(View &view);

	void saveStage(std::string fileName);
	bool loadStage(std::string fileName, View &view);

	void updateBackground(const float &dt, View &view);
	void update(const float &dt, View &view, bool editor);

	void draw(RenderTarget &target, View &view, bool editor, Font &font);

	//Static
	static dArr<Texture> backgroundTextures;
	static int nrOfBackgrounds;

	static void initTextures();

	enum tileType { regularTile = 0, backgroundTile, enemySpawner };

};

