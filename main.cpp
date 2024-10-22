#include <iostream>

// x
#define BUTTON_1
#define BUTTON_2
#define BUTTON_3
#define BUTTON_4
#define BUTTON_5
#define BUTTON_6
#define BUTTON_7
#define BUTTON_8

// y
#define BUTTON_A
#define BUTTON_B
#define BUTTON_C
#define BUTTON_D
#define BUTTON_E
#define BUTTON_F
#define BUTTON_G
#define BUTTON_H

// x - y
#define LED_10
#define LED_30
#define LED_50
#define LED_70

#define LED_01
#define LED_21
#define LED_41
#define LED_61

#define LED_12
#define LED_32
#define LED_52
#define LED_72

#define LED_03
#define LED_23
#define LED_43
#define LED_63

#define LED_14
#define LED_34
#define LED_54
#define LED_74

#define LED_05
#define LED_25
#define LED_45
#define LED_65


#define LED_16
#define LED_36
#define LED_56
#define LED_76

#define LED_07
#define LED_27
#define LED_47
#define LED_67 "trocar pela porta correta da posição [6][7]"

struct CartesianPlane{
	int x; // 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7
	int y; // 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7
};

CartesianPlane pos;
CartesianPlane newPos;

struct Tile{
	CartesianPlane pos;
	char type[20]; // Tile | Move | Piece | King | None
	char team[20]; // Black | White | None
	int ledPort;
};

// newPos name repeats inside functions

Tile board[8][8];
bool moving = false;
char playing[20] = "White"; // Black | White



void start(){
	boardStart();

	pos.x = -1;
	pos.y = -1;

	newPos.x = -1;
	newPos.y = -1;
}

void loop(){
	boardUpdate();
	
	if(!moving){
		pos.x = buttonXHandler();
		pos.y = buttonYHandler();
	}
	else{
		newPos.x = buttonXHandler();
		newPos.y = buttonYHandler();		
	}
	
	if( pos.x >= 0 && pos.y >= 0 && !moving && isPiece(pos) && isPlaying(pos) ){
		moving = true;

		resetMove();
		moveStart( pos );
	}
	else if( newPos.x >= 0 && newPos.y >= 0 && moving && isMove(newPos) ){
		moving = false;

		resetMove();
		moveHandler( pos, newPos );
	}
	else if( newPos.x >= 0 && newPos.y >= 0 && moving && !isMove(newPos) ){
		moving = false;

		resetMove();
		
		pos.x = -1;
		pos.y = -1;
		
		newPos.x = -1;
		newPos.y = -1;
	}
}

// Validations
bool isPiece( CartesianPlane pos ){
	return (
		board[pos.x][pos.y].type == "Piece" ||
		board[pos.x][pos.y].type == "King"			
	);
}

bool isPlaying( CartesianPlane pos ){
	return board[pos.x][pos.y].team == playing;
}

bool isMove( CartesianPlane pos ){
	return board[pos.x][pos.y].type == "Move";
}

// Arduino Handlers
void boardUpdate(){
	
	for(int i = 0; i < 8; i++)
	for(int j = 0; j < 8; j++){
		Tile aux = board[i][j];
		
		if(aux.type == "None")
			continue;

		if(aux.ledPort >= 0){
			digitalWrite(aux.ledPort, LOW);
			
			switch(aux.type){ // Set Led Color
				case "Piece":
					digitalWrite(aux.ledPort, HIGH);
					break;
				case "King":
					digitalWrite(aux.ledPort, HIGH);
					break;
				case "Move":
					digitalWrite(aux.ledPort, HIGH);
					break;
			}
		}
	}
}

int buttonXHandler(){
	if(digitalRead(BUTTON_1) == HIGH)
		return 0; 
	else if(digitalRead(BUTTON_2) == HIGH)
		return 1;
	else if(digitalRead(BUTTON_3) == HIGH)
		return 2;
	else if(digitalRead(BUTTON_4) == HIGH)
		return 3;
	else if(digitalRead(BUTTON_5) == HIGH)
		return 4;
	else if(digitalRead(BUTTON_6) == HIGH)
		return 5;
	else if(digitalRead(BUTTON_7) == HIGH)
		return 6;
	else if(digitalRead(BUTTON_8) == HIGH)
		return 7;
	else
		return pos.x;
}

int buttonYHandler(){
	
	if(digitalRead(BUTTON_A) == HIGH)
		return 0; 
	else if(digitalRead(BUTTON_B) == HIGH)
		return 1;
	else if(digitalRead(BUTTON_C) == HIGH)
		return 2;
	else if(digitalRead(BUTTON_D) == HIGH)
		return 3;
	else if(digitalRead(BUTTON_E) == HIGH)
		return 4;
	else if(digitalRead(BUTTON_F) == HIGH)
		return 5;
	else if(digitalRead(BUTTON_G) == HIGH)
		return 6;
	else if(digitalRead(BUTTON_H) == HIGH)
		return 7;
	else
		return pos.y;
}


