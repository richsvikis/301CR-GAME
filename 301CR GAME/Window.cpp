#include "Window.h"

myWindow::myWindow()
{
	width = 800;
	height = 600;

	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = false;
	}
}

myWindow::myWindow(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
}

int myWindow::initalise()
{
	//init GLFW
	if (!glfwInit())
	{
		printf("GLFW Initalisation failed");
		glfwTerminate();
		return 1;
	}

	//GLFW window props
	//OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	mainWindow = glfwCreateWindow(width, height, "301CR", NULL, NULL);
	if (!mainWindow)
	{
		printf("GLFW Window failed");
		glfwTerminate();
		return 1;
	}


	//Buffer size info
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//Set context to mainWindow
	glfwMakeContextCurrent(mainWindow);

	//Keys and Mouse Input
	createCallbacks();
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//GLEW initalisation for modern extensions
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("GLEW initalisation failed");
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


GLfloat myWindow::getXChange()
{
	GLfloat theChange = changeX;
	changeX = 0.0f;
	return theChange;
}

GLfloat myWindow::getYChange()
{
	GLfloat theChange = changeY;
	changeY = 0.0f;
	return theChange;
}

myWindow::~myWindow()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}

void myWindow::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, handleKeys);
	glfwSetCursorPosCallback(mainWindow, handleMouse);
}

void myWindow::handleKeys(GLFWwindow* window, int key, int code, int action, int mod)
{
	myWindow* theWindow = static_cast<myWindow*>(glfwGetWindowUserPointer(window));

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


void myWindow::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
	myWindow* theWindow = static_cast<myWindow*>(glfwGetWindowUserPointer(window));

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
