#pragma once
#include <exception>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include <stack>
#include <map>
#include <array>
#include "SFML/Audio.hpp"
#include <cassert>
#include <stdexcept>
#include <string>
#ifdef _DEBUG
#pragma comment(lib, "sfml-main-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-audio-d.lib")
#elif defined(NDEBUG)
#pragma comment(lib, "sfml-main.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-graphics.lib")
#pragma comment(lib, "sfml-audio.lib")
#else
#error "Unrecognized configuration!"
#endif
const unsigned int STATE_WIDTH = 1700;
const unsigned int STATE_HEIGTH = 1000;
// menustate
const sf::IntRect IN = sf::IntRect{ 299, 0, 299, 84 };
const sf::IntRect OUT = sf::IntRect{ 0, 0, 299, 84 };
const sf::Vector2f pos{ 1000, 530 }; 
#define START "start"
#define RANK "ScoreBoard"
#define INSTRA "Instructions"
#define EXITMENU "Exit"
const int addIndexY = 100;
const sf::Vector2f mutePos{ 1650,50 };
//-----------------------------------------------------------------------------
const std::string UNKNOW = "unknow error..";
#define CANTOPEN  "cannot open audio file!"
#define CANTLOAD "load failed"
const std::string ER = "ERROR: ";
const std::string Button = "img/button.png";
const std::string Mute = "img/mute.png";
const std::string BG = "img/BackgroundMenu.png";
const std::string Font = "ALGER.ttf";
const std::string switchBuffer = "sounds/Switch.ogg";
const std::string switchSound = "sounds/Switch.ogg";
const std::string musicBG = "sounds/Menu.ogg";
enum States { PLAY, SCORES, INTRO, EXIT, MENU, ENDGAME, PAUSE };
//---------------------- Constants Section ---------------------------------
enum Direction { Right, Left, Down, Up, Stay, Space }; // saves the directions
const unsigned int STATIC_SIZE = 16;
const unsigned int BREAKABLE_X = 0;
const unsigned int BREAKABLE_Y = 0;
const unsigned int LIFE_COL = 1;
const unsigned int BULLET_ADD = 3;