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

    if (dtime < 1.f)   // process physics only if more than 1 fps
    {
        physxTimeToProcess += dtime;
    }
    while (physxTimeToProcess > 0)
    {
        physxScene.step(physxStepTime);
        physxTimeToProcess -= physxStepTime;
    }

    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    auto x=[time]()
    {
        return time * time;
    }
    ();
    camera.resize(width, height);
    scene.calculateMatrices(time);
    scene.render();
}

glm::mat4 move_ball(float time)
{
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

}

void init()
{

    terrain.init();
    //creating exemplary planetary system
    //creating 'sun'
    ball = new RenderOBJ("models/ball.obj");
    ball->setMatrixFunction([](float time)
    {
        return glm::translate(glm::vec3(0, 50,0))*glm::rotate(time / 19, glm::vec3(0, 1, 0))*glm::translate(glm::vec3(0, 0, 0))*glm::scale(glm::vec3(3));
    });
    scene.registerObject(ball);
    //creating planet with parent object as sun
    ball = new RenderOBJ("models/ball.obj",ball);

    ball->setMatrixFunction([](float time)
    {
        return glm::rotate(time / 3, glm::vec3(0, 1, 0))*glm::translate(glm::vec3(10, 0, 0))*glm::scale(glm::vec3(0.5));
    });
    scene.registerObject(ball);
    //creating moon for a planet
    ball = new RenderOBJ("models/ball.obj",ball);

    ball->setMatrixFunction([](float time)
    {
        return glm::rotate(time*2, glm::vec3(0, 1, 0))*glm::translate(glm::vec3(1, 0, 0))*glm::scale(glm::vec3(0.1));
    });
    scene.registerObject(ball);
    //end od planetary system

    //physix example
    ball = new RenderOBJ("models/ball.obj");
    //physix based objects shouldn't have parent object
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
    //registering camera and controlle for it
    scene.setCamera(&camera);
    scene.registerInput(&controller);
    //scene.registerInput(bController);
    glEnable(GL_DEPTH_TEST);
}

void shutdown()
{

}
//binding scene to mouse and keyboard input
void mouse(int button, int state, int x, int y)
{
    scene.mouse(button, state, x, y);
}
void motion(int x, int y)
{
    scene.mouse(-1, -1, x, y);
}
void keyboard(unsigned char key, int x, int y)
{
    scene.keyboard(key, x, y);
}


void idle()
{
    glutPostRedisplay();
}

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(600, 600);
    glutCreateWindow("OpenGL Pierwszy Program");

    glewInit();

    init();
    glutDisplayFunc(renderScene);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    glutMainLoop();

    shutdown();

    return 0;
}
