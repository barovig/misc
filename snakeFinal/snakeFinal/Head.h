#pragma once

using namespace std;

struct item
{
	int m_Row;
	int m_Col;
	int m_Type;
};

enum items { DOWN = 1, RIGHT, LEFT, UP, HEAD, TAIL, APPLE, PAPPLE, GRENADE
};

class CHead
{
public:
	CHead(void);
	~CHead(void);
private:
	item m_Head;
public:
	CHead(int row, int col, int movDir);
	int GetRowPos(void);
	int GetColPos(void);
	int GetDirection(void);
	void Move(int direction);
	bool HasHeadAt(int row, int col);
};

