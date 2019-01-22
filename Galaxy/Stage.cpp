#include "Stage.h"

//Save format
//rect rect rect rect pos pos bool bool
//texturerect, position, collider, damage

//Static
dArr<Texture> Stage::backgroundTextures;
int Stage::nrOfBackgrounds;

void Stage::initTextures()
{
	Texture temp;
	std::string tempStr;

	std::ifstream in;

	in.open("Textures/Backgrounds/backgrounds.txt");

	if (in.is_open())
	{
		while (std::getline(in, tempStr))
		{ 
			temp.loadFromFile(tempStr.c_str());
			temp.setRepeated(true);
			Stage::backgroundTextures.add(Texture(temp));
			tempStr.clear();
		}
	}
	else
		std::cout << "COULD NOT OPEN BACKGROUNDS FILE, initTextures() STAGE" << "\n\n";

	in.close();

	Stage::nrOfBackgrounds = Stage::backgroundTextures.size();
}

Stage::Stage(unsigned long sizeX, unsigned long sizeY)
	:stageSizeX(sizeX),
	stageSizeY(sizeY),
	tiles(stageSizeX),
	backgroundTiles(stageSizeX),
	enemySpawners(stageSizeX)
{
	this->dtMultiplier = 62.5f;
	this->fromCol = 0;
	this->toCol = 0;
	this->fromRow = 0;
	this->toRow = 0;
	
	this->scrollSpeed = 2.f;

	for (unsigned i = 0; i < this->stageSizeX; i++) //Col
	{
		this->tiles.push(TileArr<Tile>(stageSizeY), i);
		this->backgroundTiles.push(TileArr<Tile>(stageSizeY), i);
		this->enemySpawners.push(TileArr<EnemySpawner>(stageSizeY), i);
	}

	this->backgroundIndex = 0;
	this->background.setSize(Vector2f(Galaxy::backgroundSize, Galaxy::backgroundSize));
	this->background.setTextureRect(IntRect(0, 0, Galaxy::backgroundSize, Galaxy::backgroundSize));
	this->background.setTexture(&Stage::backgroundTextures[this->backgroundIndex]);
}

Stage::~Stage()
{

}

void Stage::addTile(const Tile tile, unsigned row, unsigned col, int type)
{
	if (row >= this->stageSizeX || col >= this->stageSizeY)
		throw("OUT OF BOUNDS STAGE ADDTILE");

	if (type == tileType::regularTile)
	{
		if (this->tiles[row].isNull(col))
			this->tiles[row].push(tile, col);
		else
			std::cout << "Aleady a tile in that position!" << "\n";
	}
	else if(type == tileType::backgroundTile)
	{
		if (this->backgroundTiles[row].isNull(col))
		{
			this->backgroundTiles[row].push(Tile(tile.getTexRect(), tile.getPos(), false, false), col);
			this->backgroundTiles[row][col].setColor(Color(100, 100, 100, 255));
		}
		else
			std::cout << "Aleady a background tile in that position!" << "\n";
	}
}

void Stage::removeTile(unsigned row, unsigned col, bool background)
{
	if (row >= this->stageSizeX || col >= this->stageSizeY)
		throw("OUT OF BOUNDS STAGE REMOVETILE");

	if (!background)
	{
		if (!this->tiles[row].isNull(col))
			this->tiles[row].remove(col);
		else
			std::cout << "No tile in that position!" << "\n";
	}
	else
	{
		if (!this->backgroundTiles[row].isNull(col))
			this->backgroundTiles[row].remove(col);
		else
			std::cout << "No background tile in that position!" << "\n";
	}
}

void Stage::addEnemySpawner(const EnemySpawner es, unsigned row, unsigned col)
{
	if (this->enemySpawners[row].isNull(col))
	{
		this->enemySpawners[row].push(es, col);
	}
	else
		std::cout << "Aleady a enemyspawner in that position!" << "\n";
}

void Stage::removeEnemySpawner(unsigned row, unsigned col)
{
	if (row >= this->stageSizeX || col >= this->stageSizeY)
		throw("OUT OF BOUNDS STAGE REMOVEENEMYSPAWNER");

	if (!this->enemySpawners[row].isNull(col))
		this->enemySpawners[row].remove(col);
	else
		std::cout << "No enemy spawner in that position!" << "\n";	
}

void Stage::reset(View &view)
{
	//Reset background
	this->backgrounds.clear();
	this->background.setPosition(
		Vector2f(
			view.getCenter().x - view.getSize().x / 2, 
			view.getCenter().y - view.getSize().y / 2
		)
	);
	this->backgrounds.add(this->background);

	//Reset enemyspawners
	for (size_t i = 0; i < this->stageSizeX; i++)
	{
		for (size_t k = 0; k < this->stageSizeY; k++)
		{
			if (!this->enemySpawners[i].isNull(k))
				this->enemySpawners[i][k].setUnused();
		}
	}
}

void Stage::setBackground(const int index, const int width, const int height)
{
	if (index < 0 || index >= Stage::nrOfBackgrounds)
		std::cout << "NO SUCH BACKGROUND IN ARRAY! setBaackground Stage" << "\n\n";
	else
	{
		this->backgroundIndex = index;
		this->background.setSize(Vector2f(width, height));
		this->background.setTextureRect(IntRect(0, 0, width, height));
		this->background.setTexture(&Stage::backgroundTextures[index]);
	}
}

