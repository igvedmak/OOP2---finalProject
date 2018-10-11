#include "EndState.h"

bool EndState::m_registerit = SpawnManager<States, GameState>::registerit(States::ENDGAME, [](const sf::Vector2f& pos) -> std::unique_ptr<GameState> { return std::make_unique<EndState>(pos, Source::instance().getEndTexture()); });

// constractor
EndState::EndState(const sf::Vector2f& coords, const sf::Texture& texture)
	:GameState(coords, texture)
{
	m_sprite.setScale(2.25f, 1.6f);
	m_text1 = sf::Text(Quotation, Source::instance().getFont(), 100U);
	m_text1.setPosition(STATE_WIDTH / 2, STATE_HEIGTH / 2);
	m_text1.setOutlineThickness(3);
	m_text1.setOutlineColor(sf::Color::Yellow);
	m_text2 = sf::Text(Enter, Source::instance().getFont(), 40U);
	m_text2.setPosition(0, STATE_HEIGTH - 50);
}
//----------------------------------------------------------------------------------------------
// the function get the controller and display the end state when the user finished the levels
// successfully or not
void EndState::displayState(GameManager & controller)
{
	auto& window = controller.getWindow();
	draw(window);
	std::string to_print;
	if (Source::instance().endOfLevels()) // if the user finished all the levels
		to_print = win;
	else
		to_print = GameOver;

	m_text1.setString(to_print);
	m_text1.setOrigin(m_text1.getGlobalBounds().width / 2, m_text1.getGlobalBounds().height / 2);
	window.draw(m_text1);
	window.draw(m_text2);
}
//----------------------------------------------------------------------------------------------
// the function get the controller and handle the event that happend by the user
void EndState::handleEvent(GameManager & controller)
{
	sf::Event event = controller.getEvent();      // get the event user from the wait for events main loop 
	while (controller.getWindow().pollEvent(event))  // get the game window
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			controller.popState();           // the user closed the state. pop the state from stack at the controller
			return;

		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Return:
				controller.setPlayerName();           // the user ask to enter his name
				controller.saveScore();               // save the score from the current game 
				controller.changeState(States::MENU); // back to menu state 
				Source::instance().getMenuMusic().play(); // menu music
				break;

			default:
				break;
			}
		}
	}
}
