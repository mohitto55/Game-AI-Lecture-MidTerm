#include "GameManager.h"
#include "GameMap.h"
#include "Enemy.h"
#include "Pacman.h"

GameMap::GameMap(int w, int h) : width(w), height(h)
{
    map = new Tile * [h];
    //GameMap::Instance = this;
    for (int i = 0; i < h; i++) {
        map[i] = new Tile[w];
    }
    initMap();
}


GameMap::GameMap(int** _map, int w, int h, std::vector<GameObject*>& generatedObjects) : width(w), height(h)
{
    map = new Tile * [h];

    for (int i = 0; i < h; i++) {
        map[i] = new Tile[w];
    }
    // 맵노드가 1이면 벽으로 친다.
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            switch (_map[y][x])
            {
            case (int)GameObjectType::ESPACE:
                map[y][x] = Tile(x, y, COIN, GameObjectType::ECOIN);
                map[y][x].SetImgColor(EColor::YELLOW);
                coinCount++;
                    break;
            case (int)GameObjectType::EWALL:
                map[y][x] = Tile(x, y, WALL, GameObjectType::EWALL);
                break;
            case (int)GameObjectType::EENEMY: 
                map[y][x] = Tile(x, y, SPACE, GameObjectType::ESPACE);
                {
                    Enemy* enemy = new Enemy(x, y, ENEMY, GameObjectType::EENEMY);
                    enemy->SetImgColor(EColor::RED);
                    enemy->ChangeState(new HunterState());
                    generatedObjects.push_back(enemy);
                }
                break;
            case (int)GameObjectType::EPACMAN: 
                map[y][x] = Tile(x, y, SPACE, GameObjectType::ESPACE);
                {
                Pacman* pacman = new Pacman(x, y, NONEDIR, UPIMG, GameObjectType::EPACMAN);
                pacman->SetImgColor(EColor::SKY);
                generatedObjects.push_back(pacman);
                }
                break;
            
            case (int)GameObjectType::EITEM:
                map[y][x] = Tile(x, y, ITEM, GameObjectType::EITEM);
                map[y][x].SetImgColor(EColor::YELLOW);
                break;
            case (int)GameObjectType::ECOIN:
                map[y][x] = Tile(x, y, COIN, GameObjectType::ECOIN);
                map[y][x].SetImgColor(EColor::YELLOW);
                coinCount++;
                break;
            }
        }
    }
    initMap();
}

GameMap::~GameMap()
{
    if (map) {
        for (int i = 0; i < height; i++) {
            delete[] map[i];
        }
        delete[] map;
    }
}

// 맵 가장자리에 벽을 생성한다.
void GameMap::initMap()
{
    //if (GameMap::Instance == nullptr)
    //    GameMap::Instance = this;

    // 외각 생성하기
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
                map[y][x] = Tile(x, y, WALL, GameObjectType::EWALL);
            }
        }
    }
}

Tile* GameMap::getTile(int x, int y)
{
    if(InMap(x,y))
        return &map[y][x];
    return nullptr;
}

void GameMap::setTile(int x, int y, Tile obj)
{
    map[y][x] = obj;
}

bool GameMap::InMap(int x,int y)
{
    if (0 <= x && x < width && 0 <= y && y < height)
        return true;
    return false;
}

vector<Tile*> GameMap::GetNeighbourTiles(int x, int y)
{
    int dx[4] = { 0,1,0,-1 };
    int dy[4] = { 1,0,-1,0 };
    vector<Tile*> vec;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        Tile* meighbourTile = getTile(nx, ny);
        if (meighbourTile != nullptr)
            vec.push_back(meighbourTile);
    }
    return vec;
}

void GameMap::draw()
{
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            map[y][x].draw();
        }
    }
}
