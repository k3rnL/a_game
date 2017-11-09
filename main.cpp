/**
 * @Author: danielb
 * @Date:   2017-07-22T23:35:22+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-11-09T11:29:30+01:00
 */

#include "Window.hpp"
#include "Renderer.hpp"
#include "Object.hpp"
#include "Triangle.hpp"
#include "Scene/Object/Wavefront.hpp"
#include "Scene/SceneManager.hpp"
#include "Scene/CameraFPS.hpp"

#include "Map.hpp"

#include <chrono>

using namespace mxe::scene::object;

void    generate_world(mxe::scene::SceneManager &scene)
{
  std::shared_ptr<Material>   mat = std::make_shared<Material>();
  mat->setTexture("Ressource/grass_terrain.jpg");
  mat->setColor(0.1, 0.5, 1);
  std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
  for (int x = -50 ; x < 50 ; x++)
  for (int y = -1 ; y < 0 ; y++)
  for (int z = -50 ; z < 50 ; z++)
  {
    Object *cube = scene.addWavefront("Ressource/cube.obj");
    cube->setPosition({x, y , z});
    cube->applyMaterial(mat);
  }
  std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

  std::cout << "Loading time : " << duration / 1000000 << "s" << duration % 1000000 << "ms\n";
}


int main()
{
    Window                      window(1540, 960);
    mxe::Renderer               renderer(window);
    mxe::scene::SceneManager    scene;
    mxe::scene::CameraFPS       camera;
    float speed = 4.f; // 3 units / second

    scene.camera = &camera;
    camera.getPosition()[2] = 10;
    camera.getPosition()[1] = 10;
    camera.mouseInput(0, 0, 0);

    scene.getLight() = glm::vec3(0, 10, 0);

    // Object *wavefront = scene.addWavefront("Ressource/Audi R8.fbx");
    // wavefront->setScale({0.05, 0.05, 0.05});
    // // wavefront->getMaterial()->setTexture("Ressource/alduin.bmp");
    // wavefront->getMaterial()->setColor(0.5, 0.5, 0.5);

    size_t size = 2;
    game::Map *map = new game::Map(scene, size, size, 10);
    // map->setPosition({-size / 2, 0, -size / 2});
    map->getMaterial()->setTexture("Ressource/grass_terrain.jpg");
    scene.addChild(map);

    Object *wavefront = scene.addWavefront("Ressource/alduin.obj");
    wavefront->setScale({0.005, 0.005, 0.005});
    wavefront->getMaterial()->setTexture("Ressource/alduin.bmp");
    // Wavefront wavefront2("Ressource/teapot.obj");
    // Triangle triangle(glm::vec3(-1, 1, 0), glm::vec3(1, 1, 0), glm::vec3(0, 0, 0));
    // Wavefront wavefront("/home/daniel_b/gfx_raytracer2/Wavefront/cow.obj");

    for (int i = 0 ; i < 00 ; i++)
    {
      Object *w = scene.addWavefront("Ressource/alduin.obj");
      w->getPosition()[0] = rand() % 100 - 50;
      w->getPosition()[1] = rand() % 100;
      w->getPosition()[2] = rand() % 100 - 50;
      // w->getMaterial().setTexture("Ressource/alduin.bmp");
    }

    // generate_world(scene);

    // wavefront->getPosition().y += 1;
    // wavefront->getRotation().y += 90;

    // objects.push_back(&triangle);
    // objects.push_back(&wavefront2);

    while (1)
    {
        renderer.render(scene);

        float   move_handle = 1.0 / renderer.getFrameCounter().getFrameRate();

        static glm::vec3 vector(1, 0, 1);
        scene.getLight() +=  vector * 3.f * move_handle;
        if (scene.getLight().x > 10)
          vector *= -1;
        else if (scene.getLight().x < 0)
          vector *= -1;
        // wavefront->getRotation().y += 1 * move_handle;

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
                if (event.key.keysym.sym == SDLK_SPACE) {
                    map->randomize();
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
