#include "vector.h"
#include "puk.h"
#include "world.h"
#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

pukk puka;
wrl world;
CPlayer LPlayer;

vec fVect; 
vec normal;
SDL_Event event;
//float rot;
int go;


void Init(void)
{
	GLubyte *vend;
	GLubyte *rend;
	GLubyte *ver;
	GLubyte *ext;

	float ambientlight[] = {0.5, 0.5, 0.5, 0.0};
	float diffuselight[] = {0.5, 0.5, 0.5, 0.0};
	float specular[]     = {0.8, 0.8, 0.8, 0.0};
	float LightPos[]     = {0.0, 0.0, 0.0};

	vend=(GLubyte *)glGetString(GL_VENDOR);
	rend=(GLubyte *)glGetString(GL_RENDERER);
	ver=(GLubyte *)glGetString(GL_VERSION);
	ext=(GLubyte *)glGetString(GL_EXTENSIONS);
	printf("GL_VENDOR: %s\n", vend);
	printf("GL_RENDERER: %s\n", rend);
	printf("GL_VERSION: %s\n", ver);
	printf("GL_EXTENSIONS: %s\n", ext);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, 1.0, 2.0, 20000);

	glShadeModel(GL_SMOOTH);	
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientlight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuselight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPos);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_DEPTH_TEST);
	//glFrontFace(GL_CCW);
	//glEnable(GL_CULL_FACE);

	//glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_NORMAL_ARRAY);
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);	
	puka.vel.x = 0.2;
	puka.vel.z = 0.3;	
}


void display(void)
{
//	rot += 0.1;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode( GL_PROJECTION );
	glPopMatrix();
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glTranslatef(0.0, 0.0, -140.0);
	glRotatef(-60, 1.0, 0.0, 0.0);
//	if(!go) 
//	{
//		if(rot >= 100)
//		{
//			go = 1;
//			rot = 0.0;
//		}
//	}
		
//	if(go)
//	{
//		glRotatef(rot, 0.0, 0.0, 1.0);
//	}
	world.Render();	
		
	if(puka.pos.x <= -30) 
	{
		normal.x = 1.0;
		normal.z = 0.0;
		fVect = puka.CalcResponse(&normal);		
		puka.vel.x = fVect.x;
		puka.vel.z = fVect.z;
		puka.pos.x = -29.9;
	}

	if(puka.pos.x >= 30) 
	{
		normal.x = -1.0;
		normal.z = 0.0;		
		fVect = puka.CalcResponse(&normal);		
		puka.vel.x = fVect.x;
		puka.vel.z = fVect.z;
		puka.pos.x = 29.9;
	}

	
	if(puka.pos.z <= -60) 
	{
		normal.x = 0.0;
		normal.z = 1.0;
		fVect = puka.CalcResponse(&normal);		
		puka.vel.x = fVect.x;
		puka.vel.z = fVect.z;
		puka.pos.z = -59.9;
	}

	if(puka.pos.z >= 60) 
	{
		normal.x = 0.0;
		normal.z = -1.0;
		fVect = puka.CalcResponse(&normal);		
		puka.vel.x = fVect.x;
		puka.vel.z = fVect.z;
		puka.pos.z = 59.9;
	}

		
	puka.pos.x += puka.vel.x;
	puka.pos.z += puka.vel.z;
	
	puka.Render();
	LPlayer.Render();
	
	SDL_GL_SwapBuffers();
}


int main(int argc, char argv[])
{
	int done;
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) 
	{
		fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	if ( SDL_SetVideoMode(320, 200, 0, SDL_OPENGL) == NULL ) 
	{
		fprintf(stderr, "Unable to create OpenGL screen: %s\n", SDL_GetError());
		SDL_Quit();
		exit(2);
	}

	SDL_WM_SetCaption("The Puk Game! v0.1b", NULL);
	
	Init();
	done = 0;
	while(!done)
	{
		while (SDL_PollEvent(&event)) 
		{
			if (event.type == SDL_QUIT) 
			{
				done = 1;
			}
		}

		if (event.type == SDL_KEYDOWN) 
		{
			if (event.key.keysym.sym == SDLK_ESCAPE) 
			{
				done = 1;
			}
			
			if (event.key.keysym.sym == SDLK_UP) 
			{
				LPlayer.pos.z += 0.2;
			}			
			
			if (event.key.keysym.sym == SDLK_DOWN) 
			{
				LPlayer.pos.z -= 0.2;
			}			

			if (event.key.keysym.sym == SDLK_LEFT) 
			{
				LPlayer.pos.x -= 0.2;
			}			

			if (event.key.keysym.sym == SDLK_RIGHT) 
			{
				LPlayer.pos.x += 0.2;
			}			
			
		}
	
		display();
	}
	return 0;
}
