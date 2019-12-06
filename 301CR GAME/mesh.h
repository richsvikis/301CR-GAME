#ifndef __MESH__
#define __MESH__
#include <GL/glew.h>

class Mesh
{
public:
	Mesh();

	void createMesh(GLfloat* vertices, unsigned int* indices, unsigned int numOfvertices, unsigned int numOfindices);
	void renderMesh();
	void clearMesh();

	~Mesh();

private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;
};

#endif
