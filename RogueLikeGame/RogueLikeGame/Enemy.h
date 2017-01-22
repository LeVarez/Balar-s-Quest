#pragma once
#include <SDL.h>
#include "Entity.h" 
class CEnemy : public CEntity
{
public:
	CEnemy(char * file, int x, int y, int hight, int width, SDL_Renderer * window);
	CEnemy();
	~CEnemy();
	//Se passa como parametro las cordenadas del jugador i mueve el enemigo
	void movee(int x, int y);
	void move();
private:
	//Array con las posiciones del jugador
	int posPlayer_x[8] = { 130,140,150,160,170,180,190,200 };
	int posPlayer_y[8] = { 200,200,200,200,200,200,200,200 };
	//Contador del movimiento del jugador
	int MovePlayer = 0;
};

