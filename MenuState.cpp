#include "MenuState.h"

bool MenuState::m_registerit = SpawnManager<States, GameState>::registerit(States::MENU, [](const sf::Vector2f& pos) -> std::unique_ptr<GameState> { return std::make_unique<MenuState>(pos, Source::instance().getSplashTexture()); });

// c-tor
MenuState::MenuState(const sf::Vector2f& coords, const sf::Texture& texture)
	:GameState(coords, texture), m_selected(0), m_mute(MuteButton(mutePos, Source::instance().getMuteTexture()))
{
	m_sprite.setScale(1.66f, 1.8f);
	if (!bufferSwitch.loadFromFile(switchBuffer))
		throw std::exception(CANTOPEN);
	soundSwitch.setBuffer(bufferSwitch);
	const auto& temp = Source::instance().getButtonTexture();
	m_options[0] = std::move(std::make_unique<PlayButton>(pos, temp, START));
	m_options[1] = std::move(std::make_unique<ScoreButton>(sf::Vector2f{ pos.x,pos.y + addIndexY }, temp, RANK));
	m_options[2] = std::move(std::make_unique<InstructionButton>(sf::Vector2f{ pos.x,pos.y + 2*addIndexY }, temp, INSTRA));
	m_options[3] = std::move(std::make_unique<ExitButton>(sf::Vector2f{ pos.x,pos.y + 3*addIndexY }, temp, EXITMENU));
	updateOptions();
}

// display the menu state and menu bottons
void MenuState::displayState(GameManager& controller)
{
	sf::RenderWindow& window = controller.getWindow();
	window.draw(m_sprite);
	m_mute.draw(window);
	for (const auto& i : m_options)
	{
		i->draw(window);
		window.draw(i->getText());
	}
}
// handle the event by the user choises at the menu state 
void MenuState::handleEvent(GameManager& controller){
	sf::Event event = controller.getEvent();
	while (controller.getWindow().pollEvent(event)) {
		switch (event.type)
		{
		case sf::Event::Closed:
			//controller.saveScoresToFile();        // save all the current scores at the map to the file
			controller.popState();                // pop the menu state from stack at the controller
			return;

		case sf::Event::KeyPressed:
			switch (event.key.code)	{
			case sf::Keyboard::Up:
				soundSwitch.play();
				m_selected = m_selected > 0 ? m_selected - 1 :    // selected button of menu
					m_options.size() - 1;
				updateOptions();             // show different the chosen button
				break;

			case sf::Keyboard::Down:
				soundSwitch.play();
				m_selected = (m_selected + 1) % m_options.size();
				updateOptions();
				break;

			case sf::Keyboard::P:        // mute the menu music
				soundSwitch.play();
				m_mute.updateChoice();
				if (m_mute.getOnOff())
					Source::instance().getMenuMusic().stop();
				else 
					Source::instance().getMenuMusic().play();
				break;

			case sf::Keyboard::Return:
				switch (m_selected)
				{
				case PLAY:            // play state
					//Resource::instance().initCurrentLevel();
					if (!m_mute.getOnOff())
						Source::instance().getStageMusic().play();
					//Source::instance().setMuted(m_mute.getOnOff());
					Source::instance().getMenuMusic().stop();
					controller.changeState(PLAY);
					break;
				case SCORES:          // ranking state
					controller.changeState(SCORES);
					break;
				case INTRO:           // intro state
					controller.changeState(INTRO);
					break;
				case EXIT:           // exit state
					/*controller.saveScoresToFile();*/
					controller.popState();
					break;
				default:
					break;
				}
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}

// the function update the options (buttons) of the menu
void MenuState::updateOptions()
{
	for (auto& option : m_options)
	{
		option->updateTextColor(sf::Color::White);
		option->UpdateTexure(OUT);
	}
	m_options[m_selected]->updateTextColor(sf::Color::Yellow);
	m_options[m_selected]->UpdateTexure(IN);
}

