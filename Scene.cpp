#include "Scene.h"



Scene::Scene()
{
    light = glm::vec3(80.0, 50.0, 0.0);
}


Scene::~Scene()
{
}

int Scene::registerInput(InputControl* input)
{
    lastIdInput += 1;
    inputControls[lastIdInput] = input;
    return lastIdInput;
}

void Scene::removeObject(int id)
{
    renderObjects.erase(id);
}

void Scene::removeInput(int id)
{
    renderObjects.erase(id);
}

void Scene::calculateMatrices(float time)
{
    for (auto object = renderObjects.begin(); object != renderObjects.end(); object++)
    {
        object->second->calculateTransformationMarix(time);
    }

}

void Scene::keyboard(unsigned char key, int x, int y)
{

    for (auto control = inputControls.begin(); control != inputControls.end(); control++)
    {
        control->second->keyboardInput(key,x,y);
    }

}

void Scene::mouse(int button, int state, int x, int y)
{
    for (auto control = inputControls.begin(); control != inputControls.end(); control++)
    {
        control->second->mouseInput(button,state, x, y);
    }

}

void Scene::setLight(glm::vec3 light)
{
    this->light = light;
}

glm::vec3 Scene::getLight()
{
    return this->light;
}

void Scene::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    RenderData data;
    data.lightSource = light;
    data.cameraProjectionMatrix = camera->getCameraProjectionMatix();
    for (auto object = renderObjects.begin(); object != renderObjects.end(); object++)
    {
        object->second->render(data);
    }
    glutSwapBuffers();
}

void Scene::setCamera(Camera * camera)
{
    this->camera = camera;
}

int Scene::registerObject(RenderObject * object)
{
    lastIdObjects += 1;
    renderObjects[lastIdObjects] = object;
    return lastIdObjects;
}
