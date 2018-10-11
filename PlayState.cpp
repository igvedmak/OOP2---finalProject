#include "PlayState.h"
#include "GameClock.h"
#include <experimental/vector>
bool PlayState::m_registerit = SpawnManager<States, GameState>::registerit(States::PLAY, [](const sf::Vector2f& pos) -> std::unique_ptr<GameState> { return std::make_unique<PlayState>(pos, Source::instance().getLvlTexture()); });

//----------------------------------------------------------------------------------------------
// the function get the controller and handle the event that the user make at this state
void PlayState::handleEvent(GameManager& controller)
{
	sf::Event& event = controller.getEvent();
	sf::RenderWindow& window = controller.getWindow();

	// if the player failed the level or finish all the levels succesfully
	if (m_life == 0 || Source::instance().endOfLevels())
	{
		// handle music, update state at the controller, save the score
		controller.setPlayerScore(m_score);
		controller.changeState(States::ENDGAME);
		Source::instance().getStageMusicLvl1().stop();
		return;
	}
	 //wait for event
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::P:         // pause the level
				m_isPaused = !m_isPaused;
				return;
			case sf::Keyboard::Escape:      // back to menu state
				Source::instance().initCurrentLevel();
				controller.changeState(States::MENU);
				Source::instance().getStageMusicLvl1().stop();
				Source::instance().getMenuMusic().play();
				return;
			default:
				break;
			}

			break;
		case sf::Event::KeyReleased: {
			switch (event.key.code) {
			case sf::Keyboard::Left: {
				handlePlayer(window.getSize().x, LeftRelease);
				break;
			}
			case sf::Keyboard::Right: {
				handlePlayer(window.getSize().x, RightRelease);
				break;
			}
			case sf::Keyboard::Up: {
				handlePlayer(window.getSize().x, UpRelease);
				break;
			}
			case sf::Keyboard::Down: {
				handlePlayer(window.getSize().x, DownRelease);
				break;
			}
			}
		}
		default:
			break;
		}
	}
	if (!m_isPaused)            // keep running the level
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_Player->canJump()) { // move the player																	  
			m_Player->setJump();
			whileJump = true;
			handlePlayer(window.getSize().x, Space);
			m_Player->setCanJump(false);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))   // move the player
			handlePlayer(window.getSize().x, Right);

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))    // move the player
			handlePlayer(window.getSize().x, Left);

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))    // move the player
			handlePlayer(window.getSize().x, LAlt);

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !m_Player->isJumping())    // move the player
			handlePlayer(window.getSize().x, Up);

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))    // move the player
			handlePlayer(window.getSize().x, Down);

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) || sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))    // move the player	
			handlePlayer(window.getSize().x, R);
		else
			handlePlayer(window.getSize().x, Stay);
		handleEnemy();
	}
}

// c-tor
PlayState::PlayState(const sf::Vector2f& coords, const sf::Texture& texture)
	: GameState(coords, texture),
	m_life(MAX_LIFE),
	m_score(0), m_lifePre(MAX_LIFEPRE),
	m_leftCommand(std::make_shared<MoveLeftCommand>()),
	m_rightCommand(std::make_shared<MoveRightCommand>()),
	m_upCommad(std::make_shared<MoveUpCommand>()),
	m_downCommad(std::make_shared<MoveDownCommand>()),
	m_defCommand(std::make_shared<DefaultCommand>()),
	m_attackCommad(std::make_shared<AttackCommand>()),
	m_jumpCommad(std::make_shared<JumpCommand>()),
	m_leftReleaseCommand(std::make_shared<LeftReleaseCommand>()),
	m_rightReleaseCommand(std::make_shared<RightReleaseCommand>()),
	m_upReleaseCommand(std::make_shared<UpReleaseCommand>()),
	m_downReleaseCommand(std::make_shared<DownReleaseCommand>()),
	m_AltCommand(std::make_shared<ShootCommand>()),
	m_deathCommad(std::make_shared<DeathCommand>()),
	m_enterPressed(false), m_isPaused(false), m_finish(false), m_gun(false),
	m_bar(StatusBar(sf::Vector2f{ 0,STATE_HEIGTH-100 }, Source::instance().getBarTexture()))
{
	m_pauseText = sf::Text(Pause, Source::instance().getFont(), 65U);
	m_pauseText.setOrigin(m_pauseText.getGlobalBounds().width, m_pauseText.getGlobalBounds().height);
	m_pauseText.setPosition(STATE_WIDTH / 2, STATE_HEIGTH / 2);
	m_pauseText.setOutlineThickness(3);
	setMultimapDIr();
	setMultimapDIrE();
	m_view.setSize(static_cast<float>(STATE_WIDTH), static_cast<float>(STATE_HEIGTH));
	m_view.setViewport({ 0,0,1,1 });
	m_view.zoom(0.5);
	initMappingPointer();
	Source::instance().getStageMusicLvl1().setVolume(loudMusic);
	clock.restart();
}

