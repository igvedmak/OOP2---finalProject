#include "CollisionManager.h"
#include "Player.h"
#include "PlayState.h" // if it's in header it's makes a loop for headers
#include "Enemy.h"

namespace CollisionManager {
	class BitmaskManager
	{
	public:
		~BitmaskManager() {
			std::map<const sf::Texture*, sf::Uint8*>::const_iterator end = Bitmasks.end();
			for (std::map<const sf::Texture*, sf::Uint8*>::const_iterator iter = Bitmasks.begin(); iter != end; iter++)
				delete[] iter->second;
		}

		sf::Uint8 GetPixel(const sf::Uint8* mask, const sf::Texture* tex, unsigned int x, unsigned int y) {
			if (x > tex->getSize().x || y > tex->getSize().y)
				return 0;

			return mask[x + y * tex->getSize().x];
		}

		sf::Uint8* GetMask(const sf::Texture* tex) {
			sf::Uint8* mask;
			std::map<const sf::Texture*, sf::Uint8*>::iterator pair = Bitmasks.find(tex);
			if (pair == Bitmasks.end())
			{
				sf::Image img = tex->copyToImage();
				mask = CreateMask(tex, img);
			}
			else
				mask = pair->second;

			return mask;
		}

		sf::Uint8* CreateMask(const sf::Texture* tex, const sf::Image& img) {
			sf::Uint8* mask = new sf::Uint8[tex->getSize().y*tex->getSize().x];

			for (unsigned int y = 0; y < tex->getSize().y; y++)
			{
				for (unsigned int x = 0; x < tex->getSize().x; x++)
					mask[x + y * tex->getSize().x] = img.getPixel(x, y).a;
			}

			Bitmasks.insert(std::pair<const sf::Texture*, sf::Uint8*>(tex, mask));

			return mask;
		}
	private:
		std::map<const sf::Texture*, sf::Uint8*> Bitmasks;
	};

	BitmaskManager Bitmasks;

	bool PixelPerfectTest(const sf::Sprite& Object1, const sf::Sprite& Object2, sf::Uint8 AlphaLimit) {
		sf::FloatRect Intersection;
		if (Object1.getGlobalBounds().intersects(Object2.getGlobalBounds(), Intersection)) {
			sf::IntRect O1SubRect = Object1.getTextureRect();
			sf::IntRect O2SubRect = Object2.getTextureRect();

			sf::Uint8* mask1 = Bitmasks.GetMask(Object1.getTexture());
			sf::Uint8* mask2 = Bitmasks.GetMask(Object2.getTexture());

			// Loop through our pixels
			for (int i = int(Intersection.left); i < Intersection.left + Intersection.width; i++) {
				for (int j = int(Intersection.top); j < Intersection.top + Intersection.height; j++) {

					sf::Vector2f o1v = Object1.getInverseTransform().transformPoint(float(i), float(j));
					sf::Vector2f o2v = Object2.getInverseTransform().transformPoint(float(i), float(j));

					// Make sure pixels fall within the sprite's subrect
					if (o1v.x > 0 && o1v.y > 0 && o2v.x > 0 && o2v.y > 0 &&
						o1v.x < O1SubRect.width && o1v.y < O1SubRect.height &&
						o2v.x < O2SubRect.width && o2v.y < O2SubRect.height) {

						if (Bitmasks.GetPixel(mask1, Object1.getTexture(), (int)(o1v.x) + O1SubRect.left, (int)(o1v.y) + O1SubRect.top) > AlphaLimit &&
							Bitmasks.GetPixel(mask2, Object2.getTexture(), (int)(o2v.x) + O2SubRect.left, (int)(o2v.y) + O2SubRect.top) > AlphaLimit)
							return true;

					}
				}
			}
		}
		return false;
	}

	bool CreateTextureAndBitmask(sf::Texture &LoadInto, const std::string& Filename)
	{
		sf::Image img;
		if (!img.loadFromFile(Filename))
			return false;
		if (!LoadInto.loadFromImage(img))
			return false;

		Bitmasks.CreateMask(&LoadInto, img);
		return true;
	}

