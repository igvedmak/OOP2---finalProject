#include "RankState.h"

bool RankState::m_registerit = SpawnManager<States, GameState>::registerit(States::SCORES, [](const sf::Vector2f& pos) -> std::unique_ptr<GameState> { return std::make_unique<RankState>(pos, Source::instance().getScoreTexture()); });
// Default constructor which use base class in order to use the same window and
// the same statemanager pointer
RankState::RankState(const sf::Vector2f& coords, const sf::Texture& texture)
	:GameState(coords, texture)
{
	m_sprite.setScale(scaleWidth, scaleHeigth);
	const auto& font = Source::instance().getFont();

	m_title = sf::Text{bestScore ,font ,80U };
	m_title.setOrigin(m_title.getGlobalBounds().width / 2, m_title.getGlobalBounds().height / 2);
	m_title.setPosition(STATE_WIDTH / 2, 10.f);
	m_title.setFillColor(sf::Color::Yellow);

	m_player = sf::Text{ playerScore ,font, 50U };
	m_player.setFillColor(sf::Color::White);
	m_player.setOrigin(m_player.getGlobalBounds().width / 2, m_player.getGlobalBounds().height / 2);
	m_player.setPosition(setPosScore + m_player.getGlobalBounds().width / 2, m_title.getPosition().y + m_player.getGlobalBounds().height + setPosScore);

	m_scores = sf::Text{scorePlayer ,font, 50U };
	m_scores.setFillColor(sf::Color::White);
	m_scores.setOrigin(m_scores.getGlobalBounds().width / 2, m_scores.getGlobalBounds().height / 2);
	m_scores.setPosition(STATE_WIDTH - 200.f, m_title.getPosition().y + m_scores.getGlobalBounds().height + setPosScore);

	m_main = sf::Text{ECSscore ,font, 45U };
	m_main.setOrigin(m_main.getGlobalBounds().width / 2, m_main.getGlobalBounds().height / 2);
	m_main.setFillColor(sf::Color::White);
	m_main.setPosition(sf::Vector2f(STATE_WIDTH / 2, STATE_HEIGTH - setPosScore));

}
// Function which draw this states members
void RankState::displayState(GameManager& controller) {
	auto& window = controller.getWindow();
	draw(window);
	window.draw(m_title);
	window.draw(m_player);
	window.draw(m_scores);
	window.draw(m_main);

	controller.displayScoreTable();
}

// Function which draw this states members
void RankState::handleEvent(GameManager& controller) {
	sf::Event event = controller.getEvent();
	while (controller.getWindow().pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			controller.popState();
			return;

		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				controller.changeState(States::MENU);
				break;

			default:
				break;
			}
		}
	}
}