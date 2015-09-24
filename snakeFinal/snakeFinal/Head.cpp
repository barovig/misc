#include "stdafx.h"
#include "Head.h"


CHead::CHead(void)
{
}


CHead::~CHead(void)
{
}


CHead::CHead(int row, int col, int movDir)
{
	m_Head.m_Row = row;
	m_Head.m_Col = col;
	m_Head.m_Type = movDir;
}

int CHead::GetRowPos(void)
{
	return m_Head.m_Row;
}


int CHead::GetColPos(void)
{
	return m_Head.m_Col;
}


int CHead::GetDirection(void)
{
	return m_Head.m_Type;
}

void CHead::Move(int direction)
{
	if(direction == UP)
		if( m_Head.m_Type == DOWN)
			direction = DOWN;

	if(direction == DOWN)
		if(m_Head.m_Type == UP )
			direction = UP;

	if(direction == LEFT)
		if(m_Head.m_Type == RIGHT)
			direction = RIGHT;

	if(direction == RIGHT)
		if(m_Head.m_Type == LEFT)
			direction = LEFT;

	switch(direction)
	{
	    case DOWN:					//DOWN
			if(m_Head.m_Row < 18)
                m_Head.m_Row++;
            else
                m_Head.m_Row = 1;
            break;

        case RIGHT:					//RIGHT
			if( m_Head.m_Col < 18)
                 m_Head.m_Col++;
            else
                 m_Head.m_Col = 1;
            break;

        case LEFT:					//LEFT
            if( m_Head.m_Col > 1)
                 m_Head.m_Col--;
            else
                 m_Head.m_Col = 18;
            break;

        case UP:					//UP
            if(m_Head.m_Row > 1)
                m_Head.m_Row--;
            else
                m_Head.m_Row = 18;
            break;
	}
	m_Head.m_Type = direction;
}


bool CHead::HasHeadAt(int row, int col)
{
	if(m_Head.m_Row == row && m_Head.m_Col == col )
		return true;
	else 
		return false;
}
