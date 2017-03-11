#include "Player.h"
#include "Entity.h"
#include "FireBall.h"

CPlayer::CPlayer(char * file, int x, int y, int hight, int width, SDL_Renderer * window) : CEntity(file, x, y, hight, width, window)
{
	this->gSpriteSheetTexture = CTexture::CTexture();
	this->frame = 0;
	this->mVelX = 0;
	this->mVelY = 0;
	this->vida = 3;
	this->coins = 0;
	this->bombs = 0;
	this->keys = 0;
	this->m_WindowRenderer = window;
}
CPlayer::CPlayer()
{
	this->gSpriteSheetTexture = CTexture::CTexture();
	this->mVelX = 0;
	this->mVelY = 0;
	this->vida = 3;
	this->coins = 0;
	this->bombs = 0;
	this->keys = 0;
}

//Este movimiento est� obsoleto, se le passaba un mapa del teclado
void CPlayer::move(const Uint8 *keyboard_state_array) {
	bool entrat = false;
	if (keyboard_state_array[SDL_SCANCODE_RIGHT] && !keyboard_state_array[SDL_SCANCODE_LEFT])
	{
		if (frame < 27 || frame > 34) {
			frame = 27;
		}
		mPosX += 5;
		if (frame < 35 && cont == 2) {
			frame++;
		}
		entrat = true;
	}
	else if (!keyboard_state_array[SDL_SCANCODE_RIGHT] && keyboard_state_array[SDL_SCANCODE_LEFT])
	{

		if (frame > 16 || frame < 9) {
			frame = 9;
		}
		mPosX -= 5;
		if (frame < 17 && cont == 2) {
			frame++;
		}
		entrat = true;
	}
	// Move centerpoint of rotation for one of the trees:
	if (keyboard_state_array[SDL_SCANCODE_UP] && !(keyboard_state_array[SDL_SCANCODE_DOWN]))
	{
		if (frame > 7 && entrat != true) {
			frame = 0;
		}
		mPosY -= 5;
		if (frame < 8 && entrat != true && cont == 2)
		{
			frame++;
		}

	}
	else if (!keyboard_state_array[SDL_SCANCODE_UP] && keyboard_state_array[SDL_SCANCODE_DOWN])
	{
		if ((frame > 25 || frame < 18) && entrat != true) {
			frame = 18;
		}
		mPosY += 5;
		if (frame < 26 && entrat != true && cont == 2) {
			frame++;
		}
	}
	cont++;
	if (cont > 2) {
		cont = 0;
	}


}

void CPlayer::move(int x, int y)
{
}


//eventos del teclado
void CPlayer::handleEvent(SDL_Event & e)
{
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_w: mVelY -= PLAYER_VEL;	w			= true;		break;
		case SDLK_s: mVelY += PLAYER_VEL;	s			= true;		break;
		case SDLK_a: mVelX -= PLAYER_VEL;	a			= true;		break;
		case SDLK_d: mVelX += PLAYER_VEL;	d			= true;		break;

		case SDLK_UP:						atkUP		= true;		break;
		case SDLK_LEFT:						atkLEFT		= true;		break;
		case SDLK_DOWN:						atkDOWN		= true;		break;
		case SDLK_RIGHT:					atkRIGHT	= true;		break;
		}
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_w: mVelY += PLAYER_VEL;	w			= false;	movimiento = false;		frame = 0;	 break;
		case SDLK_a: mVelX += PLAYER_VEL;	a			= false;	movimiento = false;		frame = 9;	 break;
		case SDLK_s: mVelY -= PLAYER_VEL;	s			= false;	movimiento = false;		frame = 18;  break;
		case SDLK_d: mVelX -= PLAYER_VEL;	d			= false;	movimiento = false;		frame = 27;  break;

		case SDLK_UP:
						atkdirection = 'U'; if (frame == 41)attack();	battack = true;
						atkUP		= false;							frame = 0;	break;

		case SDLK_LEFT:
						atkdirection = 'L'; if (frame == 48)attack();	battack = true;
						atkLEFT		= false;							frame = 9;	break;

		case SDLK_DOWN:	
						atkdirection = 'D'; if (frame == 55)attack();	battack = true;
						atkDOWN		= false;							frame = 18;	break;

		case SDLK_RIGHT:
						atkdirection = 'R'; if (frame == 62)attack();	battack = true;
						atkRIGHT	= false;							frame = 27; break;
		}
	}

}


