#include "Color.hpp"
#include "Object.hpp"
#include "Camera.hpp"
#include <tinyxml2.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace tinyxml2;

/*void loadScene(const char* filePath, world& w, camera& cam) {
    XMLDocument doc;
    if (doc.LoadFile(filePath) != XML_SUCCESS) {
        std::cerr << "Erreur lors du chargement du fichier XML.\n";
        exit(1);
    }

    XMLElement* root = doc.RootElement();
    if (!root) {
        std::cerr << "Fichier XML mal formé.\n";
        exit(1);
    }

    // Charger les paramètres de la caméra
    XMLElement* cameraElement = root->FirstChildElement("camera");
    if (cameraElement) {
        cam.aspect_ratio = cameraElement->FirstChildElement("aspect_ratio")->DoubleText();
        cam.image_width = cameraElement->FirstChildElement("image_width")->IntText();
        cam.samples_per_pixel = cameraElement->FirstChildElement("samples_per_pixel")->IntText();
    }

    // Charger les objets
    XMLElement* objectsElement = root->FirstChildElement("objects");
    if (objectsElement) {
        for (XMLElement* object = objectsElement->FirstChildElement("object"); object != nullptr; object = object->NextSiblingElement("object")) {
            const char* type = object->Attribute("type");

            // Charger un objet de type "sphere"
            if (std::string(type) == "sphere") {
                XMLElement* position = object->FirstChildElement("position");
                if (position) {
                    double x = position->DoubleAttribute("x");
                    double y = position->DoubleAttribute("y");
                    double z = position->DoubleAttribute("z");
                    double radius = object->FirstChildElement("radius")->DoubleText();

                    w.add(new Sphere(Vect(x, y, z), radius));
                }
            }

            // Charger un objet de type "triangle"
            else if (std::string(type) == "triangle") {
                XMLElement* vertexA = object->FirstChildElement("vertexA");
                XMLElement* vertexB = object->FirstChildElement("vertexB");
                XMLElement* vertexC = object->FirstChildElement("vertexC");

                if (vertexA && vertexB && vertexC) {
                    double ax = vertexA->DoubleAttribute("x");
                    double ay = vertexA->DoubleAttribute("y");
                    double az = vertexA->DoubleAttribute("z");

                    double bx = vertexB->DoubleAttribute("x");
                    double by = vertexB->DoubleAttribute("y");
                    double bz = vertexB->DoubleAttribute("z");

                    double cx = vertexC->DoubleAttribute("x");
                    double cy = vertexC->DoubleAttribute("y");
                    double cz = vertexC->DoubleAttribute("z");

                    w.add(new Triangle(Vect(ax, ay, az), Vect(bx, by, bz), Vect(cx, cy, cz)));
                }
            }
        }
    }
}*/
void loadScene(const char* filePath, world& w, camera& cam) {
    XMLDocument doc;
    if (doc.LoadFile(filePath) != XML_SUCCESS) {
        std::cerr << "Erreur lors du chargement du fichier XML.\n";
        exit(1);
    }

    XMLElement* root = doc.RootElement();
    if (!root) {
        std::cerr << "Fichier XML mal formé.\n";
        exit(1);
    }

    // Charger les paramètres de la caméra
    XMLElement* cameraElement = root->FirstChildElement("camera");
    if (cameraElement) {
        cam.aspect_ratio = cameraElement->FirstChildElement("aspect_ratio")->DoubleText();
        cam.image_width = cameraElement->FirstChildElement("image_width")->IntText();
        cam.samples_per_pixel = cameraElement->FirstChildElement("samples_per_pixel")->IntText();
    }

    // Charger les objets
    XMLElement* objectsElement = root->FirstChildElement("objects");
    if (objectsElement) {
        for (XMLElement* object = objectsElement->FirstChildElement("object"); object != nullptr; object = object->NextSiblingElement("object")) {
            const char* type = object->Attribute("type");

            if (std::string(type) == "sphere") {
                // Charger un objet de type Sphere
                XMLElement* position = object->FirstChildElement("position");
                if (position) {
                    double x = position->DoubleAttribute("x");
                    double y = position->DoubleAttribute("y");
                    double z = position->DoubleAttribute("z");
                    double radius = object->FirstChildElement("radius")->DoubleText();

                    w.add(new Sphere(Vect(x, y, z), radius));
                }
            } else if (std::string(type) == "rectangle") {
                // Charger un objet de type Rectangle
                XMLElement* position = object->FirstChildElement("position");
                if (position) {
                    double x = position->DoubleAttribute("x");
                    double y = position->DoubleAttribute("y");
                    double z = position->DoubleAttribute("z");

                    XMLElement* sizeElement = object->FirstChildElement("size");
                    XMLElement* dimensionsElement = object->FirstChildElement("dimensions");

                    if (sizeElement) {
                        // Si l'élément 'size' est présent, le rectangle est défini par deux coins opposés
                        double x2 = sizeElement->DoubleAttribute("x2");
                        double y2 = sizeElement->DoubleAttribute("y2");
                        double z2 = sizeElement->DoubleAttribute("z2");

                        w.add(new Rectangle(Vect(x, y, z), Vect(x2, y2, z2)));
                    } else if (dimensionsElement) {
                        // Si l'élément 'dimensions' est présent, le rectangle est défini par un centre et des dimensions
                        double a = dimensionsElement->DoubleAttribute("a");
                        double b = dimensionsElement->DoubleAttribute("b");
                        double c = dimensionsElement->DoubleAttribute("c");

                        w.add(new Rectangle(Vect(x, y, z), a, b, c));
                    }
                }
            }
        }
    }
}

int main(int argc, char** argv) {
    // Ouvrir un fichier pour écrire l'image
    std::ofstream image_file("outt.ppm");
    if (!image_file) {
        std::cerr << "Erreur : impossible de créer le fichier image.\n";
        return 1;
    }

    world w;
    camera cam;

    // Charger la scène depuis un fichier XML
    loadScene("/home/takoua/Documents/RayTracer-IN204-main(3)/RayTracer-IN204-main/Scene.xml", w, cam);

    // Rendu
    cam.render(w, image_file);

    std::cout << "Image générée dans le fichier 'o.ppm'.\n";
    image_file.close();

    return 0;
}