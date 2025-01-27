#include "Camera.hpp"
#include "Material.hpp"

void camera::initialize() {
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        pixel_sample_scale = 1.0 / samples_per_pixel;

        center = lookfrom;

        // Determine viewport dimensions.
       // auto focal_length = (lookfrom - lookat).norme();

        auto theta = degrees_to_radians(vfov);
        auto h = std::tan(theta/2);
       // auto viewport_height = 2 * h * focal_length;
       auto viewport_height = 2 * h * focus_dist;

        auto viewport_width = viewport_height * (double(image_width)/image_height);

        //calcul des vecteurs de la camera
        w = (lookfrom - lookat).Unit();
        u = (vup^w).Unit();
        v = w^u;

        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        auto viewport_u = viewport_width * u;
        auto viewport_v = viewport_height * -v;

        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Calculate the location of the upper left pixel.
        auto viewport_upper_left = center - (focus_dist * w) - viewport_u/2 - viewport_v/2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

        // Calculate the defocus disk vectors.
        auto defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
        defocus_disk_u = defocus_radius * u;
        defocus_disk_v = defocus_radius * v;
    }
    
/* version originelle
void camera::render(const object& world, std::ostream& out) {
    initialize();

    out << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j) { 
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(0, 0, 0);
            for (int sample = 0; sample < samples_per_pixel; sample++){
                Ray r = get_ray(i,j);
                pixel_color += ray_color(r, world, max_depth);
            }

            write_color(out, pixel_sample_scale * pixel_color);
        }
    }
}
*/

/*version multithreading*/

void camera::render(const world& w, std::ostream& out) {
    initialize();

    out << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    std::vector<std::thread> threads;
    std::mutex mutex;
    int num_threads = std::thread::hardware_concurrency();
    std::vector<std::stringstream> buffers(num_threads);
    int rows_per_thread = image_height / num_threads;

    std::vector<std::unique_ptr<world>> world_copies(num_threads);
    for (int t = 0; t < num_threads; ++t) {
        world_copies[t] = std::make_unique<world>(w);
    }

    auto render_row_range = [&](int start_row, int end_row, int thread_id) {
        std::stringstream& buffer = buffers[thread_id];
        world& thread_world = *world_copies[thread_id];
        for (int j = start_row; j < end_row; ++j) {
            for (int i = 0; i < image_width; ++i) {
                color pixel_color(0, 0, 0);
                for (int sample = 0; sample < samples_per_pixel; sample++) {
                    Ray r = get_ray(i, j);
                    pixel_color += ray_color(r, thread_world, max_depth);
                }

                std::lock_guard<std::mutex> lock(mutex);
                write_color(buffer, pixel_sample_scale * pixel_color);
            }
        }
    };
    
    for (int t = 0; t < num_threads; ++t) {
        int start_row = t * rows_per_thread;
        int end_row = (t == num_threads - 1) ? image_height : start_row + rows_per_thread;
        threads.emplace_back(render_row_range, start_row, end_row, t);
    }
    
    for (auto& thread : threads) {
        thread.join();
    }
    
    for (const auto& buffer : buffers) {
        out << buffer.str();    //resultat finaux
    }

    for (auto& ptr : world_copies) {
        ptr.release(); // Relacher les pointeurs qui ont deja ete libere dans les threads
    }
}


color camera::ray_color(const Ray& r, const object& world, int depth) const {
    if (depth <= 0){
     //   std::cout << "max reached" << std::endl;
        return color();
    }    

    RayIntersection inters = RayIntersection(world, r);
    double t = inters.getHit();
    if ((t > 0.0) && (inters.mat != nullptr)) {
 //       return Vect(1, 0, 0); 
 //       return Vect(1, 0, 1) * (1.0 / (1.0 + 0.1 * t)); 
//       return 0.5 * (inters.getNormal() + color(1));
    //    Vect direction = random_on_hemisphere(inters.getNormal());
 //       Vect direction = inters.getNormal() + random_unit_vector();
 //       return 0.1 * ray_color(Ray(inters.getPoint(), direction), world, depth-1);
        Ray scattered;
        color attenuation;
        if (inters.mat->scatter(r, inters, attenuation, scattered)){
            auto rec = ray_color(scattered, world, depth-1);
            auto res = color(attenuation.getX()*rec.getX(), attenuation.getY()*rec.getY(), attenuation.getZ()*rec.getZ());
            return res;
        }
        return color();
    }

    Vect unit_direction = r.getDirection().Unit();
    t = 0.5 * (unit_direction.getY() + 1.0);
    return (1.0-t) * Vect(1.0, 1.0, 1.0) + t * Vect(0.5, 0.7, 1.0);
}

Ray camera::get_ray(int i, int j) const {
        auto offset = sample_square();
        auto pixel_sample = pixel00_loc
                          + ((i + offset.getX()) * pixel_delta_u)
                          + ((j + offset.getY()) * pixel_delta_v);

        auto ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
        auto ray_direction = pixel_sample - ray_origin;

        return Ray(ray_origin, ray_direction);
    }

Vect camera::sample_square() const {
    // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
    return Vect(random_double() - 0.5, random_double() - 0.5, 0);
}

Vect camera::defocus_disk_sample() const {
    // Returns a random point in the defocus disk.
    auto p = random_in_unit_disk();
    return center + (p.getX() * defocus_disk_u) + (p.getY() * defocus_disk_v);
}