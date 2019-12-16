//==============================================================================================
//==============================================================================================
//
//         THIS IS IS A COMMON FILE FOR ALL THE GROUPS
//
//         BE CAREFUL WHEN MODYFING IT !!!!!!!!!!!!!!!
//
//         PLACE COMMENTS AROUND YOUR CHANGES TO MAKE IT CLEAR FOR THE OTHER GROUPS
//         WHAT PART OF THE CODE IS RESPONSIBLE FOR WHAT AND WHO WROTE IT
//
//==============================================================================================
//==============================================================================================
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

//==========================================================
const float gravity = 9.8; // m / s^2
// fixed timestep for stable and deterministic simulation
const double physxStepTime = 1.f / 60.f;
double physxTimeToProcess = 0;

Scene scene;
PhysxScene pxScene(gravity);
Camera camera;
//==========================================================


//==========================================================
// Group: Terrain
// ...
// ...

//==========================================================
// Group: Physics
// ...
// ...

//==========================================================
// Group: Effects
// ...
// ...

//==========================================================

void init()
{
    scene.setCamera(&camera);

    //==========================================================
    // Group: Terrain
    // ...
    // ...

    //==========================================================
    // Group: Physics
    // ...
    // ...

    //==========================================================
    // Group: Effects
    // ...
    // ...

    //==========================================================

    glEnable(GL_DEPTH_TEST);
}

void shutdown()
{
    //==========================================================
    // Group: Terrain
    // ...
    // ...

    //==========================================================
    // Group: Physics
    // ...
    // ...

    //==========================================================
    // Group: Effects
    // ...
    // ...

    //==========================================================
}

//==========================================================
void updateTransforms()
{
    // Here we retrieve the current transforms of the objects from the physical simulation.
    auto actorFlags = PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC;
    PxU32 nbActors = pxScene.scene->getNbActors(actorFlags);
    if (nbActors)
    {
        std::vector<PxRigidActor*> actors(nbActors);
        pxScene.scene->getActors(actorFlags, (PxActor**)&actors[0], nbActors);
        for (auto actor : actors)
        {
            // We use the userData of the objects to set up the proper model matrices.
            if (!actor->userData) continue;
            Renderable *renderable = (Renderable*)actor->userData;

            // get world matrix of the object (actor)
            PxMat44 transform = actor->getGlobalPose();
            auto &c0 = transform.column0;
            auto &c1 = transform.column1;
            auto &c2 = transform.column2;
            auto &c3 = transform.column3;

            // set up the model matrix used for the rendering
            renderable->setModelMatrix(glm::mat4(
                c0.x, c0.y, c0.z, c0.w,
                c1.x, c1.y, c1.z, c1.w,
                c2.x, c2.y, c2.z, c2.w,
                c3.x, c3.y, c3.z, c3.w));
        }
    }
}

void updatePhysics(float dtime)
{
    if (dtime < 1.f) // process physics only if more than 1 fps
    {
        physxTimeToProcess += dtime;
    }
    while (physxTimeToProcess > 0)
    {
        pxScene.step(physxStepTime);
        physxTimeToProcess -= physxStepTime;
    }
}

void renderScene()
{
    static double prevTime = 0;
    double time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    double dtime = time - prevTime;
    prevTime = time;

    updatePhysics(dtime);
    updateTransforms();

    scene.update(time);
    scene.render();
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
