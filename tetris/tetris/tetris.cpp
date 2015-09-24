// tetris.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Figure.h"

using namespace std;

// define dimensions
const int ROWS = 18;
const int COLS = 12;

//globals
bool endGame = false;
int waitTime = 10;
// property grid
int propGrid[ROWS][COLS];

int GetConsoleColour(CFigure& figure);


// copies figures property into the propGrid's points at figures location
void CopyIntoGrid(CFigure figure);

//checks whether a figure can be placed at its current position
bool IsValid(CFigure figure);

//writes char to console at specified position without redrawing entire console
void WriteCharToConsole(int row, int col, char* c, int colour);
void WriteCharToConsole(int row, int col, char* c);

//helper function that takes member function pointer(implemented using stl function<> ) to figure.method() as parameter 
void MoveFigure(function<void (void)> figureMethod, CFigure& figure );

//function that moves figure down and does additional work
void MoveFigureDown(CFigure& figure);

//function destroys line at position row
void DestroyLine(int n);

//checks if line can be destroyed - returns zero if nothing found
void LineCheck(void);
//helpers
void DisplayBoard(void);
void InitPropGrid(void);
CFigure GenerateFigure(void);
CFigure CreateTap(void);
CFigure CreateBar(void);
CFigure CreateCube(void);
CFigure CreateLZag(void);
CFigure CreateRZag(void);
CFigure CreateLHook(void);
CFigure CreateRHook(void);


//////////////////////////////////////////////////////////////////
//		Create methods:
//						CFigure GenerateFigure(void) - returns a CFigure object. (set figure probability?)
//						bool IsValid(CFigure, propGrid) - checks figure's current location against the grid i.e. if it can be placed there
//						void CopyIntoGrid(CFigure, propGrid) - copies figure into grid and destroys it
//						void HasLine(propGrid) - (do last)Checks if a continuous line has been built and modifies propgrid accordingly
//						void DisplayBoard(propGrid) - redraw board relative to property grid
//
//		Later on (or straight away) display figure movemnt as change in separate "pixels"
//		rather then redrawing entire board. (see snakeFinal)
//
//		grid dimensions (excluding border) 10x16
//		with border - 12x18
//
//////////////////////////////////////////////////////////////////
int _tmain(int argc, _TCHAR* argv[])
{
	//initialize property grid
	InitPropGrid();


	DisplayBoard();

	//create empty Figure object
	CFigure figure = GenerateFigure();
	
//  dont copy into grid yet - will break IsValid() func
//	CopyIntoGrid(figure);

	int frame = 1;
	//main loop
	while( !endGame )
	{
			
		//create a function<> object that will contain pointer to member function
		function<void (void)> figMethod = nullptr;

		if(GetAsyncKeyState(VK_UP))				
			figMethod = bind(&CFigure::Rotate, &figure);

		if( GetAsyncKeyState(VK_LEFT) )
			figMethod = bind(&CFigure::MoveLeft, &figure);

		if( GetAsyncKeyState(VK_RIGHT) )
			figMethod = bind(&CFigure::MoveRight, &figure);

		if( figMethod != nullptr)
			MoveFigure(figMethod, figure);

		if(GetAsyncKeyState(VK_ESCAPE))
			endGame = true;
		if(GetAsyncKeyState(VK_DOWN))
			MoveFigureDown(figure);
		Sleep(100);
		
		if(frame % 10 == 0 )
			MoveFigureDown(figure);
		++frame;
	}

	system("CLS");
	std::cout << "\n\n\n\n\t\tGAME OVER\n\n\n\n\n\n\n\n";
	system("PAUSE");
	return 0;
}


void DisplayBoard(void)
{
	HANDLE hConsole;
	hConsole= GetStdHandle(STD_OUTPUT_HANDLE);

	for(int row = 0; row < ROWS; row++)
	{
		for(int col = 0; col < COLS; col++)
		{
			switch(propGrid[row][col])
			{
			case EMPTY:
				cout << ' ';
				break;
			case BORDER:
				SetConsoleTextAttribute(hConsole, 8);
				cout << (char)0xDB;
				break;
			case TAP:
				SetConsoleTextAttribute(hConsole, 4);
				cout << (char)0xDB;
				break;
			case RZAG:
				SetConsoleTextAttribute(hConsole, 6);
				cout << (char)0xDB;
				break;
			case LZAG:
				SetConsoleTextAttribute(hConsole, 0X0E);
				cout << (char)0xDB;
				break;
			case CUBE:
				SetConsoleTextAttribute(hConsole, 0X0A);
				cout << (char)0xDB;
				break;
			case LHOOK:
				SetConsoleTextAttribute(hConsole, 0X02);
				cout << (char)0xDB;
				break;
			case RHOOK:
				SetConsoleTextAttribute(hConsole, 0X05);
				cout << (char)0xDB;
				break;
			case BAR:
				SetConsoleTextAttribute(hConsole, 3);
				cout << (char)0xDB;
				break;
			}
		}
		cout << endl;
	}
}


