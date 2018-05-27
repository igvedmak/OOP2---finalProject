#pragma once
#include "GameState.h"
#include "MenuButton.h"
#include "Source.h"
class MenuState : public GameState
{
public:
	explicit MenuState(const sf::Vector2f& coords, const sf::Texture& texture);
	MenuState(const MenuState&) = delete;//copy c-tor (lvalue)
	MenuState& operator=(const MenuState&) = delete;//assigment operator (lvalue)
	MenuState(MenuState&&) = default;////move copy c-tor (rvalue)
	MenuState& operator=(MenuState&&) = delete;//move assigment operator (rvalue)
	void updateOptions();
	void displayState(GameManager& controller);
	void handleEvent(GameManager& controller);
private:
	size_t m_selected;
	MuteButton m_mute;
	std::array<std::unique_ptr<MenuButton>, NUM_OF_BUTTON> m_options;
	static bool m_registerit;
	// sound for switch buttons
	sf::SoundBuffer bufferSwitch;
	sf::Sound soundSwitch;
};

