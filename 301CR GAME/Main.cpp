#define STB_IMAGE_IMPLEMENTATION
#define OPENGL_INCLUDES


#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <glew.h>
#include <freeglut.h>

#include <glext.h>
#include <glew.h>

#include <enet/enet.h>
#include <fmod_studio.hpp>
#include <fmod.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Val.h"
#include "gameObject.h"
#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "DirectionalLight.h"

#include "SpotLight.h"
#include "Material.h"

#include "Model.h"

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}


#include "Skybox.h"


#include <LuaBridge.h>
#include <time.h>
#include <GL/GL.h>
#include <glext.h>
#include <time.h>
#include <math.h>
#include <cstdio>
#include <fstream>

MainWindw Window;



std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera cam;

#define PI 3.1415926535897932384626433832795
Material shinyMaterial;
Material dullMaterial;







Model Knight;
Model Enviro;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

DirectionalLight mainLight;
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

Skybox skybox;


static const char* vshader = "shaders/shader.vert";


static const char* fshader = "shaders/shader.frag";



using namespace luabridge;
using namespace std;

int oldTimeSinceStart = 0;
int newTimeSinceStart = 0;

//int initial_time = time(NULL), final_time, frame_count = 0;


std::vector<std::string> getElements(const std::string& table, lua_State* L);





void calculateAverageNormals(unsigned int* indicies, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount, unsigned int vLengh, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indicies[i] * vLengh;
		unsigned int in1 = indicies[i + 1] * vLengh;
		unsigned int in2 = indicies[i + 2] * vLengh;

		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset;
		in1 += normalOffset;
		in2 += normalOffset;

		vertices[in0] += normal.x;
		vertices[in0 + 1] += normal.y;
		vertices[in0 + 2] += normal.z;

		vertices[in1] += normal.x;
		vertices[in1 + 1] += normal.y;
		vertices[in1 + 2] += normal.z;

		vertices[in2] += normal.x;
		vertices[in2 + 1] += normal.y;
		vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLengh; i++)
	{
		unsigned int nOffset = i * vLengh + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);

		vertices[nOffset] = vec.x;
		vertices[nOffset + 1] = vec.y;
		vertices[nOffset + 2] = vec.z;
	}
}

void createObjects()
{
	unsigned int indicies[] =
	{
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] =
	{//   X      Y     Z		  U     V		 NX    NY    NZ
		-1.0f, -1.0f, -0.6f,	 0.0f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 1.0f,		 0.5f, 0.0f,	0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, -0.6f,		 1.0f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,		 0.5f, 1.0f,	0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndicies[] =
	{
		0, 2, 1,
		1, 2, 3,
	};

	GLfloat floorVerticies[] =
	{
		-10.0f, 0.0f, -10.0,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};

	calculateAverageNormals(indicies, 12, vertices, 32, 8, 5);

	Mesh* obj1 = new Mesh();
	obj1->createMesh(vertices, indicies, 32, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->createMesh(floorVerticies, floorIndicies, 32, 6);
	meshList.push_back(obj2);
}

void createShaders()
{
	Shader* shader1 = new Shader();
	shader1->createFromFiles(vshader, fshader);
	shaderList.push_back(*shader1);
}


////////////////window/////////////////


MainWindw::MainWindw()
{
	width = 800;
	height = 600;

	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = false;
	}
}

MainWindw::MainWindw(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
}

int MainWindw::initalise()
{
	//init GLFW
	if (!glfwInit())
	{
		printf("Could not link GLFW");
		glfwTerminate();
		return 1;
	}


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	mainWindow = glfwCreateWindow(width, height, "301CR", NULL, NULL);
	if (!mainWindow)
	{
		printf(" error ");
		glfwTerminate();
		return 1;
	}



	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);


	glfwMakeContextCurrent(mainWindow);

	//Keys and Mouse Input
	createCallbacks();
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//GLEW initalisation 
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}
	glfwPollEvents();
	glEnable(GL_DEPTH_TEST);

	//setup viewport
	glViewport(0, 0, bufferWidth, bufferHeight);

	glfwSetWindowUserPointer(mainWindow, this);
}


