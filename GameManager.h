#pragma once
#include "Constants.h"
#include "GameState.h"
#include "SpawnManager.h"
#include "Source.h"

class GameState;

class GameManager
{
public:
	explicit GameManager();
	GameManager(const GameManager&) = delete;//copy c-tor (lvalue)
	GameManager& operator=(const GameManager&) = delete;//assigment operator (lvalue)
	GameManager(GameManager&&) = delete;//move copy c-tor (rvalue)
	GameManager& operator=(GameManager&&) = delete;//move assigment operator (rvalue)
	~GameManager();
	void run();
	void saveScore();
	void displayScoreTable();
	sf::RenderWindow& getWindow() { return m_window; }
	sf::Event& getEvent() { return m_event; }
	void addState(const States& state);
	void changeState(const States& state);
	GameState* getState();
	void popState();
	void saveScoresToFile();
	const std::string& getPlayerName() const { return m_ScoreRecord.second; }
	void setPlayerName();
	void setPlayerScore(int score);

private:
	std::multimap<unsigned, std::string, std::greater<unsigned>> m_scoresTable;
	std::pair<unsigned, std::string> m_ScoreRecord;
	sf::Text m_playerNameText, m_playerScoreText;
	void reloadWindow(GameState *curr);
	std::stack<std::unique_ptr<GameState>> m_screens;
	sf::RenderWindow m_window;
	sf::Event m_event;
	int i;
	bool first;
};

