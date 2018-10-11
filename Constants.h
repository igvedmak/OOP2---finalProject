#pragma once
#include <fstream>
#include <exception>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include <stack>
#include <map>
#include <set>
#include <array>
#include "SFML/Audio.hpp"
#include <cassert>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <typeinfo>
#include <typeindex>
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

//---------------------- Window ---------------------------------
const unsigned int STATE_WIDTH = 1700;
const unsigned int STATE_HEIGTH = 1000;
const unsigned int SAVE_WIDTH = 400;
const unsigned int SAVE_HEIGTH = 300;
const std::string Claw = "Captian Claw is Back!";
const int SFL = 15;
const float scaleWidth = 1.66f;
const float scaleHeigth = 1.33f;

//---------------------- MenuState ---------------------------------
const sf::IntRect IN = sf::IntRect{ 299, 0, 299, 84 };
const sf::IntRect OUT = sf::IntRect{ 0, 0, 299, 84 };
const sf::Vector2f pos{ 1000, 530 };
#define START "Start"
#define RANK "ScoreBoard"
#define INSTRA "Instructions"
#define EXITMENU "Exit"
const int addIndexY = 100;
const sf::Vector2f mutePos{ 1650,50 };

//---------------------------- Source -------------------------------------
const std::string UNKNOW = "unknow error..";
const std::string FileFail = "Failed to load ";
#define CANTOPEN  "cannot open audio file!"
#define CANTLOAD "load failed"
#define CANTOPENFILE "cannot open file!"
const std::string ER = "ERROR: ";
const std::string Button = "img/button.png";
const std::string Mute = "img/mute.png";
const std::string BG = "img/BackgroundMenu.png";
const std::string BG2 = "img/BackgroundScore.png";
const std::string Font = "ALGER.ttf";
const std::string switchBuffer = "sounds/Switch.ogg";
const std::string switchSound = "sounds/Switch.ogg";
const std::string BGMusiclvl1 = "sounds/MusicLvl1.ogg";
const std::string musicBG = "sounds/Menu.ogg";
const std::string captainClawSprites = "img/CaptainClaw.png";
const std::string EnemySprites = "img/Enemy1.png";
const std::string BGlvl1 = "img/lvl1BG.jpg";
const std::string tileSprite = "img/Tile1.png";
const std::string tile1Sprite = "img/Tile2.png";
const std::string tile2Sprite = "img/Tile3.png";
const std::string tile3Sprite = "img/Tile4.png";
const std::string smallTileSprite = "img/smallTile.png";
const std::string wallSprite = "img/Wall.png";
const std::string lvl1Obj = "img/lvl1objects.png";
const std::string BarState = "img/statusbar.png";
const std::string levelStatus = "Level: 1";
const std::string scoreStatus = "Score: 0";
const std::string lifeStatus = "Life: 4";
const std::string lifePreStatus = "Life %: 100";
const std::string levelStatus2 = "Level: ";
const std::string scoreStatus2 = "Score: ";
const std::string lifeStatus2 = "Life: ";
const std::string lifePreStatus2 = "Life %: ";
const std::string lampSprite = "img/lamp.png";
const std::string spkieSprite = "img/s.png";
const std::string spkie1Sprite = "img/s1.png";
const std::string spkie2Sprite = "img/s2.png";
const std::string spkie3Sprite = "img/s3.png";
const std::string spkie4Sprite = "img/s4.png";
const std::string spkie5Sprite = "img/s5.png";
const std::string ladderSprite = "img/ladder.png";
const std::string ladder2Sprite = "img/ladder2.png";
const std::string healSprite = "img/heal.png";
const std::string coinSprite = "img/Coins.png";
const std::string tokenSprite = "img/token.png";
const std::string Wall1 = "img/1.png";
const std::string Wall2 = "img/2.png";
const std::string Wall3 = "img/3.png";
const std::string Wall4 = "img/4.png";
const std::string Wall5 = "img/5.png";
const std::string Wall6 = "img/6.png";
const std::string Wall7 = "img/7.png";
const std::string Wall8 = "img/8.png";
const std::string Wall9 = "img/9.png";
const std::string empty = "img/empty.png";
const std::string coins = "img/onecoin.png";
const std::string redcrown = "img/redcrown.png";
const int MAX_LEVELS = 1;
enum States { PLAY, SCORES, INTRO, EXIT, MENU, ENDGAME, PAUSE };
const float loudMusic = 30;

//---------------------- Constants Section ---------------------------------
enum Direction { Right, Left, Down, Up, Stay, Space, R, LControl, LeftRelease
,RightRelease, UpRelease, DownRelease, LAlt, Death}; // saves the directions

//---------------------- ScoreBoard ---------------------------------
const int HIGHSCORES_COUNTER = 10;
const int MAX_STR_LEN = 15;
const sf::Vector2f SCORE_POS = sf::Vector2f{ 0, 0 };
const sf::Vector2f PLAYER_SUBTITLE_POS = sf::Vector2f{ 50.f, 100.f };
const sf::Vector2f SCORE_SUBTITLE_POS = sf::Vector2f{ STATE_WIDTH - 200.f, 100.f };
const std::string bestScore = "BEST SCORES";
const std::string playerScore = "PLAYER";
const std::string scorePlayer = "SCORE";
const std::string ECSscore = "Press esc to back";
const std::string SCORETXT = "scores.txt";
const std::string LEVELTXT = "levels.txt";
const std::string Enter = "Press enter to go back to main menu";
const std::string win = "Y  O  U     W  O  N!!!";
const std::string GameOver = "G  A  M  E     O  V  E  R!";
const std::string Quotation= " ";
const float setPosScore = 50.f;

