#include "stdafx.h"
#include "Tail.h"


CTail::CTail(void)
	: m_NumPieces(0)
{
}


CTail::~CTail(void)
{
}


int CTail::GetRowOfPiece(int pos)
{
	return m_Tail[pos].m_Row;
}


int CTail::GetColOfPiece(int pos)
{
	return m_Tail[pos].m_Col;
}


int CTail::GetNumPieces(void)
{
	return m_NumPieces;
}


void CTail::AddPieceToStart(int row, int col, int movDir)
{
	item piece;
	piece.m_Row = row;
	piece.m_Col = col;
	piece.m_Type = movDir;
	m_Tail.insert(m_Tail.begin(), piece);
	m_NumPieces++;
}


void CTail::AddPieceToEnd(int row, int col, int movDir)
{
	item piece;					//create tail piece
	piece.m_Row = row;			//update internal struct`s variables
	piece.m_Col = col;
	piece.m_Type = movDir;
	m_Tail.push_back(piece);	//place created piece at the end of vector of structs
	m_NumPieces++;				//increment num of pieces
}


bool CTail::HasPieceAt(int row, int col)
{
	for(int i = 0; i < m_NumPieces; i++)
	{
		if(m_Tail[i].m_Row == row && m_Tail[i].m_Col == col)
			return true;
	}
	return false;
}


void CTail::Move(int headMovDir)
{
	for(int i = m_NumPieces - 1; i >= 0; i--)		//start at the end of a tail
	{
		switch( m_Tail[i].m_Type)	//set row or column position according to the direction of movement
		{
		case DOWN:					//DOWN
			if(m_Tail[i].m_Row < 18)
                m_Tail[i].m_Row++;
            else
                m_Tail[i].m_Row = 1;
            break;

        case RIGHT:					//RIGHT
			if(m_Tail[i].m_Col < 18)
                m_Tail[i].m_Col++;
            else
                m_Tail[i].m_Col = 1;
            break;

        case LEFT:					//LEFT
            if(m_Tail[i].m_Col > 1)
                m_Tail[i].m_Col--;
            else
                m_Tail[i].m_Col = 18;
            break;

        case UP:					//UP
            if(m_Tail[i].m_Row > 1)
                m_Tail[i].m_Row--;
            else
                m_Tail[i].m_Row = 18;
            break;
		}
		(i > 0) ? m_Tail[i].m_Type = m_Tail[i-1].m_Type : m_Tail[0].m_Type = headMovDir;	//  the direction of movement of this 
	}																						//	piece should be the same of the one before it
}
