#pragma once
#include "Head.h"
#include <vector>

class CTail
{
public:
	CTail(void);
	~CTail(void);
private:
	vector<item> m_Tail;
	int m_NumPieces;
public:
	int GetRowOfPiece(int pos);
	int GetColOfPiece(int pos);
	int GetNumPieces(void);
	void AddPieceToStart(int row, int col, int movDir);
	void AddPieceToEnd(int row, int col, int movDir);
	bool HasPieceAt(int row, int col);
	void Move(int headMovDir);
};

