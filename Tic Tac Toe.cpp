#include <iostream>
#include<tesla.h>                                        // FOR COINTOSS

using namespace std;

char arena[3][3],icon='O', cicon='X';

void display() {                                         // ARENA DISPLAY
	system("cls");
	cout<<"\n\n\t\t\t-------------\n\t\t\t";
	for (int i=0; i<=2; ++i)
		{
			cout<<"| ";
			for (int j=0; j<=2; ++j)
				cout<<arena[j][i]<<" | ";
			cout<<"\n\t\t\t-------------\n\t\t\t";
		}
}

void input(char icon) {                                   // PLAYER INPUT
	char x='\0';
	int y,h,k;
	rerand:
		h=rand()%3;
		k=rand()%3;
		if (arena[h][k]!='\0')	goto rerand;
	arena[h][k]='*';
	display();
	
	do{
		x=getch(); x=tolower(x);
		if (isdigit(x) && x>'0')
			{y=(int)x; y-=48;
			y= (y%3==0) ? (11-y) : ((y%3==1) ? (7-y) : (9-y));
			}
		if (x>='1' && x<='9' && arena[y%3][y/3]=='\0')
			{ arena[h][k]='\0'; h=y%3; k=y/3;
			  arena[h][k]='*';
			}
		if (x=='\r'){
			arena[h][k]=icon;			
		}
		display();
	}while(x!='\r');
}


int wincheck() {                                                 // WINCHECK FUNCTION
	int trig=0,var=2;
	if (arena[0][0]==arena[0][1] && arena[0][1]==arena[0][2] && arena[0][0]!='\0') {
		arena[0][0]==icon ? var=1 : var=-1;
	}
	else if (arena[0][0]==arena[1][0] && arena[1][0]==arena[2][0] && arena[0][0]!='\0') {
		arena[0][0]==icon ? var=1 : var=-1;
	}
	else if (arena[0][1]==arena[1][1] && arena[1][1]==arena[2][1] && arena[0][1]!='\0') {
		arena[0][1]==icon ? var=1 : var=-1;
	}
	else if (arena[1][0]==arena[1][1] && arena[1][1]==arena[1][2] && arena[1][0]!='\0') {
		arena[1][0]==icon ? var=1 : var=-1;
	}
	else if (arena[0][2]==arena[1][2] && arena[1][2]==arena[2][2] && arena[0][2]!='\0') {
		arena[0][2]==icon ? var=1 : var=-1;
	}
	else if (arena[2][0]==arena[2][1] && arena[2][1]==arena[2][2] && arena[2][0]!='\0') {
		arena[2][0]==icon ? var=1 : var=-1;
	}
	else if (arena[0][0]==arena[1][1] && arena[1][1]==arena[2][2] && arena[0][0]!='\0') {
		arena[0][0]==icon ? var=1 : var=-1;
	}
	else if (arena[2][0]==arena[1][1] && arena[1][1]==arena[0][2] && arena[2][0]!='\0') {
		arena[2][0]==icon ? var=1 : var=-1;
	}
	else {
		for (int i=0; i<=2; ++i)
			for (int j=0; j<=2; ++j)
				if (arena[j][i]=='\0')	{trig=1;break;}
		if (trig==1)	var=2;
		else var=0;		
	}
	
return var;
}

int canwin(char a) {                                             // WIN POSSIBILITY CHECKER
	int x=10;
	a==icon ? x=1 : x=-1;
	for (int j=0; j<=2; ++j) {
		for (int i=0; i<=2; ++i) {
			if (arena[i][j]=='\0') {
				arena[i][j]=a;
				if (wincheck()==x)	{arena[i][j]='\0'; return ((3*i)+j);}
				else	arena[i][j]='\0';
			}
		}
	}
	return -1;
}

int forkcheck(char a) {                                           // FORK POSSIBILITY CHECKER
	int p=10,q=10;
	for (int j=0; j<=2; ++j) {
		for (int i=0; i<=2; ++i) {
			if (arena[i][j]=='\0') {
				arena[i][j]=a;
				if (canwin(a)>=0) {
					p=canwin(a)/3;
					q=canwin(a)%3;
					arena[p][q]='N';
					if (canwin(a)>=0) {
						arena[i][j]='\0';
						arena[p][q]='\0';
						return ((3*i)+j);
					}
					arena[p][q]='\0';	
				}
				arena[i][j]='\0';	
			}
		}
	}
	return -1;
}

