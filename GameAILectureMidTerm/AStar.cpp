#include "AStar.h"
#include "GameManager.h"
#include <queue>
#include <algorithm>
#include <list>
#include <unordered_set>
#include "math.h"

vector<Tile*> AStar::Pathfinding(int startX, int startY, int endX, int endY, bool findNeighbour)
{
    GameMap* map = GameManager::getInstance()->GetMap();
    if (findNeighbour) {
        if (map->getTile(endX, endY)->GetType() == GameObjectType::EWALL) {
            for (Tile* neighbour : map->GetNeighbourTiles(endX, endY)) {
                if (neighbour->GetType() != GameObjectType::EWALL) {
                    endX = neighbour->GetX();
                    endY = neighbour->GetY();
                }
            }
        }
    }

    for (int y = 0; y < map->getHeight(); y++) {
        for (int x = 0; x < map->getWidth(); x++) {
            Tile* tile = map->getTile(x, y);
            tile->gCost = 0;
            tile->hCost = 0;
        }
    }
    vector<Tile*> path;
    // 열린목록
    vector<Tile*> openSet;
    // 내부적으로 hashset과 같이 작용
    std::unordered_set<Tile*> closedSet;
    Tile* startNode = map->getTile(startX, startY);
    Tile* endNode = map->getTile(endX, endY);
    openSet.push_back(startNode);
    while (openSet.size() > 0) {
        Tile* node = openSet[0];
        // 열린 목록에서 비용이 가장 작은 노드를 가져온다.
        // fCost가 작고 fCost가 같다면 hCost가 작은순
        for (int i = 1; i < openSet.size(); i++) {
            if (openSet[i]->fCost() < node->fCost() || openSet[i]->fCost() == node->fCost()) {
                if (openSet[i]->hCost < node->hCost)
                    node = openSet[i];
            }
        }

        // 반복자를 이용하여 요소 삭제
        // 현재 탐색중인 노드는 openset에서 제거
        auto iter = std::find(openSet.begin(), openSet.end(), node);
        if (iter != openSet.end()) {
            openSet.erase(iter);
        }
        // Close Flag에 넣기
        closedSet.insert(node);

        // 최종경로 찾으면 반환
        if (node == endNode) {
            path = RetracePath(startNode, endNode);
            return path;
        }

        // 다음 탐색 노드를 설정하기 위해 현재 탐색중인 노드의 주변 노드들 검색
        for (Tile* neighbour : map->GetNeighbourTiles(node->GetX(), node->GetY())) {
            // 이웃이 벽이거나 이미 탐색한 곳이면 건너뛰기
            auto iter = closedSet.find(neighbour);
            if (neighbour->GetType() == GameObjectType::EWALL || iter != closedSet.end()) {
                continue;
            }
            // 새롭게 openset에 추가할 노드의 코스트 계산
            int newCostToNeighbour = node->gCost + GetDistance(node->GetX(), node->GetY(), neighbour->GetX(), neighbour->GetY());

            // 이미 openset에 넣은게 아니거나 이웃의 코스트가 새로운 코스트보다 크다면 새롭게 추가한다.
            auto openiter = std::find(openSet.begin(), openSet.end(), neighbour);
            if (newCostToNeighbour < neighbour->gCost || (openiter == openSet.end())) {
                neighbour->gCost = newCostToNeighbour;
                neighbour->hCost = GetDistance(neighbour, endNode);
                neighbour->parent = node;

                // closed에 담겨있지 않으면 추가한다.
                openiter = std::find(openSet.begin(), openSet.end(), neighbour);
                if (iter == closedSet.end())
                    openSet.push_back(neighbour);
            }
        }
    }
    return path;
}


int AStar::GetDistance(int x1, int y1, int x2, int y2)
{
    int dstX = abs(x1 - x2);
    int dstY = abs(y1 - y2);

    // 거리를 직접 연산하지 않고 근사치로 계산할 수 있다.
    if (dstX > dstY)
        return 14 * dstY + 10 * (dstX - dstY);
    return 14 * dstX + 10 * (dstY - dstX);
}

int AStar::GetDistance(GameObject* v1, GameObject* v2)
{
    int x1 = v1->GetX(), y1 = v1->GetY(), x2 = v2->GetX(), y2 = v2->GetY();
    return GetDistance(x1, y1, x2, y2);
}

vector<Tile*> AStar::RetracePath(Tile* startTile, Tile* endTile)
{
    vector<Tile*> path;
    Tile* curTile = endTile;

    while (curTile != startTile) {
        path.push_back(curTile);
        curTile = curTile->parent;
    }
    // 
    std::reverse(path.begin(), path.end());
    return path;
}
