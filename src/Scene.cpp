#include "Scene.h"

Scene::Scene()
    : light_(glm::vec3(80.0, 50.0, 0.0))
{
}

Scene::~Scene()
{
}

int Scene::addRenderable(Renderable * object)
{
    renderables_[nextRenderableId_] = object;
    return nextRenderableId_++;
}

int Scene::addInput(InputController* input)
{
    inputs_[nextInputId_] = input;
    return nextInputId_++;
}

void Scene::removeRenderable(int id)
{
    renderables_.erase(id);
}

void Scene::removeInput(int id)
{
    inputs_.erase(id);
}

void Scene::keyboard(unsigned char key, int x, int y)
{
    for (auto &input : inputs_) {
        input.second->keyboardInput(key, x, y);
    }
}

void Scene::mouse(int button, int state, int x, int y)
{
    for (auto &input : inputs_) {
        input.second->mouseInput(button, state, x, y);
    }
}

void Scene::setLight(glm::vec3 light)
{
    light_ = light;
}

glm::vec3 Scene::getLight() const
{
    return light_;
}

void Scene::update(float time)
{
    for (auto &renderable : renderables_)
        renderable.second->update(time);
}
void Scene::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    if (!camera_) return;

    RenderData data;
    data.lightSource = light_;
    data.viewProjMatrix = camera_->getViewProjMatrix();

    for (auto &renderable : renderables_)
        renderable.second->render(data);

    glutSwapBuffers();
}

void Scene::setCamera(Camera *camera)
{
    camera_ = camera;
}
