#include "MoteurVersion1.hpp"
#include "loadScene.hpp"
#include <fstream>
#include <iostream>

// Constructeur
MoteurVersion1::MoteurVersion1(const std::string& scene_file, const std::string& output_file)
    : scene_file_(scene_file), output_file_(output_file) {}

// Implémentation de la méthode executer
void MoteurVersion1::executer() {
    // Ouvrir un fichier pour écrire l'image
    std::ofstream image_file(output_file_);
    if (!image_file) {
        std::cerr << "Erreur : impossible de créer le fichier image.\n";
        return;
    }

    // Charger la scène
    world w;
    camera cam;

    // Utiliser c_str() pour convertir std::string en const char*
    loadScene(scene_file_.c_str(), w, cam);

    // Rendu
    cam.render(w, image_file);
    std::cout << "Image générée dans le fichier '" << output_file_ << "'.\n";

    // Fermer le fichier
    image_file.close();
}