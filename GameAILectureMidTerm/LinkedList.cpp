#include "LinkedList.h"
#include "GameObject.h"

void LinkedList::insert(int pos, GameObject* data)
{
    // 범위가 벗아났는지 체크
    if (pos < 0 || pos > m_count)
        return;

    node* inData = new node(data);
    // 첫 번째 위치에 데이터 추가
    if (pos == 0 && m_count != 0) {
        inData->next = m_head;
        m_head = inData;
        m_count++;
    }
    else if (pos == m_count) {      // 마지막 위치에 데이터 추가하는 경우
        delete inData;
        append(data);
    }
    else {
        // pos-1위치까지 포인터 이동
        node* temp = m_head;
        for (int i = 0; i < pos - 1; i++)
            temp = temp->next;
        inData->next = temp->next;
        temp->next = inData;
        m_count++;
    }
}

// 마지막 위치에 데이터 추가
void LinkedList::append(GameObject* data)
{
    node* inData = new node(data);
    if (m_tail) {
        m_tail->next = inData;
        m_tail = inData;
    }
    else {  // m_tail == null 인경우
        m_head = inData;
        m_tail = inData;
    }
    m_count++;
}

void LinkedList::remove(int pos)
{
    // 범위 검사
    if (pos < 0 || pos > m_count - 1 || !m_head)
        return;
    node* delNode;
    if (pos == 0) {     // 첫번째 데이터 삭제하는 경우
        delNode = m_head;
        m_head = m_head->next;
        if (m_count == 1)
            m_tail = m_head;
    }
    else {          // 중간 데이터를 삭제하는 경우
        node* temp = m_head;
        for (int i = 0; i < pos - 1; i++)
            temp = temp->next;
        delNode = temp->next;
        temp->next = delNode->next;
        if (pos == m_count - 1)
            m_tail = temp;
    }
    delete delNode;
    m_count--;
}

void LinkedList::remove(GameObject* obj) {
    int pos = getPos(obj);
    if (pos != -1) {
        remove(pos);
    }
}
GameObject* LinkedList::retrieve(int pos)
{
    // 범위 체크
    if (pos < 0 || pos > m_count - 1 || !m_head)
        return nullptr;

    node* temp = m_head;
    for (int i = 0; i < pos; i++)
        temp = temp->next;
    return temp->data;
}

int LinkedList::getPos(GameObject* obj)
{
    int curPos = 0;
    int x = obj->GetX();
    int y = obj->GetY();

    node* curNode = m_head;
    for (curPos = 0; curPos < m_count; curPos++) {
        if (curNode->data->GetX() == x && curNode->data->GetY() == y) {
            return curPos;
        }
        curNode = curNode->next;
    }
    return -1;
}

void LinkedList::Update() {
    node* curNode = m_head;
    while (curNode != nullptr) {
        curNode->data->Update();
        curNode = curNode->next;
    }
}
void LinkedList::draw()
{
    node* temp = m_head;
    while (temp != nullptr) {
        temp->data->draw();
        temp = temp->next;
    }
}
