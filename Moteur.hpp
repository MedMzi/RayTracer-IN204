#ifndef MOTEUR_HPP
#define MOTEUR_HPP

#include <string>

// Classe abstraite Moteur
class Moteur {
public:
    virtual ~Moteur() = default;

    // Méthode virtuelle pure que les sous-classes doivent implémenter
    virtual void executer() = 0;
};

#endif
