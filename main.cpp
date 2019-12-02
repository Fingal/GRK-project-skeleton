#include "glew.h"
#include <ctime>
#include "freeglut.h"
#include "glm.hpp"
#include "ext.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include "SOIL/SOIL.h"
#include "Shader_Loader.h"
#include "Render_Utils.h"

#include "Scene.h"
#include "PhysxScene.h"
#include "CameraControl.h"
#include "Camera.h"
#include "RenderOBJ.h"
#include "Terrain.h"
#include "BallControl.h"

Scene scene=Scene();
RenderOBJ* ball;
Terrain terrain = Terrain();
Camera camera=Camera();
CameraControl controller= CameraControl(&camera);
BallControl* bController;
int id = 0;

PhysxScene physxScene(9.8);
PxRigidDynamic* dynamicBall = nullptr;
PxMaterial *ballMaterial = nullptr;
// fixed timestep for stable and deterministic simulation
const double physxStepTime = 1.f / 60.f;
double physxTimeToProcess = 0;


void renderScene()
{
    static double prevTime = 0;
	double time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    double dtime = time - prevTime;
    prevTime = time;

    if (dtime < 1.f) { // process physics only if more than 1 fps
        physxTimeToProcess += dtime;
    }
    while (physxTimeToProcess > 0) {
        physxScene.step(physxStepTime);
        physxTimeToProcess -= physxStepTime;
    }

    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
	auto x=[time]() {
		return time * time;
	}();
    camera.resize(width, height);
	scene.calculateMatrices(time);
	scene.render();
}

glm::mat4 move_ball(float time) {
    auto actorFlags = PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC;
    PxU32 nbActors = physxScene.scene->getNbActors(actorFlags);
    if (nbActors)
    {
        std::vector<PxRigidActor*> actors(nbActors);
        physxScene.scene->getActors(actorFlags, (PxActor**)&actors[0], nbActors);

        // get world matrix of actor
        PxMat44 transform = actors.back()->getGlobalPose();
        auto &c0 = transform.column0;
        auto &c1 = transform.column1;
        auto &c2 = transform.column2;
        auto &c3 = transform.column3;
        return glm::mat4(
            c0.x, c0.y, c0.z, c0.w,
            c1.x, c1.y, c1.z, c1.w,
            c2.x, c2.y, c2.z, c2.w,
            c3.x, c3.y, c3.z, c3.w);
    }

	return glm::translate(bController->get_pos());
}

void init()
{

	terrain.init();
	bController = new BallControl(&terrain);
	ball = new RenderOBJ("models/ball.obj");

	ball->setMatrixFunction([](float time) {
		return glm::translate(glm::vec3(0, 50,0))*glm::rotate(time / 19, glm::vec3(0, 1, 0))*glm::translate(glm::vec3(0, 0, 0))*glm::scale(glm::vec3(3));
	});
	scene.registerObject(ball);

	ball = new RenderOBJ("models/ball.obj",ball);

	ball->setMatrixFunction([](float time) {
		return glm::rotate(time / 3, glm::vec3(0, 1, 0))*glm::translate(glm::vec3(10, 0, 0))*glm::scale(glm::vec3(0.5));
	});
	scene.registerObject(ball);

	ball = new RenderOBJ("models/ball.obj",ball);

	ball->setMatrixFunction([](float time) {
		return glm::rotate(time*2, glm::vec3(0, 1, 0))*glm::translate(glm::vec3(1, 0, 0))*glm::scale(glm::vec3(0.1));
	});
	scene.registerObject(ball);

	ball = new RenderOBJ("models/ball.obj");

	ball->setMatrixFunction(move_ball);
	scene.registerObject(ball);

    {
        PxTransform t(0, 10, 0);

        ballMaterial = physxScene.physics->createMaterial(0.5f, 0.5f, 0.6f);

        PxShape* shape = physxScene.physics->createShape(
            PxSphereGeometry(1), *ballMaterial);

        dynamicBall = physxScene.physics->createRigidDynamic(t);
        dynamicBall->attachShape(*shape);
        dynamicBall->setLinearVelocity(PxVec3(0,10,0));
        PxRigidBodyExt::updateMassAndInertia(*dynamicBall, 10.0f);
        physxScene.scene->addActor(*dynamicBall);

        shape->release();
    }


	id=scene.registerObject(&terrain);

	scene.setCamera(&camera);
	scene.registerInput(&controller);
	scene.registerInput(bController);
	glEnable(GL_DEPTH_TEST);
}

void shutdown()
{
	
}

void mouse(int button, int state, int x, int y) {
	scene.mouse(button, state, x, y);
}
void motion(int x, int y) {
	scene.mouse(-1, -1, x, y);
}

void keyboard(unsigned char key, int x, int y) {
	scene.keyboard(key, x, y);
}


void idle()
{
	// Ta funkcja informuje freegluta, ze nalezy odzwiezyc zawartosc okna przy uzyciu funkcji podanej w glutDisplayFunc
	glutPostRedisplay();
}

int main(int argc, char ** argv)
{
	// Stworzenie okna przy u¿yciu biblioteki freeglut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(600, 600);
	glutCreateWindow("OpenGL Pierwszy Program");

	// Inicjalizacja rozszerzen OpenGL
	glewInit();

	// Inicjalizacja programu (ladowanie shaderow, tekstur itp)
	init();
	// Poinformowanie freegluta jaka funkcja bedzie sluzyc do odswiezania obrazu
	glutDisplayFunc(renderScene);
	//Poinformowanie freegluta jaka funkcja bedzie sluzyc do obslugi myszy
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	//Poinformowanie freegluta jaka funkcja bedzie sluzyc do obslugi klawiatury
	glutKeyboardFunc(keyboard);
	// Poinformowanie freegluta jaka funkcja bedzie wywolywana w glownej petli programu
	glutIdleFunc(idle);

	// Uruchomienie glownej petli
	glutMainLoop();

	// Sprzatanie (usuwanie shaderow itp)
	shutdown();

	return 0;
}