//----------------------------------------------------------------------------------------------
// display the play state objects, information, background
void PlayState::displayState(GameManager& controller)
{
	sf::RenderWindow& window = controller.getWindow();
	sf::View last = window.getView();

	window.setView(m_view); //set camera view
	window.draw(m_sprite); //draw the background

	for (int i = m_obs.size(); i >= 1; i--){  //draw objects from end to start
		m_obs[i - 1]->draw(window); //draw static objects once
		if (CollisionManager::PixelPerfectTest(m_Player->getSprite(), m_obs[i - 1]->getSprite(), 0)) {
			CollisionManager::processCollision(m_Player, m_obs[i - 1], *this);
		}
		for (auto enemy : m_Enemy){
			if (CollisionManager::PixelPerfectTest(enemy->getSprite(), m_obs[i - 1]->getSprite(), 0)) {
				CollisionManager::processCollision(enemy, m_obs[i - 1], *this);
			}
		}
		if (m_life == 0)
			break;
	}
	for (auto i : m_pickables) {
		if (!i->isUsed()) {
			i->draw(window);
			if (CollisionManager::PixelPerfectTest(m_Player->getSprite(), i->getSprite(), 0)) {
				CollisionManager::processCollision(m_Player, i, *this);
			}
		}
	}

	if (m_lastDir != m_currDir) {
		m_currDir = m_lastDir;
		m_Player->setVelocity(sf::Vector2f(12, 12));
	}

	for(auto enemy : m_Enemy)
		enemy->draw(window); // draw the enemeis
	m_Player->draw(window); //draw the player
	if (m_isPaused)
		window.draw(m_pauseText);   // draw paused text
	window.setView(last);
	drawStatusBar(window);// draw status bar
}

//----------------------------------------------------------------------------------------------
// the function get the controller and update the state objects 
void PlayState::updateStage(GameManager& controller){
	if (m_isPaused) return;

	if (!m_finish){
		if (!loadedOnce) { //load level static object only once 
			initLevelObjects();
			loadedOnce = true;
		}
	}
}

//----------------------------------------------------------------------------------------------
// the function inittilize the objects vector of the current level according to the text file
// (that information is taken from Reasource class)
void PlayState::initLevelObjects()
{
	float m_rowLevel = 0.f, m_colLevel = 0.f;//reset the map size
	m_rowLevel = static_cast<float>(Source::instance().getLvlMat().size());

	for (size_t row = 0; row < m_rowLevel; row++){	//setting the new level's map
		m_colLevel = static_cast<float>(Source::instance().getLvlMat()[row].size());
		auto curr_row = Source::instance().getLvlMat()[row];
		for (size_t column = 0; column < m_colLevel; column++){
			position = setPos(curr_row[column], row, column);

			if (auto ptr = SpawnManager<char, Pickup>::create(curr_row[column], position))
				m_pickables.emplace_back(std::move(ptr));		//move semantics
			else if (auto ptr = SpawnManager<char, StaticObject>::create(curr_row[column], position))
				m_obs.emplace_back(std::move(ptr));		//move semantics
			else if (curr_row[column] == PLAYER_C) // placed the player
			{
				playerPosition = position;
				m_Player = std::make_shared<Player>(Player(playerPosition, Source::instance().getPlayerTexture()));
				m_view.setCenter(m_Player->getCenter());
			}
			else if (curr_row[column] == ENEMYDUMP_C) // placed the enemies
				m_Enemy.emplace_back(std::move(std::make_shared<Enemy>(position, Source::instance().getEnemySmartTexture())));
		}
	}
}

