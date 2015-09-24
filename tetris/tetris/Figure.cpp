#include "stdafx.h"
#include "Figure.h"


CFigure::CFigure(void) 
	: m_Prop(EMPTY)
	, m_RotState(0)
{
	m_Pivot.x = 0;		//set pivot to zero by default
	m_Pivot.y = 0;
}


CFigure::~CFigure(void)
{
}


void CFigure::Rotate(void)
{
	//for(auto& p : m_ptList)
	//{
	//	// translate point back to origin:
	//	p.x -= m_Pivot.x;
	//	p.y -= m_Pivot.y;

	//	// rotate point
	//	int xnew = -p.y;
	//	int ynew = p.x;

	//	// translate point back:
	//	p.x= xnew + m_Pivot.x;
	//	p.y = ynew + m_Pivot.y;
	//}
	switch(m_Prop)
	{
	case TAP:
		RotateTap();
		break;
	case LZAG:
		RotateLZag();
		break;
	case RZAG:
		RotateRZag();
		break;
	case BAR:
		RotateBar();
		break;
	case CUBE:
		break;
	case LHOOK:
		RotateLHook();
		break;
	case RHOOK:
		RotateRHook();
		break;
	}

}


void CFigure::MoveDown(void)
{
	for(auto& p : m_ptList)
		p.y += 1;

	m_Pivot.y += 1; 
}


void CFigure::SetPivot(int px, int py)
{
	m_Pivot.x = px;
	m_Pivot.y = py;
}


void CFigure::SetPointList(vector<p> pList)
{
	m_ptList = pList;
}


vector<p> CFigure::GetPointList(void)
{
	return m_ptList;
}


void CFigure::MoveLeft(void)
{
	for(auto& p : m_ptList)
		p.x -= 1;

	m_Pivot.x -= 1; 
}


void CFigure::MoveRight(void)
{
	for(auto& p : m_ptList)
		p.x += 1;

	m_Pivot.x += 1; 
}


Prop CFigure::GetProperty(void)
{
	return m_Prop;
}


void CFigure::SetProperty(Prop prop)
{
	m_Prop = prop;
}

bool p::operator!=(const p& other)
{
	if(x == other.x && y == other.y )
		return false;
	else
		return true;
}

void CFigure::RotateTap(void)
{
	if(m_RotState != 3)
		m_RotState++;
	else
		m_RotState = 0;

	p p1 = m_Pivot, 
	  p2 = m_Pivot,
   	  p3 = m_Pivot,
	  p4 = m_Pivot;

	vector<p> pList;

	switch(m_RotState)
	{
	case 0:
		p2.x = p1.x + 1;
		p3.y = p1.y + 1;
		p4.y = p1.y - 1;
		break;
	case 1:
		p2.x = p1.x + 1;
		p3.x = p1.x - 1;
		p4.y = p1.y + 1;
		break;
	case 2:
		p2.y = p1.y - 1;
		p3.y = p1.y + 1;
		p4.x = p1.x - 1;
		break;
	case 3:
		p2.y = p1.y - 1;
		p3.x = p1.x + 1;
		p4.x = p1.x - 1;
		break;
	}

	pList.push_back(p1);
	pList.push_back(p2);
	pList.push_back(p3);
	pList.push_back(p4);

	m_ptList = pList;
}

void CFigure::RotateLZag(void)
{
	if(m_RotState == 0)
		m_RotState = 1;
	else
		m_RotState = 0;

	p p1 = m_Pivot, 
	  p2 = m_Pivot,
   	  p3 = m_Pivot,
	  p4 = m_Pivot;

	switch(m_RotState)
	{
	case 0:
		p2.x = p1.x + 1;
		p2.y = p1.y - 1;
		p3.x = p1.x + 1;
		p4.y = p1.y + 1;
		break;
	case 1:
		p2.x = p1.x - 1;
		p2.y = p1.y - 1;
		p3.y = p1.y - 1;
		p4.x = p1.x + 1;
		break;
	}

	vector<p> pList;
	pList.push_back(p1);
	pList.push_back(p2);
	pList.push_back(p3);
	pList.push_back(p4);

	m_ptList = pList;
}


