#include "Tile.h"

void Tile::SetType(GameObjectType type)
{
	switch (type)
	{
	case GameObjectType::ESPACE:
		SetImgColor(EColor::WHITE);
		break;
	case GameObjectType::EWALL:
		SetImgColor(EColor::WHITE);
		break;
	case GameObjectType::EITEM:
		SetImgColor(EColor::WHITE);
		break;
	case GameObjectType::ECOIN:
		SetImgColor(EColor::YELLOW);
		break;
	default:
		break;
	}
	__super::SetType(type);
}
