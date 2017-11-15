/**
 * @Author: danielb
 * @Date:   2017-07-22T23:35:22+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-11-15T15:50:30+01:00
 */

#include <fse/Window.hpp>
#include <fse/Renderer/Renderer.hpp>
#include <fse/Scene/Object/Object.hpp>
#include <fse/Scene/Object/Wavefront.hpp>
#include <fse/Scene/SceneManager.hpp>
#include <fse/Scene/CameraFPS.hpp>

#include "Map.hpp"

#include <chrono>

using namespace fse::scene::object;

void    generate_world(fse::scene::SceneManager &scene)
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
    Window                      window(1024, 1024);
    // Window                      window(1540, 960);
    fse::Renderer               renderer(window);
    fse::scene::SceneManager    scene;
    fse::scene::CameraFPS       camera;
    float speed = 4.f; // 3 units / second

    scene.camera = &camera;
    camera.getPosition()[2] = 10;
    camera.getPosition()[1] = 10;
    camera.mouseInput(0, 0, 0);

    scene.setLight(std::make_shared<fse::scene::Light>());
    scene.getLight()->setPosition({5, 10, 5});

    std::cout << "[OpenGL]\nVendor: " << glGetString(GL_VENDOR) << "\nRenderer: ";
    std::cout << glGetString(GL_RENDERER) << "\nVersion: ";
    std::cout << glGetString(GL_VERSION) << "\nGLSL Version: ";
    std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\nExtension: ";
    // std::cout << glGetString(GL_EXTENSIONS) << "\n\n\n";

    // Object *wavefront = scene.addWavefront("Ressource/Audi R8.fbx");
    // wavefront->setScale({0.05, 0.05, 0.05});
    // // wavefront->getMaterial()->setTexture("Ressource/alduin.bmp");
    // wavefront->getMaterial()->setColor(0.5, 0.5, 0.5);

    Object *wavefront = scene.addWavefront("Ressource/alduin.obj");
    wavefront->setScale({0.005, 0.005, 0.005});
    wavefront->setPosition({5,0,5});
    wavefront->getMaterial()->setColor(100.5, 0, 0);
    wavefront->getMaterial()->setTexture("Ressource/alduin.jpg");

    float size = 2;
    game::Map *map = new game::Map(scene, size, size, 10);
    // map->setPosition({-2, 0, -2});
    // map->setPosition({-size / 2., 0, -size / 2.});
    map->getMaterial()->setTexture("Ressource/grass_terrain.jpg");
    scene.addChild(map);

    fse::scene::object::Object *surface = scene.addWavefront("Ressource/plan.obj");
    surface->getMaterial()->setTexture(scene.getLight()->getTexture());
    surface->setScale({5, 1, 5});
    surface->setPosition({-7, 0, 3});
    surface->getMaterial()->setShader(fse::ShaderManager::getInstance().addShader("depth_viewer"));

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
        scene.getLight()->getPosition() +=  vector * 3.f * move_handle;
        // scene.camera->setPosition(scene.getLight()->getPosition());
        if (scene.getLight()->getPosition().x > 10)
          vector *= -1;
        else if (scene.getLight()->getPosition().x < 0)
          vector *= -1;
        // wavefront->getRotation().y += 1 * move_handle;

        // scene.getLight()->setView(scene.camera->getView());

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
