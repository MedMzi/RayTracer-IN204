#ifndef COLOR_HPP
#define COLOR_HPP

#include "Rand.hpp"


using color = Vect;

inline void write_color(std::ostream& out, const color& pixel_color) {
    // Récupérer les composantes de la couleur
    auto r = pixel_color.getX();
    auto g = pixel_color.getY();
    auto b = pixel_color.getZ();

    // Traduire les valeurs [0,1] en [0,255]
    int rbyte = int(256 * clamp(r));
    int gbyte = int(256 * clamp(g));
    int bbyte = int(256 * clamp(b));

    // Écrire les composantes de couleur
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif