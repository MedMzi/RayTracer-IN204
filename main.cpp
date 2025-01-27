#include "Color.hpp"
#include "Object.hpp"
#include "Camera.hpp"
#include "loadScene.hpp"
#include <fstream>
#include <iostream>

#include <chrono>

int main(int argc, char** argv) {

    auto start = std::chrono::high_resolution_clock::now();

    // Ouvrir un fichier pour écrire l'image
    std::ofstream image_file("output.ppm");
    if (!image_file) {
        std::cerr << "Erreur : impossible de créer le fichier image.\n";
        return 1;
    }

    world w;
    camera cam;

    // Charger la scène depuis un fichier XML
    loadScene("Scene.xml", w, cam);
    // Rendu
    cam.render(w, image_file);
    std::cout << "Image générée dans le fichier 'output.ppm'.\n";
    image_file.close();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Exec time: " << duration.count() << " seconds" << std::endl;


    return 0;
}