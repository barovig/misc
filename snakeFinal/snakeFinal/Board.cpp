#include "stdafx.h"
#include "Board.h"


CBoard::CBoard(void)
	: m_Score(0)
	, appleShown(true)
	, pappleShown(false)
	, grenadeShown(false)
{
	m_Apple.m_Type = APPLE;
	m_PApple.m_Type = PAPPLE;
	m_Grenade.m_Type = GRENADE;



	// initialize frame
	for(int row = 0; row < 20; row++)
	{
		for(int col = 0; col < 20; col++)
		{
			if(row == 0 || row == 19 ||col == 0 || col == 19)
                m_Frame[row][col] = 1;		//border
            else
                m_Frame[row][col] = NULL;
		}
	}
}


CBoard::~CBoard(void)
{
}




int CBoard::HasItemAt(int row, int col)
{
	if(m_Apple.m_Row == row && m_Apple.m_Col == col)
		return APPLE;

	else if(m_PApple.m_Row == row && m_PApple.m_Col == col)
		if(pappleShown)
			return PAPPLE;
		else
			return NULL;

	else if(m_Grenade.m_Row == row && m_Grenade.m_Col == col)
		if(grenadeShown)
			return GRENADE;
		else
			return NULL;

	else
		return NULL;
}


void CBoard::CreateApple(CHead& head, CTail& tail)		//creates Apple and fills m_Apple coords
{
//	srand((int)10 *sin(time(0)));

	do{
		m_Apple.m_Row = rand() % 18 + 1;
		m_Apple.m_Col= rand() % 18 + 1;
	} while(head.HasHeadAt(m_Apple.m_Row, m_Apple.m_Col) || tail.HasPieceAt(m_Apple.m_Row, m_Apple.m_Col) || (m_Apple.m_Row == m_PApple.m_Row && m_Apple.m_Col == m_PApple.m_Col) 
		||   (m_Apple.m_Row == m_Grenade.m_Row && m_Apple.m_Col == m_Grenade.m_Col) );

}


void CBoard::CreatePApple(CHead& head, CTail& tail)		//creates PApple and fills m_PApple coords
{
//	srand((int)10 *sin(time(0)));
	do{
		m_PApple.m_Row = rand() % 18 + 1;
		m_PApple.m_Col= rand() % 18 + 1;
	} while(head.HasHeadAt(m_PApple.m_Row, m_PApple.m_Col) || tail.HasPieceAt(m_PApple.m_Row, m_PApple.m_Col) || (m_PApple.m_Row == m_Apple.m_Row && m_PApple.m_Col == m_Apple.m_Col) 
		||   (m_PApple.m_Row == m_Grenade.m_Row && m_PApple.m_Col == m_Grenade.m_Col) );
	
}


void CBoard::CreateGrenade(CHead& head, CTail& tail)
{
//	srand((int)10 *sin(time(0)));
	do{
		m_Grenade.m_Row = rand() % 18 + 1;
		m_Grenade.m_Col= rand() % 18 + 1;
	} while(head.HasHeadAt(m_Grenade.m_Row, m_Grenade.m_Col) || tail.HasPieceAt(m_Grenade.m_Row, m_Grenade.m_Col) || (m_Grenade.m_Row == m_Apple.m_Row && m_Grenade.m_Col == m_Apple.m_Col) || (m_Grenade.m_Row == m_PApple.m_Row && m_Grenade.m_Col == m_PApple.m_Col) );
	
}


void CBoard::UpdateScore(int score)
{
	m_Score += score;
}

void CBoard::ShowFrame(void)
{
	for(int row = 0; row < 20; row++)
	{
		for(int col = 0; col < 20; col++)
		{
			if(m_Frame[row][col] == 1)
				cout << (char)0xDB;
			else
				cout << (char)NULL;
		}
		cout << endl;
	}
}


void CBoard::FillFrame(CHead& head, CTail& tail)
{
	m_Frame[ head.GetRowPos() ][ head.GetColPos() ] = HEAD;

	for(int i = 0; i < tail.GetNumPieces(); i++)
	{
		m_Frame[ tail.GetRowOfPiece(i) ][ tail.GetColOfPiece(i) ] = TAIL;
	}

	m_Frame[ m_Apple.m_Row ][ m_Apple.m_Col ] = APPLE;

	if(pappleShown)
		m_Frame[ m_PApple.m_Row ][ m_PApple.m_Col ] = PAPPLE;

	if(grenadeShown)
		m_Frame[ m_Grenade.m_Row ][ m_Grenade.m_Col ] = GRENADE;
}


void CBoard::FillConsole(CHead& head, CTail& tail)
{
	char c = (char)0xDB;
	WriteCharToConsole(head.GetRowPos(), head.GetColPos(), &c);

	for(int i = 0; i < tail.GetNumPieces(); i++)
	{
		WriteCharToConsole(tail.GetRowOfPiece(i), tail.GetColOfPiece(i), &c);
	}

	c = 'o';
	WriteCharToConsole( m_Apple.m_Row, m_Apple.m_Col, &c);

	if(pappleShown)
	{
		c = '$';
		WriteCharToConsole( m_PApple.m_Row, m_PApple.m_Col, &c );
	}

	if(grenadeShown)
	{
		c = '@';
		WriteCharToConsole( m_Grenade.m_Row, m_Grenade.m_Col, &c );
	}
}


void CBoard::WriteCharToConsole(int row, int col, char* c)
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInf;
	cursorInf.bVisible = false;
	cursorInf.dwSize = 1;
	SetConsoleCursorInfo(hOutput, &cursorInf);

	COORD coord = {col, row};
	SetConsoleCursorPosition(hOutput, coord);
	WriteConsoleA(hOutput, c, 1, NULL, NULL);	
}


void CBoard::UpdateScreen(CHead& head, CTail& tail)
{
	char c = (char)NULL;

	for(int row = 1; row < 19; row++)
	{	for(int col = 1; col < 19; col++)
		{	if(m_Frame[row][col] != NULL)
			{	
				if( !HasItemAt(row,col) && !head.HasHeadAt(row,col) && !tail.HasPieceAt(row,col) )
				{
					WriteCharToConsole(row, col, &c);
					m_Frame[row][col] = NULL;
				}

			}
		}
	}


	if(!grenadeShown)
	{

	}
}


int CBoard::GetScore(void)
{
	return m_Score;
}


void CBoard::DeletePineapple(void)
{
	char c = (char)NULL;
	WriteCharToConsole(m_PApple.m_Row, m_PApple.m_Col, &c);
	m_Frame[m_PApple.m_Row][ m_PApple.m_Col] = NULL;
}


void CBoard::DeleteGrenade(void)
{
	char c = (char)NULL;
	WriteCharToConsole(m_Grenade.m_Row, m_Grenade.m_Col, &c);
	m_Frame[m_Grenade.m_Row][ m_Grenade.m_Col] = NULL;
}
