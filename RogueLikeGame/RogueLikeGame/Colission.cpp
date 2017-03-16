#include "Colission.h"

CColission::CColission()
{
}


CColission::~CColission()
{
}

//SDL_Rect a es la posicion dle jugador, list es una lista de CTile que
//contiene todas las tiles con colision
bool CColission::checkColission(SDL_Rect a, list<CTile> lista, bool* print)
{
	*print = false;
	bool collision = true, collisionPrint = true;
	int cont = 0;
	list<CTile>::iterator it = lista.begin();
	while ( it != lista.end()) {
		collision = true;
		collisionPrint = true;
		//The sides of the rectangles
		int leftA = 0, leftB = 0, leftC = 0;
		int rightA = 0, rightB = 0, rightC = 0;
		int topA = 0, topB = 0, topC = 0;
		int bottomA = 0, bottomB = 0, bottomC = 0;

		//Rectangle player
		leftA = a.x;
		rightA = a.x + a.w;
		topA = a.y;
		bottomA = a.y + a.h;


		//Depende del tipo pone los limites a un sitio u otro
		if (it->getTipo() == "rWall") {
			//Calculate the sides of rect A
			leftB = it->getRectDestino().x + 32;
			rightB = it->getRectDestino().x + it->getRectDestino().w - 60;
			topB = it->getRectDestino().y - 35;
			bottomB = it->getRectDestino().y + it->getRectDestino().h - 5;
		}
		else if (it->getTipo() == "lWall") {
			//Calculate the sides of rect A
			leftB = it->getRectDestino().x;
			rightB = it->getRectDestino().x + it->getRectDestino().w - 60;
			topB = it->getRectDestino().y - 32;
			bottomB = it->getRectDestino().y + it->getRectDestino().h - 5;
		}
		else if (it->getTipo() == "dWall") {
			leftB = it->getRectDestino().x;
			rightB = it->getRectDestino().x + it->getRectDestino().w -32;
			topB = it->getRectDestino().y;
			bottomB = it->getRectDestino().y + it->getRectDestino().h - 70;
		}
		else if (it->getTipo() == "uWall") {
			//Calculate the sides of rect A
			leftB = it->getRectDestino().x ;
			rightB = it->getRectDestino().x + it->getRectDestino().w - 32;
			topB = it->getRectDestino().y;
			bottomB = it->getRectDestino().y + it->getRectDestino().h - 70;
		}
		else if (it->getTipo() == "dWallSL") {
			leftB = it->getRectDestino().x;
			rightB = it->getRectDestino().x + it->getRectDestino().w;
			topB = it->getRectDestino().y;
			bottomB = it->getRectDestino().y + it->getRectDestino().h;
		}
		else {
			leftB = it->getRectDestino().x;
			rightB = it->getRectDestino().x + it->getRectDestino().w;
			topB = it->getRectDestino().y;
			bottomB = it->getRectDestino().y + it->getRectDestino().h;
		}
		//Calculate the sides of rect B

		//da los valores al rectagulo C
		leftC = it->getRectDestino().x;
		rightC = it->getRectDestino().x + it->getRectDestino().w;
		topC = it->getRectDestino().y;
		bottomC = it->getRectDestino().y + it->getRectDestino().h;
		//If any of the sides from A are outside of B
		if (bottomA <= topB)
		{
			collision = false;
		}

		if (topA >= bottomB)
		{
			collision = false;
		}

		if (rightA <= leftB)
		{
			collision = false;
		}

		if (leftA >= rightB)
		{
			collision = false;
		}
		if (collision) {
			cont++;
		}



		//Comprueba colisiones para imprimir capas
		if (bottomA <= topC)
		{
			collisionPrint = false;
		}

		if (topA >= bottomC)
		{
			collisionPrint = false;
		}

		if (rightA <= leftC)
		{
			collisionPrint = false;
		}

		if (leftA >= rightC)
		{
			collisionPrint = false;
		}
		//Comprobar donde se imprime la textura(capa)

		//establecemos valores 
		leftA = a.x + 25;
		rightA = a.x + a.w;
		topA = a.y + 15;
		bottomA = a.y + a.h + 25;
	


		if (topA < bottomC && collisionPrint && it->getTipo() != "lWall" && it->getTipo() != "rWall") {
			if (topA >= topC) {
				*print = true;
			}
		}
		it++;
	}
	//If none of the sides from A are outside B
	if (cont != 0) {
		return true;
	}
	else {
		return false;
	}
}

void CColission::getRectColission(CTile tiles[], list<CTile>* list, char* id)
{
	if (id == "wall") {
		for (int i = 0; i < 130; i++)
		{
			if (tiles[i].getTipo() == "rWall" || tiles[i].getTipo() == "lWall" ||
				tiles[i].getTipo() == "uWall" || tiles[i].getTipo() == "dWall" ||
				tiles[i].getTipo() == "dWallSL") {
				list->push_back(tiles[i]);
			}
		}
	}
	else {
		for (int i = 0; i < 130; i++)
		{
			if (tiles[i].getTipo() == id) {
				list->push_back(tiles[i]);
			}
		}
	}
}