int forkblock() {                                                  // BLOCK OPPONENT'S FORK
	if (forkcheck(icon)>=0) {
		for (int j=0; j<=2; ++j) {
			for (int i=0; i<=2; ++i) {
				if (arena[i][j]=='\0') {
					arena[i][j]=cicon;
					if (canwin(cicon)>=0 && forkcheck(icon)!=canwin(cicon)) {
						arena[i][j]='\0';
						return ((3*i)+j);
					}
					arena[i][j]='\0';	
				}
			
			}
		}	
	}
	return -1;	
}

int main()                                                              // MAIN
{
	srand(time(0));
	system("cls");
	
	int x,y,winstat=2,turn=0,buff;
	char opt;
	time_t start,stop;

			
	cout<<"\n\n\t\t\t###############################";             // START
	cout<<"  \n\t\t\t#  -----  #   ---   #   ---   #";
	cout<<"  \n\t\t\t#    |    #    |    #   |     #";
	cout<<"  \n\t\t\t#         #   ---   #   ---   #";
	cout<<"  \n\t\t\t###############################";
	cout<<"  \n\t\t\t#  -----  #   ___   #   ---   #";
	cout<<"  \n\t\t\t#    |    #   |-|   #   |     #";
	cout<<"  \n\t\t\t#         #         #   ---   #";
	cout<<"  \n\t\t\t###############################";
	cout<<"  \n\t\t\t#  -----  #   ----  #   ---   #";
	cout<<"  \n\t\t\t#    |    #   |  |  #   |--   #";
	cout<<"  \n\t\t\t#         #   ----  #   ---   #";
	cout<<"  \n\t\t\t###############################";
	cout<<"\n\n\n\t\t\t    BY NAVEEN UNNIKRISHNAN";
	start=time(0);
	retime:
		stop=time(0);
		if (stop-start<3 && kbhit()==0)	goto retime;
	
menu:                                                                 // MENU
	
	system("cls");
	cout<<"\n\n\t\t\tTIC TAC TOE\n\t\t\t===========";
	cout<<"\n\n\t\t\t1. PLAY\n\t\t\t2. INSTRUCTIONS\n\t\t\t3. EXIT";
	cout<<"\n\n\t\t\t(Press 1, 2 or 3 to continue...)";

start:                                                                
	
	opt=getch();
		if (opt!='1' && opt!='2' && opt!='3')	goto start;
	if (opt=='1')	goto play;
	else if (opt=='2')	goto instruct;
	else	exit(0);
	
instruct:                                                              // INSTRUCTIONS 
	
	system("cls");
	cout<<"\n\n\t\tTHIS IS A STANDARD GAME OF TIC TAC TOE\n\t\t( X AND O / CROSS & KNOTS ) IN WHICH YOU\n\t\tPLAY AGAINST YOUR COMPUTER.\n\t\t(ALSO, YOUR COMPUTER IS AN UNBEATABLE BASTARD!)\n\n\t\tHERE ARE THE CONTROLS : ";
	cout<<"\n\n\t\tUSE YOUR NUMPAD ( ON THE RIGHT OF YOUR KEYBOARD )\n\t\tTO PLACE THE * ON THE DESIRED SQUARE\n\t\tAND THEN PRESS ENTER TO PLACE YOUR TILE\n\t\t(X OR O) THERE.";
	cout<<"\n\n\t\t __________________________";
	cout<<"  \n\t\t|        |        |        |";
	cout<<"  \n\t\t|    7   |    8   |    9   |";
	cout<<"  \n\t\t|________|________|________|";
	cout<<"  \n\t\t|        |        |        |";
	cout<<"  \n\t\t|    4   |    5   |    6   |";
	cout<<"  \n\t\t|________|________|________|";
	cout<<"  \n\t\t|        |        |        |";
	cout<<"  \n\t\t|    1   |    2   |    3   |";
	cout<<"  \n\t\t|________|________|________|";
	cout<<"\n\n\t\t( Press any key to go back to Main Menu )";
	getch();
	goto menu;
		
play:                                                                   // PLAY
	
	turn=0;	
	icon='0';
	cicon='X';
	for (int i=0; i<=2; ++i)
		for (int j=0; j<=2; ++j)
			arena[j][i]='\0';
	system("cls");
	int toss=cointoss();                                                    // TOSS
	if (toss==1) {     
		rechoose :
		cout<<"\n\t\tWould you like to play first ( Y | N ) ? : ";
		char choice=getch();
		if (choice=='Y' || choice == 'y')	{ icon='X'; cicon='O'; goto player;}
		else if (choice=='N' || choice=='n')	goto cpu;
		else {
			cout<<"\n\t\tINVALID choice!! Lets Try that again.\n";
			goto rechoose;
		}
	}
	else {
		cout<<"\n\t\tYou'll be playing second!"; 
		getch();
		goto cpu;
	}
	
	player:                                                             // PLAYER SEQUENCE
				
		input(icon);
		++turn;
		winstat=wincheck();
		if (winstat==1) {
			cout<<"\n\n\t\t\t  YOU WIN!!";
			goto end;
	    }
	    else if (winstat==0) {
	    	cout<<"\n\n\t\t\tIt's a DRAW!!";
	    	goto end;
	    }
	
	cpu :                                                          // CPU SEQUENCE        :                            ALGORITHM
		                                                                             //                          =====================
		                                                     
		if (turn==0) {                                                                                     // PLAY CORNER OR CENTRE IN 1st TURN.
			buff=(rand()%5)*2;
			x=buff/3; y=buff%3;
		}
		else if (turn==1) {                                                                                // PLAY CENTRE (IF FREE) ON 2nd TURN. ELSE PLAY CORNER.
			if (arena[1][1]=='\0') {
				x=1; y=1;
			}
			else {
				rebuff:
					buff=(rand()%5)*2;
					if (arena[buff/3][buff%3]!='\0')	goto rebuff;
				x=buff/3; y=buff%3;
			}	
					
		} 
		else if (canwin(cicon)>=0) {                                                                        // PLAY WINNING MOVE
			x=canwin(cicon)/3; y=canwin(cicon)%3;
		}
		else if (canwin(icon)>=0) {                                                                         // BLOCK OPPONENT'S WINNING MOVE
			x=canwin(icon)/3; y=canwin(icon)%3;
		}
		else if (forkcheck(cicon)>=0) {                                                                     // PLAY TRAP
			x=forkcheck(cicon)/3; y=forkcheck(cicon)%3;
		}
		else if (forkblock()>=0) {                                                                          // BLOCK OPPONENT'S TRAP
			x=forkblock()/3; y=forkblock()%3; 
		}
		else if (arena[1][1]=='\0') {                                                                       // PLAY CENTRE IF OPEN
			x=1; y=1;
		}
		else if (turn==2 && arena[1][1]==icon) {                                                            // IF TURN IS 3, TRY TO ADVANCE TO FORKING POSITION
			if (arena[0][0]==cicon) 	{
				x=2; y=2;
			}
			else if (arena[2][0]==cicon) {
				x=0; y=2;
			}
			else if (arena[0][2]==cicon) {
				x=2; y=0;
			}
			else if (arena[2][2]==cicon) {
				x=0; y=0;
			}
		}
		else if (arena[0][0]=='\0' || arena[2][0]=='\0' || arena[0][2]=='\0' || arena[2][2]=='\0') {      	// PLAY CORNER
			resetbuff:
				buff=(rand()%5)*2;
				x=buff/3; y=buff%3;
				if (arena[x][y]!='\0')	goto resetbuff;
		}
		else {																   	                            // PLAY RANDOM MOVE
			repos: 
			x=rand()%3;
			y=rand()%3;
			if (arena[x][y]!='\0')	goto repos;
		}
	
		arena[x][y]=cicon;
		++turn;
		display();
		winstat=wincheck();
		if (winstat==-1) 	cout<<"\n\n\t\t\t  YOU LOSE!";
		else if (winstat==0)	cout<<"\n\n\t\t\tIt's a DRAW!!";
		else	goto player;
		

	end:	
		getch();
		goto menu;
	return 0;
}