//initialize player after death
void PlayState::initPlayerAfterDeath() {
	m_Player.reset();
	m_Player = std::make_shared<Player>(Player(playerPosition, Source::instance().getPlayerTexture()));
	m_Player->setDeadStatus(false);
	m_bar.UpdatePreLife(MAX_LIFEPRE);
	m_life -= 1;
	m_bar.UpdateLife(m_life);
}

// function which insert the objects
void PlayState::initMappingPointer(){
	m_mapping.insert(std::make_pair(PLAYER_C, sf::Vector2f(static_cast<float>(WALL_WIDTH), static_cast<float>(WALL_HEIGHT))));
	m_mapping.insert(std::make_pair(ENEMYDUMP_C, sf::Vector2f(static_cast<float>(WALL_WIDTH), static_cast<float>(WALL_HEIGHT))));
	m_mapping.insert(std::make_pair(ENEMYSMART_C, sf::Vector2f(static_cast<float>(WALL_WIDTH), static_cast<float>(WALL_HEIGHT))));
	m_mapping.insert(std::make_pair(EMPTY_C, sf::Vector2f(0, 0)));
	m_mapping.insert(std::make_pair(TILE_C, sf::Vector2f(static_cast<float>(WALL_WIDTH), static_cast<float>(WALL_HEIGHT))));
	m_mapping.insert(std::make_pair(TILE1_C, sf::Vector2f(static_cast<float>(WALL_WIDTH), static_cast<float>(WALL_HEIGHT))));
	m_mapping.insert(std::make_pair(TILE2_C, sf::Vector2f(static_cast<float>(WALL_WIDTH), static_cast<float>(WALL_HEIGHT))));
	m_mapping.insert(std::make_pair(TILE3_C, sf::Vector2f(static_cast<float>(WALL_WIDTH), static_cast<float>(WALL_HEIGHT))));
	m_mapping.insert(std::make_pair(SMALLTILE_C, sf::Vector2f(static_cast<float>(WALL_WIDTH), static_cast<float>(WALL_HEIGHT))));
	m_mapping.insert(std::make_pair(SPIKES_C, sf::Vector2f(static_cast<float>(WALL_WIDTH), static_cast<float>(WALL_HEIGHT))));
	m_mapping.insert(std::make_pair(SPIKES1_C, sf::Vector2f(static_cast<float>(WALL_WIDTH), static_cast<float>(WALL_HEIGHT))));
	m_mapping.insert(std::make_pair(SPIKES2_C, sf::Vector2f(static_cast<float>(WALL_WIDTH), static_cast<float>(WALL_HEIGHT))));
	m_mapping.insert(std::make_pair(SPIKES3_C, sf::Vector2f(static_cast<float>(WALL_WIDTH), static_cast<float>(WALL_HEIGHT))));
	m_mapping.insert(std::make_pair(SPIKES4_C, sf::Vector2f(static_cast<float>(WALL_WIDTH), static_cast<float>(WALL_HEIGHT))));
	m_mapping.insert(std::make_pair(SPIKES5_C, sf::Vector2f(static_cast<float>(WALL_WIDTH), static_cast<float>(WALL_HEIGHT))));
	m_mapping.insert(std::make_pair(LADDER_C, sf::Vector2f(static_cast<float>(WALL_WIDTH), static_cast<float>(WALL_HEIGHT))));
	m_mapping.insert(std::make_pair(LADDER2_C, sf::Vector2f(static_cast<float>(WALL_WIDTH), static_cast<float>(WALL_HEIGHT))));
	m_mapping.insert(std::make_pair(HEAL_C, sf::Vector2f(static_cast<float>(WALL_WIDTH), static_cast<float>(WALL_HEIGHT) + 4)));
	m_mapping.insert(std::make_pair(WALL_C, sf::Vector2f(static_cast<float>(WALL_WIDTH), static_cast<float>(WALL_HEIGHT))));
	m_mapping.insert(std::make_pair(WALL1_C, sf::Vector2f(static_cast<float>(WALL_WIDTH), static_cast<float>(WALL_HEIGHT))));
	m_mapping.insert(std::make_pair(WALL2_C, sf::Vector2f(static_cast<float>(WALL_WIDTH), static_cast<float>(WALL_HEIGHT))));
	m_mapping.insert(std::make_pair(WALL3_C, sf::Vector2f(static_cast<float>(WALL_WIDTH), static_cast<float>(WALL_HEIGHT))));
	m_mapping.insert(std::make_pair(WALL4_C, sf::Vector2f(static_cast<float>(WALL_WIDTH), static_cast<float>(WALL_HEIGHT))));
	m_mapping.insert(std::make_pair(WALL5_C, sf::Vector2f(static_cast<float>(WALL_WIDTH), static_cast<float>(WALL_HEIGHT))));
	m_mapping.insert(std::make_pair(WALL6_C, sf::Vector2f(static_cast<float>(WALL_WIDTH), static_cast<float>(WALL_HEIGHT))));
	m_mapping.insert(std::make_pair(WALL7_C, sf::Vector2f(static_cast<float>(WALL_WIDTH), static_cast<float>(WALL_HEIGHT))));
	m_mapping.insert(std::make_pair(WALL8_C, sf::Vector2f(static_cast<float>(WALL_WIDTH), static_cast<float>(WALL_HEIGHT))));
	m_mapping.insert(std::make_pair(WALL9_C, sf::Vector2f(static_cast<float>(WALL_WIDTH), static_cast<float>(WALL_HEIGHT))));
	m_mapping.insert(std::make_pair(EMPRYHELP_C, sf::Vector2f(static_cast<float>(WALL_WIDTH), static_cast<float>(WALL_HEIGHT))));
	m_mapping.insert(std::make_pair(FIRE_C, sf::Vector2f(static_cast<float>(WALL_WIDTH), static_cast<float>(WALL_HEIGHT))));
	m_mapping.insert(std::make_pair(LAMP_C, sf::Vector2f(static_cast<float>(WALL_WIDTH), static_cast<float>(WALL_HEIGHT))));
	m_mapping.insert(std::make_pair(REDCROWN_C, sf::Vector2f(static_cast<float>(WALL_WIDTH), static_cast<float>(WALL_HEIGHT+4))));
	m_mapping.insert(std::make_pair(COIN_C, sf::Vector2f(static_cast<float>(WALL_WIDTH), static_cast<float>(WALL_HEIGHT+4))));
}

