#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

char yoba[55][30];
char map[20][40];
int i,j,score,ii,jj, gamelvl=0, ls_i=0;
int inp_code=0;
char cl;
struct PNTS{
	int score;
	int difficulty;
}pts[5];

void set_d(void)
{
	switch(gamelvl)
	{
	case 1:
		for(int li=0; li<5; ++li)
		{
			ii=rand()%39;
			jj=rand()%39;
			if(map[ii][jj]==' ')
			{
				map[ii][jj]='D';
			}
			else
			{
				--li;
			}
		}
		break;
	case 2:
		for(int li=0; li<7; ++li)
		{
			ii=rand()%39;
			jj=rand()%39;
			if(map[ii][jj]==' ')
			{
				map[ii][jj]='D';
			}
			else
			{
				--li;
			}
		}
		break;
	case 3:
		for(int li=0; li<9; ++li)
		{
			ii=rand()%39;
			jj=rand()%39;
			if(map[ii][jj]==' ')
			{
				map[ii][jj]='D';
			}
			else
			{
				--li;
			}
		}
		break;
	}
}

void get_yoba(void)
{
	int i,j;
	FILE *yobaf;
	yobaf=fopen("yoba.txt","r");
	for(i=0; i<55; ++i)
	{
		for(j=0; j<30; ++j)
		{
			fscanf(yobaf,"%c",&yoba[i][j]);
			if(yoba[i][j]=='\n')
			{
				break;
			}
		}
	}
	fclose(yobaf);
}

void print_yoba(void)
{
	for(i=0; i<55; ++i)
	{
		for(j=0; j<30; ++j)
		{
			printf("%c",yoba[i][j]);
			if(yoba[i][j]=='\n')
			{
				break;
			}
		}
	}
}

void read_rating(int inp_score, int lvlgame){
	int li, repindx, acc1, acc2;
	int lli;
	FILE* in;
	FILE* out;
	if(!((in=fopen("rate.txt","r"))==NULL)){
	//================
		for(li=0; li<5; ++li)
		{
			fscanf(in, "%d %d\n", &pts[li].score, &pts[li].difficulty);
		}
		fclose(in);

		for(li=0; li<5; ++li)
		{
			if(inp_score>pts[li].score)
			{
				repindx=li;
				for(lli=repindx; lli<4; ++lli)
				{
					acc1=pts[lli].score;
					acc2=pts[lli].difficulty;
					pts[lli].score=pts[lli+1].score;
					pts[lli].difficulty=pts[lli+1].difficulty;
					pts[lli+1].score=acc1;
					pts[lli+1].difficulty=acc2;
				}
				pts[repindx].score=inp_score;
				pts[repindx].difficulty=gamelvl;
				break;
			}
		}

	printf("\n\n===========\n\n");
	printf("Score\tDifficulty\n");
	for(li=0; li<5; ++li)
	{
		printf("%d\t%d\n", pts[li].score, pts[li].difficulty);
	}
	printf("\n\n===========\n\n");

	out=fopen("rate.txt", "w");
	for(li=0; li<5; ++li)
	{
		fprintf(out, "%d %d\n", pts[li].score, pts[li].difficulty);
	}

	fclose(in);
	//==================
	}
	else
	{
		printf("Error reading rating file!");
	}
}

void generate_field(void)
{
	int ii, jj;
	switch(gamelvl){
	default: break;
	case 1: 
		for(int li=0; li<3; ++li)
		{
			ii=rand()%39;
			jj=rand()%39;
			if(map[ii][jj]==' ')
			{
				map[ii][jj]='$';
			}
			else
			{
				--li;
			}
		}
		for(int li=0; li<15; ++li)
		{
			ii=rand()%39;
			jj=rand()%39;
			if(map[ii][jj]==' ')
			{
				map[ii][jj]='#';
			}
			else
			{
				--li;
			}
		}
		break;
	case 2:
		for(int li=0; li<6; ++li)
		{
			ii=rand()%39;
			jj=rand()%39;
			if(map[ii][jj]==' ')
			{
				map[ii][jj]='$';
			}
			else
			{
				--li;
			}
		}
		for(int li=0; li<25; ++li)
		{
			ii=rand()%39;
			jj=rand()%39;
			if(map[ii][jj]==' ')
			{
				map[ii][jj]='#';
			}
			else
			{
				--li;
			}
		}
		break;
	case 3:
		for(int li=0; li<9; ++li)
		{
			ii=rand()%39;
			jj=rand()%39;
			if(map[ii][jj]==' ')
			{
				map[ii][jj]='$';
			}
			else
			{
				--li;
			}
		}//
		for(int li=0; li<40; ++li)
		{
			ii=rand()%39;
			jj=rand()%39;
			if(map[ii][jj]==' ')
			{
				map[ii][jj]='#';
			}
			else
			{
				--li;
			}
		}
		break;
	}
}

