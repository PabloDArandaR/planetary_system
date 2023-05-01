#include <SFML/Graphics.hpp>
#include "Planet.cpp"
#include "forces.cpp"

#define R_MARS 3389.5
#define M_MARS 6.39e23
#define R_EARTH 6371
#define M_EARTH 5.972e24
#define R_SUN 696340
#define M_SUN 1.989e30

int main()
{
    // Define the Planets of the system
    Eigen::Vector3d pos {Eigen::Vector3d::Zero()}, vel {Eigen::Vector3d::Zero()};

    pos[0] = 0.0; pos[1] = 225e6; pos[2] = 0.0;
    vel[0] = 24e3; vel[1] = 0.0; vel[2] = 0.0;
    Planet mars = Planet(R_MARS, M_MARS, pos, vel, sf::Color::Red);

    pos[0] = 147.5e6; pos[1] = 7.0; pos[2] = 3.0;
    vel[0] = 0.0; vel[1] = 30e3; vel[2] = 0.0;
    Planet earth = Planet(R_EARTH, M_EARTH, pos, vel, sf::Color::Blue);

    pos[0] = 0.0; pos[1] = 0.0; pos[2] = 0.0;
    vel[0] = 0.0; vel[1] = 0.0; vel[2] = 0.0;
    Planet sun = Planet(R_SUN, M_SUN, pos, vel, sf::Color::Yellow);  

    std::vector<Planet> system;
    system.push_back(mars);
    system.push_back(earth);
    system.push_back(sun);

    // Simulation parameters:
    float t {0.0};
    float dt {1.0};
    
    // Define the main configuration of the window
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");

    sf::CircleShape shape_mars(mars.get_radius());
    shape_mars.setFillColor(mars.get_color());
    shape_mars.setPosition(500 - shape_mars.getRadius() + mars.get_position()[0]*50, 500 - shape_mars.getRadius() + mars.get_position()[1]*50);

    sf::CircleShape shape_earth(earth.get_radius());
    shape_earth.setFillColor(earth.get_color());
    shape_earth.setPosition(500 - shape_earth.getRadius() + earth.get_position()[0]*50, 500 - shape_earth.getRadius() + earth.get_position()[1]*50);

    sf::CircleShape shape_sun(sun.get_radius());
    shape_sun.setFillColor(sun.get_color());
    shape_sun.setPosition(500 - shape_sun.getRadius() + sun.get_position()[0]*50, 500 - shape_sun.getRadius() + sun.get_position()[1]*50);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Calculate new state of forces appearing in the system
        std::vector<Eigen::Vector3d> new_forces = gravity_system(system);

        // Update the state of each of the elements of the system
        for (int i = 0; i < system.size(); i++){
            system[i].update_kin(new_forces[i], t, t+dt);
        }

        t += dt;

            shape_mars.setPosition(500 - shape_mars.getRadius() + system[0].get_position()[0], 500 - shape_mars.getRadius() + system[0].get_position()[1]);
            shape_earth.setPosition(500 - shape_earth.getRadius() + system[1].get_position()[0], 500 - shape_earth.getRadius() + system[1].get_position()[1]);
            shape_sun.setPosition(500 - shape_sun.getRadius() + system[2].get_position()[0], 500 - shape_sun.getRadius() + system[2].get_position()[1]);

            window.clear();
            window.draw(shape_mars);
            window.draw(shape_earth);
            window.draw(shape_sun);
            window.display();

    }

    return 0;
}