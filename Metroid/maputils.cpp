﻿#include "maputils.h"

list<BaseObject*>* GetListObjectFromXML(const string path)
{
	xml_document doc;
	list<BaseObject*>* listObject = new list<BaseObject*>();

	auto result = doc.load_file(path.data(), pugi::parse_default | pugi::parse_pi);
	if (result == false)
		return listObject;

	auto map = doc.child("map");
	if (map == NULL)
		return listObject;

	auto mapHeight = 2 * map.attribute("tileheight").as_int() * map.attribute("height").as_int();

	xml_node objectGroup = map.child("objectgroup");
	if (objectGroup == NULL)
		return listObject;

	auto objects = objectGroup.children();
	for (auto object : objects)
	{
		int id = object.attribute("id").as_int();
		auto type = object.attribute("type").as_int();

		eID enumID;
		try
		{
			enumID = (eID)type;
		}
		catch (exception e)
		{
			continue;
		}

		auto baseObject = GetObjectById(object, enumID, mapHeight);
		if (baseObject != nullptr)
		{
			listObject->push_back(baseObject);
		}
	}

	return listObject;
}

map<string, string> GetObjectProperties(xml_node node)
{
	map<string, string> properties;

	// Lấy kích thước của object
	properties["x"] = node.attribute("x").as_string();
	properties["y"] = node.attribute("y").as_string();
	properties["width"] = node.attribute("width").as_string();
	properties["height"] = node.attribute("height").as_string();

	// Lấy các property của object
	auto params = node.child("properties");
	if (params)
	{
		for (auto item : params)
		{
			auto key = item.attribute("name").as_string();
			auto value = item.attribute("value").as_string();
			properties[key] = value;
		}
	}

	return properties;
}

BaseObject* GetObjectById(eID id, int left, int top, int right, int bottom, eMapDirection mapDirection, GVector2 mapDirectionAnchorPoint)
{
	switch (id)
	{
	case WALL:
	{
		auto wall = new Wall(left, bottom, right - left, top - bottom);
		wall->init();
		return wall;
		break;
	}
	case CHANGE_MAP_DIRECTION:
	{
		auto changeMapDirection = new ChangeMapDirection(left, bottom, right - left, top - bottom, mapDirection, mapDirectionAnchorPoint);
		changeMapDirection->init();
		return changeMapDirection;
		break;
	}
	case FIRE:
	{
		auto fire = new Fire(left, bottom, right - left, top - bottom);
		fire->init();
		return fire;
		break;
	}
	case BLUE_DOOR:
	{
		auto blueDoor = new BlueDoor(left, top);
		blueDoor->init();
		return blueDoor;
		break;
	}
	case RED_DOOR:
	{
		auto redDoor = new RedDoor(left, top);
		redDoor->init();
		return redDoor;
		break;
	}
	case BREAKABLE_BLUE_WALL:
	{
		auto breakableBlueWall = new BreakableBlueWall(left, top);
		breakableBlueWall->init();
		return breakableBlueWall;
		break;
	}
	case BREAKABLE_RED_WALL:
	{
		auto breakableRedWall = new BreakableRedWall(left, top);
		breakableRedWall->init();
		return breakableRedWall;
		break;
	}
	case RIPPER:
	{
		auto ripper = new Ripper(left, top);
		ripper->init();
		return ripper;
		break;
	}
	case WAVER:
	{
		auto waver = new Waver(left, top, false);
		waver->init();
		return waver;
		break;
	}
	case SKREE:
	{
		auto skree = new Skree(left, top);
		skree->init();
		return skree;
		break;
	}
	case MELLOW:
	{
		auto mellow = new Mellow(left, top, false);
		mellow->init();
		return mellow;
		break;
	}
	case RIO:
	{
		auto rio = new Rio(left, top, false);
		rio->init();
		return rio;
		break;
	}
	case ZEB_PIPE:
	{
		auto zebPipe = new ZebPipe(left, bottom, right - left, top - bottom);
		zebPipe->init();
		return zebPipe;
		break;
	}
	case ZOOMER:
	{
		auto zoomer = new Zoomer(left, top);
		zoomer->init();
		return zoomer;
		break;
	}
	case ENERGY_TANK:
	{
		auto energyTank = new EnergyTank(left, top);
		energyTank->init();
		return energyTank;
		break;
	}
	case ENERGY_BALL:
	{
		auto energyBall = new EnergyBall(left, top);
		energyBall->init();
		return energyBall;
		break;
	}
	case MARU_MARI:
	{
		auto maruMari = new MaruMari(left, top);
		maruMari->init();
		return maruMari;
		break;
	}
	case LONG_BEAM:
	{
		auto longBeam = new LongBeam(left, top);
		longBeam->init();
		return longBeam;
		break;
	}
	case ICE_BEAM:
	{
		auto iceBeam = new IceBeam(left, top);
		iceBeam->init();
		return iceBeam;
		break;
	}
	case MISSILE_ROCKET_BALL:
	{
		auto missileRocketBall = new MissileRocketBall(left, top);
		missileRocketBall->init();
		return missileRocketBall;
		break;
	}
	case BOMB_BALL:
	{
		auto bombBall = new BombBall(left, top);
		bombBall->init();
		return bombBall;
		break;
	}
	case VARIA:
	{
		auto varia = new Varia(left, top);
		varia->init();
		return varia;
		break;
	}
	default:
		return nullptr;
	}
}

