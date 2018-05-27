#include "GameManager.h"
#include "MenuState.h"  
#include "PlayState.h"
#include "EndState.h"
GameManager::GameManager()// default constructor which add states of the game and start with menu state
{
	m_window.create(sf::VideoMode(STATE_WIDTH, STATE_HEIGTH), "Captian Claw is Back!", sf::Style::Titlebar);
	m_window.setFramerateLimit(60);
	addState(States::MENU);
}
// the function get state and add it to the screens stack
void GameManager::addState(const States& state)
{
	m_screens.emplace(SpawnManager<States, GameState>::create(state, sf::Vector2f{ 0,0 }));
}

GameManager::~GameManager(){}

// the function get state, pop from the screens stack the last state and push the one that sent
void GameManager::changeState(const States & state)
{
	if (!m_screens.empty())   // if the stack not empty
		popState();           // pop the last state
	addState(state);          // add the new one
}
// the function return pointer of the current state
GameState* GameManager::getState() {
	if (m_screens.empty())
		return nullptr;
	return m_screens.top().get();
}
// the function pops the last state from the stack
void GameManager::popState(){
	m_screens.pop();
}

// this function manage the loop of the winfows using the states we defined
// in order to help the gameManger to manage this game
void GameManager::run(){

	while (m_window.isOpen())
	{
		auto curr = getState();                 // get the current state
		if (curr)
			reloadWindow(curr);
		else
			break;
	}
}

void GameManager::reloadWindow(GameState *curr) {
	m_window.clear();
	curr->updateStage(*this);          // update the current stage
	curr->displayState(*this);         // display the current state
	curr->handleEvent(*this);          // handle event at the the current state
	m_window.display();                // display the update game window
}