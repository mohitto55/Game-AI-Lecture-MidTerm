#include "LinkedList.h"
#include "GameObject.h"

void LinkedList::insert(int pos, GameObject* data)
{
    // ������ ���Ƴ����� üũ
    if (pos < 0 || pos > m_count)
        return;

    node* inData = new node(data);
    // ù ��° ��ġ�� ������ �߰�
    if (pos == 0 && m_count != 0) {
        inData->next = m_head;
        m_head = inData;
        m_count++;
    }
    else if (pos == m_count) {      // ������ ��ġ�� ������ �߰��ϴ� ���
        delete inData;
        append(data);
    }
    else {
        // pos-1��ġ���� ������ �̵�
        node* temp = m_head;
        for (int i = 0; i < pos - 1; i++)
            temp = temp->next;
        inData->next = temp->next;
        temp->next = inData;
        m_count++;
    }
}

// ������ ��ġ�� ������ �߰�
void LinkedList::append(GameObject* data)
{
    node* inData = new node(data);
    if (m_tail) {
        m_tail->next = inData;
        m_tail = inData;
    }
    else {  // m_tail == null �ΰ��
        m_head = inData;
        m_tail = inData;
    }
    m_count++;
}

void LinkedList::remove(int pos)
{
    // ���� �˻�
    if (pos < 0 || pos > m_count - 1 || !m_head)
        return;
    node* delNode;
    if (pos == 0) {     // ù��° ������ �����ϴ� ���
        delNode = m_head;
        m_head = m_head->next;
        if (m_count == 1)
            m_tail = m_head;
    }
    else {          // �߰� �����͸� �����ϴ� ���
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
    // ���� üũ
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