//movimiento fluido
void CPlayer::move(float timeStep)
{
	//Move the dot left or right
	mPosX += mVelX * timeStep;

	//If the dot went too far to the left or right
	if (mPosX < 0)
	{
		mPosX = 0;
	}
	else if (mPosX > 850 - DOT_WIDTH)
	{
		mPosX = 850 - DOT_WIDTH;
	}

	//Move the dot up or down
	mPosY += mVelY * timeStep;

	//If the dot went too far up or down
	if (mPosY < 0)
	{
		mPosY = 0;
	}
	else if (mPosY > 650 - DOT_HEIGHT)
	{
		mPosY = 650 - DOT_HEIGHT;
	}


}


//Carga todas las sprites
bool CPlayer::loadMedia(SDL_Renderer* m_WindowRenderer)
{
	//Loading success flag
	bool success = true;

	//Load sprite sheet texture | MOVIMIENTO
	if (!gSpriteSheetTexture.loadFromFile("../src/sprites/pj/player.bmp", m_WindowRenderer))
	{
		printf("Failed to load walking animation texture!\n");
		success = false;
	}
	else
	{
		//Set sprite clips || MOVIMIENTO
		gSpriteClips[0].x = 0;
		gSpriteClips[0].y = 0;
		gSpriteClips[0].w = 64;
		gSpriteClips[0].h = 64;

		gSpriteClips[1].x = 64;
		gSpriteClips[1].y = 0;
		gSpriteClips[1].w = 64;
		gSpriteClips[1].h = 64;

		gSpriteClips[2].x = 128;
		gSpriteClips[2].y = 0;
		gSpriteClips[2].w = 64;
		gSpriteClips[2].h = 64;

		gSpriteClips[3].x = 192;
		gSpriteClips[3].y = 0;
		gSpriteClips[3].w = 64;
		gSpriteClips[3].h = 64;

		gSpriteClips[4].x = 256;
		gSpriteClips[4].y = 0;
		gSpriteClips[4].w = 64;
		gSpriteClips[4].h = 64;

		gSpriteClips[5].x = 320;
		gSpriteClips[5].y = 0;
		gSpriteClips[5].w = 64;
		gSpriteClips[5].h = 64;

		gSpriteClips[6].x = 384;
		gSpriteClips[6].y = 0;
		gSpriteClips[6].w = 64;
		gSpriteClips[6].h = 64;

		gSpriteClips[7].x = 448;
		gSpriteClips[7].y = 0;
		gSpriteClips[7].w = 64;
		gSpriteClips[7].h = 64;

		gSpriteClips[8].x = 512;
		gSpriteClips[8].y = 0;
		gSpriteClips[8].w = 64;
		gSpriteClips[8].h = 64;

		gSpriteClips[9].x = 0;
		gSpriteClips[9].y = 64;
		gSpriteClips[9].w = 64;
		gSpriteClips[9].h = 64;

		gSpriteClips[10].x = 64;
		gSpriteClips[10].y = 64;
		gSpriteClips[10].w = 64;
		gSpriteClips[10].h = 64;

		gSpriteClips[11].x = 128;
		gSpriteClips[11].y = 64;
		gSpriteClips[11].w = 64;
		gSpriteClips[11].h = 64;

		gSpriteClips[12].x = 192;
		gSpriteClips[12].y = 64;
		gSpriteClips[12].w = 64;
		gSpriteClips[12].h = 64;

		gSpriteClips[13].x = 256;
		gSpriteClips[13].y = 64;
		gSpriteClips[13].w = 64;
		gSpriteClips[13].h = 64;

		gSpriteClips[14].x = 320;
		gSpriteClips[14].y = 64;
		gSpriteClips[14].w = 64;
		gSpriteClips[14].h = 64;

		gSpriteClips[15].x = 384;
		gSpriteClips[15].y = 64;
		gSpriteClips[15].w = 64;
		gSpriteClips[15].h = 64;

		gSpriteClips[16].x = 448;
		gSpriteClips[16].y = 64;
		gSpriteClips[16].w = 64;
		gSpriteClips[16].h = 64;

		gSpriteClips[17].x = 512;
		gSpriteClips[17].y = 64;
		gSpriteClips[17].w = 64;
		gSpriteClips[17].h = 64;

		gSpriteClips[18].x = 0;
		gSpriteClips[18].y = 128;
		gSpriteClips[18].w = 64;
		gSpriteClips[18].h = 64;

		gSpriteClips[19].x = 64;
		gSpriteClips[19].y = 128;
		gSpriteClips[19].w = 64;
		gSpriteClips[19].h = 64;

		gSpriteClips[20].x = 128;
		gSpriteClips[20].y = 128;
		gSpriteClips[20].w = 64;
		gSpriteClips[20].h = 64;

		gSpriteClips[21].x = 192;
		gSpriteClips[21].y = 128;
		gSpriteClips[21].w = 64;
		gSpriteClips[21].h = 64;

		gSpriteClips[22].x = 256;
		gSpriteClips[22].y = 128;
		gSpriteClips[22].w = 64;
		gSpriteClips[22].h = 64;

		gSpriteClips[23].x = 320;
		gSpriteClips[23].y = 128;
		gSpriteClips[23].w = 64;
		gSpriteClips[23].h = 64;

		gSpriteClips[24].x = 384;
		gSpriteClips[24].y = 128;
		gSpriteClips[24].w = 64;
		gSpriteClips[24].h = 64;

		gSpriteClips[25].x = 448;
		gSpriteClips[25].y = 128;
		gSpriteClips[25].w = 64;
		gSpriteClips[25].h = 64;

		gSpriteClips[26].x = 512;
		gSpriteClips[26].y = 128;
		gSpriteClips[26].w = 64;
		gSpriteClips[26].h = 64;

		gSpriteClips[27].x = 0;
		gSpriteClips[27].y = 192;
		gSpriteClips[27].w = 63;
		gSpriteClips[27].h = 63;

		gSpriteClips[28].x = 64;
		gSpriteClips[28].y = 192;
		gSpriteClips[28].w = 63;
		gSpriteClips[28].h = 63;

		gSpriteClips[29].x = 128;
		gSpriteClips[29].y = 192;
		gSpriteClips[29].w = 63;
		gSpriteClips[29].h = 63;

		gSpriteClips[30].x = 192;
		gSpriteClips[30].y = 192;
		gSpriteClips[30].w = 63;
		gSpriteClips[30].h = 63;

		gSpriteClips[31].x = 256;
		gSpriteClips[31].y = 192;
		gSpriteClips[31].w = 63;
		gSpriteClips[31].h = 63;

		gSpriteClips[32].x = 320;
		gSpriteClips[32].y = 192;
		gSpriteClips[32].w = 63;
		gSpriteClips[32].h = 63;

		gSpriteClips[33].x = 384;
		gSpriteClips[33].y = 192;
		gSpriteClips[33].w = 63;
		gSpriteClips[33].h = 63;

		gSpriteClips[34].x = 448;
		gSpriteClips[34].y = 192;
		gSpriteClips[34].w = 63;
		gSpriteClips[34].h = 63;

		gSpriteClips[35].x = 512;
		gSpriteClips[35].y = 192;
		gSpriteClips[35].w = 63;
		gSpriteClips[35].h = 63;
	}
	
	if (!gSpriteSheetTextureAttack.loadFromFile("../src/sprites/pj/playerAttack2.bmp", m_WindowRenderer))
	{
		printf("Failed to load attack animation texture!\n");
		success = false;
	}
	else
	{
		//Set sprite clips || ATAQUE
		gSpriteClips[36].x = 0;
		gSpriteClips[36].y = 0;
		gSpriteClips[36].w = 64;
		gSpriteClips[36].h = 64;

		gSpriteClips[37].x = 64;
		gSpriteClips[37].y = 0;
		gSpriteClips[37].w = 64;
		gSpriteClips[37].h = 64;

		gSpriteClips[38].x = 128;
		gSpriteClips[38].y = 0;
		gSpriteClips[38].w = 64;
		gSpriteClips[38].h = 64;

		gSpriteClips[39].x = 192;
		gSpriteClips[39].y = 0;
		gSpriteClips[39].w = 64;
		gSpriteClips[39].h = 64;

		gSpriteClips[40].x = 256;
		gSpriteClips[40].y = 0;
		gSpriteClips[40].w = 64;
		gSpriteClips[40].h = 64;

		gSpriteClips[41].x = 320;
		gSpriteClips[41].y = 0;
		gSpriteClips[41].w = 64;
		gSpriteClips[41].h = 64;

		gSpriteClips[42].x = 384;
		gSpriteClips[42].y = 0;
		gSpriteClips[42].w = 64;
		gSpriteClips[42].h = 64;

		gSpriteClips[43].x = 0;
		gSpriteClips[43].y = 64;
		gSpriteClips[43].w = 64;
		gSpriteClips[43].h = 64;

		gSpriteClips[44].x = 64;
		gSpriteClips[44].y = 64;
		gSpriteClips[44].w = 64;
		gSpriteClips[44].h = 64;

		gSpriteClips[45].x = 128;
		gSpriteClips[45].y = 64;
		gSpriteClips[45].w = 64;
		gSpriteClips[45].h = 64;

		gSpriteClips[46].x = 192;
		gSpriteClips[46].y = 64;
		gSpriteClips[46].w = 64;
		gSpriteClips[46].h = 64;

		gSpriteClips[47].x = 256;
		gSpriteClips[47].y = 64;
		gSpriteClips[47].w = 64;
		gSpriteClips[47].h = 64;

		gSpriteClips[48].x = 320;
		gSpriteClips[48].y = 64;
		gSpriteClips[48].w = 64;
		gSpriteClips[48].h = 64;

		gSpriteClips[49].x = 384;
		gSpriteClips[49].y = 64;
		gSpriteClips[49].w = 64;
		gSpriteClips[49].h = 64;

		gSpriteClips[50].x = 0;
		gSpriteClips[50].y = 128;
		gSpriteClips[50].w = 64;
		gSpriteClips[50].h = 64;

		gSpriteClips[51].x = 64;
		gSpriteClips[51].y = 128;
		gSpriteClips[51].w = 64;
		gSpriteClips[51].h = 64;

		gSpriteClips[52].x = 128;
		gSpriteClips[52].y = 128;
		gSpriteClips[52].w = 64;
		gSpriteClips[52].h = 64;

		gSpriteClips[53].x = 192;
		gSpriteClips[53].y = 128;
		gSpriteClips[53].w = 64;
		gSpriteClips[53].h = 64;

		gSpriteClips[54].x = 256;
		gSpriteClips[54].y = 128;
		gSpriteClips[54].w = 64;
		gSpriteClips[54].h = 64;

		gSpriteClips[55].x = 320;
		gSpriteClips[55].y = 128;
		gSpriteClips[55].w = 64;
		gSpriteClips[55].h = 64;

		gSpriteClips[56].x = 384;
		gSpriteClips[56].y = 128;
		gSpriteClips[56].w = 64;
		gSpriteClips[56].h = 64;

		gSpriteClips[57].x = 0;
		gSpriteClips[57].y = 192;
		gSpriteClips[57].w = 64;
		gSpriteClips[57].h = 64;

		gSpriteClips[58].x = 64;
		gSpriteClips[58].y = 192;
		gSpriteClips[58].w = 64;
		gSpriteClips[58].h = 64;

		gSpriteClips[59].x = 128;
		gSpriteClips[59].y = 192;
		gSpriteClips[59].w = 64;
		gSpriteClips[59].h = 64;

		gSpriteClips[60].x = 192;
		gSpriteClips[60].y = 192;
		gSpriteClips[60].w = 64;
		gSpriteClips[60].h = 64;

		gSpriteClips[61].x = 256;
		gSpriteClips[61].y = 192;
		gSpriteClips[61].w = 64;
		gSpriteClips[61].h = 64;

		gSpriteClips[62].x = 320;
		gSpriteClips[62].y = 192;
		gSpriteClips[62].w = 64;
		gSpriteClips[62].h = 64;

		gSpriteClips[63].x = 384;
		gSpriteClips[63].y = 192;
		gSpriteClips[63].w = 64;
		gSpriteClips[63].h = 64;
		
	}

	return success;
}

