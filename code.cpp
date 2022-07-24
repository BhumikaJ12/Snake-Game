# include <iostream>
# include <conio.h>
# include <windows.h>
using namespace std;

int height = 20;
int width = 20;
int headX, headY, foodX, foodY;
int tailX[100], tailY[100];
int nTail;
int score;
bool Gameover;
enum command {Stop = 0, Left, Right, Up, Down};
command dir;

void Setup(){
	dir = Stop;
	score = 0;
	headX = height/2;
	headY = width/2;
	foodX = rand() % width;
	foodY = rand() % height;
	Gameover = false;
}

void Draw(){
	system("cls");
	for(int i=0; i<width+2; i++){
		cout << "#";
	}
	cout << endl;
	for(int i=0; i<height; i++){
		for(int j=0; j<width; j++){
			if(j == 0) 
				cout << "#";
			if(i == foodY && j == foodX) 
				cout << "F";
			else if(i == headY && j == headX) 
				cout << "O";
			else{
				bool print = false;
				for(int k=0; k<nTail; k++){
					if(tailX[k] == j && tailY[k] == i){
						cout << "o"; 
						print = true;
					}
				}
				if(!print)
					cout << " ";  	
			}

			    if(j == width-1)
			       cout << "#";
		}
		cout << endl;
	}
	for(int i=0; i<width+2; i++){
		cout << "#";
	}
	cout << endl;
	cout << "SCORE = " << score << endl;
	cout << "Press X to quit" << endl;
}
void Input(){

	if(_kbhit()) {	
		
		switch(_getch()){
			case 'A':
			dir = Left;
			break;

			case 'W':
			dir = Up;
			break;

			case 'D':
			dir = Right;
			break;

			case 'S':
			dir = Down;
			break;

			case 'X':
			Gameover = true;
			break;

			default:
            cout<<"INVALID INPUT";
            break;
		}
	}
    
}
		
void Logic(){
    tailX[0] = headX;
	tailY[0] = headY;
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	switch(dir){
		case Left:
		headX--;
		break;

		case Right:
		headX++;
		break;

		case Up:
		headY--;
		break;

		case Down:
		headY++;
		break;

		default:
		break;
	}
	if(headX<0 || headX>width || headY<0 || headY>height)
	            Gameover = true; 
	for(int i=0; i<nTail; i++){
		if(tailX[i] == headX && tailY[i] == headY)
			Gameover = true;
	} 
	if(headX == foodX && headY == foodY){
			score +=10;
			foodX = rand() % width; 
			foodY = rand() % height;
			nTail++;
		}
	for(int k=1; k<nTail; k++){
		prev2X = tailX[k];
		prev2Y = tailY[k];
		tailX[k] = prevX;
		tailY[k] = prevY;
		prevX = prev2X;
		prevY = prev2Y; 
	} 			
}
int main(){
	Setup();
	while(Gameover != true){
		Draw();
		Input();
		Logic();
		Sleep(300);
	}
	return 0;
}
