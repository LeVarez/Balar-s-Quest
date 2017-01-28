#include "Enemy.h"
#include "Entity.h"

CEnemy::CEnemy(char * file, int x, int y, int hight, int width, SDL_Renderer * window) : CEntity(file, x, y, hight, width, window)
{

}

CEnemy::CEnemy()
{
}


CEnemy::~CEnemy()
{
}


void CEnemy::move(int x, int y)
{
	if (MovePlayer < 8) {
		//Guarda les posicions anterior del pj a les cordenades del enemic
 		this->x = posPlayer_x[MovePlayer];
		this->y = posPlayer_y[MovePlayer];
		//Esborra les cordenades utilitzades ara i les actualitza amb les actuals
		posPlayer_x[MovePlayer] = x;
		posPlayer_y[MovePlayer] = y;
		//Suma el contador
		MovePlayer++;
	}

	else
	{
		//El contador arriba al maxim i es torna a possar a 0
		MovePlayer = 0;
	}
}

void CEnemy::move(SDL_Event)
{
}

