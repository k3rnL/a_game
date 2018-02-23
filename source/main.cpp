/**
 * @Date:   2018-01-27T01:48:05+01:00
 * @Last modified time: 2018-02-23T01:32:17+01:00
 */

#include <fse/Window.hpp>
#include <fse/Renderer/Renderer.hpp>
#include <fse/Renderer/ObjectPicker.hpp>
#include <fse/Scene/Object/Object.hpp>
#include <fse/Scene/Object/Wavefront.hpp>
#include <fse/Scene/DynamicScene.hpp>
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
    Object *cube = scene.addObject("Ressource/cube.obj");
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

	std::cout << "GLM size = " << sizeof(glm::vec3) << " bt size = " << sizeof(btVector3) << "\n";

    fse::Renderer               renderer(window);
    fse::scene::DynamicScene    scene;
    fse::scene::CameraFPS       camera;
    float speed = 20.f; // 3 units / second

    scene.camera = &camera;
    camera.getPosition()[2] = 0;
	camera.getPosition()[1] = 0;
	camera.getPosition()[0] = 0;
    camera.mouseInput(0, 0, 0);
    scene.setLight(std::make_shared<fse::scene::Light>());
    scene.getLight()->setPosition({0.1, 30,0.1});

    // std::cout << glGetString(GL_EXTENSIONS) << "\n\n\n";
    // Object *wavefront = scene.addWavefront("Ressource/Audi R8.fbx");
    // wavefront->setScale({0.05, 0.05, 0.05});
    // // wavefront->getMaterial()->setTexture("Ressource/alduin.bmp");
    // wavefront->getMaterial()->setColor(0.5, 0.5, 0.5);

    Object *wavefront = scene.createObject("Ressource/alduin.obj");
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

    /*fse::scene::object::Object *surface = scene.addObject("Ressource/plan.obj");
    surface->getMaterial()->setTexture(scene.getLight()->getTexture());
    surface->setScale({5.f, 1.f, 5.f});
    surface->setPosition({-7, 1, 3});
    surface->getMaterial()->setShader(fse::ShaderManager::getInstance().addShader("depth_viewer"));*/

    /*fse::scene::object::Object *wavefront2 = scene.addObject("Ressource/teapot.obj");
    wavefront2->setScale(glm::vec3(0.015f));
    wavefront2->getMaterial()->setColor(0.7f, 0.7f, 0.7f);
    // wavefront2->getMaterial()->setTexture("Ressource/water.jpg");
    wavefront2->getMaterial()->setNormal("Ressource/alduin_n.jpg");
    wavefront2->setPosition(glm::vec3(2,0,2));
    //wavefront2->getMesh()->smoothNormal();
    // Triangle triangle(glm::vec3(-1, 1, 0), glm::vec3(1, 1, 0), glm::vec3(0, 0, 0));
    // Wavefront wavefront("/home/daniel_b/gfx_raytracer2/Wavefront/cow.obj");*/


	fse::scene::object::Object *wavefront3 = scene.addObject("Ressource/egypt_table/Egy1.obj");
	//wavefront3->setScale(glm::vec3(0.1f));
    wavefront3->setPosition(wavefront3->getPosition() + glm::vec3(0, 5, 0));
    wavefront3->getMaterial()->setColor(0.6, 0.4, 0.4);
    //wavefront3->getMaterial()->setNormal("Ressource/egypt_table/LR1VRayBumpNormalsMap.jpg");
    //wavefront3->getMaterial()->setTexture("Ressource/egypt_table/LR1VRayDiffuseFilterMa.jpg");
	scene.addChild(wavefront3);
	std::cout << "Mesh=" << wavefront3->getMesh()->getVertexes().size() << "\n";

	for (float x = 0; x < 0; x++)
		for (float y = 0; y < 10 ; y++)
			for (float z = 0; z < 10; z++) {
				DynamicObject *w = scene.addObject("Ressource/cube.obj", 10);
				w->setPosition(glm::vec3(x - 10, y+0.5, z + 10));
				w->applyMaterial(wavefront->getMaterial());
				w->wakeOnMovement();
			}

	{
		DynamicObject *parent = scene.addObject("Ressource/cube.obj", 10);
		parent->setPosition(glm::vec3(50, 0.5, 0));
		DynamicObject *child = scene.createObject("Ressource/cube.obj", 10);
		child->setPosition(glm::vec3(5, 0, 0));
		parent->addChild(child);

	}

    for (int i = 0 ; i < 000 ; i++)
    {
      Object *w = scene.addObject("Ressource/cube.obj");
	  w->setPosition(glm::vec3(rand() % 100 - 50, rand() % 300 + 150, rand() % 100 - 50));
	  //w->setScale({ 0.007f, 0.007f, 0.007f });
	  w->applyMaterial(wavefront->getMaterial());
    }

    // generate_world(scene);

    // wavefront->getPosition().y += 1;
    // wavefront->getRotation().y += 90;

    // objects.push_back(&triangle);
    // objects.push_back(&wavefront2);
	std::shared_ptr<fse::gl_item::Shader> shader = std::make_shared<fse::gl_item::Shader>("shader/basic.vert", "shader/picker.frag");
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

	attribute.addUniform("projection", renderer.projection);

	fse::renderer::ObjectPicker picker(1290, 800);

	Object *picked_obj = 0;

	std::map<int, bool> key;

    while (1)
    {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		picker.clean();
		for (auto node : scene.getNodes()) {
			picker.addNode((Object*)node);
		}
		//picker.pickObject(renderer.projection, camera.getView(), 0, 0);
		renderer.render(scene, 0, true, false);
		//scene.drawPhysicsScene(renderer.projection);
		scene.update(1.0 / 60);
		window.flipScreen();
		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR)
		{
			std::cout << "[ERROR]  POUET err = " << err << "\n";
		}

        float   move_handle = 1.0 / 60;

        static glm::vec3 vector(1, 0, 1);
        //scene.getLight()->getPosition() +=  vector * 3.f * move_handle;
        // scene.camera->setPosition(scene.getLight()->getPosition());
        if (scene.getLight()->getPosition().x > 10)
          vector *= -1;
        else if (scene.getLight()->getPosition().x < 0)
          vector *= -1;
        //wavefront->getRotation().z += 1 * move_handle;

        // scene.getLight()->setView(scene.camera->getView());

		glm::vec3 direction = camera.getDirection();

		if (key[SDLK_z])
			camera.getPosition() += glm::vec3(speed) * direction * glm::vec3(1.f / 60);
		if (key[SDLK_s])
			camera.getPosition() -= glm::vec3(speed) * direction * glm::vec3(1.f / 60);
		if (key[SDLK_LSHIFT] && picked_obj != 0)
			picked_obj->setPosition(picked_obj->getPosition() + glm::vec3(0, 10, 0) * 1.f / 60);
		if (key[SDLK_LCTRL] && picked_obj != 0)
			picked_obj->setPosition(picked_obj->getPosition() - glm::vec3(0, 10, 0) * 1.f / 60);
		camera.mouseInput(0, 0, move_handle);

        SDL_Event event;
        while (window.pollEvent(event))
        {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (event.button.button == SDL_BUTTON_LEFT) {
					DynamicObject *obj = scene.addObject("Ressource/cube.obj", 1);
					obj->setPosition(camera.getPosition() + camera.getDirection() * 3);
					obj->setScale(glm::vec3(0.15));
					obj->addForce(camera.getDirection() * 2000);
				}
				else if (event.button.button == SDL_BUTTON_RIGHT && picked_obj) {
					for (auto node : scene.getNodes()) {
						auto obj = dynamic_cast<DynamicObject *>(node);
						if (obj) {
							float force = glm::distance(obj->getPosition(), picked_obj->getPosition());
							glm::vec3 vector = glm::normalize(obj->getPosition() - picked_obj->getPosition());
							obj->addForce(vector * 0);
						}
					}
				}
			}
			if (event.type == SDL_KEYDOWN)
				key[event.key.keysym.sym] = true;
			else if (event.type == SDL_KEYUP)
				key[event.key.keysym.sym] = false;

			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_m)
					scene.launchRay(1540 / 2, 1024 / 2, renderer.projection);
				if (event.key.keysym.sym == SDLK_a && picked_obj != 0 && dynamic_cast<DynamicObject *>(picked_obj) != 0)
					if (((DynamicObject *)picked_obj)->isWake())
						((DynamicObject *)picked_obj)->wakeOnMovement();
					else
						((DynamicObject *)picked_obj)->wakeUp();
				if (event.key.keysym.sym == SDLK_e) {
					DynamicObject *obj = scene.createObject("Ressource/cube.obj", 1000);
					obj->setPosition(camera.getPosition() + camera.getDirection() * 3);
					obj->setScale(glm::vec3(0.5));
					obj->addForce(camera.getDirection() * 4700000);
					scene.addChild(obj);
				}

				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					window.close();
					return (0);
				}
				if (event.key.keysym.sym == SDLK_SPACE) {
					if (picked_obj)
						picked_obj = 0;
					else
						picked_obj = picker.pickObject(renderer.projection, camera.getView(), 0, 0);
					std::cout << "Picked=" << picked_obj << "\n";
				}
				camera.mouseInput(0, 0, move_handle);
			}

            if (event.type == SDL_MOUSEMOTION)
            {
                int xpos = 0, ypos = 0;
                SDL_GetRelativeMouseState(&xpos, &ypos);
				//camera.mouseInput(xpos, ypos, move_handle);
				camera.mouseInput(xpos, ypos, 1.F/60);
				if (picked_obj) {
					float denom = glm::dot(glm::vec3(0, 1, 0), camera.getDirection());
					if (glm::abs(denom) > 0.f) {
						float k = glm::dot(picked_obj->getPosition() - camera.getPosition(), glm::vec3(0, 1, 0)) / denom;
						picked_obj->setPosition(camera.getDirection() * k + camera.getPosition());
					}
					//picked_obj->getPosition() += glm::vec3(xpos, 0, ypos);
				}
			}
        } // end event polling
    }

    return (0);
}
