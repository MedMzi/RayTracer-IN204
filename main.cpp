#include "MoteurVersion1.hpp"
#include <chrono>

int main(int argc, char** argv) {

    auto start = std::chrono::high_resolution_clock::now();

    // Fichiers de scène et de sortie
    const std::string scene_file = "Scene.xml";
    const std::string output_file = "output.ppm";

    // Utilisation du moteur version 1
    Moteur* moteur = new MoteurVersion1(scene_file, output_file);

    // Exécution
    moteur->executer();

    // Nettoyage
    delete moteur;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Exec time: " << duration.count() << " seconds" << std::endl;

    return 0;
}