BaseObject* GetObjectById(xml_node item, eID id, int mapHeight)
{
	switch (id)
	{
	case WALL:
		return GetWall(item, mapHeight);
		break;
	case CHANGE_MAP_DIRECTION:
		return GetChangeMapDirection(item, mapHeight);
		break;
	case FIRE:
		return GetFire(item, mapHeight);
		break;
	case BLUE_DOOR:
		return GetBlueDoor(item, mapHeight);
		break;
	case RED_DOOR:
		return GetRedDoor(item, mapHeight);
		break;
	case BREAKABLE_BLUE_WALL:
		return GetBreakableBlueWall(item, mapHeight);
		break;
	case BREAKABLE_RED_WALL:
		return GetBreakableRedWall(item, mapHeight);
		break;
	case RIPPER:
		return GetRipper(item, mapHeight);
		break;
	case WAVER:
		return GetWaver(item, mapHeight);
		break;
	case SKREE:
		return GetSkree(item, mapHeight);
		break;
	case MELLOW:
		return GetMellow(item, mapHeight);
		break;
	case RIO:
		return GetRio(item, mapHeight);
		break;
	case ZEB_PIPE:
		return GetZebPipe(item, mapHeight);
		break;
	case ZOOMER:
		return GetZoomer(item, mapHeight);
		break;
	case ENERGY_TANK:
		return GetEnergyTank(item, mapHeight);
		break;
	case ENERGY_BALL:
		return GetEnergyBall(item, mapHeight);
		break;
	case MARU_MARI:
		return GetMaruMari(item, mapHeight);
		break;
	case LONG_BEAM:
		return GetLongBeam(item, mapHeight);
		break;
	case ICE_BEAM:
		return GetIceBeam(item, mapHeight);
		break;
	case MISSILE_ROCKET_BALL:
		return GetMissileRocketBall(item, mapHeight);
		break;
	case BOMB_BALL:
		return GetBombBall(item, mapHeight);
		break;
	case VARIA:
		return GetVaria(item, mapHeight);
		break;
	default:
		return nullptr;
	}
}

BaseObject* GetWall(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	// Do tọa độ được tạo từ Tiled Map Editor là top-left, nên ta chuyển về tọa độ world (x, y)
	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	auto wall = new Wall(x, y, width, height);
	wall->init();
	return wall;
}

BaseObject* GetChangeMapDirection(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	// Do tọa độ được tạo từ Tiled Map Editor là top-left, nên ta chuyển về tọa độ world (x, y)
	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	auto mapDirection = (eMapDirection)stoi(properties["direction"]);
	auto anchorPointX = 2 * stoi(properties["anchorpointx"]);
	auto anchorPointY = mapHeight - 2 * stoi(properties["anchorpointy"]) - height;
	auto mapDirectionAnchorPoint = GVector2(anchorPointX, anchorPointY);

	auto changeMapDirection = new ChangeMapDirection(x, y, width, height, mapDirection, mapDirectionAnchorPoint);
	changeMapDirection->init();
	return changeMapDirection;
}

BaseObject* GetFire(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	auto fire = new Fire(x, y, width, height);
	fire->init();
	return fire;
}

BaseObject* GetBlueDoor(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto blueDoor = new BlueDoor(x, y);
	blueDoor->init();
	return blueDoor;
}

BaseObject* GetRedDoor(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto redDoor = new RedDoor(x, y);
	redDoor->init();
	return redDoor;
}

BaseObject* GetBreakableBlueWall(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto breakableBlueWall = new BreakableBlueWall(x, y);
	breakableBlueWall->init();
	return breakableBlueWall;
}

BaseObject* GetBreakableRedWall(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto breakableRedWall = new BreakableRedWall(x, y);
	breakableRedWall->init();
	return breakableRedWall;
}

BaseObject* GetRipper(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto ripper = new Ripper(x, y);
	ripper->init();
	return ripper;
}

BaseObject* GetWaver(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	auto waver = new Waver(x, y, false);
	waver->init();
	return waver;
}

BaseObject* GetSkree(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	auto skree = new Skree(x, y);
	skree->init();
	return skree;
}

BaseObject* GetMellow(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto mellow = new Mellow(x, y, false);
	mellow->init();
	return mellow;
}

BaseObject* GetRio(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	auto rio = new Rio(x, y, false);
	rio->init();
	return rio;
}

BaseObject* GetZebPipe(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	auto zebPipe = new ZebPipe(x, y, width, height);
	zebPipe->init();
	return zebPipe;
}

BaseObject* GetZoomer(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	auto zoomer = new Zoomer(x, y);
	zoomer->init();
	return zoomer;
}

BaseObject* GetEnergyTank(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto energyTank = new EnergyTank(x, y);
	energyTank->init();
	return energyTank;
}

BaseObject* GetEnergyBall(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto energyBall = new EnergyBall(x, y);
	energyBall->init();
	return energyBall;
}

BaseObject* GetMaruMari(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto maruMari = new MaruMari(x, y);
	maruMari->init();
	return maruMari;
}

BaseObject* GetLongBeam(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto longBeam = new LongBeam(x, y);
	longBeam->init();
	return longBeam;
}

BaseObject* GetIceBeam(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto iceBeam = new IceBeam(x, y);
	iceBeam->init();
	return iceBeam;
}

BaseObject* GetMissileRocketBall(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto missileRocketBall = new MissileRocketBall(x, y);
	missileRocketBall->init();
	return missileRocketBall;
}

BaseObject* GetBombBall(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto bombBall = new BombBall(x, y);
	bombBall->init();
	return bombBall;
}

BaseObject* GetVaria(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto varia = new Varia(x, y);
	varia->init();
	return varia;
}
