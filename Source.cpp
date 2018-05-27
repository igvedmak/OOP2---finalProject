#include "Source.h"
//c-tor: builds the game from all the textures/music files/fonts and from the levels file
Source::Source() {
	try {
		if (!m_textButton.loadFromFile(Button) || !m_muteButtom.loadFromFile(Mute)
			|| !m_textureMenu.loadFromFile(BG) || !m_font.loadFromFile(Font))
			throw std::exception(CANTLOAD);
		if (!m_menusound.openFromFile(musicBG) || !m_menuswitch.openFromFile(switchSound))
			throw std::exception(CANTOPEN);
	}
	catch (...) {
		exit(0);
	}

	m_menusound.setVolume(30);         // reduce the volume
	m_menusound.setLoop(true);
	m_menusound.play();
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