	sf::Vector2f GetSpriteCenter(const sf::Sprite& Object)
	{
		sf::FloatRect AABB = Object.getGlobalBounds();
		return sf::Vector2f(AABB.left + AABB.width / 2.f, AABB.top + AABB.height / 2.f);
	}

	sf::Vector2f GetSpriteSize(const sf::Sprite& Object)
	{
		sf::IntRect OriginalSize = Object.getTextureRect();
		sf::Vector2f Scale = Object.getScale();
		return sf::Vector2f(OriginalSize.width*Scale.x, OriginalSize.height*Scale.y);
	}

	bool CircleTest(const sf::Sprite& Object1, const sf::Sprite& Object2) {
		sf::Vector2f Obj1Size = GetSpriteSize(Object1);
		sf::Vector2f Obj2Size = GetSpriteSize(Object2);
		float Radius1 = (Obj1Size.x + Obj1Size.y) / 4;
		float Radius2 = (Obj2Size.x + Obj2Size.y) / 4;

		sf::Vector2f Distance = GetSpriteCenter(Object1) - GetSpriteCenter(Object2);

		return (Distance.x * Distance.x + Distance.y * Distance.y <= (Radius1 + Radius2) * (Radius1 + Radius2));
	}

	class OrientedBoundingBox // Used in the BoundingBoxTest
	{
	public:
		OrientedBoundingBox(const sf::Sprite& Object) // Calculate the four points of the OBB from a transformed (scaled, rotated...) sprite
		{
			sf::Transform trans = Object.getTransform();
			sf::IntRect local = Object.getTextureRect();
			Points[0] = trans.transformPoint(0.f, 0.f);
			Points[1] = trans.transformPoint(float(local.width), 0.f);
			Points[2] = trans.transformPoint(float(local.width), float(local.height));
			Points[3] = trans.transformPoint(0.f, float(local.height));
		}

		sf::Vector2f Points[4];

		void ProjectOntoAxis(const sf::Vector2f& Axis, float& Min, float& Max) // Project all four points of the OBB onto the given axis and return the dotproducts of the two outermost points
		{
			Min = (Points[0].x*Axis.x + Points[0].y*Axis.y);
			Max = Min;
			for (int j = 1; j < 4; j++)
			{
				float Projection = (Points[j].x*Axis.x + Points[j].y*Axis.y);

				if (Projection < Min)
					Min = Projection;
				if (Projection > Max)
					Max = Projection;
			}
		}
	};

	bool BoundingBoxTest(const sf::Sprite& Object1, const sf::Sprite& Object2) {
		OrientedBoundingBox OBB1(Object1);
		OrientedBoundingBox OBB2(Object2);

		// Create the four distinct axes that are perpendicular to the edges of the two rectangles
		sf::Vector2f Axes[4] = {
			sf::Vector2f(OBB1.Points[1].x - OBB1.Points[0].x,
			OBB1.Points[1].y - OBB1.Points[0].y),
			sf::Vector2f(OBB1.Points[1].x - OBB1.Points[2].x,
			OBB1.Points[1].y - OBB1.Points[2].y),
			sf::Vector2f(OBB2.Points[0].x - OBB2.Points[3].x,
			OBB2.Points[0].y - OBB2.Points[3].y),
			sf::Vector2f(OBB2.Points[0].x - OBB2.Points[1].x,
			OBB2.Points[0].y - OBB2.Points[1].y)
		};

		for (int i = 0; i < 4; i++) // For each axis...
		{
			float MinOBB1, MaxOBB1, MinOBB2, MaxOBB2;

			// ... project the points of both OBBs onto the axis ...
			OBB1.ProjectOntoAxis(Axes[i], MinOBB1, MaxOBB1);
			OBB2.ProjectOntoAxis(Axes[i], MinOBB2, MaxOBB2);

			// ... and check whether the outermost projected points of both OBBs overlap.
			// If this is not the case, the Separating Axis Theorem states that there can be no collision between the rectangles
			if (!((MinOBB2 <= MaxOBB1) && (MaxOBB2 >= MinOBB1)))
				return false;
		}
		return true;
	}