void InitPropGrid(void)
{
	for(int row = 0; row < ROWS; row++) 
	{
		for(int col = 0; col < COLS; col++) 
		{
			if(row == 0 || row == ROWS - 1 || col == 0 || col == COLS - 1)
				propGrid[row][col] = BORDER;
			else
				propGrid[row][col] = EMPTY;
		}
	}
}

CFigure GenerateFigure(void)
{
	CFigure figure;

	srand(time(0));
	int option = rand() % 7 + 1;

	switch( option )
	{
	case 1:
		figure = CreateTap();
		break;
	case 2:
		figure = CreateBar();
		break;
	case 3:
		figure = CreateLZag();
		break;
	case 4:
		figure = CreateRZag();
		break;
	case 5:
		figure = CreateCube();
		break;
	case 6:
		figure = CreateLHook();
		break;
	case 7:
		figure = CreateRHook();
		break;
	}


	//test purpose - display figure
	for(auto p : figure.GetPointList() )
	{
		char c = (char)0xDB;
		int colour = GetConsoleColour(figure);
		WriteCharToConsole(p.y, p.x, &c, colour);
	}

	if( !IsValid(figure) )
		endGame = true;

	return figure;
}

void CopyIntoGrid(CFigure figure)
{
	for( auto p : figure.GetPointList() )
	{
		propGrid[p.y][p.x] = figure.GetProperty();
	}
}

bool IsValid(CFigure figure)
{
	for( auto p : figure.GetPointList() )
	{
		if( propGrid[p.y][p.x] != EMPTY)
			return false;
	}

	return true;
}

void WriteCharToConsole(int row, int col, char* c, int colour)
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInf;
	cursorInf.bVisible = false;
	cursorInf.dwSize = 1;
	SetConsoleCursorInfo(hOutput, &cursorInf);

	COORD coord = {col, row};
	SetConsoleTextAttribute(hOutput, colour);
	SetConsoleCursorPosition(hOutput, coord);
	WriteConsoleA(hOutput, c, 1, NULL, NULL);	
}

void MoveFigure(function<void (void)> figureMethod, CFigure& figure )
{
	CFigure oldFigure = figure;
	figureMethod();

	if( IsValid(figure) )
	{
		for(int i = 0; i < figure.GetPointList().size(); i++)
		{
			if(figure.GetPointList()[i] != oldFigure.GetPointList()[i])
			{
				p oldPt = oldFigure.GetPointList()[i];
				char c = ' ';
				WriteCharToConsole(oldPt.y, oldPt.x, &c);
					
				c = (char)0xDB;
				for(auto p : figure.GetPointList() )
				{
					int colour = GetConsoleColour(figure);
					WriteCharToConsole(p.y, p.x, &c, colour);
				}
			}
		}
	}
	else
		figure = oldFigure;
}


CFigure CreateTap(void)
{
	CFigure figure;
	figure.SetPivot(5, 2);

	p p1,p2,p3,p4;

	//pivot
	p1.x = 5;
	p1.y = 2;

	p2.x = 5;
	p2.y = 1;
	
	p3.x = 6;
	p3.y = 2;
	
	p4.x = 5;
	p4.y = 3;

	vector<p> pList;

	pList.push_back(p1);
	pList.push_back(p2);
	pList.push_back(p3);
	pList.push_back(p4);

	figure.SetPointList(pList);
	figure.SetProperty(TAP);

	return figure;
}

CFigure CreateBar(void)
{
	CFigure figure;
	figure.SetPivot(5, 2);

	p p1,p2,p3,p4;

	//pivot
	p1.x = 5;
	p1.y = 2;

	p2.x = 5;
	p2.y = 1;
	
	p3.x = 5;
	p3.y = 3;
	
	p4.x = 5;
	p4.y = 4;

	vector<p> pList;

	pList.push_back(p1);
	pList.push_back(p2);
	pList.push_back(p3);
	pList.push_back(p4);

	figure.SetPointList(pList);
	figure.SetProperty(BAR);

	return figure;
}

CFigure CreateCube(void)
{
	CFigure figure;
	figure.SetPivot(5, 2);
	
	p p1,p2,p3,p4;

	//pivot
	p1.x = 5;
	p1.y = 2;

	p2.x = 5;
	p2.y = 1;
	
	p3.x = 6;
	p3.y = 2;
	
	p4.x = 6;
	p4.y = 1;

	vector<p> pList;

	pList.push_back(p1);
	pList.push_back(p2);
	pList.push_back(p3);
	pList.push_back(p4);

	figure.SetPointList(pList);
	figure.SetProperty(CUBE);

	return figure;
}