// function which returns the right pos to the objects
sf::Vector2f PlayState::setPos(char obj, size_t row, size_t col) {
	return sf::Vector2f(static_cast<float>(col) * m_mapping.find(obj)->second.x , static_cast<float>(row) * m_mapping.find(obj)->second.y); // + m_mapping.find(obj)->second.y / 2
}

// function which update the scode when the player collide with token
void PlayState::updateScoreWithToken() {
	m_score += tokenScore;
	m_bar.UpdateScore(m_score);
	Source::instance().getPickUpSound().play();
}

// function which update the scode when the player collide with coins
void PlayState::updateScoreWithCoin() {
	m_score += coinscore;
	m_bar.UpdateScore(m_score);
	Source::instance().getCoinPickSound().play();
}

// function which update the scode when the player collide with token
void PlayState::updateLifePre() {
	if (m_Player->getLife() + healadd > MAX_LIFE_PRE)
		m_Player->setLife(MAX_LIFE_PRE);
	else
		m_Player->increaseLife(healadd);
	m_bar.UpdatePreLife(m_Player->getLife());
	Source::instance().getHealPickSound().play();
}

void PlayState::decLifePreByEnemy(){
	m_Player->reduceLife(lifeDec);
	m_bar.UpdatePreLife(m_Player->getLife());
}

