/**
 * @Author: danielb
 * @Date:   2017-07-22T23:35:22+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2018-02-12T07:12:56+01:00
 */

#include <fse/Window.hpp>
#include <fse/Renderer/Renderer.hpp>
#include <fse/Scene/Object/Object.hpp>
#include <fse/Scene/Object/Wavefront.hpp>
#include <fse/Scene/SceneManager.hpp>
#include <fse/Scene/CameraFPS.hpp>

#include "Map.hpp"

#include <chrono>
#include <thread>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

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

#if defined(_WIN32)

#include <direct.h>
#include <stdlib.h>
#include <stdio.h>

std::string getcwd_string(void) {
	char buff[256];
	_getcwd(buff, 256);
	std::string cwd(buff);
	return cwd;
}

#endif

int main(int argc, char **argv)
{
	Window                      window(1290, 800);

	std::cout << "[OpenGL]\nVendor: " << glGetString(GL_VENDOR) << "\nRenderer: ";
	std::cout << glGetString(GL_RENDERER) << "\nVersion: ";
	std::cout << glGetString(GL_VERSION) << "\nGLSL Version: ";
	std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\nExtension: ";
	// Window                      window(1540, 960);

    fse::Renderer               renderer(window);
    fse::scene::SceneManager    scene;
    fse::scene::CameraFPS       camera;
    float speed = 20.f; // 3 units / second

    scene.camera = &camera;
    camera.getPosition()[2] = 0;
	camera.getPosition()[1] = 0;
	camera.getPosition()[0] = 0;
    camera.mouseInput(0, 0, 0);
    scene.setLight(std::make_shared<fse::scene::Light>());
    scene.getLight()->setPosition({0.1, 10,0.1});


    // std::cout << glGetString(GL_EXTENSIONS) << "\n\n\n";
    // Object *wavefront = scene.addWavefront("Ressource/Audi R8.fbx");
    // wavefront->setScale({0.05, 0.05, 0.05});
    // // wavefront->getMaterial()->setTexture("Ressource/alduin.bmp");
    // wavefront->getMaterial()->setColor(0.5, 0.5, 0.5);

    Object *wavefront = scene.addWavefront("Ressource/alduin.obj");
    wavefront->setScale({0.007f, 0.007f, 0.007f});
    wavefront->setPosition({5,0,5});
    wavefront->getMaterial()->setColor(100.5, 0, 0);
    wavefront->getMaterial()->setTexture("Ressource/alduin.jpg");
    wavefront->getMaterial()->setNormal("Ressource/alduin_n.jpg");

    float size = 20;
    game::Map *map = new game::Map(scene, size, size, 10);
    // map->setPosition({-2, 0, -2});
    // map->setPosition({-size / 2., 0, -size / 2.});
    map->getMaterial()->setTexture("Ressource/grass_terrain.jpg");
    map->getMaterial()->setRepeat(200);
    map->setPosition({-100,0, -100});
    map->getMaterial()->setColor(0.3, 0.7, 0.3);
    scene.addChild(map);

    fse::scene::object::Object *surface = scene.addWavefront("Ressource/plan.obj");
    surface->getMaterial()->setTexture(scene.getLight()->getTexture());
    surface->setScale({5.f, 1.f, 5.f});
    surface->setPosition({-7, 1, 3});
    surface->getMaterial()->setShader(fse::ShaderManager::getInstance().addShader("depth_viewer"));

    fse::scene::object::Object *wavefront2 = scene.addWavefront("Ressource/teapot.obj");
    wavefront2->setScale(glm::vec3(0.015f));
    wavefront2->getMaterial()->setColor(0.7f, 0.7f, 0.7f);
    // wavefront2->getMaterial()->setTexture("Ressource/water.jpg");
    wavefront2->getMaterial()->setNormal("Ressource/alduin_n.jpg");
    wavefront2->setPosition(glm::vec3(2,0,2));
    wavefront2->getMesh()->smoothNormal();
    // Triangle triangle(glm::vec3(-1, 1, 0), glm::vec3(1, 1, 0), glm::vec3(0, 0, 0));
    // Wavefront wavefront("/home/daniel_b/gfx_raytracer2/Wavefront/cow.obj");


	fse::scene::object::Object *wavefront3 = scene.addWavefront("Ressource/egypt_table/Egy1.obj");
	wavefront3->setScale(glm::vec3(0.1f));
    wavefront3->getPosition() += 1.3f;
    wavefront3->getMaterial()->setColor(0.6, 0.4, 0.4);
    wavefront3->getMaterial()->setNormal("Ressource/egypt_table/LR1VRayBumpNormalsMap.jpg");
    wavefront3->getMaterial()->setTexture("Ressource/egypt_table/LR1VRayDiffuseFilterMa.jpg");

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
	std::shared_ptr<fse::gl_item::Shader> shader = std::make_shared<fse::gl_item::Shader>("shader/basic.vert", "shader/basic.frag");
	shader->useProgram();
	glDisable(GL_CULL_FACE);

	fse::gl_item::Buffer<glm::vec3> vertex_buffer;
	std::vector<glm::vec3>			vertex;

	vertex.push_back({ -1.f, -1.f, -01.f });
	vertex.push_back({ 1.f, -1.f, -01.f });
	vertex.push_back({ 0.f, 1.f, -01.f });
	vertex_buffer.send(vertex);

	fse::renderer::ObjectRenderer obj_rend;
	obj_rend.addNode(wavefront3);

	fse::gl_item::Shader::AttributeHolder attribute;

    while (1)
    {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderer.render(scene, 0, true, false);
		obj_rend.clean();
		obj_rend.addNode(wavefront3);
		shader->useProgram();
		attribute.addUniform("projection", renderer.projection);
		attribute.addUniform("view", camera.getView());

		glClear(0);
		//obj_rend.drawAll(attribute, shader);
		shader->setUniformValue(glm::scale(wavefront3->getScale()), "model_view");
		//glDrawArrays(0, 0, 0);
		window.flipScreen();
		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR)
		{
			std::cout << "[ERROR]  POUET err = " << err << "\n";
		}

        float   move_handle = 1.0 / renderer.getFrameCounter().getFrameRate();

        static glm::vec3 vector(1, 0, 1);
        //scene.getLight()->getPosition() +=  vector * 3.f * move_handle;
        // scene.camera->setPosition(scene.getLight()->getPosition());
        if (scene.getLight()->getPosition().x > 10)
          vector *= -1;
        else if (scene.getLight()->getPosition().x < 0)
          vector *= -1;
        //wavefront->getRotation().y += 1 * move_handle;

        // scene.getLight()->setView(scene.camera->getView());

        SDL_Event event;
        while (window.pollEvent(event))
        {
            if (event.type == SDL_KEYDOWN)
            {
				glm::vec3 direction = camera.getDirection();

              if (event.key.keysym.sym == SDLK_a)
                scene.launchRay(1540/2, 1024/2, renderer.projection);
                if (event.key.keysym.sym == SDLK_z)
                  camera.getPosition() += glm::vec3(speed) * direction * glm::vec3(1.f/60);
                if (event.key.keysym.sym == SDLK_s)
                  camera.getPosition() -= glm::vec3(speed) * direction * glm::vec3(1.f/60);
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        window.close();
                        return (0);
                    }
                if (event.key.keysym.sym == SDLK_SPACE) {
                    //map->randomize();
                }
                camera.mouseInput(0, 0, move_handle);
            }

            if (event.type == SDL_MOUSEMOTION)
            {
                int xpos = 0, ypos = 0;
                SDL_GetRelativeMouseState(&xpos, &ypos);
				//camera.mouseInput(xpos, ypos, move_handle);
				camera.mouseInput(xpos, ypos, 1.F/60);

			}
        } // end event polling
    }

    return (0);
}
