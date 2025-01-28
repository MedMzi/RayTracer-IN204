#ifndef MOTEURVERSION1_HPP
#define MOTEURVERSION1_HPP

#include "Moteur.hpp"
#include "Color.hpp"
#include "Object.hpp"
#include "Camera.hpp"
#include <string>

class MoteurVersion1 : public Moteur {
public:
    // Constructeur
    MoteurVersion1(const std::string& scene_file, const std::string& output_file);

    // Méthode pour exécuter le moteur
    void executer() override;

private:
    std::string scene_file_;   // Fichier de la scène
    std::string output_file_;  // Fichier de sortie
};

#endif // MOTEURVERSION1_HPP