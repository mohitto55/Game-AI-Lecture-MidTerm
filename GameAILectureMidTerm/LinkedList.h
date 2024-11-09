#pragma once
class GameObject;

struct node {
	GameObject* data;
	node* next;
	node(GameObject* d) { data = d; next = nullptr; }
};

class LinkedList
{
	node* m_head;
	node* m_tail;
	int m_count;
public:
	LinkedList() : m_head(nullptr), m_tail(nullptr), m_count(0) { }
	~LinkedList() {
		if (m_head) {
			while (m_head != nullptr)
				remove(0);
		}	
	}

	void insert(int pos, GameObject* data);
	void append(GameObject* data);				// 마지막 위치에 데이터 추가
	void remove(int pos);
	void remove(GameObject* obj);
	GameObject* retrieve(int pos);
	int getPos(GameObject* obj);
	int getCount() { return m_count; }

	void Update();

	bool isEmpty() { return m_head == nullptr; }
	void draw();
};

