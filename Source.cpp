#include "Source.h"

//c-tor: builds the game from all the textures/music files/fonts and from the levels file
Source::Source() :m_textures(), m_fonts() {
	//load text files
	std::ifstream levelFile(LEVELTXT);
	std::fstream scoresFile(SCORETXT);

	//load texture files
	m_textures.load(Textures::ID::Background, BG);
	m_textures.load(Textures::ID::Button, Button);
	m_textures.load(Textures::ID::Score, BG2);
	m_textures.load(Textures::ID::Mute, Mute);
	m_textures.load(Textures::ID::Instro, BG2);
	m_textures.load(Textures::ID::Player, captainClawSprites);
	m_textures.load(Textures::ID::Tile, tileSprite);
	m_textures.load(Textures::ID::Tile1, tile1Sprite);
	m_textures.load(Textures::ID::Tile2, tile2Sprite);
	m_textures.load(Textures::ID::Tile3, tile3Sprite);
	m_textures.load(Textures::ID::SmallTile, smallTileSprite);
	m_textures.load(Textures::ID::Wall, wallSprite);
	m_textures.load(Textures::ID::lvl1object, lvl1Obj);
	m_textures.load(Textures::ID::Bar, BarState);
	m_textures.load(Textures::ID::Lamp, lampSprite);
	m_textures.load(Textures::ID::Spkie, spkieSprite);
	m_textures.load(Textures::ID::Spkie1, spkie1Sprite);
	m_textures.load(Textures::ID::Spkie2, spkie2Sprite);
	m_textures.load(Textures::ID::Spkie3, spkie3Sprite);
	m_textures.load(Textures::ID::Spkie4, spkie4Sprite);
	m_textures.load(Textures::ID::Spkie5, spkie5Sprite);
	m_textures.load(Textures::ID::Ladder, ladderSprite);
	m_textures.load(Textures::ID::Ladder2, ladder2Sprite);
	m_textures.load(Textures::ID::Heal, healSprite);
	m_textures.load(Textures::ID::Coin, coinSprite);
	m_textures.load(Textures::ID::redcrown, redcrown);
	m_textures.load(Textures::ID::wall1, Wall1);
	m_textures.load(Textures::ID::wall2, Wall2);
	m_textures.load(Textures::ID::wall3, Wall3);
	m_textures.load(Textures::ID::wall4, Wall4);
	m_textures.load(Textures::ID::wall5, Wall5);
	m_textures.load(Textures::ID::wall6, Wall6);
	m_textures.load(Textures::ID::wall7, Wall7);
	m_textures.load(Textures::ID::wall8, Wall8);
	m_textures.load(Textures::ID::wall9, Wall9);
	m_textures.load(Textures::ID::Empty, empty);
	m_textures.load(Textures::ID::Fire, empty); // to do
	m_textures.load(Textures::ID::EnemySmart, EnemySprites);
	//load music files
	m_musics.open(Musics::ID::Background, musicBG);
	m_musics.open(Musics::ID::SwitchBuffer, switchSound);
	m_musics.open(Musics::ID::MusicLvl1, BGMusiclvl1);
	m_musics.open(Musics::ID::swordSwich, swordSwish);
	m_musics.open(Musics::ID::uppercut, uppercut);
	m_musics.open(Musics::ID::foodwait, foodwait);
	m_musics.open(Musics::ID::Shot, shot);
	m_musics.open(Musics::ID::Walk, walk);
	m_musics.open(Musics::ID::CoinPick, CoinPick);
	m_musics.open(Musics::ID::Pickup, pickup);
	m_musics.open(Musics::ID::Click, Click);
	m_musics.open(Musics::ID::HealPick, healpick);
	m_musics.open(Musics::ID::Death, death);
	m_musics.open(Musics::ID::EnemyDeath, Enemydeath);
	m_musics.open(Musics::ID::EnemyHit, Enemyhit);
	//load fonts
	m_fonts.load(Fonts::ID::Main, Font);

	try {
		if (!m_lvl1BG.loadFromFile(BGlvl1))
			throw std::exception(CANTLOAD);

		if (!scoresFile || !levelFile)
			throw std::exception(CANTOPEN);
	}

	catch (...) {
		exit(0);
	}
	m_musics.get(Musics::ID::Background).setVolume(loudMusic);         // reduce the volume
	m_musics.get(Musics::ID::Background).setLoop(true);
	m_musics.get(Musics::ID::Background).play();        // reduce the volume

	m_levelBack.emplace_back(m_lvl1BG);
	for (auto& i : m_levelBack)
	{
		i.setSmooth(true);
		i.setRepeated(true);
	}

	loadScoreTable(scoresFile);

	unsigned row, col, counter = 0;
	std::string line;
	std::vector<std::string> mat;
	levelFile >> row;
	levelFile >> col;
	getline(levelFile, line);
	while (!levelFile.eof()) {
		counter++;
		mat.clear();
		for (size_t i = 0; i < row; i++)
		{
			getline(levelFile, line);
			mat.push_back(line);
		}
		m_levels.push_back(mat);
		levelFile >> row;
		getline(levelFile, line);
	}
	levelFile.close();
}
// Function which load the txt of the scores
void Source::loadScoreTable(std::fstream &scoresFile) {
	std::string name;
	int score;
	while (scoresFile >> name >> score)
		m_playerScores.emplace(score, name);

	scoresFile.clear();
	scoresFile.close();
}
// Function which define static inst at first time and return the exist object at other times
Source & Source::instance()
{
	static Source inst; // build only at first time
	return inst;		// at other time return the object
}

// Function which return the curr texture according to string she get as key
sf::Texture Source::getTexture(std::string str) const
{
	auto it = m_textureMap.find(str);  // search in the map the str
	return it->second;				   // return the value of this key
}
Source::~Source(){}
