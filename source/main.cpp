/**
 * @Author: danielb
 * @Date:   2017-07-22T23:35:22+02:00
 * @Last modified by:
 * @Last modified time: 2018-02-23T01:39:49+01:00
 */

#include <fse/Window.hpp>
#include <fse/Renderer/Renderer.hpp>
#include <fse/Renderer/ObjectPicker.hpp>
#include <fse/Scene/Object/Object.hpp>
#include <fse/Scene/Object/Wavefront.hpp>
#include <fse/Scene/SceneManager.hpp>
#include <fse/Scene/CameraFPS.hpp>
#include <fse/Ui/Surface.hpp>

#include "Map.hpp"

#include <chrono>
#include <thread>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

using namespace fse::scene::object;

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
	Window		window(800, 600);
	fse::ui::Surface		surface;

	std::shared_ptr<fse::gl_item::Shader> shader = std::make_shared<fse::gl_item::Shader>("shader/ui.vert", "shader/ui.frag");
	surface.setBackground(glm::vec4(1, 0, 0.4, 1));
	while (1) {
		surface.draw(shader);
	}


	
	return (0);
}
