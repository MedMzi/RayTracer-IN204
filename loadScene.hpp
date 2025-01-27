#ifndef LOAD_SCENE_HPP
#define LOAD_SCENE_HPP

#include "Color.hpp"
#include "Object.hpp"
#include "Camera.hpp"
#include "Material.hpp"
#include <tinyxml2.h>

using namespace tinyxml2;

// Déclaration de la fonction loadScene
void loadScene(const char* filePath, world& w, camera& cam);

std::shared_ptr<material> loadMaterial(XMLElement* materialElement);

#endif