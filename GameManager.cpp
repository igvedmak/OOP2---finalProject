#include "GameManager.h"
#include "MenuState.h"  
#include "PlayState.h"
#include "EndState.h"

sf::Uint32 FIRST_UNICODE_LETTERS = 31,
LAST_UNICODE_LETTERS = 27,
UNICODE_DELETE = 8,
MAX_LETTER = 127;

// default constructor which add states of the game and start with menu states
GameManager::GameManager() 
	:m_scoresTable(Source::instance().getPlayerScores())
{
	m_window.create(sf::VideoMode(STATE_WIDTH, STATE_HEIGTH), Claw, sf::Style::Titlebar);
	//m_window.setFramerateLimit(SFL);
	m_playerNameText.setFillColor(sf::Color::White);
	m_playerNameText.setFont(Source::instance().getFont());
	m_playerScoreText.setFillColor(sf::Color::White);
	m_playerScoreText.setFont(Source::instance().getFont());
	addState(States::MENU);
}
// the function get state and add it to the screens stack
void GameManager::addState(const States& state){
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
// the function open new window to ask the user his name and save it at the scores table (map) 
void GameManager::setPlayerName()
{
	sf::RenderWindow window(sf::VideoMode(SAVE_WIDTH, SAVE_HEIGTH), PlayerName, sf::Style::Titlebar);
	window.setFramerateLimit(60);
	sf::Event event;
	sf::Text text(EnterName, Source::instance().getFont(), 30U);
	sf::Text name(Quotation, Source::instance().getFont(), 30U);
	text.setPosition(0, 0);
	name.setPosition(0, 50);
	std::string string;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Return:
					m_ScoreRecord.second = (string.size() == 0) ? User : string;
					window.close();
					break;
				}
				break;
			case sf::Event::TextEntered:
				if (event.text.unicode == UNICODE_DELETE && string.size() > 0)   // delete key
				{
					string.pop_back();           // update string
					name.setString(string);      // update text to display
				}
				// letter keys
				else if (event.text.unicode > FIRST_UNICODE_LETTERS && event.text.unicode < MAX_LETTER)
				{
					if (string.size() < MAX_STR_LEN)
					{
						string.push_back(static_cast<char>(event.text.unicode));     // update string
						name.setString(string);                         // update text to display
					}
				}
				break;
			}
		}
		window.clear();
		window.draw(text);        // draw the text "Please Enter Your Name"
		window.draw(name);        // draw the name letters of every step 
		window.display();
	}
}
// this function manage the loop of the winfows using the states we defined
// in order to help the gameManger to manage this game
void GameManager::run(){

	while (m_window.isOpen())
	{
		if (auto curr = getState())// get the current state
			reloadWindow(curr); //reload all the needs to current window
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

// the function display the best scores of the game 
void GameManager::displayScoreTable()
{
	i = 1;
	first = true;
	for (auto it = m_scoresTable.begin(); it != m_scoresTable.end(); ++it)
	{
		// place and set all the names of players 
		m_playerNameText.setString(it->second);
		m_playerNameText.setPosition(sf::Vector2f(PLAYER_SUBTITLE_POS.x,
			PLAYER_SUBTITLE_POS.y + setPosScore * (i + 1)));
		m_playerNameText.setFillColor(sf::Color::White);

		// place and set all the scores of players 
		m_playerScoreText.setString(std::to_string(it->first));
		m_playerScoreText.setPosition(sf::Vector2f(SCORE_SUBTITLE_POS.x,
			SCORE_SUBTITLE_POS.y + setPosScore * (i + 1)));
		m_playerScoreText.setFillColor(sf::Color::White);

		// if its the name and score of the current player
		if (it->second == m_ScoreRecord.second && it->first == m_ScoreRecord.first && first)
		{
			m_playerNameText.setFillColor(sf::Color::Red);   // score and name of current user 
			m_playerScoreText.setFillColor(sf::Color::Red);  // paint in red
			first = false;
		}

		m_window.draw(m_playerScoreText);
		m_window.draw(m_playerNameText);
		++i;
	}
}
// the function get int number and update the score to it
void GameManager::setPlayerScore(int score){
	m_ScoreRecord.first = score;
}
// the function save the user score and name of the current game to map of scores
void GameManager::saveScore()
{
	if (m_scoresTable.size() > HIGHSCORES_COUNTER)
		m_scoresTable.erase(std::prev(m_scoresTable.end()));
	m_scoresTable.emplace(m_ScoreRecord.first, m_ScoreRecord.second);
}
// the function save the score table to file at the text format when the main window of the game closes
void GameManager::saveScoresToFile()
{
	std::ofstream scoresFile(SCORETXT);

	for (auto it = m_scoresTable.begin(); it != m_scoresTable.end(); ++it)
		scoresFile << (it->second + Quotation + std::to_string(it->first) + Quotation);

	scoresFile.close();
}