#pragma once
#include "Player.h"

#include "DynamicObject.h"
#include <time.h>
#include <windows.h>
#include "GameClock.h"
//Command design pattern
class Command
{
public:
	int current_frame = 0;
	virtual void execute(std::shared_ptr<DynamicObject> obj) = 0;
};

class MoveLeftCommand : public Command {
public:
	void execute(std::shared_ptr<DynamicObject> dynamicObj) override {
		dynamicObj->handleInupt(PRESS_LEFT);
	}
};
class LeftReleaseCommand : public Command {
public:
	void execute(std::shared_ptr<DynamicObject> dynamicObj) override {
		dynamicObj->handleInupt(RELEASE_LEFT);
	}
};

class MoveRightCommand : public Command {
public:
	void execute(std::shared_ptr<DynamicObject> dynamicObj) override {
		dynamicObj->handleInupt(PRESS_RIGHT);
	}
};
class RightReleaseCommand : public Command {
public:
	void execute(std::shared_ptr<DynamicObject> dynamicObj) override {
		dynamicObj->handleInupt(RELEASE_RIGHT);
	}
};

class MoveUpCommand : public Command {
public:
	void execute(std::shared_ptr<DynamicObject> dynamicObj) override {
		dynamicObj->handleInupt(PRESS_UP);
	}
};

class UpReleaseCommand : public Command {
public:
	void execute(std::shared_ptr<DynamicObject> dynamicObj) override {
		dynamicObj->handleInupt(RELEASE_UP);
	}
};

class MoveDownCommand : public Command {
public:
	void execute(std::shared_ptr<DynamicObject> dynamicObj) override {
		dynamicObj->handleInupt(PRESS_DOWN);
	}
};

class DownReleaseCommand : public Command {
public:
	void execute(std::shared_ptr<DynamicObject> dynamicObj) override {
		dynamicObj->handleInupt(RELEASE_DOWN);
	}
};

class DefaultCommand : public Command {
public:
	void execute(std::shared_ptr<DynamicObject> dynamicObj) override {
		dynamicObj->handleInupt(NONE);
	}
};

class JumpCommand : public Command {
public:
	void execute(std::shared_ptr<DynamicObject> dynamicObj) override {
		dynamicObj->handleInupt(PRESS_SPACE);
	}
};


class ShootCommand : public Command {
public:
	void execute(std::shared_ptr<DynamicObject> dynamicObj) override {
		dynamicObj->handleInupt(PRESS_ALT);
	}
};

class AttackCommand : public Command {
public:
	void execute(std::shared_ptr<DynamicObject> dynamicObj) override {
		dynamicObj->handleInupt(PRESS_R);
	}
};
class DeathCommand : public Command {
public:
	void execute(std::shared_ptr<DynamicObject> dynamicObj) override {
		dynamicObj->handleInupt(DEATH);
	}
};

class CrouchCommand : public Command {
public:
	void execute(std::shared_ptr<DynamicObject> dynamicObj) override {
	}
};
class EnemyAttackCommand : public Command {
public:
	void execute(std::shared_ptr<DynamicObject> dynamicObj) override {
	}
};
