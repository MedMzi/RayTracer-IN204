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
    }//l camera jawha ahla jaw 
    //std::vector<material*> materials; // Container to store all allocated materials

     
    // Charger les objets
    //material *mat;
    XMLElement* objectsElement = root->FirstChildElement("objects");
    if (objectsElement) {
        for (XMLElement* object = objectsElement->FirstChildElement("object"); object != nullptr; object = object->NextSiblingElement("object")) {
            std::string type = std::string(object->Attribute("type"));
        

            if (type == "sphere") {
                // Charger un objet de type Sphere
                XMLElement* position = object->FirstChildElement("position");

                if (position) {
                    double x = position->DoubleAttribute("x");
                    double y = position->DoubleAttribute("y");
                    double z = position->DoubleAttribute("z");
                    double radius = object->FirstChildElement("radius")->DoubleText();//had hnee ya9ra mriguell 


                    XMLElement* materialElement = object->FirstChildElement("material");
                    w.add(new Sphere(Vect(x, y, z), radius,  loadMaterial(materialElement)));
                }
            }
            else if (type == "cube"){
                XMLElement* position = object->FirstChildElement("position");

                if (position) {
                    double x = position->DoubleAttribute("x");
                    double y = position->DoubleAttribute("y");
                    double z = position->DoubleAttribute("z");
                    double edge = object->FirstChildElement("edge")->DoubleText();


                    XMLElement* materialElement = object->FirstChildElement("material");
                    w.add(new Rectangle(Vect(x, y, z), edge,  loadMaterial(materialElement)));
                }

            }
            else if (type == "rectangle"){
                XMLElement* position = object->FirstChildElement("position");

                if (position) {
                    double x = position->DoubleAttribute("x");
                    double y = position->DoubleAttribute("y");
                    double z = position->DoubleAttribute("z");
                    
                    double width = 0.0;
                    double height = 0.0;
                    double length = 0.0;
                    XMLElement* dimensions = object->FirstChildElement("dimensions");
                    if (dimensions) {
                        width = dimensions->DoubleAttribute("w");
                        height = dimensions->DoubleAttribute("h");
                        length = dimensions->DoubleAttribute("l");
                    }

                    XMLElement* materialElement = object->FirstChildElement("material");
                    w.add(new Rectangle(Vect(x, y, z), width, height, length, loadMaterial(materialElement)));
                }

            }
            else if (type == "objFile"){
                XMLElement* filenameElement = object->FirstChildElement("filename"); // Replace "filename" with the actual element name
                if (filenameElement) {
                    const char* filenameCStr = filenameElement->GetText(); 
                    std::string filename(filenameCStr);  

                XMLElement* position = object->FirstChildElement("position");
                    if (position) {
                        double x = position->DoubleAttribute("x");
                        double y = position->DoubleAttribute("y");
                        double z = position->DoubleAttribute("z");

                        w.add(new dotobj(filename, Vect(x, y, z))); 
                    }
                }
            }

        }
    }      
}

material* loadMaterial(XMLElement* materialElement){
    if (materialElement == nullptr) {
        throw std::invalid_argument("materialElement is empty");
    }

    std::string materialText = std::string(materialElement->Attribute("type"));

    if (materialText == "lambertian"){
        XMLElement* co = materialElement->FirstChildElement("color");
        if (co) {
            double r = co->DoubleAttribute("r");
            double g = co->DoubleAttribute("g");
            double b = co->DoubleAttribute("b");
            return new lambertian(color(r,g,b));  
        }
    }
    else if (materialText == "metal"){
        XMLElement* co = materialElement->FirstChildElement("color");
        if (co) {
            double r = co->DoubleAttribute("r");
            double g = co->DoubleAttribute("g");
            double b = co->DoubleAttribute("b");
            double f = materialElement->FirstChildElement("fuzz")->DoubleText();
            return new metal(color(r,g,b),f);
        }
    }
    else if (materialText == "dielectric"){
        XMLElement* ri = materialElement->FirstChildElement("refraction_index");
        if (ri) {
            double refraction_index = ri->DoubleText();
            return new dielectric(refraction_index);
        }
    } 
    //si tout se passe mal on va juste retourner un solide blanc
    return new lambertian(color(1,1,1));
}