void execute_motion(int code)
{
	switch(code){
	case 72://up
		switch(map[ii-1][jj])
		{
		case '#':
			map[ii][jj]=' ';
			map[ii-1][jj]='@';
			ii=ii-1;
			score-=8000;
			Beep(1400, 300);
			break;
		case '$':
			map[ii][jj]=' ';
			map[ii-1][jj]='@';
			ii=ii-1;
			score+=4000;
			Beep(7000, 200);
			break;
		case ' ':
			map[ii][jj]=' ';
			map[ii-1][jj]='@';
			ii=ii-1;
			break;
		case 'D':
			score=-1;
			break;
		}
		break;
	case 75://left
		switch(map[ii][jj-1])
		{
			case '#':
			map[ii][jj]=' ';
			map[ii][jj-1]='@';
			jj=jj-1;
			score-=8000;
			Beep(1400, 300);
			break;
		case '$':
			map[ii][jj]=' ';
			map[ii][jj-1]='@';
			jj=jj-1;
			score+=4000;
			Beep(7000, 200);
			break;
		case ' ':
			map[ii][jj]=' ';
			map[ii][jj-1]='@';
			jj=jj-1;
			break;
		case 'D':
			score=-1;
			break;
		}
		break;
	case 77://right
		switch(map[ii][jj+1])
		{
			case '#':
			map[ii][jj]=' ';
			map[ii][jj+1]='@';
			jj=jj+1;
			score-=8000;
			Beep(1400, 300);
			break;
		case '$':
			map[ii][jj]=' ';
			map[ii][jj+1]='@';
			jj=jj+1;
			score+=4000;
			Beep(7000, 200);
			break;
		case ' ':
			map[ii][jj]=' ';
			map[ii][jj+1]='@';
			jj=jj+1;
			break;
		case 'D':
			score=-1;
			break;
		}
		break;
	case 80://down
		switch(map[ii+1][jj])
		{
		case '#':
			map[ii][jj]=' ';
			map[ii+1][jj]='@';
			ii=ii+1;
			score-=8000;
			Beep(1400, 300);
			break;
		case '$':
			map[ii][jj]=' ';
			map[ii+1][jj]='@';
			ii=ii+1;
			score+=4000;
			Beep(7000, 200);
			break;
		case ' ':
			map[ii][jj]=' ';
			map[ii+1][jj]='@';
			ii=ii+1;
			break;
		case 'D':
			score=-1;
			break;
		}
		break;
	}
}

int check_field_endofgame(void)
{
	int check=0;
	for(i=0; i<20; ++i)
	{
		for(j=0; j<40; ++j)
		{
			if(map[i][j]=='$') check++;
		}
	}
	if(check==0)
		return 1;
	else
		return 0;
}

void end_game(int state)
{
	switch(state){
	case -1:
		system("cls");
		print_yoba();
		break;
	case 0:
		break;
	case 1:
		system("cls");
		read_rating(score, gamelvl);
		break;
	}
}

int play_game(void)
{
	int t_score=score/3;

	while(1)
	{
		if(kbhit())
		{
			inp_code=getch();
			if (inp_code==27) 
			{
				Beep(400, 200);
				return 0;
			}
		}
		execute_motion(inp_code);
		inp_code=0;
		system("cls");
		score--;
		printf("score: %d\n\n\n", score);
		for(i=0; i<20; ++i)
		{
			for(j=0; j<40; ++j)
			{
				printf("%c", map[i][j]);
			}
			printf("\n");
		}
		if(check_field_endofgame()==1) 
		{	
			printf("WIN\n");
			return 1;
		}
		if(score<0)
		{
			return -1;
		}
		if(score<t_score) 
		{
			
		}
		Sleep(50);
	}
}

int main()
{
	get_yoba();

	for(i=0; i<20; ++i)
	{
		for(j=0; j<40; ++j)
		{
			map[i][j]=' ';
		}
	}

	printf("Your mission is taking a money at game field in minimal time. Your character is marked by \"@\"\n");
	printf("Select a difficulty level:\n");
	printf("[1] if easy\n");
	printf("[2] if medium\n");
	printf("[3] if hard\n");
	scanf("%d", &gamelvl);
	srand(clock());
	ii=rand()%19;
	jj=rand()%39;
	map[ii][jj]='@';
	generate_field();

	switch(gamelvl)
	{
	case 1:
		score=30000;
		break;
	case 2:
		score=20000;
		break;
	case 3:
		score=10000;
		break;
	default: break;
	}
	
	end_game(play_game());


	Sleep(2000);
	return 0;
}