#include "MoteurVersion1.hpp"

int main(int argc, char** argv) {
    // Fichiers de scène et de sortie
    const std::string scene_file = "Scene.xml";
    const std::string output_file = "output.ppm";

    // Utilisation du moteur version 1
    Moteur* moteur = new MoteurVersion1(scene_file, output_file);

    // Exécution
    moteur->executer();

    // Nettoyage
    delete moteur;

    return 0;
}
