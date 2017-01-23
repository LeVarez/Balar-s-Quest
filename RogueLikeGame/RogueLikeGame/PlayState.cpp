#include <stdio.h>

#include "SDL.h"
#include "Game.h"
#include "PlayState.h"
#include "PauseState.h"
#include <vector>


PlayState PlayState::m_PlayState;

void PlayState::Init(Game* game)
{

	//CTile tile1 = CTile(0, 0, 0, 0, 0, 32, 32, "suelo");
	//CTile tile2 = CTile(0, 0, 0, 0, 0, 32, 32, "suelo");
	//CTile tile3 = CTile(0, 0, 0, 0, 0, 32, 32, "suelo");
	//CTile tile4 = CTile(0, 0, 0, 0, 0, 32, 32, "suelo");
	//CTile tile5 = CTile(0, 0, 0, 0, 0, 32, 32, "suelo");
	//CTile tile6 = CTile(0, 0, 0, 0, 0, 32, 32, "suelo");
	//CTile tile7 = CTile(0, 0, 0, 0, 0, 32, 32, "suelo");
	//CTile tile8 = CTile(0, 0, 0, 0, 0, 32, 32, "suelo");
	//CTile tile9 = CTile(0, 0, 0, 0, 0, 32, 32, "suelo");
	//CTile tile10 = CTile(0, 0, 0, 0, 0, 32, 32, "suelo");

	//CTile tileset[2] = { tile1,tile2 };
	CTile tileset[50];
	CMapa mapa = CMapa("../src/maps/m1.map");

	bool funciona;

	funciona = mapa.setTiles(tileset);

	mapa.renderMap(tileset, game->GetRenderer());

	/*playSprite = NULL;

	playSprite = Sprite::Load("../src/sprites/atlas.bmp", game->GetRenderer());

	playSprite = Sprite::Load("sprites/playstate.bmp", game->GetRenderer());
	*/

	SDL_Texture* textura = Sprite::Load("sprites/atlas.bmp", game->GetRenderer());


	for (int i = 0; i < 42; i++)
	{
		//Sprite::Draw(m_WindowRenderer, textura, 0, 0, 32, 32, 480, 352);
		//Sprite::Draw(m_WindowRenderer, textura, 32, 0, 32, 32, 480, 352);

 		//int pixelX = tileset[i].getpixelX();
		//std::cout << "" + tileset[i].getpixelX() << '\n';

		//Sprite::Draw(game->GetRenderer(), textura, tileset[i].getpixelX(), tileset[i].getpixelY(), tileset[i].getWidth(), tileset[i].getHeight(), tileset[i].getposX(), tileset[i].getposY());

		SDL_Rect rectOrigen = tileset[i].getRectOrigen();
		SDL_Rect rectDestino = tileset[i].getRectDestino();

		Sprite::Draw(game->GetRenderer(), textura, rectOrigen, rectDestino);

		SDL_RenderPresent(game->GetRenderer());

		printf("PlayState Init Successful\n");

	}
}

void PlayState::Clean()
{
	printf("PlayState Clean Successful\n");
}

void PlayState::Pause()
{
	printf("PlayState Paused\n");
}

void PlayState::Resume()
{
	printf("PlayState Resumed\n");
}

void PlayState::HandleEvents(Game* game)
{
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			game->Quit();
			break;

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {

				//En presionar Space canvia el estado del juego a PAUSA
			case SDLK_SPACE:
				game->PushState(PauseState::Instance());
				break;
			}
		}
	}
}

void PlayState::Update(Game* game)
{
}

void PlayState::Draw(Game* game)
{
	Sprite::DrawFullScreen(game->GetRenderer(), playSprite);
	SDL_RenderPresent(game->GetRenderer());
}