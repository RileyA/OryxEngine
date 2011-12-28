#include "Mesh.h"
#include "GLSubsystem.h"
#include <GL/gl.h>
#include <GL/glu.h>

namespace Oryx
{
	Mesh::Mesh()
	{

	}
	//-----------------------------------------------------------------------

	Mesh::~Mesh()
	{

	}
	//-----------------------------------------------------------------------

	void Mesh::_draw()
	{
		// just a triangle...
		glBegin(GL_TRIANGLES);
		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(0.f, 1.f, 0.f);
		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(-1.f, -1.f, 0.f);
		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(1.f, -1.f, 0.f);
		glEnd();
	}
	//-----------------------------------------------------------------------
}

