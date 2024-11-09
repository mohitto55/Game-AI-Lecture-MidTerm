#pragma once
class gameCursor {
	int x;
	int y;
public:
	gameCursor(int x = 0, int y = 0) {
		this->x = x;
		this->y = y;
	}
	int GetX() { return x; }
	int GetY() { return y; }

	void SetXY(int x, int y) {
		this->x = x;
		this->y = y;
	}
	void Up() { y--; }
	void Down() { y++; }
	void Left() { x--; }
	void Right() { x++; }

	void Draw();
};