CFigure CreateLZag(void)
{
	CFigure figure;
	figure.SetPivot(5, 2);

	p p1,p2,p3,p4;

	//pivot
	p1.x = 5;
	p1.y = 2;

	p2.x = 6;
	p2.y = 1;
	
	p3.x = 6;
	p3.y = 2;
	
	p4.x = 5;
	p4.y = 3;

	vector<p> pList;

	pList.push_back(p1);
	pList.push_back(p2);
	pList.push_back(p3);
	pList.push_back(p4);

	figure.SetPointList(pList);
	figure.SetProperty(LZAG);

	return figure;
}

CFigure CreateRZag(void)
{
	CFigure figure;
	figure.SetPivot(5, 2);

	p p1,p2,p3,p4;

	//pivot
	p1.x = 5;
	p1.y = 2;

	p2.x = 5;
	p2.y = 1;
	
	p3.x = 6;
	p3.y = 2;
	
	p4.x = 6;
	p4.y = 3;

	vector<p> pList;

	pList.push_back(p1);
	pList.push_back(p2);
	pList.push_back(p3);
	pList.push_back(p4);

	figure.SetPointList(pList);
	figure.SetProperty(RZAG);

	return figure;
}
CFigure CreateLHook(void)
{
	CFigure figure;
	figure.SetPivot(6, 2);

	p p1,p2,p3,p4;

	//pivot
	p1.x = 6;
	p1.y = 2;

	p2.x = 6;
	p2.y = 1;
	
	p3.x = 6;
	p3.y = 3;
	
	p4.x = 5;
	p4.y = 1;

	vector<p> pList;

	pList.push_back(p1);
	pList.push_back(p2);
	pList.push_back(p3);
	pList.push_back(p4);

	figure.SetPointList(pList);
	figure.SetProperty(LHOOK);

	return figure;
}
CFigure CreateRHook(void)
{
	CFigure figure;
	figure.SetPivot(5, 2);

	p p1,p2,p3,p4;

	//pivot
	p1.x = 5;
	p1.y = 2;

	p2.x = 5;
	p2.y = 1;
	
	p3.x = 5;
	p3.y = 3;
	
	p4.x = 6;
	p4.y = 1;

	vector<p> pList;

	pList.push_back(p1);
	pList.push_back(p2);
	pList.push_back(p3);
	pList.push_back(p4);

	figure.SetPointList(pList);
	figure.SetProperty(RHOOK);

	return figure;
}

void MoveFigureDown(CFigure& figure)
{
	CFigure oldFigure = figure;
	
	figure.MoveDown();

	if( IsValid(figure) )
	{
		for(int i = 0; i < figure.GetPointList().size(); i++)
		{
			if(figure.GetPointList()[i] != oldFigure.GetPointList()[i])
			{
				p oldPt = oldFigure.GetPointList()[i];
				char c = ' ';
				WriteCharToConsole(oldPt.y, oldPt.x, &c);
					
				c = (char)0xDB;
				for(auto p : figure.GetPointList() )
				{
					int colour = GetConsoleColour(figure);
					WriteCharToConsole(p.y, p.x, &c, colour);
				}
			}
		}
	}
	else
	{
		CopyIntoGrid(oldFigure);
		LineCheck();
		figure = GenerateFigure();

	}
}

void DestroyLine(int n)
{
	int tempGrid[ROWS][COLS];

	for(int row = 0; row < ROWS; row++)
		for(int col = 0; col < COLS; col++)
			tempGrid[row][col] = propGrid[row][col];

	for(int row = n; row > 0; row--)
	{
		for(int col = 1; col < COLS - 1; col++)
		{
			if(row > 1)
				tempGrid[row][col] = propGrid[row - 1][col];
			else
				tempGrid[row][col] = EMPTY;
		}
	}
	
	for(int row = 0; row < ROWS; row++)
		for(int col = 0; col < COLS; col++)
			propGrid[row][col] = tempGrid[row][col];

}

void LineCheck(void)
{
	for(int row = 1; row < ROWS - 1; row++)
	{
		int numNotEmpty = 0;

		for(int col = 1; col < COLS - 1; col++)
		{
			if( propGrid[row][col] != EMPTY )
				numNotEmpty++;
		}

		if(numNotEmpty == COLS - 2)
		{
			DestroyLine(row);
			row--;
			system("CLS");
			DisplayBoard();
		}
	}
}


int GetConsoleColour(CFigure& figure)
{
	switch(figure.GetProperty())
	{
		case EMPTY:
			return 0;
			break;
		case BORDER:
			return 8;
			break;
		case TAP:
			return 4;
			break;
		case RZAG:
			return 6;
			break;
		case LZAG:
			return 0X0E;
			break;
		case CUBE:
			return 0X0A;
			break;
		case LHOOK:
			return 0X02;
			break;
		case RHOOK:
			return 0X05;
			break;
		case BAR:
			return 3;
			break;
		default:
			return 0;
	}
}

void WriteCharToConsole(int row, int col, char* c)
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