// Logic
// change functions to another file ? 

void setUselessTile( CartesianPlane pos ){
	strcpy(board[pos.x][pos.y].team, "None");
	strcpy(board[pos.x][pos.y].type, "None");
	board[pos.x][pos.y].pos = pos;
	board[pos.x][pos.y].ledPort = -1;
}

void setPieceTile( CartesianPlane pos ){
	strcpy(board[pos.x][pos.y].team, pos.y > 3 ? "Black" : "White");
	strcpy(board[pos.x][pos.y].type, "Piece");
	board[pos.x][pos.y].pos = pos;
	
	// Black Pieces
	
	if(pos.x == 1 && pos.y == 0)
		board[pos.x][pos.y].ledPort = LED_10;
	else if(pos.x == 3 && pos.y == 0)
		board[pos.x][pos.y].ledPort = LED_30;
	else if(pos.x == 5 && pos.y == 0)
		board[pos.x][pos.y].ledPort = LED_50;
	else if(pos.x == 7 && pos.y == 0)
		board[pos.x][pos.y].ledPort = LED_70;
		
	else if(pos.x == 0 && pos.y == 1)
		board[pos.x][pos.y].ledPort = LED_01;
	else if(pos.x == 2 && pos.y == 1)
		board[pos.x][pos.y].ledPort = LED_21;
	else if(pos.x == 4 && pos.y == 1)
		board[pos.x][pos.y].ledPort = LED_41;
	else if(pos.x == 6 && pos.y == 1)
		board[pos.x][pos.y].ledPort = LED_61;

	else if(pos.x == 1 && pos.y == 2)
		board[pos.x][pos.y].ledPort = LED_12;
	else if(pos.x == 3 && pos.y == 2)
		board[pos.x][pos.y].ledPort = LED_32;
	else if(pos.x == 5 && pos.y == 2)
		board[pos.x][pos.y].ledPort = LED_52;
	else if(pos.x == 7 && pos.y == 2)
		board[pos.x][pos.y].ledPort = LED_72;
		
	// Tile Pieces
	
	else if(pos.x == 0 && pos.y == 3)
		board[pos.x][pos.y].ledPort = LED_03;
	else if(pos.x == 2 && pos.y == 3)
		board[pos.x][pos.y].ledPort = LED_23;
	else if(pos.x == 4 && pos.y == 3)
		board[pos.x][pos.y].ledPort = LED_43;
	else if(pos.x == 6 && pos.y == 3)
		board[pos.x][pos.y].ledPort = LED_63;

	else if(pos.x == 1 && pos.y == 4)
		board[pos.x][pos.y].ledPort = LED_14;
	else if(pos.x == 3 && pos.y == 4)
		board[pos.x][pos.y].ledPort = LED_34;
	else if(pos.x == 5 && pos.y == 4)
		board[pos.x][pos.y].ledPort = LED_54;
	else if(pos.x == 7 && pos.y == 4)
		board[pos.x][pos.y].ledPort = LED_74;	

	// White Pieces

	else if(pos.x == 0 && pos.y == 5)
		board[pos.x][pos.y].ledPort = LED_05;
	else if(pos.x == 2 && pos.y == 5)
		board[pos.x][pos.y].ledPort = LED_25;
	else if(pos.x == 4 && pos.y == 5)
		board[pos.x][pos.y].ledPort = LED_45;
	else if(pos.x == 6 && pos.y == 5)
		board[pos.x][pos.y].ledPort = LED_65;

	else if(pos.x == 1 && pos.y == 6)
		board[pos.x][pos.y].ledPort = LED_16;
	else if(pos.x == 3 && pos.y == 6)
		board[pos.x][pos.y].ledPort = LED_36;
	else if(pos.x == 5 && pos.y == 6)
		board[pos.x][pos.y].ledPort = LED_56;
	else if(pos.x == 7 && pos.y == 6)
		board[pos.x][pos.y].ledPort = LED_76;

	else if(pos.x == 0 && pos.y == 7)
		board[pos.x][pos.y].ledPort = LED_07;
	else if(pos.x == 2 && pos.y == 7)
		board[pos.x][pos.y].ledPort = LED_27;
	else if(pos.x == 4 && pos.y == 7)
		board[pos.x][pos.y].ledPort = LED_47;
	else if(pos.x == 6 && pos.y == 7)
		board[pos.x][pos.y].ledPort = LED_67;
}

void setUselessRow( int y ){
	for(int i = 0; i < 8; i++){
		CartesianPlane target;

		target.x = i;
		target.y = y;
		
		setUselessTile( target ); 
	}
}

void boardStart(){
	for( int i = 0; i < 8; i++ ){
		if(i != 3 && i != 4)
			for( int j = 0; j < 8; j++ ){
				CartesianPlane aux;

				aux.x = i;
				aux.y = j;
				
				if(i % 2 == 0){
					if(j % 2 == 0)
						setUselessTile( aux );
					else
						setPieceTile( aux );
				}
				else{
					if(j % 2 == 0)
						setPieceTile( aux );
					else
						setUselessTile( aux );
				}
			}
		else
			setUselessRow( i );
	}
}

