#include "mesh.h"
#include "glut.h"
#include <fstream>
#include <string>
#include <vector>

mesh *object;

int windowSize[2];

void light();
void display();
void reshape(GLsizei , GLsizei );

int main(int argc, char** argv)
{
	object = new mesh("box.obj");

	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Mesh Example");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();

	return 0;
}

typedef struct LIGHT
{
	GLfloat position[4] = { 1.0 };
	GLfloat ambient[4] = { 1.0 };
	GLfloat diffuse[4] = { 1.0 };
	GLfloat specular[4] = { 1.0 };
} LIGHT;

void light()
{
	std::fstream fin("light.light", std::fstream::in);
	std::string term;
	std::vector<LIGHT> lights;
	GLfloat ambient[4] = { 1.0 };
	while(fin >> term)
	{
		if (term == "light")
		{
			LIGHT light;
			fin >> light.position[0] >> light.position[1] >> light.position[2];
			fin >> light.ambient[0] >> light.ambient[1] >> light.ambient[2];
			fin >> light.diffuse[0] >> light.diffuse[1] >> light.diffuse[2];
			fin >> light.specular[0] >> light.specular[1] >> light.specular[2];
			lights.push_back(light);
		}
		else if (term == "ambient")
		{
			fin >> ambient[0] >> ambient[1] >> ambient[2];
		}
	}

	glShadeModel(GL_SMOOTH);

	// z buffer enable
	glEnable(GL_DEPTH_TEST);

	// enable lighting
	glEnable(GL_LIGHTING);
	// set light property
	for (int i = 0; i < lights.size(); ++i)
	{
		glEnable(GL_LIGHT0 + i);
		glLightfv(GL_LIGHT0 + i, GL_POSITION, lights[i].position);
		glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, lights[i].diffuse);
		glLightfv(GL_LIGHT0 + i, GL_SPECULAR, lights[i].specular);
		glLightfv(GL_LIGHT0 + i, GL_AMBIENT, lights[i].ambient);
	}
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
}

void display()
{
	// clear the buffer
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);      //清除用color
	glClearDepth(1.0f);                        // Depth Buffer (就是z buffer) Setup
	glEnable(GL_DEPTH_TEST);                   // Enables Depth Testing
	glDepthFunc(GL_LEQUAL);                    // The Type Of Depth Test To Do
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//這行把畫面清成黑色並且清除z buffer

	// viewport transformation
	glViewport(0, 0, windowSize[0], windowSize[1]);

	// projection transformation
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)windowSize[0]/(GLfloat)windowSize[1], 1.0, 1000.0);
	// viewing and modeling transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(	200.0, 300.0, 150.0,// eye
				0.0, 0.0, 0.0,     // center
				0.0, 1.0, 0.0);    // up

	//注意light位置的設定，要在gluLookAt之後
	light();

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

		glBegin(GL_TRIANGLES);
		for (size_t j=0;j<3;++j)
		{
			//textex corrd. object->tList[object->faceList[i][j].t].ptr
			glNormal3fv(object->nList[object->faceList[i][j].n].ptr);
			glVertex3fv(object->vList[object->faceList[i][j].v].ptr);	
		}
		glEnd();
	}

	glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h)
{
	windowSize[0] = w;
	windowSize[1] = h;
}