void CFigure::RotateRZag(void)
{
	if(m_RotState == 0)
		m_RotState = 1;
	else
		m_RotState = 0;

	p p1 = m_Pivot, 
	  p2 = m_Pivot,
   	  p3 = m_Pivot,
	  p4 = m_Pivot;

	switch(m_RotState)
	{
	case 0:
		p2.y = p1.y - 1;
		p3.x = p1.x + 1;
		p4.y = p1.y + 1;
		p4.x = p1.x + 1;
		break;
	case 1:
		p2.x = p1.x + 1;
		p2.y = p1.y - 1;
		p3.y = p1.y - 1;
		p4.x = p1.x - 1;
		break;
	}

	vector<p> pList;
	pList.push_back(p1);
	pList.push_back(p2);
	pList.push_back(p3);
	pList.push_back(p4);

	m_ptList = pList;
}


void CFigure::RotateBar(void)
{
	if(m_RotState == 0)
		m_RotState = 1;
	else
		m_RotState = 0;

	p p1 = m_Pivot, 
	  p2 = m_Pivot,
   	  p3 = m_Pivot,
	  p4 = m_Pivot;

	switch(m_RotState)
	{
	case 0:
		p2.y = p1.y - 1;
		p3.y = p1.y + 1;
		p4.y = p1.y + 2;
		break;
	case 1:
		p2.x = p1.x - 1;
		p3.x = p1.x + 1;
		p4.x = p1.x + 2;
		break;
	}

	vector<p> pList;
	pList.push_back(p1);
	pList.push_back(p2);
	pList.push_back(p3);
	pList.push_back(p4);

	m_ptList = pList;
}


void CFigure::RotateLHook(void)
{
	if(m_RotState != 3)
		m_RotState++;
	else
		m_RotState = 0;

	p p1 = m_Pivot, 
	  p2 = m_Pivot,
   	  p3 = m_Pivot,
	  p4 = m_Pivot;

	vector<p> pList;

	switch(m_RotState)
	{
	case 0:
		p2.x = p1.x - 1;
		p2.y = p1.y - 1;
		p3.y = p1.y - 1;
		p4.y = p1.y + 1;
		break;
	case 1:
		p2.x = p1.x + 1;
		p2.y = p1.y - 1;
		p3.x = p1.x + 1;
		p4.x = p1.x - 1;
		break;
	case 2:
		p2.y = p1.y - 1;
		p3.y = p1.y + 1;
		p4.x = p1.x + 1;
		p4.y = p1.y + 1;
		break;
	case 3:
		p2.x = p1.x + 1;
		p3.x = p1.x - 1;
		p4.x = p1.x - 1;
		p4.y = p1.y + 1;
		break;
	}

	pList.push_back(p1);
	pList.push_back(p2);
	pList.push_back(p3);
	pList.push_back(p4);

	m_ptList = pList;
}



void CFigure::RotateRHook(void)
{
	if(m_RotState != 3)
		m_RotState++;
	else
		m_RotState = 0;

	p p1 = m_Pivot, 
	  p2 = m_Pivot,
   	  p3 = m_Pivot,
	  p4 = m_Pivot;

	vector<p> pList;

	switch(m_RotState)
	{
	case 0:
		p2.x = p1.x + 1;
		p2.y = p1.y - 1;
		p3.y = p1.y - 1;
		p4.y = p1.y + 1;
		break;
	case 1:
		p2.x = p1.x + 1;
		p2.y = p1.y + 1;
		p3.x = p1.x + 1;
		p4.x = p1.x - 1;
		break;
	case 2:
		p2.x = p1.x - 1;
		p2.y = p1.y + 1;
		p3.y = p1.y + 1;
		p4.y = p1.y - 1;
		break;
	case 3:
		p2.x = p1.x - 1;
		p2.y = p1.y - 1;
		p3.x = p1.x - 1;
		p4.x = p1.x + 1;
		break;
	}

	pList.push_back(p1);
	pList.push_back(p2);
	pList.push_back(p3);
	pList.push_back(p4);

	m_ptList = pList;
}