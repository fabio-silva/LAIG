#include "GL\glew.h"
#include "YafReader.h"
void myGlutIdle();
void display();
void controlPanelCamera(int id);
void controlSpotLights(int id);
void controlOmniLights(int id);
void controlDrawMode(int id);

int main_window;
YafReader *x;
GLUI  *glui2;
GLUI_RadioGroup *group;
GLUI_RadioGroup *drawmode;
vector <GLUI_Checkbox*> spots;
vector <GLUI_Checkbox*>	omnis;

void init()
{
	x->scene.init();

}

void display()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	x->scene.display();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:		//ESC termina o programa
		exit(0);
		break;
	}
}

int main(int argc, char* argv[])
{	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(30,30);

	main_window = glutCreateWindow(argv[0]);
	
	glewInit();



		


	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glui2 = GLUI_Master.create_glui_subwindow( main_window, GLUI_SUBWINDOW_RIGHT );
	glui2->set_main_gfx_window( main_window );

	GLUI_Master.set_glutIdleFunc(myGlutIdle);

	int activeCam;
	if(argc == 2) x = new YafReader(argv[1]);
	else x = new YafReader("projXML.yaf");

	for(unsigned int i = 0;i<x->scene.getCameras().size();i++) if(strcmp(x->scene.getInitialCameraId(), x->scene.getCameras()[i]->getId()) == 0) activeCam = i;
	GLUI_Panel *obj_panel = glui2->add_panel("Camaras");
	group = glui2->add_radiogroup_to_panel(obj_panel, &activeCam,-1, controlPanelCamera);


	for(unsigned int i = 0; i <x->scene.getCameras().size();i++) glui2->add_radiobutton_to_group(group, x->scene.getCameras()[i]->getId());

	glui2->add_separator();
	glui2->add_statictext("Spots");

	for(unsigned int i = 0; i <x->scene.getSpots().size();i++)
	{
		int enabled = 0;

		if(x->scene.getSpots()[i]->isEnabled()) enabled = 1;
		GLUI_Checkbox * spot = glui2->add_checkbox(x->scene.getSpots()[i]->getId(), &enabled, i, controlSpotLights);

		spots.push_back(spot);
	}

	glui2->add_separator();
	glui2->add_statictext("Omni");
	for(unsigned int i = 0; i <x->scene.getOmnis().size();i++)
	{
		int enabled = 0;

		if(x->scene.getOmnis()[i]->isEnabled()) enabled = 1;
		GLUI_Checkbox * omni = glui2->add_checkbox(x->scene.getOmnis()[i]->getId(), &enabled, i, controlOmniLights);

		omnis.push_back(omni);
	}


	glui2->add_separator();


	int selectedMode ;

	if(strcmp(x->scene.getDrawMode(), "fill") == 0) selectedMode = 0;
	else if(strcmp(x->scene.getDrawMode(), "line") == 0) selectedMode = 1;
	else selectedMode = 2;

	GLUI_Panel *drawPanel = glui2->add_panel("Drawmode");

	drawmode = glui2->add_radiogroup_to_panel(drawPanel,&selectedMode,-1, controlDrawMode);


	GLUI_RadioButton * fillBt = glui2->add_radiobutton_to_group(drawmode, "Fill");
	GLUI_RadioButton * lineBt = glui2->add_radiobutton_to_group(drawmode, "Line");
	GLUI_RadioButton * pointBt = glui2->add_radiobutton_to_group(drawmode, "Point");

	init();	

	glutMainLoop();
}

void myGlutIdle()
{
	if ( glutGetWindow() != main_window ) 
		glutSetWindow(main_window);  

	glutPostRedisplay();
}


void controlPanelCamera(int id)
{
	int activeBt = group->get_int_val();

	x->scene.setActiveCamera(x->scene.getCameras()[activeBt]);
	x->scene.getCameras()[activeBt]->render();
}

void controlSpotLights(int id)
{
	if(spots[id]->get_int_val() == 1) glEnable(x->scene.getSpots()[id]->getLightNr());
	else glDisable(x->scene.getSpots()[id]->getLightNr());
}

void controlOmniLights(int id)
{
	if(omnis[id]->get_int_val() == 1) glEnable(x->scene.getOmnis()[id]->getLightNr());
	else glDisable(x->scene.getOmnis()[id]->getLightNr());
}

void controlDrawMode(int id)
{
	int activeMode = drawmode->get_int_val();
	GLenum mode;

	if(strcmp(x->scene.getCullFace(),"front") == 0) mode = GL_FRONT;
	else if (strcmp(x->scene.getCullFace(),"back") == 0) mode = GL_BACK;
	else if (strcmp(x->scene.getCullFace(),"both") == 0) mode = GL_FRONT_AND_BACK;
	else mode = GL_NONE;

	switch(activeMode)
	{
	case 0:
		x->scene.setDrawMode("fill");
		break;
	case 1:
		x->scene.setDrawMode("line");
		break;
	case 2:
		x->scene.setDrawMode("point");
		break;
	}
}