//---------------------- SavePlayer ------------------------------------------
const std::string PlayerName = "Player Name";
const std::string EnterName = "Please Enter Your Name:";
const std::string User = "USER";

//---------------------- Instro ------------------------------------------
const std::string instro = "							left arrow\n\
							right arrow\n\
							up arrow\n\
							down arrow\n\
							spacebar\n\
							ctrl or r\n\
							z\n\
							alt\n\
							shift\n\
							q\n\
							w\n\
							e";
const std::string instro2 = "left move\n\
right move\n\
up move\n\
down arrow\n\
jump\n\
hand attack(sword, punch, kick)\n\
pickup & throw\n\
projectile attack(pistal, magic, TNT)\n\
toggle projectile weapon\n\
pistol shot\n\
magic shot\n\
TNT throw";
const std::string instroTitle = "Instruction";

//---------------------- PlayState ---------------------------------
struct JumpData {
	float jumpF = 400.f;
	float gravityAcceleration = 9.8f;
};
const int MAX_LIFEPRE = 100;
const int MAX_LIFE = 4;
const int
WALL_WIDTH = 64,
WALL_HEIGHT = 64;
const int MAX_LIFE_PRE = 100;
const int FRAME_LIMIT_CLAW_ATTACK = 3;
const int FRAME_LIMIT_CLAW_SHOOT = 5;
const int FRAME_LIMIT_CLAW_RUN = 9;
const int FRAME_LIMIT_CLAW_STAY = 7;
const int FRAME_LIMIT_CLAW_CLIMB = 11;
const int FRAME_LIMIT_CLAW_JUMP = 6;
const int FRAME_LIMIT_ENEMY_STAY = 4;
const int FRAME_LIMIT_ENEMY_WALK = 10;
const int FRAME_LIMIT_ENEMY_ATTACK = 4;
const int CLAW_RUN = 0;
const int CLAW_DEATH = 11;
const int CLAW_STAY = 1;
const int CLAW_ATTACK = 5;
const int CLAW_CLIMB = 2;
const int CLAW_JUMP = 3;
const int CLAW_SHOT = 8;
const int CLAW_FALL = 4;
const int CLAW_PUNCH = 6;
const int CLAW_KICK = 7;
const int CLAW_WIDTH = 205;
const int CLAW_HEIGHT = 205;
const int ENEMY_WIDTH = 205;
const int ENEMY_HEIGHT = 205;
const sf::Vector2f PLAYER_START_POS = sf::Vector2f{ STATE_WIDTH / 2.f, STATE_HEIGTH - 300.f };
const std::string Pause = "PAUSED";
const std::string blankImg = "img/blank.png";
enum eObstacles { WALL, TILE, SPIKES, LAVA, BREAKABLETILE }; // Obstacles
const float PLAYER_VELOCITY = 12.f;
const float ENEMY_VELOCITY = 9.f;

//---------------------- Obstacle ---------------------------------
const char TILE_C = 'T',
WALL_C = 'W',
BREAKABLETILE_C = 'B',
SPIKES_C = 'S',
SPIKES1_C = 's',
SPIKES2_C = 'a',
SPIKES3_C = 'b',
SPIKES4_C = 'c',
SPIKES5_C = 'd',
EMPTY_C = '_',
LADDER_C = 'L',
LADDER2_C = 'l',
COIN_C = 'C',
REDCROWN_C = 'Z',
HEAL_C = 'H',
WALL1_C = '0',
WALL2_C = '1',
WALL3_C = '2',
WALL4_C = '3',
WALL5_C = '4',
WALL6_C = '5',
WALL7_C = '6',
WALL8_C = '7',
WALL9_C = 'g',
TILE1_C = '8',
TILE3_C = '9',
TILE2_C = 't',
LAMP_C = 'e',
SMALLTILE_C = 'f',
PLAYER_C = 'P',
ENEMYDUMP_C = 'E',
ENEMYSMART_C = 'G',
FIRE_C = 'F',
EMPRYHELP_C = '.';
//------------------------- Player sounds --------------------------
const sf::String swordSwish = "sounds/SWORDSWISH.ogg";
const sf::String uppercut = "sounds/UPPERCUT1.ogg";
const sf::String foodwait = "sounds/1110038.wav";
const sf::String shot = "sounds/GUNSHOT.wav";
const sf::String walk = "sounds/walk.ogg";
const sf::String pickup = "sounds/PICKUP1.wav";
const sf::String CoinPick = "sounds/COIN.wav";
const sf::String Click = "sounds/CLICK.wav";
const sf::String healpick = "sounds/MILK.wav";
const sf::String death = "sounds/DEATH.wav";
const sf::String Enemydeath = "sounds/ENEMYDEATH.wav";
const sf::String Enemyhit = "sounds/ENEMYHIT.wav";
// ------------------------- Swords& treasure ---------------------------
enum TREASURE_TYPE { REDCROWN, COIN};
enum SPECIALSWORD {REGULARSWORD, FIRESWORD, LIGHTSWORD, ICESWORT};
//--------------------------- Enemies ---------------------------------
enum Enemies { smart, dumb};

enum Input {
	PRESS_UP,
	RELEASE_UP,
	PRESS_DOWN,
	RELEASE_DOWN,
	PRESS_LEFT,
	RELEASE_LEFT,
	PRESS_RIGHT,
	RELEASE_RIGHT,
	PRESS_R,
	PRESS_ALT,
	NONE,
	PRESS_SPACE,
	RELEASE_SPACE,
	DEATH
};

//----------------------------Bar State --------------
const int tokenScore = 100,
coinscore = 10,
healadd = 10,
lifeDec = 5;