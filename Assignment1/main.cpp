#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "mesh.h"
#include "glut.h"
#include "View.h"
#include "Light.h"


mesh *object;
View *view;
Light *light;

int windowSize[2];

void display();
void reshape(GLsizei , GLsizei );

int main(int argc, char** argv)
{
	object = new mesh("box.obj");
	view = new View("view.view");
	light = new Light("light.light");

	glutInit(&argc, argv);
	glutInitWindowSize(view->viewport[2] - view->viewport[0], view->viewport[3] - view->viewport[1]);
	glutInitWindowPosition(view->viewport[0], view->viewport[1]);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Assignment1");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();

	return 0;
}

void display()
{
	// clear the buffer
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);      //清除用color
	glClearDepth(1.0f);                        // Depth Buffer (就是z buffer) Setup
	glEnable(GL_DEPTH_TEST);                   // Enables Depth Testing
	glDepthFunc(GL_LEQUAL);                    // The Type Of Depth Test To Do
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//這行把畫面清成黑色並且清除z buffer

	view->apply();
	glutReshapeWindow(windowSize[0], windowSize[1]);

	//注意light位置的設定，要在gluLookAt之後
	light->apply();

	int lastMaterial = -1;
	for(size_t i=0;i < object->fTotal;++i)
	{
		// set material property if this face used different material
		if(lastMaterial != object->faceList[i].m)
		{
			lastMaterial = (int)object->faceList[i].m;
			glMaterialfv(GL_FRONT, GL_AMBIENT  , object->mList[lastMaterial].Ka);
			glMaterialfv(GL_FRONT, GL_DIFFUSE  , object->mList[lastMaterial].Kd);
			glMaterialfv(GL_FRONT, GL_SPECULAR , object->mList[lastMaterial].Ks);
			glMaterialfv(GL_FRONT, GL_SHININESS, &object->mList[lastMaterial].Ns);

			//you can obtain the texture name by object->mList[lastMaterial].map_Kd
			//load them once in the main function before mainloop
			//bind them in display function here
		}

		glMatrixMode(GL_MODELVIEW);
		
		glPushMatrix();

		glTranslatef(-200.0, 0.0, 0.0);
		glRotatef(0.0, 0.0, 1.0, 0.0);
		glScalef(1.0, 1.0, 1.0);
		
		glBegin(GL_TRIANGLES);
		for (size_t j=0;j<3;++j)
		{
			//textex corrd. object->tList[object->faceList[i][j].t].ptr
			glNormal3fv(object->nList[object->faceList[i][j].n].ptr);
			glVertex3fv(object->vList[object->faceList[i][j].v].ptr);	
		}
		glEnd();


		glPopMatrix();
	}

	glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h)
{
	windowSize[0] = w;
	windowSize[1] = h;
}

