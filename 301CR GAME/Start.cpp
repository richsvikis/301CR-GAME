/* OPENGL_INCLUDES */


#ifndef OPENGL_INCLUDES
#define OPENGL_INCLUDES
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#pragma comment(lib, "glew32.lib") 
#endif 



#include <assimp/Importer.hpp>
#include <assimp/scene.h>         
#include <assimp/postprocess.h> 


#include <enet/enet.h>

#include <fmod.h>
#include <fmod_studio.hpp>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>



#include "Character.h"
#include <vector>
#include <GL/GL.h>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <time.h>
#include <math.h>

#include <glfw3.h>







#define PI 3.1415926535897932384626433832795

using namespace std;




//////EXPERIMENT///////





int numVerts;


std::map <int, bool> gameObject::specialKeys;
std::map <char, bool> gameObject::keys;

std::vector<gameObject*> gameobjects;

int oldTimeSinceStart = 0;
int newTimeSinceStart = 0;

//int initial_time = time(NULL), final_time, frame_count = 0;



Character Char = Character(glm::vec3(5, 4, 3));
// Initialization routine.

UINT SkyboxTexture[6];

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);








///////////////////////////////////////////////////////////////////////////////////////// ORIGINAL CODE /////////////////////////////////////////////////////////////////




void setup(void)
{
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST); // Enable depth testing.
	glEnable(GL_LIGHTING);

	// Light property vectors.
	float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
	float lightDifAndSpec[] = { 1.0, 1.0, 1.0, 1.0 };
	float lightPos[] = { 0.0, 1.0, 0.0, 0.0 };
	float globAmb[] = { 0.2, 0.2, 0.2, 1.0 };

	// Light properties.
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glEnable(GL_LIGHT0); // Enable particular light source.
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.

													 // Material property vectors.
	float matSpec[] = { 1.0, 1.0, 1.0, 1.0 };
	float matShine[] = { 50.0 };

	// Material properties.
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShine);

	// Enable color material mode.
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);


	unsigned int base = glGenLists(2); // Generate display list base. 




	base = Char.setupDrawing(base);


	Char.start();

	gameobjects.emplace_back(&Char);
}



// Drawing routine.
void drawScene()
{
	float theta;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glLoadIdentity();

	// Position the objects for viewing.

	glm::vec3 CameraPosition = Char.position;
	glm::vec3 TargetPosition = Char.position;
	CameraPosition += Char.heading * 10.0f;
	CameraPosition += glm::vec3(0, 0.5, 0) * 10.0f;
	gluLookAt(CameraPosition.x, CameraPosition.y, CameraPosition.z, TargetPosition.x, TargetPosition.y, TargetPosition.z, 0.0, 1.0, 0.0);


	glPushMatrix();
	//BottomLeftPocket



	glEnd();
	glPopMatrix();



	//floor
	glPushMatrix();
	glColor3f(0.15, 0.21, 1.00);
	glBegin(GL_QUADS);
	glVertex3f(500, -10, 1000);
	glVertex3f(850, -10, 300);
	glVertex3f(-250, -10, -250);
	glVertex3f(-600, -10, 500);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.00, 0.50, 0.06);
	glBegin(GL_QUADS);
	glVertex3f(600, -5, 5);
	glVertex3f(300, -5, 10);
	glVertex3f(-250, -5, -10);
	glVertex3f(-600, -5, 20);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(700, -5, 10);
	glVertex3f(700, -5, 20);
	glVertex3f(400, -5, -30);
	glVertex3f(100, -5, 40);
	glEnd();
	glPopMatrix();




	Char.drawScene();



	glutSwapBuffers();

	//frame_count++;
	//final_time = time(NULL);
	//if (final_time - initial_time > 0)
	//{
	//	std::cout << "FPS : " << frame_count / (final_time - initial_time) << std::endl;
	//	frame_count = 0;
	//	initial_time = final_time;
	//}



}




// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (float)w / (float)h, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}




void idle() {
	//Calculate delta time (in mili seconds).
	oldTimeSinceStart = newTimeSinceStart;
	newTimeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	int deltaTime = newTimeSinceStart - oldTimeSinceStart;

	//If the last frame was rendered less than 1 ms ago, the detalaTime will be 0 ms. This causes problems in calculations, so sleep for 1ms to adjust.
	if (deltaTime == 0) {
		Sleep(1);
		newTimeSinceStart = glutGet(GLUT_ELAPSED_TIME);
		deltaTime = newTimeSinceStart - oldTimeSinceStart;
	}

	//Run update for all game objects.
	for (std::vector<gameObject*>::size_type i = 0; i != gameobjects.size(); i++) {
		gameobjects[i]->update(deltaTime);
	}

	//ask glut for a redraw after allthe updates
	glutPostRedisplay();
}

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};








// Main routine.
int main(int argc, char** argv)
{
	
	

	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Game");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);







	//Key func

	glutKeyboardFunc([](unsigned char key, int x, int y) {
		gameObject::keys[key] = true;
		//if we press escape, exit the game
		if (key == 27) {
			exit(0);
		}
		});

	glutKeyboardUpFunc([](unsigned char key, int x, int y) {
		gameObject::keys[key] = false;
		});

	glutSpecialFunc([](int key, int x, int y) {
		gameObject::specialKeys[key] = true;
		});

	glutSpecialUpFunc([](int key, int x, int y) {
		gameObject::specialKeys[key] = false;
		});




	glutIdleFunc(idle);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();



}


//////////////////////////////////////////////////////////////////////////////////////// ORIGINAL CODE /////////////////////////////////////////////////////////////////