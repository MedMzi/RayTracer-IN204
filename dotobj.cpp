#include "Object.hpp"
#include "Material.hpp"

const std::vector<Triangle>& dotobj::getTriangles() const {
        return triangles;
    }

const Vect& dotobj::getPosition() const {
        return position;
    }

void dotobj::loadFromObjFile(const std::string& filename, Vect position) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier .obj");
    }

    mat = std::make_shared<lambertian>(color(0.0, 0.0, 0.0));   //en attendant d'implémenter le support pour les textures

    std::vector<Vect> vertices;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v") { // Vertex lines
 //           std::cout << "found v" << std::endl;
            double x, y, z;
            ss >> x >> y >> z;
            vertices.push_back(Vect(x, y, z) + position);
        } 
        else if (prefix == "f") { // Face lines
 //           std::cout << "found f" << std::endl;
            std::vector<int> vertexIndices;
            std::string vertex;
            while (ss >> vertex) {
                std::istringstream vertexStream(vertex);
                std::string v, t, n;
                std::getline(vertexStream, v, '/');
                std::getline(vertexStream, t, '/');
                std::getline(vertexStream, n, '/');
                vertexIndices.push_back(std::stoi(v) - 1); // Convert to 0-based index
            }
            if (vertexIndices.size() >= 3) {
                for (size_t i = 1; i < vertexIndices.size() - 1; ++i) {
                    triangles.push_back(Triangle(vertices[vertexIndices[0]], vertices[vertexIndices[i]], vertices[vertexIndices[i + 1]], mat));
                    //TODO changer nullptr pour mat en des textures plus complexe
                }
            }
        }
    }
}

double dotobj::hit(const Ray& r) const {
        double tmin = ray_tmax;
        for (const auto& triangle : triangles) {
            double t = triangle.hit(r);
            if (t > ray_tmin && t < tmin) {
                tmin = t;
                center = triangle.getCenter();
                norm = triangle.getNormal();
 //               mat = triangle.mat;
            }
        }
        if (tmin == ray_tmax) {
            return -1.0;
        }

        return tmin;
    }


object* dotobj::clone() const{
    return new dotobj(*this);
}