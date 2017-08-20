/**
 * @Author: danielb
 * @Date:   2017-07-22T23:35:22+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-08-20T23:50:06+02:00
 */

#include "Window.hpp"
#include "Renderer.hpp"
#include "Object.hpp"
#include "Triangle.hpp"
#include "Scene/Object/Wavefront.hpp"
#include "Scene/SceneManager.hpp"
#include "Scene/CameraFPS.hpp"

#include <chrono>

using namespace mxe::scene::object;

void    generate_world(mxe::scene::SceneManager &scene, ObjectList &objs)
{
  std::shared_ptr<Material>   mat = std::make_shared<Material>();
  mat->setTexture("Ressource/grass.jpg");
  std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
  for (int x = -50 ; x < 50 ; x++)
  for (int z = -50 ; z < 50 ; z++)
  {
    Wavefront *cube = scene.addWavefront("Ressource/cube.obj");
    cube->getPosition()[0] = x;
    cube->getPosition()[2] = z;
    cube->applyMaterial(mat);
    objs.push_back(cube);
  }
  std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

  std::cout << "Loading time : " << duration / 1000000 << "s" << duration % 1000000 << "ms\n";
}


int main()
{
    Window                      window;
    mxe::Renderer               renderer(window);
    mxe::scene::SceneManager    scene;
    mxe::scene::CameraFPS       camera;
    ObjectList                  objects;
    float speed = 4.f; // 3 units / second

    scene.camera = &camera;
    camera.getPosition()[2] = 10;
    camera.mouseInput(0, 0, 0);

    Wavefront *wavefront = scene.addWavefront("Ressource/cube.obj");
    wavefront->getMaterial()->setTexture("Ressource/alduin.bmp");


    Wavefront wavefront2("Ressource/teapot.obj");
    // Triangle triangle(glm::vec3(-1, 1, 0), glm::vec3(1, 1, 0), glm::vec3(0, 0, 0));
    // Wavefront wavefront("/home/daniel_b/gfx_raytracer2/Wavefront/cow.obj");

    for (int i = 0 ; i < 000 ; i++)
    {
      Wavefront *w = scene.addWavefront("Ressource/alduin.obj");
      w->getPosition()[0] = rand() % 100 - 50;
      w->getPosition()[1] = rand() % 100;
      w->getPosition()[2] = rand() % 100 - 50;
      // w->getMaterial().setTexture("Ressource/alduin.bmp");
      objects.push_back(w);
    }

    generate_world(scene, objects);

    wavefront->getPosition().y += 1;
    wavefront->getRotation().y += 90;

    // objects.push_back(&triangle);
    objects.push_back(&wavefront2);

    while (1)
    {
        renderer.render(scene);

        float   move_handle = 1. / renderer.fps.getFrameRate();

        wavefront->getRotation().y += 1 * move_handle;

        SDL_Event event;
        while (window.pollEvent(event))
        {
            if (event.type == SDL_KEYDOWN)
            {
              glm::vec3 direction = camera.getDirection();

                if (event.key.keysym.sym == SDLK_z)
                  camera.getPosition() += glm::vec3(speed) * direction * glm::vec3(move_handle);
                if (event.key.keysym.sym == SDLK_s)
                  camera.getPosition() -= glm::vec3(speed) * direction * glm::vec3(move_handle);
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        window.close();
                        return (0);
                    }
                camera.mouseInput(0, 0, move_handle);

            }

            if (event.type == SDL_MOUSEMOTION)
            {
                int xpos = 0, ypos = 0;
                SDL_GetRelativeMouseState(&xpos, &ypos);
                camera.mouseInput(xpos, ypos, move_handle);
            }
        } // end event polling
    }

    return (0);
}
