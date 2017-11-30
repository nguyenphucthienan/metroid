#include "BlueItemBall.h"

BlueItemBall::BlueItemBall(int x, int y, eID itemId) : BaseObject(BLUE_ITEM_BALL)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::ITEM_BALL);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ITEM_BALL, "blue_item_ball_01"));
	_sprite->setPosition(x, y);

	_animation = new Animation(_sprite, 1.0f);
	_animation->addFrameRect(eID::ITEM_BALL, "blue_item_ball_01", NULL);

	_effect = SpriteManager::getInstance()->getSprite(eID::ITEM_BALL);
	_effect->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ITEM_BALL, "blue_item_ball_01"));
	_effectAnimation = new Animation(_effect, 0.25f, false);
	_effectAnimation->addFrameRect(ITEM_BALL, "blue_item_ball_01", "blue_item_ball_02", "blue_item_ball_03", NULL);

	_itemId = itemId;
	_hitPoint = 2;
}

void BlueItemBall::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;
}

void BlueItemBall::update(float deltatime)
{
	if (_hitPoint > 0)
	{
		_animation->update(deltatime);

		for (auto it = _componentList.begin(); it != _componentList.end(); it++)
		{
			it->second->update(deltatime);
		}
	}
	else
	{
		_effect->setPosition(this->getPosition());
		_effectAnimation->update(deltatime);

		if (!_effectAnimation->isAnimate())
		{
			this->setStatus(DESTROY);

			BaseObject* item = nullptr;
			switch (_itemId)
			{
			case ENERGY_TANK:
				item = new EnergyTank(this->getPositionX(), this->getPositionY());
				break;
			case LONG_BEAM:
				item = new LongBeam(this->getPositionX(), this->getPositionY());
				break;
			case ICE_BEAM:
				item = new IceBeam(this->getPositionX(), this->getPositionY());
				break;
			case MISSILE_ROCKET_BALL:
				item = new MissileRocketBall(this->getPositionX(), this->getPositionY());
				break;
			case BOMB_BALL:
				item = new BombBall(this->getPositionX(), this->getPositionY());
				break;
			case VARIA:
				item = new Varia(this->getPositionX(), this->getPositionY());
				break;
			}

			if (item != nullptr)
			{
				item->init();
				QuadTreeNode::getInstance()->insert(item);
			}
		}
	}
}

void BlueItemBall::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	if (_hitPoint > 0)
		_animation->draw(spriteHandle, viewport);
	else
		_effectAnimation->draw(spriteHandle, viewport);
}

void BlueItemBall::release()
{
	SAFE_DELETE(_animation);
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

void BlueItemBall::wasHit(int hitPoint)
{
	_hitPoint -= hitPoint;
}

bool BlueItemBall::isDead()
{
	return (_hitPoint <= 0);
}

float BlueItemBall::checkCollision(BaseObject* object, float dt)
{
	return 0;
}

eID BlueItemBall::getItemId()
{
	return _itemId;
}
