#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGl/glu.h>
	#include <GLUT/glut.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

class pukk
{
	public:
		vec vel;
		vec pos;
		vec frict;
		float radius;
		vec CalcResponse(vec *normal);
		void Render(void);

};

vec pukk::CalcResponse(vec *normal)
{
	float t_dot;
	float mod;
	vec unit;
	vec temp;
	t_vector vector;
	unit = vector.UnitaryVector(&vel);
	t_dot = vector.Dot(&unit, normal);
	temp = vector.MultiplyVectorScalar(2 * t_dot, normal);
	temp = vector.Substract(&unit, &temp);
	mod = vector.Modulus(&vel);
	temp = vector.MultiplyVectorScalar(mod, &temp);

	return temp;
}

void pukk::Render(void)
{
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
		glTranslatef(pos.x, pos.z, 0.0);
		glBegin(GL_QUADS);
			glVertex3f(-1.0, -1.0, -5.0);
			glVertex3f(-1.0, 1.0, -5.0);
			glVertex3f(1.0, 1.0, -5.0);
			glVertex3f(1.0, -1.0, -5.0);
		glEnd();
	glPopMatrix();
}