void PlayState::decLifeSpkies() {
	m_life -= 1;
	m_bar.UpdatePreLife(0);
	m_bar.UpdateLife(m_life);
}
// Initialize the direction map
void PlayState::setMultimapDIrE() {
	m_DirectorE.insert(std::make_pair(Right, m_rightCommand));
	m_DirectorE.insert(std::make_pair(Left, m_leftCommand));
	m_DirectorE.insert(std::make_pair(R, m_attackCommad));
}
//----------------------------------------------------------------------------------------------
// Initialize the direction map
void PlayState::setMultimapDIr() {
	m_Director.insert(std::make_pair(Right, m_rightCommand));
	m_Director.insert(std::make_pair(Left, m_leftCommand)); 
	m_Director.insert(std::make_pair(LeftRelease, m_leftReleaseCommand));
	m_Director.insert(std::make_pair(RightRelease, m_rightReleaseCommand));
	m_Director.insert(std::make_pair(Up, m_upCommad));
	m_Director.insert(std::make_pair(Down, m_downCommad));
	m_Director.insert(std::make_pair(Stay, m_defCommand));
	m_Director.insert(std::make_pair(R, m_attackCommad));
	m_Director.insert(std::make_pair(LControl, m_attackCommad));
	m_Director.insert(std::make_pair(Space, m_jumpCommad));
	m_Director.insert(std::make_pair(UpRelease, m_upReleaseCommand));
	m_Director.insert(std::make_pair(DownRelease, m_downReleaseCommand));
	m_Director.insert(std::make_pair(Death, m_deathCommad));

}
// the function get the game window and draw the number of score,life and level
void PlayState::drawStatusBar(sf::RenderWindow& window)
{
	m_bar.draw(window);
	window.draw(m_bar.getLevelText());
	window.draw(m_bar.getScoreText());
	window.draw(m_bar.getLifeText());
	window.draw(m_bar.getLifePreText());
}

//----------------------------------------------------------------------------------------------
// the function get size for range and diraction for moving and handle the player
void PlayState::handlePlayer(size_t x, const Direction & dir)
{
	static float lastTIme = 0;

	if (m_Player->getLife() == 0)
	{
		m_currCommand = m_Director.find(Death)->second;	// update current command
		m_currCommand.lock()->execute(m_Player); // move the player according to the current command
		if (m_Player->getDeadStatus())
		{
			initPlayerAfterDeath();
		}
	}
	if (dir != Stay) {
		m_currCommand = m_Director.find(dir)->second;	// update current command
		m_currCommand.lock()->execute(m_Player); // move the player according to the current command
	}
	if (GameClock::getInstance().isTimePassed(lastTIme, 1/15.f)) {
		m_Player->update();
		m_view.setCenter(m_Player->getCenter());
		lastTIme = GameClock::getInstance().getElapsedTime();
	}
	if (!m_Player->inRange(x))                // get the player step back if out of range
	{
		m_currCommand = (dir == Left) ? m_rightCommand : m_leftCommand;
		m_currCommand.lock()->execute(m_Player);
	}
}
void PlayState::handleEnemy()
{
	for (auto enemy : m_Enemy) {
		if (GameClock::getInstance().isTimePassed(enemy->getLastTime(), 1 / 10.f)) {
			if (CollisionManager::PixelPerfectTest(m_Player->getSprite(), enemy->getSprite(), 0)) {
				CollisionManager::processCollision(m_Player, enemy, *this);
			}
			m_currCommandEnemy = m_DirectorE.find(enemy->getDirection())->second;	// update current command
			m_currCommandEnemy.lock()->execute(enemy); // move the player according to the current command
			float dis = getDest(enemy->getCenter(), m_Player->getCenter());
			if (enemy->isTarget() && m_Player->getLife() > 0) {
				enemy->gotoTarget();
				if (dis < 90.f) {
					m_currCommandEnemy = m_DirectorE.find(R)->second;	// update current command
					m_currCommandEnemy.lock()->execute(enemy); // move the player according to the current command
				}
			} else {
				if (dis < 200.f && m_Player->getLife() > 0) {
					enemy->setTarget(m_Player);
				}
				else if(m_Player->getLife() == 0)
					enemy->setTarget(nullptr);
			}
			enemy->update();
			enemy->setLastTime();
		}
	}
	std::experimental::erase_if(m_Enemy, [](auto enemy) {
		return enemy->getToRemove();
	});
}

float PlayState::getDest(sf::Vector2f enemy, sf::Vector2f player) {
	return sqrt(pow(enemy.x - player.x, 2) + pow(enemy.y - player.y, 2));
}