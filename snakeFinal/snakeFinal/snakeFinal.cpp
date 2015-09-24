// snakeFinal.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Board.h"

using namespace std;

//globals
bool endGame = false;

//helpers 
int GetDirection(CHead& head);
void OnMove(CBoard& board, CHead& head, CTail& tail);
void CreateItem(CBoard& board, CHead& head, CTail& tail, int frameCount, int lvl);
void PauseGame(void);
void DisplayMenu(int& level, int& waitTime);

int _tmain(int argc, _TCHAR* argv[])
{


	CBoard board;
	CHead head(10, 10, UP);
	CTail tail;
	tail.AddPieceToEnd(11, 10, UP);
	tail.AddPieceToEnd(12, 10, UP);



	board.CreateApple(head, tail);
	board.CreatePApple(head, tail);
	board.CreateGrenade(head, tail);


	cout << ",DMMMMMMN~    OMM88     ~NO   $NO    $$M$       OMMZI       ,DMMMMMMMM\n$MOI   ~D~    ONDMMI    ~NO   $NO   IMMO       ~NODDZ,      ,DD,      \nOM=~          ON+NDN,   ~NO   $NO  =MDN,       ?N+$MO=      ,DD,      \n?MMZ=         OD,::NN~  ~NO   $NO:DM=         =MI  O8N~     ,DD,      \n ZMMMM=       OD,  ?M$  ~NO   $NOZMI          $N~  I$M?     ,DMMMMMMM\n     ,DMM=    OD,   =MO ~NO   $NO~NN:       ==M=    ~$M=    ,DD,      \n       ?MD:,  OD,    OMI~NO   $NO +MD,,     ZZMMMMMMMMM$    ,DD,      \n       ,DN=~  OD,    :NN=NO   $NO  ZM88    :NMNMMMMMMMMD,   ,DD,      \nNI     OMZ,   OD,     ,DMMO   $NO   ~NNM=  OMN~       IMZ   ,DD,      \nNMMMMMMMD,    OD,      ?MMO   $NO    ==MD  NO          DN   ,DMMMMMMMM" << endl;
	cout << "\n\n\n\n\n\n\n\n\t\t\t";
	system("PAUSE");
	system("CLS");

	int level;
	int waitTime;

	do{
		DisplayMenu(level, waitTime);
	}while(level > 10 || level < 1);

	system("CLS");

	board.ShowFrame();

	board.FillConsole(head, tail);
	board.FillFrame(head, tail);

	long int frameCount = 300;

	while( !endGame )
	{

		CreateItem(board, head, tail, frameCount, level);

		head.Move( GetDirection(head) );
		tail.Move( head.GetDirection() );

		board.FillFrame(head, tail);
		board.FillConsole(head, tail);
		OnMove( board, head, tail );

		board.UpdateScreen(head, tail);


		for(int i = 0; i < waitTime; i++)			//remove this loop later
		{			
			if(GetAsyncKeyState(VK_ESCAPE))
				endGame = true;
		}	

		frameCount++;
	}

	system("CLS");

	std::cout << "\n\n\n\n\t\tGAME OVER\n\n\n\n\n\n\n\n";
	std::cout << "\tYour score is: " << board.GetScore() << endl << endl;
	system("PAUSE");
	return 0;
}

int GetDirection(CHead& head)
{
	int movDir = head.GetDirection();

	if(GetAsyncKeyState(VK_DOWN))
		return movDir = DOWN;

	if(GetAsyncKeyState(VK_UP))
		return movDir = UP;	

	if(GetAsyncKeyState(VK_LEFT))
		 return movDir = LEFT;

	if(GetAsyncKeyState(VK_RIGHT))
		return movDir = RIGHT;
	else
		return movDir;

}

void OnMove(CBoard& board, CHead& head, CTail& tail)
{
	char c = (char)0xDB;

	switch(board.HasItemAt( head.GetRowPos(), head.GetColPos() ) )
	{
	case APPLE:
		board.WriteCharToConsole(head.GetRowPos(), head.GetColPos(), &c);
		tail.AddPieceToStart(head.GetRowPos(), head.GetColPos(), head.GetDirection() );		//add piece at current head direction to the start of tail vector.
		head.Move( GetDirection( head ) );				//move head again to allow space for tailpiece to be inserted
		board.CreateApple( head, tail );				//create apple
		board.UpdateScore(50);
		break;
	case PAPPLE:
		board.WriteCharToConsole(head.GetRowPos(), head.GetColPos(), &c);
		board.UpdateScore(150);
		board.DeletePineapple();
		board.pappleShown = false;
		Beep(2000, 50);
		break;
	case GRENADE:
		endGame = true;
		break;
	}

	if( tail.HasPieceAt(head.GetRowPos(), head.GetColPos() ) )
		endGame = true;
}

void CreateItem(CBoard& board, CHead& head, CTail& tail, int frameCount, int lvl)
{
		if(frameCount % 100 == 0)
		{
			board.CreatePApple(head,tail);
			board.pappleShown = true;
		}

		if(frameCount % 100 == 35)
		{
			board.DeletePineapple();
			board.pappleShown = false;
		}

		if(lvl < 9)		//dont create grenade for last two lvls
		{
			if(frameCount % 200 == 0 )
			{
				board.CreateGrenade(head, tail);
				board.grenadeShown = true;
			}

			if(frameCount % 200 == 20 )
			{
				board.DeleteGrenade();
				board.grenadeShown = false;
			} 
		}

}

void DisplayMenu(int& level, int& waitTime)
{
	system("CLS");
	cout << "   1. Insulting\n   2. Really Easy\n   3. Very Easy\n   4. Easy\n   5. Normal\n   6. Hard\n   7. Very Hard\n   8. Hardcore\n   9. Impossible\n   10.Inhuman\n\n   0. Additional Info\n\n";
	cout << "   Choose difficulty level.: ";

	while(!(cin >> level) )			// wrong input handling
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');

		system("CLS");
		cout << "   1. Insulting\n   2. Really Easy\n   3. Very Easy\n   4. Easy\n   5. Normal\n   6. Hard\n   7. Very Hard\n   8. Hardcore\n   9. Impossible\n   10.Inhuman\n\n   0. Additional Info\n\n";
		cout << "   Choose difficulty level.: ";
	};

	switch(level)
	{
	case 1:
		waitTime = 60000000;
		break;
	case 2:
		waitTime = 45000000;
		break;
	case 3:
		waitTime = 22000000;
		break;
	case 4:
		waitTime = 15000000;
		break;
	case 5:
		waitTime = 11000000;
		break;
	case 6:
		waitTime = 7000000;
		break;
	case 7:
		waitTime = 4000000;
		break;
	case 8:
		waitTime = 2000000;
		break;
	case 9:
		waitTime = 1000000;
		break;
	case 10:
		waitTime = 10;
		break;
	case 0:
		system("CLS");
		cout << "\n\n\n  While in the game, press ESC to quit immediately.\n\n  o - Apple.\n  $ - Pineapple (bonus scores).\n  @ - Grenade. Don't eat that.\n\n\n";
		cout << "\t\t\tSnkae v 1.0b by iggagi\n\n\n\t";
		system("PAUSE");
	}
}