	// Start of collision types
	static void DynamicTile(std::shared_ptr<Object> dynamicPtr, std::shared_ptr<Object> tilePtr, PlayState& board){
		auto dynamic = std::static_pointer_cast<Player>(dynamicPtr);
		auto tile = std::static_pointer_cast<Tile>(tilePtr);
		dynamic->setCanJump(true);
		dynamic->collideWithTile(tile);
	}

	static void TileDynamic(std::shared_ptr<Object> tile, std::shared_ptr<Object> dynamic, PlayState& board){
		DynamicTile(dynamic, tile, board);
	}

	static void DynamicWall(std::shared_ptr<Object> dynamicPtr, std::shared_ptr<Object> wallPtr, PlayState& board){
		auto dynamic = std::static_pointer_cast<Player>(dynamicPtr);
		auto wall = std::static_pointer_cast<Wall>(wallPtr);
		dynamic->collideWithWall(wall);
	}

	static void WallDynamic(std::shared_ptr<Object> wall, std::shared_ptr<Object> dynamic, PlayState& board){
		DynamicWall(dynamic, wall, board);
	}

	static void DynamicEnemyTile(std::shared_ptr<Object> dynamicPtr, std::shared_ptr<Object> tilePtr, PlayState& board) {
		auto dynamic = std::static_pointer_cast<Enemy>(dynamicPtr);
		auto tile = std::static_pointer_cast<Tile>(tilePtr);
		dynamic->collideWithTile(tile);
	}

	static void TileDynamicEnemy(std::shared_ptr<Object> tile, std::shared_ptr<Object> dynamic, PlayState& board) {
		DynamicEnemyTile(dynamic, tile, board);
	}

	static void DynamicEnemyWall(std::shared_ptr<Object> dynamicPtr, std::shared_ptr<Object> wallPtr, PlayState& board) {
		auto dynamic = std::static_pointer_cast<Enemy>(dynamicPtr);
		auto wall = std::static_pointer_cast<Wall>(wallPtr);
		dynamic->collideWithEnemyWall(wall);
	}

	static void WallDynamicEnemy(std::shared_ptr<Object> wall, std::shared_ptr<Object> dynamic, PlayState& board) {
		DynamicEnemyWall(dynamic, wall, board);
	}

	static void DynamicEnemyWallTile(std::shared_ptr<Object> dynamicPtr, std::shared_ptr<Object> walltilePtr, PlayState& board) {
		auto dynamic = std::static_pointer_cast<Enemy>(dynamicPtr);
		auto walltile = std::static_pointer_cast<WallTile>(walltilePtr);
		dynamic->collideWithWallTile(walltile);
	}

	static void WallTileDynamicEnemy(std::shared_ptr<Object> walltile, std::shared_ptr<Object> dynamic, PlayState& board) {
		DynamicEnemyWallTile(dynamic, walltile, board);
	}

	static void DynamicWallTile(std::shared_ptr<Object> dynamicPtr, std::shared_ptr<Object> walltilePtr, PlayState& board) {
		auto dynamic = std::static_pointer_cast<Player>(dynamicPtr);
		auto walltile = std::static_pointer_cast<WallTile>(walltilePtr);
		dynamic->setCanJump(true);
		dynamic->collideWithWallTile(walltile);
	}

	static void WallTileDynamic(std::shared_ptr<Object> walltile, std::shared_ptr<Object> dynamic, PlayState& board) {
		DynamicEnemyWallTile(dynamic, walltile, board);
	}