void Stage::saveStage(std::string fileName)
{
	std::ofstream out;

	out.open(fileName.c_str());

	if (out.is_open())
	{
		//Save map size
		out << std::to_string(this->stageSizeX) << " ";
		out << std::to_string(this->stageSizeY) << " ";

		//Save background
		out << this->backgroundIndex 
			<< " " << static_cast<int>(this->background.getGlobalBounds().width) 
			<< " " << static_cast<int>(this->background.getGlobalBounds().height);

		out << "\n"; 

		for (size_t i = 0; i < this->stageSizeX; i++)
		{
			//Regular tiles
			for (size_t k = 0; k < this->stageSizeY; k++)
			{
				if(!this->tiles[i].isNull(k))
					out << this->tiles[i][k].getAsString() << " ";
			}
		}

		out << "\n";

		for (size_t i = 0; i < this->stageSizeX; i++)
		{
			//Regular tiles
			for (size_t k = 0; k < this->stageSizeY; k++)
			{
				if (!this->backgroundTiles[i].isNull(k))
					out << this->backgroundTiles[i][k].getAsString() << " ";
			}
		}

		out << "\n";

		for (size_t i = 0; i < this->stageSizeX; i++)
		{
			//Regular tiles
			for (size_t k = 0; k < this->stageSizeY; k++)
			{
				if (!this->enemySpawners[i].isNull(k))
					out << this->enemySpawners[i][k].getAsString() << " ";
			}
		}
	}
	else
		std::cout << "Could not open map file " << fileName << "\n";

	out.close();
}

bool Stage::loadStage(std::string fileName, View &view)
{
	std::ifstream in;
	bool loadSuccess = false;

	std::stringstream ss;
	std::string line = "";

	//Map
	unsigned sizeX = 0;
	unsigned sizeY = 0;

	//Background
	int bgIndex = 0;
	int bgWidth = 0;
	int bgHeight = 0;

	//Tiles
	int rectLeft = 0;
	int rectTop = 0;
	int rectWidth = 0;
	int rectHeight = 0;
	int gridPosX = 0;
	int gridPosY = 0;
	bool isCollider = 0;
	bool isDamaging = 0;

	//EnemySpawner
	bool randomSpawnPos = 0;
	int maxVelocity = 0;
	int type = 0;
	int levelInterval = 0;
	int nrOfEnemies = 0;

	//Open file
	in.open(fileName);

	if (in.is_open())
	{
		//Load basics
		std::getline(in, line);
		ss.str(line);

		ss >> sizeX >> sizeY >> bgIndex >> bgWidth >> bgHeight;

		this->stageSizeX = sizeX;
		this->stageSizeY = sizeY;

		this->backgroundIndex = bgIndex;
		this->background.setSize(Vector2f(bgWidth, bgHeight));
		this->background.setTextureRect(IntRect(0, 0, bgWidth, bgHeight));
		this->background.setTexture(&Stage::backgroundTextures[bgIndex]);
		this->backgrounds.add(background);
		

		//Enemy Spawners

		line.clear();
		ss.clear();

		std::getline(in, line);
		ss.str(line);

		while (
			ss 
			>> gridPosX 
			>> gridPosY
			>> randomSpawnPos
			>> maxVelocity
			>> type 
			>> levelInterval
			>> nrOfEnemies 
			)
		{
			this->enemySpawners[gridPosX].push(
				EnemySpawner(
					Vector2i(gridPosX, gridPosY),
					randomSpawnPos,
					maxVelocity,
					type,
					levelInterval,
					nrOfEnemies
					),
				gridPosY
			);
		}

		loadSuccess = true;
	}
	else
		loadSuccess = false;

	in.close();

	return loadSuccess;
}

void Stage::updateBackground(const float &dt, View &view)
{
	bool bgRemoved = false;
	for (size_t i = 0; i < this->backgrounds.size() && !bgRemoved; i++)
	{
		this->backgrounds[i].move(this->scrollSpeed * dt * this->dtMultiplier * 0.8f, 0.f);
		
		//When Background top-right is less or equal to view left side
		//Remove background
		if (
			this->backgrounds.size() < 3 
			&& this->backgrounds[i].getPosition().x
			+ this->backgrounds[i].getGlobalBounds().width
			<=
			view.getCenter().x + view.getSize().x / 2
			)
		{
			this->background.setPosition(
				this->backgrounds[i].getPosition().x 
				+ this->backgrounds[i].getGlobalBounds().width, 
				this->background.getPosition().y);

			this->backgrounds.add(background);
		}	
		else if (
			this->backgrounds[i].getPosition().x
			+ this->backgrounds[i].getGlobalBounds().width
			<=
			view.getCenter().x - view.getSize().x / 2
			)
		{
			bgRemoved = true;
		}

		if (bgRemoved)
			this->backgrounds.remove(i);
	}	
}

void Stage::setBackgroundSize(float width, float height)
{
	if (width < Galaxy::backgroundSize || height < Galaxy::backgroundSize)
	{
		std::cout << "ERROR IN setBackGroundSize, WIDTH OR HRIGHT TOO SMALL!" << "\n\n";
		width = Galaxy::backgroundSize;
		height = Galaxy::backgroundSize;
	}

	this->background.setSize(Vector2f(width, height));////////////////
}

void Stage::update(const float &dt, View &view, bool editor)
{
	

	if(!editor)
		this->updateBackground(dt, view);
}

void Stage::draw(RenderTarget &target, View &view, bool editor, Font &font)
{

	//Background
	if (editor)
	{
		target.draw(this->background);
	}
	else
	{
		for (size_t i = 0; i < this->backgrounds.size(); i++)
	  {
			target.draw(this->backgrounds[i]);
		}
	}

}