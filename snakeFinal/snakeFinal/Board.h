#pragma once
#include "Tail.h"
#include "head.h"

class CBoard
{
public:
	CBoard(void);	//default constructor will initalize all data members
	~CBoard(void);
private:
	item m_Apple;
	item m_PApple;
	item m_Grenade;
	int m_Score;
	int m_Frame[20][20];	



public:	
//flags stating whether item should be visible. possibly should incorporate these into "item" struct

	bool appleShown;	///shown by default (initialized with default constructor)
	bool pappleShown;
	bool grenadeShown;

// member functions
	int HasItemAt(int row, int col);
	void CreateApple(CHead& head, CTail& tail);
	void CreatePApple(CHead& head, CTail& tail);
	void CreateGrenade(CHead& head, CTail& tail);
	void UpdateScore(int score);
	void ShowFrame(void);



	void FillFrame(CHead& head, CTail& tail);
	void FillConsole(CHead& head, CTail& tail);
	void WriteCharToConsole(int row, int col, char* c);
	void UpdateScreen(CHead& head, CTail& tail);
	int GetScore(void);
	void DeletePineapple(void);
	void DeleteGrenade(void);
};