	static void DynamicHeal(std::shared_ptr<Object> dynamicPtr, std::shared_ptr<Object> haelPtr, PlayState& board) {
		auto player = std::static_pointer_cast<Player>(dynamicPtr);
		auto health = std::static_pointer_cast<HealthPotion>(haelPtr);
		if (player->getLife() < MAX_LIFE_PRE) {
			static_cast<PlayState&>(board).updateLifePre();
			haelPtr->setTransperent();
			health->set2used();
		}
	}

	static void HealDynamic(std::shared_ptr<Object> heal, std::shared_ptr<Object> dynamic, PlayState& board) {
		DynamicWall(dynamic, heal, board);
	}

	static void DynamicToken(std::shared_ptr<Object> dynamicPtr, std::shared_ptr<Object> tokenPtr, PlayState& board) {
		auto token = std::static_pointer_cast<Token>(tokenPtr);
		static_cast<PlayState&>(board).updateScoreWithToken();
		token->set2used();
		tokenPtr->setTransperent();
	}

	static void TokenDynamic(std::shared_ptr<Object> token, std::shared_ptr<Object> dynamic, PlayState& board) {
		DynamicToken(dynamic, token, board);
	}

	static void DynamicCoin(std::shared_ptr<Object> dynamicPtr, std::shared_ptr<Object> coinPtr, PlayState& board) {
		auto coin = std::static_pointer_cast<Coins>(coinPtr);
		static_cast<PlayState&>(board).updateScoreWithCoin();
		coin->set2used();
		coinPtr->setTransperent();
	}

	static void CoinDynamic(std::shared_ptr<Object> coin, std::shared_ptr<Object> dynamic, PlayState& board) {
		DynamicCoin(dynamic, coin, board);
	}

	static void DynamicSpkie(std::shared_ptr<Object> dynamicPtr, std::shared_ptr<Object> spkiesPtr, PlayState& board) {
		static_cast<PlayState&>(board).decLifeSpkies();
	}

	static void SpkieDynamic(std::shared_ptr<Object> spkies, std::shared_ptr<Object> dynamic, PlayState& board) {
		DynamicSpkie(dynamic, spkies, board);
	}
	static void PlayerEnemy(std::shared_ptr<Object> playerPtr, std::shared_ptr<Object> enemyPtr, PlayState& board) {
		auto enemy = std::static_pointer_cast<Enemy>(enemyPtr);
		auto player = std::static_pointer_cast<Player>(playerPtr);
		if(enemy->isAttack() && enemy->getFrame() == FRAME_LIMIT_ENEMY_ATTACK+1)
			static_cast<PlayState&>(board).decLifePreByEnemy();

		if (player->isAttack() && player->getFrame() == FRAME_LIMIT_CLAW_ATTACK+1)
			enemy->decLifePoints();
	}

	static void EnemyPlayer(std::shared_ptr<Object> enemy, std::shared_ptr<Object> player, PlayState& board) {
		PlayerEnemy(player, enemy, board);
	}

	static void DynamicEnemyempty(std::shared_ptr<Object> playerPtr, std::shared_ptr<Object> emptyPtr, PlayState& board) {
		auto dynamic = std::static_pointer_cast<Enemy>(playerPtr);
		auto empty = std::static_pointer_cast<Wall>(emptyPtr);
		dynamic->collideWithEnemyWall(empty);
	}

	static void emptyDynamicEnemy(std::shared_ptr<Object> empty, std::shared_ptr<Object> player, PlayState& board) {
		DynamicEnemyempty(player, empty, board);
	}

	static void PlayerLadder(std::shared_ptr<Object> playerPtr, std::shared_ptr<Object> ladderPtr, PlayState& board) {
		auto player = std::static_pointer_cast<Player>(playerPtr);
		auto ladder = std::static_pointer_cast<Ladder>(ladderPtr);
		player->collideWithLadder(ladder);
	}

	static void LadderpPlayer(std::shared_ptr<Object> ladder, std::shared_ptr<Object> player, PlayState& board) {
		PlayerLadder(player, ladder, board);
	}

