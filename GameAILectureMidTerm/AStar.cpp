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
    // �������
    vector<Tile*> openSet;
    // ���������� hashset�� ���� �ۿ�
    std::unordered_set<Tile*> closedSet;
    Tile* startNode = map->getTile(startX, startY);
    Tile* endNode = map->getTile(endX, endY);
    openSet.push_back(startNode);
    while (openSet.size() > 0) {
        Tile* node = openSet[0];
        // ���� ��Ͽ��� ����� ���� ���� ��带 �����´�.
        // fCost�� �۰� fCost�� ���ٸ� hCost�� ������
        for (int i = 1; i < openSet.size(); i++) {
            if (openSet[i]->fCost() < node->fCost() || openSet[i]->fCost() == node->fCost()) {
                if (openSet[i]->hCost < node->hCost)
                    node = openSet[i];
            }
        }

        // �ݺ��ڸ� �̿��Ͽ� ��� ����
        // ���� Ž������ ���� openset���� ����
        auto iter = std::find(openSet.begin(), openSet.end(), node);
        if (iter != openSet.end()) {
            openSet.erase(iter);
        }
        // Close Flag�� �ֱ�
        closedSet.insert(node);

        // ������� ã���� ��ȯ
        if (node == endNode) {
            path = RetracePath(startNode, endNode);
            return path;
        }

        // ���� Ž�� ��带 �����ϱ� ���� ���� Ž������ ����� �ֺ� ���� �˻�
        for (Tile* neighbour : map->GetNeighbourTiles(node->GetX(), node->GetY())) {
            // �̿��� ���̰ų� �̹� Ž���� ���̸� �ǳʶٱ�
            auto iter = closedSet.find(neighbour);
            if (neighbour->GetType() == GameObjectType::EWALL || iter != closedSet.end()) {
                continue;
            }
            // ���Ӱ� openset�� �߰��� ����� �ڽ�Ʈ ���
            int newCostToNeighbour = node->gCost + GetDistance(node->GetX(), node->GetY(), neighbour->GetX(), neighbour->GetY());

            // �̹� openset�� ������ �ƴϰų� �̿��� �ڽ�Ʈ�� ���ο� �ڽ�Ʈ���� ũ�ٸ� ���Ӱ� �߰��Ѵ�.
            auto openiter = std::find(openSet.begin(), openSet.end(), neighbour);
            if (newCostToNeighbour < neighbour->gCost || (openiter == openSet.end())) {
                neighbour->gCost = newCostToNeighbour;
                neighbour->hCost = GetDistance(neighbour, endNode);
                neighbour->parent = node;

                // closed�� ������� ������ �߰��Ѵ�.
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

    // �Ÿ��� ���� �������� �ʰ� �ٻ�ġ�� ����� �� �ִ�.
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