void resetMove(){
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			if(board[i][j].type == "Move")
				strcpy(board[i][j].type, "Tile");
}

void setMoveTile( CartesianPlane pos ){
	strcpy(board[pos.x][pos.y].type, "Move");
}

void attackStart( CartesianPlane pos ){
	Tile piece = board[pos.x][pos.y];
	
	for(int i = 0; i < 4; i++){

        CartesianPlane targetPos;

        switch(i) {
            case 0:
                targetPos.x = 1;
                targetPos.y = 1;
                break;
            case 1:
                targetPos.x = -1;
                targetPos.y = 1;
                break;
            case 2:
                targetPos.x = 1;
                targetPos.y = -1;
                break;
            case 3:
                targetPos.x = -1;
                targetPos.y = -1;
                break;
        }
        
		CartesianPlane target;
		target.x = pos.x + targetPos.x;
		target.y = pos.y + targetPos.y;

		
		CartesianPlane attack;
		attack.x = pos.x + targetPos.x * 2;
		attack.y = pos.y + targetPos.y * 2;

		if( // Attack Move
			!( attack.x > 7 || attack.y > 7 ) &&
			!( attack.x < 0 || attack.y < 0 ) &&
			!isPiece( attack ) &&
			isPiece( target ) &&
			board[target.x][target.y].team != playing
		){
			if( piece.type == "Piece" ){
				if( piece.team == "White"  && pos.y > target.y ){
					setMoveTile( attack );
				}
				else if( piece.team == "Black" && pos.y < target.y ){
					setMoveTile( attack );
				}
			}
			else if( piece.type == "King" ){
				setMoveTile( target );
			}
		}
	}
}

void moveStart( CartesianPlane pos ){
	Tile piece = board[pos.x][pos.y];
	
	for(int i = 0; i < 4; i++){

        CartesianPlane targetPos;

        switch(i) {
            case 0:
                targetPos.x = 1;
                targetPos.y = 1;
                break;
            case 1:
                targetPos.x = -1;
                targetPos.y = 1;
                break;
            case 2:
                targetPos.x = 1;
                targetPos.y = -1;
                break;
            case 3:
                targetPos.x = -1;
                targetPos.y = -1;
                break;
        }
        
		CartesianPlane target;
		target.x = pos.x + targetPos.x;
		target.y = pos.y + targetPos.y;

		
		CartesianPlane attack;
		attack.x = pos.x + targetPos.x * 2;
		attack.y = pos.y + targetPos.y * 2;

        
		if( // Normal Move
			!( target.x > 7 || target.y > 7 ) &&
			!( target.x < 0 || target.y < 0 ) &&
			!isPiece( target )
		){
			if( piece.type == "Piece" ){
				if( piece.team == "White"  && pos.y > target.y ){
					setMoveTile( target );
				}
				else if( piece.team == "Black" && pos.y < target.y ){
					setMoveTile( target );					
				}
			}
			else if( piece.type == "King" ){
				setMoveTile( target );
			}
		}
		if( // Attack Move
			!( attack.x > 7 || attack.y > 7 ) &&
			!( attack.x < 0 || attack.y < 0 ) &&
			!isPiece( attack ) &&
			isPiece( target ) &&
			board[target.x][target.y].team != playing
		){
			if( piece.type == "Piece" ){
				if( piece.team == "White"  && pos.y > target.y ){
					setMoveTile( attack );
				}
				else if( piece.team == "Black" && pos.y < target.y ){
					setMoveTile( attack );
				}
			}
			else if( piece.type == "King" ){
				setMoveTile( target );
			}
		}
	}
} 

void moveHandler( CartesianPlane oldPos, CartesianPlane movedPos ){
	Tile oldTile = board[oldPos.x][oldPos.y];
	Tile newTile = board[movedPos.x][movedPos.y];	
	
	board[movedPos.x][movedPos.y].team == oldTile.team;
	board[movedPos.x][movedPos.y].type == oldTile.type;	
	
	strcpy(board[pos.x][pos.y].type, "Tile");

	if(abs(pos.x - movedPos.x) > 1){
		strcpy(board[movedPos.x + (pos.x - movedPos.x) / 2][movedPos.y + (pos.y - movedPos.y) / 2].type, "Tile");
		
		pos.x = movedPos.x;
		pos.y = movedPos.y;
		
		moving = true;
		
		attackStart( pos );
	}
	else{
		pos.x = -1;
		pos.y = -1;

		movedPos.x = -1;
		movedPos.y = -1;

		if(playing == "Black")
			strcpy(playing, "White");
		else 
			strcpy(playing, "Black");

		strcpy(playing, playing == "Black" ? "White" : "Black");
	}
}


