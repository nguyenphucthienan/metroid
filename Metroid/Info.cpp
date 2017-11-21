#include "Info.h"
#include "TextSprite.h"
#include <string>

Info::Info() : BaseObject(eID::LIFE_ICON)
{
	_iconLife = SpriteManager::getInstance()->getSprite(eID::LIFE_ICON);
	_iconLife->setPosition(50, 25);

	_textLife = new TextSprite(eID::FONT, "", GVector2(0, 280));
	_textLife->init();

	_iconEnergy = SpriteManager::getInstance()->getSprite(eID::ENERGY_ICON);
	_iconEnergy->setPosition(50, 50);

	_textEnergy = new TextSprite(eID::FONT, "", GVector2(0, 280));
	_textEnergy->init();

	_missileRocketNumber = 10;
	_iconMissileRocket = SpriteManager::getInstance()->getSprite(BULLET_EFFECT);
	_iconMissileRocket->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BULLET_EFFECT, "missile_rocket_01"));
	_iconMissileRocket->setPosition(50, 75);

	_textMissileRocket = new TextSprite(eID::FONT, "", GVector2(0, 280));
	_textMissileRocket->init();

	_weaponID = NORMAL_BULLET;
	this->setWeapon(_weaponID);
}

Info::~Info()
{
}

void Info::init()
{
}

void Info::update(float deltatime)
{
	_textLife->setPosition(GVector2(_iconLife->getPosition().x + 35, _iconLife->getPosition().y));

	if (_lifeNumber < 0)
	{
		_textLife->setString("00");
	}
	if (_lifeNumber >= 0 && _lifeNumber < 10)
	{
		_textLife->setString("0" + to_string(_lifeNumber));
	}
	else if (_lifeNumber >= 10 && _lifeNumber < 100)
	{
		_textLife->setString("" + to_string(_lifeNumber));
	}

	_textEnergy->setPosition(GVector2(_iconEnergy->getPosition().x + 35, _iconEnergy->getPosition().y));
	
	if (_energyNumber < 0)
	{
		_textEnergy->setString("00");
	}
	if (_energyNumber >= 0 && _energyNumber < 10)
	{
		_textEnergy->setString("0" + to_string(_energyNumber));
	}
	else if (_energyNumber >= 10 && _energyNumber < 100)
	{
		_textEnergy->setString("" + to_string(_energyNumber));
	}

	_textMissileRocket->setPosition(GVector2(_iconMissileRocket->getPosition().x + 35, _iconMissileRocket->getPosition().y));

	if (_missileRocketNumber < 0)
	{
		_textMissileRocket->setString(" 00");
	}
	if (_missileRocketNumber >= 0 && _missileRocketNumber < 10)
	{
		_textMissileRocket->setString("0" + to_string(_missileRocketNumber));
	}
	else if (_missileRocketNumber >= 10 && _missileRocketNumber < 100)
	{
		_textMissileRocket->setString("" + to_string(_missileRocketNumber));
	}
}

void Info::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_iconLife->render(spriteHandle);
	_textLife->draw(spriteHandle);

	_iconEnergy->render(spriteHandle);
	_textEnergy->draw(spriteHandle);

	if (_missileRocketNumber > 0)
	{
		_iconMissileRocket->render(spriteHandle);
		_textMissileRocket->draw(spriteHandle);
	}
}

void Info::release()
{
	SAFE_DELETE(_iconLife);
	SAFE_DELETE(_textLife);
	SAFE_DELETE(_iconEnergy);
	SAFE_DELETE(_textEnergy);
	SAFE_DELETE(_iconMissileRocket);
}

int Info::getLife()
{
	return _lifeNumber;
}

void Info::setLife(int number)
{
	_lifeNumber = number;
}

int Info::getEnergy()
{
	return _energyNumber;
}

void Info::setEnergy(int number)
{
	_energyNumber = number;

	if (_energyNumber >= 100)
		_energyNumber = 99;
}

eID Info::getWeapon()
{
	return _weaponID;
}

void Info::setWeapon(eID id)
{
	_weaponID = id;
}

int Info::getMissileRocket()
{
	return _missileRocketNumber;
}

void Info::setMissileRocke(int number)
{
	_missileRocketNumber = number;
}
