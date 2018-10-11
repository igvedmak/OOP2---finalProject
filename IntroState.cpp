#include "IntroState.h"

bool IntroState::m_registerit = SpawnManager<States, GameState>::registerit(States::INTRO, [](const sf::Vector2f& pos) -> std::unique_ptr<GameState> { return std::make_unique<IntroState>(pos, Source::instance().getIntroTexture()); });
//----------------------------------------------------------------------------------------------
// constractor
IntroState::IntroState(const sf::Vector2f& coords, const sf::Texture& texture)
	: GameState(coords, texture) {
	m_sprite.setScale(scaleWidth, scaleHeigth);
	const auto& font = Source::instance().getFont();

	m_title = sf::Text{ instroTitle ,font ,80U };
	m_title.setOrigin(m_title.getGlobalBounds().width / 2, m_title.getGlobalBounds().height / 2);
	m_title.setPosition(STATE_WIDTH / 2, 10.f);
	m_title.setFillColor(sf::Color::Yellow);

	m_textInst = sf::Text{ instro ,font ,40U };
	m_textInst.setOrigin(m_textInst.getGlobalBounds().width / 2, m_textInst.getGlobalBounds().height / 2);
	m_textInst.setPosition(setPosScore + m_textInst.getGlobalBounds().width / 2, m_title.getPosition().y + m_textInst.getGlobalBounds().height / 2 + setPosScore * 2);
	m_textInst.setFillColor(sf::Color::White);

	m_textInst2 = sf::Text{ instro2 ,font ,40U };
	m_textInst2.setOrigin(m_textInst.getGlobalBounds().width / 2, m_textInst.getGlobalBounds().height / 2);
	m_textInst2.setPosition(STATE_WIDTH - 600.f, m_title.getPosition().y + m_textInst.getGlobalBounds().height / 2 + setPosScore * 2);
	m_textInst2.setFillColor(sf::Color::White);

	m_main = sf::Text{ ECSscore ,font, 45U };
	m_main.setOrigin(m_main.getGlobalBounds().width / 2, m_main.getGlobalBounds().height / 2);
	m_main.setFillColor(sf::Color::White);
	m_main.setPosition(sf::Vector2f(STATE_WIDTH / 2, STATE_HEIGTH - setPosScore));
}
//----------------------------------------------------------------------------------------------
// display the introduction state 
void IntroState::displayState(GameManager & controller) {
	auto& window = controller.getWindow();
	draw(window);
	window.draw(m_title);
	window.draw(m_textInst);
	window.draw(m_textInst2);
	window.draw(m_main);
}
//----------------------------------------------------------------------------------------------
// handle the event by the user at the introduction state 
void IntroState::handleEvent(GameManager & controller)
{
	sf::Event event = controller.getEvent();
	while (controller.getWindow().pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			controller.popState();           // pop the introduction state at the controller
			return;

		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				controller.changeState(States::MENU); // update the next state at the controller to menu
				break;

			default:
				break;
			}
		}
	}
}