#include <ctime>
#include <iostream>
#include <cmath>
#include <vector>

#include "glew.h"
#include "freeglut.h"
#include "glm.hpp"
#include "ext.hpp"
#include "SOIL/SOIL.h"
#include "ShaderLoader.h"

#include "Scene.h"
#include "PhysxScene.h"
#include "Camera.h"

#include "CameraController.h"
#include "BallController.h"
#include "ExampleRenderable.h"
#include "ExampleTerrain.h"

Scene scene;
ExampleRenderable *ball1, *ball2, *ball3, *ball4;
ExampleTerrain terrain;
Camera camera;
CameraController controller(&camera);
int id = 0;

PhysxScene pxScene(9.8);
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
        pxScene.step(physxStepTime);
        physxTimeToProcess -= physxStepTime;
    }

    scene.update(time);
    scene.render();
}

glm::mat4 move_ball(float time)
{
    auto actorFlags = PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC;
    PxU32 nbActors = pxScene.scene->getNbActors(actorFlags);
    if (nbActors)
    {
        std::vector<PxRigidActor*> actors(nbActors);
        pxScene.scene->getActors(actorFlags, (PxActor**)&actors[0], nbActors);

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
    return glm::mat4();
}

void init()
{
    terrain.init();
    //creating exemplary planetary system
    //creating 'sun'
    ball1 = new ExampleRenderable("models/ball.obj");
    ball1->setMatrixFunction([&](float time)
    {
        return glm::translate(glm::vec3(0, 50,0))*glm::rotate(time / 19, glm::vec3(0, 1, 0))*glm::translate(glm::vec3(0, 0, 0))*glm::scale(glm::vec3(3));
    });
    scene.addRenderable(ball1);
    //creating planet with parent object as sun
    ball2 = new ExampleRenderable("models/ball.obj");

    ball2->setMatrixFunction([&](float time)
    {
        return ball1->getModelMatrix() * glm::rotate(time / 3, glm::vec3(0, 1, 0))*glm::translate(glm::vec3(10, 0, 0))*glm::scale(glm::vec3(0.5));
    });
    scene.addRenderable(ball2);
    //creating moon for a planet
    ball3 = new ExampleRenderable("models/ball.obj");

    ball3->setMatrixFunction([&](float time)
    {
        return ball2->getModelMatrix() * glm::rotate(time * 2, glm::vec3(0, 1, 0))*glm::translate(glm::vec3(1, 0, 0))*glm::scale(glm::vec3(0.1));
    });
    scene.addRenderable(ball3);
    //end of planetary system

    //physix example
    ball4 = new ExampleRenderable("models/ball.obj");
    //physix based objects shouldn't have parent object
    ball4->setMatrixFunction(move_ball);
    scene.addRenderable(ball4);

    {
        PxTransform t(0, 10, 0);

        ballMaterial = pxScene.physics->createMaterial(0.5f, 0.5f, 0.6f);

        PxShape* shape = pxScene.physics->createShape(
                             PxSphereGeometry(1), *ballMaterial);

        dynamicBall = pxScene.physics->createRigidDynamic(t);
        dynamicBall->attachShape(*shape);
        dynamicBall->setLinearVelocity(PxVec3(0,10,0));
        PxRigidBodyExt::updateMassAndInertia(*dynamicBall, 10.0f);
        pxScene.scene->addActor(*dynamicBall);

        shape->release();
    }


    id=scene.addRenderable(&terrain);
    //registering camera and controller for it
    scene.setCamera(&camera);
    scene.addInput(&controller);
    //scene.addInput(bController);
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
    glutCreateWindow("OpenGL Project");

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
