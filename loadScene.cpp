#include "loadScene.hpp"
#include "Color.hpp"
#include "Object.hpp"
#include "Camera.hpp"
#include "Material.hpp"
#include <iostream>
#include <string>

using namespace tinyxml2;

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

    /// Charger les paramètres de la caméra
    XMLElement* cameraElement = root->FirstChildElement("camera");
    if (cameraElement) {
        // Récupération des paramètres de la caméra
        XMLElement* aspectRatioElement = cameraElement->FirstChildElement("aspect_ratio");
        if (aspectRatioElement) {
            cam.aspect_ratio = aspectRatioElement->DoubleText();
        }

        XMLElement* imageWidthElement = cameraElement->FirstChildElement("image_width");
        if (imageWidthElement) {
            cam.image_width = imageWidthElement->IntText();
        }

        XMLElement* samplesPerPixelElement = cameraElement->FirstChildElement("samples_per_pixel");
        if (samplesPerPixelElement) {
            cam.samples_per_pixel = samplesPerPixelElement->IntText();
        }

        XMLElement* maxDepthElement = cameraElement->FirstChildElement("max_depth");
        if (maxDepthElement) {
            cam.max_depth = maxDepthElement->IntText();
        }

        XMLElement* vfovElement = cameraElement->FirstChildElement("vfov");
        if (vfovElement) {
            cam.vfov = vfovElement->DoubleText();
        }

        // Récupération des vecteurs lookfrom, lookat et vup
        XMLElement* lookfromElement = cameraElement->FirstChildElement("lookfrom");
        if (lookfromElement) {
            cam.lookfrom = Vect(
                lookfromElement->FirstChildElement("x")->DoubleText(),
                lookfromElement->FirstChildElement("y")->DoubleText(),
                lookfromElement->FirstChildElement("z")->DoubleText()
            );
        }

        XMLElement* lookatElement = cameraElement->FirstChildElement("lookat");
        if (lookatElement) {
            cam.lookat = Vect(
                lookatElement->FirstChildElement("x")->DoubleText(),
                lookatElement->FirstChildElement("y")->DoubleText(),
                lookatElement->FirstChildElement("z")->DoubleText()
            );
        }

        XMLElement* vupElement = cameraElement->FirstChildElement("vup");
        if (vupElement) {
            cam.vup = Vect(
                vupElement->FirstChildElement("x")->DoubleText(),
                vupElement->FirstChildElement("y")->DoubleText(),
                vupElement->FirstChildElement("z")->DoubleText()
            );
        }

        // Récupération de la profondeur de champ
        XMLElement* defocusAngleElement = cameraElement->FirstChildElement("defocus_angle");
        if (defocusAngleElement) {
            cam.defocus_angle = defocusAngleElement->DoubleText();
        }

        XMLElement* focusDistElement = cameraElement->FirstChildElement("focus_dist");
        if (focusDistElement) {
            cam.focus_dist = focusDistElement->DoubleText();
        }
    }
    //std::vector<material*> materials; // Container to store all allocated materials

     
    // Charger les objets
    //material *mat;
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
                        //w.add(new Sphere(Vect(x, y, z), radius,  new lambertian(color(0.5,0.5,0.5))));
                        // Charger le matériau
                        
                        XMLElement* materialElement = object->FirstChildElement("material");
               
                        if (materialElement) {
                            
                            const char* materialType = materialElement->Attribute("type");

                            if (std::string(materialType) == "lambertian") {
                                XMLElement* albedo = materialElement->FirstChildElement("color");
                                if (albedo) {
                                    double r = albedo->DoubleAttribute("r");
                                    double g = albedo->DoubleAttribute("g");
                                    double b = albedo->DoubleAttribute("b");
                                    //mat = new lambertian(color(r, g, b));
                                    //w.add(new Sphere(Vect(x, y, z), radius,  new lambertian(color(r, g, b))));

                                }
                            }else if (std::string(materialType) == "metal") {
                                XMLElement* albedo = materialElement->FirstChildElement("albedo");
                                double fuzz = materialElement->FirstChildElement("fuzz")->DoubleText();
                                if (albedo) {
                                    double r = albedo->DoubleAttribute("r");
                                    double g = albedo->DoubleAttribute("g");
                                    double b = albedo->DoubleAttribute("b");
                                    //mat = new metal(color(r, g, b), fuzz);
                                    w.add(new Sphere(Vect(x, y, z), radius, new metal(color(r, g, b), fuzz)));
                                }
                            } else if (std::string(materialType) == "dielectric") {
                                double refractionIndex = materialElement->FirstChildElement("refraction_index")->DoubleText();
                                //mat = new dielectric(refractionIndex);
                                w.add(new Sphere(Vect(x, y, z), radius, new dielectric(refractionIndex)));

                            }
                        }

                        /*if (mat) {
                            //materials.push_back(mat);
                            w.add(new Sphere(Vect(x, y, z), radius, mat));
                        }*/
                       //w.add(new Sphere(Vect(x, y, z), radius,new lambertian(color(0.5, 0.5, 0.5))));
                    }
                }
                /*else if (std::string(type) == "rectangle") {
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

                        w.add(new Rectangle(Vect(x, y, z), Vect(x2, y2, z2),ground_material));
                    } else if (dimensionsElement) {
                        // Si l'élément 'dimensions' est présent, le rectangle est défini par un centre et des dimensions
                        double a = dimensionsElement->DoubleAttribute("a");
                        double b = dimensionsElement->DoubleAttribute("b");
                        double c = dimensionsElement->DoubleAttribute("c");

                        w.add(new Rectangle(Vect(x, y, z), a, b, c,ground_material));
                    }
                }
            }
        }*/
    }
}
}