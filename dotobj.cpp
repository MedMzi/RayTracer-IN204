#include "Object.hpp"

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
                    triangles.push_back(Triangle(vertices[vertexIndices[0]], vertices[vertexIndices[i]], vertices[vertexIndices[i + 1]]));
                }
            }
        }
    }
}

double dotobj::hit(const Ray& r) const {
        double tmin = INFINITY;
        for (const auto& triangle : triangles) {
            double t = triangle.hit(r);
            if (t > 0.0 && t < tmin) {
                tmin = t;
            }
        }
        return tmin;
    }