void CPlayer::render(SDL_Renderer* m_WindowRenderer)
{
	SDL_Rect* currentClip = &gSpriteClips[frame];

	if (movimiento) {
		gSpriteSheetTexture.render((int)mPosX, (int)mPosY, currentClip, m_WindowRenderer);

	}
	else {
		gSpriteSheetTextureAttack.render((int)mPosX, (int)mPosY, currentClip, m_WindowRenderer);

		if (battack && fb.colision()) {
			fb.loadMedia();
			fb.animation();
			fb.move();
			fb.render();
		}
	}

}

void CPlayer::close(SDL_Renderer* m_WindowRenderer)
{
	//Free loaded images
	gSpriteSheetTexture.free();
	gSpriteSheetTextureAttack.free();

	//Destroy window	
	//SDL_DestroyRenderer(gRenderer);
	//SDL_DestroyWindow(gWindow);
	//gWindow = NULL;
	//gRenderer = NULL;

	//Quit SDL subsystems
	//IMG_Quit();
	//SDL_Quit();
}

void CPlayer::animation()
{
	bool entrat = false;

	// 0 - 8
	if (w && entrat != true) {
		movimiento = true;

		if (frame > 7) {
			frame = 0;
		}

		if (frame < 8 && cont == 1)
		{
			frame++;
		}

		if (frame == 0) {
			frame++;
		}
	}

	// 9 - 17
	if (a) {
		movimiento = true;

		if (frame > 16 || frame < 9) {
			frame = 9;
		}
		if (frame < 18 && cont == 1) {
			frame++;
		}

		entrat = true;
	}

	//19 - 26
	if (s && entrat != true) {
		movimiento = true;
		if (frame > 25 || frame < 18) {
			frame = 18;
		}
		if (frame < 26 && cont == 1) {
			frame++;
		}

		if (frame == 18) {
			frame++;
		}
	}

	//27 - 35
	if (d) {
		movimiento = true;
		if (frame > 34 || frame < 27) {
			frame = 27;
		}
		if (frame < 35 && cont == 1) {
			frame++;
		}
	}
	
	
	//36 - 42
	if (atkUP) {
		if (frame > 42 || frame < 36) {
			frame = 36;

		}

		if (frame < 42 && cont == 1) {

			frame++;
		}

		if (frame == 41) {
			cont = -1;
		}
	}

	//43 - 49
	if (atkLEFT) {
		if (frame > 49 || frame < 43) {
			frame = 43;
		}
		if (frame < 49 && cont == 1) {
			frame++;
		}

		if (frame == 48) {
			cont = -1;
		}
	}

	//50 - 56
	if (atkDOWN) {
		if ((frame > 56 || frame < 50)) {
			frame = 50;
		}
		if (frame < 56 && cont == 1) {
			frame++;
		}

		if (frame == 55) {
			cont = -1;
		}
	}

	//57 - 63
	if (atkRIGHT) {
		//No cal >62, perque si es == 62 para el moviment
		if (frame > 63 || frame < 57) {
			frame = 57;
		}

		if (frame < 63 && cont == 1) {
			frame++;
		}

		if (frame == 62) {
			cont = -1;
		}

	}


	
	//Velocidad de transici�n entre frames.
	if (cont > 10) {
		cont = 0;
	}
	cont++;
}

void CPlayer::attack() {
	fb = CFireBall::CFireBall(mPosX, mPosY, atkdirection, m_WindowRenderer);
}