GLfloat MainWindw::getXChange()
{
	GLfloat theChange = changeX;
	changeX = 0.0f;
	return theChange;
}

GLfloat MainWindw::getYChange()
{
	GLfloat theChange = changeY;
	changeY = 0.0f;
	return theChange;
}

MainWindw::~MainWindw()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}

void MainWindw::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, handleKeys);
	glfwSetCursorPosCallback(mainWindow, handleMouse);
}

void MainWindw::handleKeys(GLFWwindow* window, int key, int code, int action, int mod)
{
	MainWindw* theWindow = static_cast<MainWindw*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
		}
		else
		{

		}
	}
}


void MainWindw::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
	MainWindw* theWindow = static_cast<MainWindw*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->changeX = xPos - theWindow->lastX;
	theWindow->changeY = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}





int main(bool* keys)
{

	if (enet_initialize() != 0)
	{
		fprintf(stderr, "An error occurred while initializing ENet.\n");
		return EXIT_FAILURE;
	}
	ENetAddress address;
	ENetHost* client;
	ENetPeer* peer;
	ENetEvent enetEvent;

	client = enet_host_create(NULL, 1, 2, 0, 0);

	if (client == NULL)
	{
		cout << "Client failed to initialise!" << "\n\n";
	}

	enet_address_set_host(&address, "localhost");
	address.port = 2222;
	

	peer = enet_host_connect(client, &address, 2, 0);

	if (peer == NULL) {
		cout << "No available peers for initializing an ENet connection.\n";
	}

	
	
	client = enet_host_create(NULL, 1, 2, 0, 0);

	if (client == NULL)
	{
		cout << "Client failed to initialise!" << "\n\n";
	}

	enet_address_set_host(&address, "localhost");
	address.port = 1234;


	peer = enet_host_connect(client, &address, 2, 0);

	if (peer == NULL) {
		cout << "No available peers for initializing an ENet connection.\n";
	}


	while (enet_host_service(client, &enetEvent, 0) > 0)
	{
		switch (enetEvent.type) {

		

		case ENET_EVENT_TYPE_RECEIVE:
			cout << "Packet received!\n";
			break;
		}
	}

	



	lua_State* F = luaL_newstate();
	luaL_dofile(F, "level.lua");
	luaL_openlibs(F);
	lua_pcall(F, 0, 0, 0);

	
	LuaRef t = getGlobal(F, "window");
	LuaRef title = t["title"];
	LuaRef w = t["width"];
	LuaRef h = t["height"];

	//std::string titleString = title.cast<std::string>();
	int width = w.cast<int>();
	int height = h.cast<int>();

	//std::vector<std::string> elementList;
	//std::vector<std::string> entityList;
	

	F = luaL_newstate();
	luaL_dofile(F, "elements.lua");
	luaL_openlibs(F);
	lua_pcall(F, 0, 0, 0);

///	elementList = getElements("elementList", F);

	LuaRef elementsRef = getGlobal(F, "elementList");
	int checker;

		Window = MainWindw(900, 720);
		Window.initalise();


		FMOD::Studio::System* system = NULL;
		FMOD::Studio::System::create(&system);

		if (system) {
			cout << "High-level (fmod studio) audio system created." << "\n";
		}




		FMOD::System* lowLevelSystem = NULL;
		system->getLowLevelSystem(&lowLevelSystem);

		if (lowLevelSystem) {
			cout << "Low-level (fmod) audio system created." << "\n";
		}

		lowLevelSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_STEREO, 0);
		system->initialize(1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, NULL);

		FMOD::Sound* medieval = NULL;
		FMOD::Sound* footsteps = NULL;

		lowLevelSystem->createSound("medieval.mp3", FMOD_LOOP_OFF, NULL, &medieval);

		lowLevelSystem->createSound("footsteps.mp3", FMOD_LOOP_OFF, NULL, &footsteps);

		if (medieval) {
			cout << "Sound loaded." << "\n";
		}

		if (footsteps) {
			cout << "Sound loaded." << "\n";
		}

		medieval->setDefaults(16400, 0);

		footsteps->setDefaults(16400, 0);

		FMOD::Channel* catChannel = NULL;




		createShaders();
		createObjects();

		cam = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 2.0f, 1.0f);

		Knight = Model();
		Knight.LoadModel("Models/KNIGHTMODEL.obj");

		Enviro = Model();
		Enviro.LoadModel("Models/3Denvironment.obj");

		mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
			1.0f, 0.5f,
			1.0f, 3.0f, 1.0f);




		std::vector<std::string> skyboxFaces;
		skyboxFaces.push_back("Textures/skybox/miramar_ft.tga");
		skyboxFaces.push_back("Textures/skybox/miramar_bk.tga");
		skyboxFaces.push_back("Textures/skybox/miramar_up.tga");
		skyboxFaces.push_back("Textures/skybox/miramar_dn.tga");
		skyboxFaces.push_back("Textures/skybox/miramar_rt.tga");
		skyboxFaces.push_back("Textures/skybox/miramar_lf.tga");

		skybox = Skybox(skyboxFaces);

		GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
			uniformSpecularIntensity = 0, uniformShininess = 0;

		glm::mat4 projection = glm::perspective(glm::radians(60.0f), ((GLfloat)Window.getBufferWidth() / (GLfloat)Window.getBufferHeight()), 0.1f, 100.0f);

		//Loop until window closed

		while (!Window.getShouldClose())
		{

			while (enet_host_service(client, &enetEvent, 0) > 0)
			{
				switch (enetEvent.type) {

					
				case ENET_EVENT_TYPE_RECEIVE:
					cout << "Packet received!\n";
					break;
				}
			}

			
			system->update();

			lowLevelSystem->playSound(medieval, NULL, false, &catChannel);
			//lowLevelSystem->playSound(footsteps, NULL, false, &catChannel);


			GLfloat now = glfwGetTime();
			deltaTime = now - lastTime;
			lastTime = now;

			// Get user input
			glfwPollEvents();

			cam.keyControl(Window.getKeys(), deltaTime);
			cam.mouseControl(Window.getXChange(), Window.getYChange());



			//clear the window
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			skybox.DrawSkybox(cam.calculateViewMatrix(), projection);

			shaderList[0].useShader();
			uniformModel = shaderList[0].getModelLocation();
			uniformProjection = shaderList[0].getProjectionLocation();
			uniformView = shaderList[0].getViewLocation();
			uniformEyePosition = shaderList[0].getEyePosition();
			uniformSpecularIntensity = shaderList[0].getSpecularIntensityLocation();
			uniformShininess = shaderList[0].getShininessLocation();

			glm::vec3 lowerLight = cam.getCamPosition();
			lowerLight.y -= 0.3f;
			spotLights[0].setFlash(lowerLight, cam.getCamDirection());

			shaderList[0].setDirectionalLight(&mainLight);


			glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
			glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(cam.calculateViewMatrix()));
			glUniform3f(uniformEyePosition, cam.getCamPosition().x, cam.getCamPosition().y, cam.getCamPosition().z);

			glm::mat4 model{ 1.0 };


			shinyMaterial.useMaterial(uniformSpecularIntensity, uniformShininess);




			model = glm::mat4{ 1.0 };
			model = glm::translate(model, glm::vec3(8.0f, -3.0f, -6.0f));
			model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			shinyMaterial.useMaterial(uniformSpecularIntensity, uniformShininess);
			Knight.RenderModel();

			model = glm::mat4{ 1.0 };
			model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
			model = glm::scale(model, glm::vec3(0.005f, 0.005f, 0.005f));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 90.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			shinyMaterial.useMaterial(uniformSpecularIntensity, uniformShininess);
			Enviro.RenderModel();

			glUseProgram(0);
			Window.swapBuffers();






		}
		return 0;
		enet_host_destroy(client);
		atexit(enet_deinitialize);
	}



	
