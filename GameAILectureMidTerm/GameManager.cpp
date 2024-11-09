#include "GameManager.h"
#include <random>
#include <algorithm>

void GameManager::initGame(std::vector<GameObject*> otherObjects, GameMap* map)
{
    this->objects = otherObjects;
    this->gameMap = map;

    std::find_if(otherObjects.begin(), otherObjects.end(), [this](GameObject* obj) {
        if (obj->GetType() == GameObjectType::EPACMAN) {
            this->SetPacman(static_cast<Pacman*>(obj));
            return true;
        }
        return false;
        });

}



std::vector<GameObject*> GameManager::GetGameObject(GameObjectType findType)
{
    std::vector<GameObject*> vec;
    for (int i = 0; i < objects.size(); i++) {
        if (objects[i]->GetType() == findType)
            vec.push_back(objects[i]);
    }
    return vec;
}


void GameManager::Update(float delta)
{
    for (int i = 0; i < objects.size(); i++) {
        objects[i]->Update(delta);
    }
    for (int i = 0; i < objects.size(); i++) {
        for (int k = 0; k < objects.size(); k++) {
            if (i != k) {
                if (objects[i]->IsSamePosition(objects[k]))
                    objects[i]->Collision(objects[k]);
            }
        }
    }
}

void GameManager::draw(float delta)
{
    textLine = 0;
    if (isGameOver) {
        if (blink <= 0) {
            blinkColor = blinkColor == EColor::WHITE ? EColor::BLUE : EColor::WHITE;
            blink = 0.5f;
        }
        blink -= delta;
        SetColor((int)blinkColor);
        ScreenClear();
        wchar_t szBuffers[20] = L"";
        swprintf(szBuffers, 20, L"(TT Game Over TT)");
        ScreenPrint(GameManager::getInstance()->GetMap()->getWidth() / 2, GameManager::getInstance()->GetMap()->getHeight() / 2, szBuffers);

        swprintf(szBuffers, 20, L"Score : %d", score);
        ScreenPrint(GameManager::getInstance()->GetMap()->getWidth() / 2, GameManager::getInstance()->GetMap()->getHeight() / 2 + 1, szBuffers);

        return;
    }

    if (isGameClear) {
        if (blink <= 0) {
            blinkColor = blinkColor == EColor::WHITE ? EColor::YELLOW : EColor::WHITE;
            blink = 0.5f;
        }
        blink -= delta;
        SetColor((int)blinkColor);
        ScreenClear();
        wchar_t szBuffers[20] = L"";
        swprintf(szBuffers, 20, L"(!!Game Clear!!)");
        ScreenPrint(GameManager::getInstance()->GetMap()->getWidth() / 2, GameManager::getInstance()->GetMap()->getHeight() / 2, szBuffers);

        swprintf(szBuffers, 20, L"Score : %d", score);
        ScreenPrint(GameManager::getInstance()->GetMap()->getWidth() / 2, GameManager::getInstance()->GetMap()->getHeight() / 2 + 1, szBuffers);

        return;
    }

    gameMap->draw();
    for (int i = 0; i < objects.size(); i++) {
        objects[i]->draw();
    }
    SetColor((int)EColor::WHITE);

    std::vector<GameObject*> pacmans = GameManager::getInstance()->GetGameObject(GameObjectType::EPACMAN);
    if (pacmans.size() > 0) {
        GameObject* pacman = pacmans[0];

        wchar_t szBuffers[30] = L"";
        swprintf(szBuffers, 30, L"(%d, %d)", pacman->GetX(), pacman->GetY());
        GameManager::getInstance()->PrintText(szBuffers);
        SetColor((int)EColor::YELLOW);
        swprintf(szBuffers, 30, L"Score : %d      ", score);
        GameManager::getInstance()->PrintText(szBuffers);
        swprintf(szBuffers, 30, L"LastCoin : %d      ", GameManager::getInstance()->GetMap()->GetCoinCount());
        GameManager::getInstance()->PrintText(szBuffers);
    }
   
}

void GameManager::AddObject(GameObject* gameObject)
{
    objects.push_back(gameObject);
}

void GameManager::SetTextColor(EColor color)
{
    SetColor((int)color);
}

void GameManager::PrintText(const wchar_t* t)
{
    if (!GetMap())
        return;
    ScreenPrint(0, GetMap()->getHeight() + textLine, t);
    textLine += 1;
}
