#pragma once
#include "GameState.h"
#include "Command.h"
#include "CollisionManager.h"
#include "Obstacle.h"
#include "Tile.h"
#include "Wall.h"
#include "AssetIDs.h"
#include "AssetManager.h"
#include "StatusBar.h"
#include "Pickup.h"
#include "Enemy.h"
#include <cmath>
class PlayState : public GameState
{
public:
	explicit PlayState(const sf::Vector2f& coords, const sf::Texture& texture);
	PlayState(const PlayState&) = delete;//copy c-tor (lvalue)
	PlayState& operator=(const PlayState&) = delete; //assignment operator (lvalue)
	PlayState(PlayState&&) = default;//move copy c-tor (rvalue)
	PlayState& operator=(PlayState&&) = delete;//move assigment operator (rvalue)

	void displayState(GameManager& controller);
	void handleEvent(GameManager& controller);
	void handlePlayer(size_t x, const Direction& dir); // handler player
	void handleEnemy(); // handler enemy
	void updateStage(GameManager& controller);
	void setEnterPressed(bool flag) { m_enterPressed = flag; }
	// updating the data of the status bar
	void updateLifePre();
	void decLifePreByEnemy();
	void updateScoreWithToken();
	void updateScoreWithCoin();
	void decLifeSpkies();
	void setMultimapDIr();	// sets the dir
	void setMultimapDIrE();	// sets the dir
	void drawStatusBar(sf::RenderWindow& window);	// draw the status bar
	void initLevelObjects(); // for the all objects in the game
	void initPlayerAfterDeath();

private:
	float getDest(sf::Vector2f enemy, sf::Vector2f player);
	bool isChanged = true;
	Direction m_currDir = Right; //last direction recorded
	static bool m_registerit;
	bool loadedOnce = false;
	float time = 0;
	sf::Vector2f last_pos;
	sf::Vector2f position;
	sf::Vector2f playerPosition;
	// pointer for the movment
	std::weak_ptr<Command>m_currCommand;
	std::weak_ptr<Command>m_currCommandEnemy;
	std::shared_ptr<Command>m_leftCommand;
	std::shared_ptr<Command>m_leftReleaseCommand;
	std::shared_ptr<Command>m_rightReleaseCommand;
	std::shared_ptr<Command>m_rightCommand;
	std::shared_ptr<Command>m_defCommand;
	std::shared_ptr<Command>m_upCommad;
	std::shared_ptr<Command>m_upReleaseCommand;
	std::shared_ptr<Command>m_downReleaseCommand;
	std::shared_ptr<Command>m_AltCommand;
	std::shared_ptr<Command>m_downCommad;
	std::shared_ptr<Command>m_attackCommad;
	std::shared_ptr<Command>m_jumpCommad;
	std::shared_ptr<Command>m_deathCommad;
	unsigned m_life; // lifes
	unsigned m_score; // player score in the game
	unsigned m_lifePre; // % life
	bool m_enterPressed;
	bool m_isPaused; // the pause button
	bool m_finish; // helps to know when the game have been finished
	bool m_gun;
	bool whileJump = false; // for the player's jump
	int coun = 0;
	sf::Text m_pauseText; // texture for the pause
	std::shared_ptr<Player> m_Player;
	std::vector<std::shared_ptr<Enemy>> m_Enemy;
	std::pair<unsigned, std::string> m_ScoreRecord; // score
	std::vector<std::shared_ptr<StaticObject>> m_obs; //levl static objects
	std::vector<std::shared_ptr<Pickup>> m_pickables;
	sf::View view; //view for camera
	std::map<Direction, std::shared_ptr<Command>> m_Director; //map for direction
	std::map<Direction, std::shared_ptr<Command>> m_DirectorE; //map for direction
	std::map<char, sf::Vector2f> m_mapping; // pointer for static objects
	Direction m_lastDir; //last direction recorded
	sf::View m_view; //for vamera
	StatusBar m_bar; // status bar
	std::multimap<bool, std::unique_ptr<Treasure>>m_currLvlTreasure;
	void initMappingPointer(); // pointer for mapping
	sf::Vector2f setPos(char obj, size_t row, size_t col); // set the object by the pos

	//clock for delay
	sf::Clock clock;
	float delta;
};