	static void TokenWallTile(std::shared_ptr<Object> tokenPtr, std::shared_ptr<Object> walltilePtr, PlayState& board) {
		auto dynamic = std::static_pointer_cast<Token>(tokenPtr);
		auto walltile = std::static_pointer_cast<WallTile>(walltilePtr);
		//dynamic->collideWithTokenWallTile(walltile);
	}

	static void WallTileToken(std::shared_ptr<Object> walltile, std::shared_ptr<Object> token, PlayState& board) {
		TokenWallTile(token, walltile, board);
	}

	static void Dynamicempty(std::shared_ptr<Object> playerPtr, std::shared_ptr<Object> emptyPtr, PlayState& board) {
		auto dynamic = std::static_pointer_cast<Player>(playerPtr);
		auto empty = std::static_pointer_cast<emptyHelper>(emptyPtr);
		//dynamic->collideWithPlayerEnd(empty);
	}

	static void emptyDynamic(std::shared_ptr<Object> empty, std::shared_ptr<Object> player, PlayState& board) {
		Dynamicempty(player, empty, board);
	}

	HitMap initializeCollisionMap()
	{
		HitMap map;
		SetFunc<Player, Tile>(map, &DynamicTile);
		SetFunc<Tile, Player>(map, &TileDynamic);
		SetFunc<Player, Wall>(map, &DynamicWall);
		SetFunc<Wall, Player>(map, &WallDynamic);

		SetFunc<Enemy, Tile>(map, &DynamicEnemyTile);
		SetFunc<Tile, Enemy>(map, &TileDynamicEnemy);
		SetFunc<Enemy, Wall>(map, &DynamicEnemyWall);
		SetFunc<Wall, Enemy>(map, &WallDynamicEnemy);

		SetFunc<Enemy, emptyHelper>(map, &DynamicEnemyempty);
		SetFunc<emptyHelper, Player>(map, &emptyDynamicEnemy);
		SetFunc<Player, HealthPotion>(map, &DynamicHeal);
		SetFunc<HealthPotion, Player>(map, &HealDynamic);

		SetFunc<Player, Token>(map, &DynamicToken);
		SetFunc<Token, Player>(map, &TokenDynamic);
		SetFunc<Player, Spkies>(map, &DynamicSpkie);
		SetFunc<Spkies, Player>(map, &SpkieDynamic);

		SetFunc<Player, Enemy>(map, &PlayerEnemy);
		SetFunc<Enemy, Player>(map, &EnemyPlayer);
		SetFunc<Player, Ladder>(map, &PlayerLadder);
		SetFunc<Ladder, Player>(map, &LadderpPlayer);

		SetFunc<Player, WallTile>(map, &DynamicWallTile);
		SetFunc<WallTile, Player>(map, &WallTileDynamic);

		SetFunc<Enemy, WallTile>(map, &DynamicEnemyWallTile);
		SetFunc<WallTile, Enemy>(map, &WallTileDynamicEnemy);

		SetFunc<Token, WallTile>(map, &TokenWallTile);
		SetFunc<WallTile, Token>(map, &WallTileToken);

		SetFunc<Player, emptyHelper>(map, &Dynamicempty);
		SetFunc<emptyHelper, Player>(map, &emptyDynamic);
		SetFunc<Player, Coins>(map, &DynamicCoin);
		SetFunc<Coins, Player>(map, &CoinDynamic);
		return map; //returns r-value (move semantics of std::map)
	}

	HitFunctionPtr lookup(const std::string & class1, const std::string & class2)
	{
		auto collisionMap = initializeCollisionMap();
		auto classPair = std::make_pair(class1, class2);

		auto mapEntry = collisionMap.find(classPair);

		if (mapEntry == collisionMap.end())
			return 0; //nullptr
		return mapEntry->second;
	}

	void processCollision(std::shared_ptr<Object> obj1Ptr, std::shared_ptr<Object> obj2Ptr, PlayState & board)
	{
		auto func = lookup(typeid(*obj1Ptr).name(), typeid(*obj2Ptr).name());
		if (func)
			func(obj1Ptr, obj2Ptr, board);
	}
}
