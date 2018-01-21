#include "nbody.hpp"
#include <boost/lexical_cast.hpp>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdexcept>

namespace DancePlanetsDance {


/***********************************
* SpaceObject
***********************************/

SpaceObject::SpaceObject() {}
SpaceObject::~SpaceObject() {}

SpaceObject::SpaceObject(sf::Vector2f position, sf::Vector2f velocity,
    double mass) {
}

void SpaceObject::draw(sf::RenderTarget& target, sf::RenderStates states)
    const {
    target.draw(sSprite_, states);
}

// setters
void SpaceObject::set_location(sf::Vector2f location) {
    location_ = location;
}

void SpaceObject::set_velocity(sf::Vector2f velocity) {
    velocity_ = velocity;
}

void SpaceObject::set_mass(double mass) {
    mass_ = mass;
}

void SpaceObject::set_sprite(sf::Sprite sprite) {
    sSprite_ = sprite;
}

void SpaceObject::set_texture(sf::Texture texture) {
    sText_ = texture;
}

void SpaceObject::set_positions(double windowScale, double winSize) {
    sf::Vector2f loc;

    // (input location / windowscale) to scale location
    // add window radius to x and y to position within the window
    // convert y values to negative to spin counter clockwise
    loc.x = (location_.x / windowScale) + (winSize / 2);
    loc.y = (location_.y *-1 / windowScale) + (winSize / 2);

    sSprite_.setPosition(loc);
}


// getters
double SpaceObject::get_xlocation() {
    return location_.x;
}
double SpaceObject::get_ylocation() {
    return location_.y;
}

double SpaceObject::get_xvelocity() {
    return velocity_.x;
}
double SpaceObject::get_yvelocity() {
    return velocity_.y;
}

double SpaceObject::get_mass() {
    return mass_;
}

sf::Sprite* SpaceObject::get_sprite() {
    return &sSprite_;
}

sf::Texture* SpaceObject::get_texture() {
    return &sText_;
}


/***********************************
* Body
***********************************/

Body::Body(sf::Vector2f location, sf::Vector2f velocity, double mass,
    std::string fileName) {
        // initialize members
        location_.x = location.x;
        location_.y = location.y;
        velocity_.x = velocity.x;
        velocity_.y = velocity.y;
        mass_ = mass;
        fileName_ = fileName;

        if (!get_texture()->loadFromFile(fileName)) {
            throw std::runtime_error("Error loading texture from file");
        get_sprite()->setTexture(*get_texture());
    }
}

void Body::step(double seconds) {
    double xAccel = xForce_ / mass_;
    double yAccel = yForce_ / mass_;

    velocity_.x = velocity_.x + (xAccel * seconds);
    velocity_.y = velocity_.y + (yAccel * seconds);

    location_.x = location_.x + (velocity_.x * seconds);
    location_.y = location_.y + (velocity_.y * seconds);
}


void Body::set_file_name(std::string fileName) {
    fileName_ = fileName;
}

std::istream &operator >>(std::istream &in, Body &body) {
    sf::Vector2f loc;
    sf::Vector2f vel;
    double m;
    std::string filen;

    in >> loc.x >> loc.y >> vel.x >> vel.y >> m >> filen;

    body.set_location(loc);
    body.set_velocity(vel);
    body.set_mass(m);
    body.set_file_name(filen);

    body.xForce_ = 0.0;
    body.yForce_ = 0.0;

    if (!body.sText_.loadFromFile(filen)) {
        throw std::runtime_error("Error loading image file");
    }

    body.sSprite_.setTexture(body.sText_);


    return in;
}

std::ostream &operator <<(std::ostream &out, const Body &body) {
    // format output and set to scientific notation
    out << std::setiosflags(std::ios::scientific);
    out << std::setw(11) << std::setprecision(4) << body.location_.x << " ";
    out << std::setw(11) << std::setprecision(4) << body.location_.y << " ";
    out << std::setw(11) << std::setprecision(4) << body.velocity_.x << " ";
    out << std::setw(11) << std::setprecision(4) << body.velocity_.y << " ";
    out << std::setw(11) << std::setprecision(4) << body.mass_ << "  ";
    out << body.fileName_;

    return out;
}

void Body::set_xForce(double xForce) {
    xForce_ = xForce;
}

void Body::set_yForce(double yForce) {
    yForce_ = yForce;
}





/***********************************
* Star
***********************************/

Star::Star(sf::CircleShape star) {
    star_ = star;
}

sf::CircleShape Star::get_star() {
    return star_;
}




/***********************************
* Universe
***********************************/

Universe::Universe() {}


Universe::Universe(int num_bodies, double radius, double windowSize,
double simTime, double deltaTime) {
    num_bodies_ = num_bodies;
    radius_ = radius;
    window_width_ = windowSize;
    window_height_ = windowSize;
    sim_time_ = simTime;
    deltaT_ = deltaTime;

    // universe diameter divided by window diameter
    windowScale_ = ((radius * 2.0) / windowSize);

    // create window
    window.create(sf::VideoMode(windowSize, windowSize),
        "Full of Stars");
    window.setFramerateLimit(40);
}


Universe::~Universe() {}

void Universe::update_bodies() {
    // gravity!
    double gravity = 6.67e-11;


    double fx;   ///< x force
    double fy;   ///< y force
    double netForce;   ///< net force
    double xDistance;   ///< x distance
    double yDistance;   ///< y distance
    double radius;   ///< radius
    double radiusx2;   ///< radius squared

    for (int i = 0; i < num_bodies_; i++) {
        // reset the force values for the new body
        fx = 0;
        fy = 0;

        for (int j = 0; j < num_bodies_; j++) {
            // so we aren't calculating for the bodies force on itself
            if (i != j) {
                // find x distance between bodies
                xDistance = planets_[j]->get_xlocation() -
                    planets_[i]->get_xlocation();
                // find y distance between bodies
                yDistance = planets_[j]->get_ylocation() -
                    planets_[i]->get_ylocation();

                // r^2 = x2 + y^2
                radiusx2 = pow(xDistance, 2) + pow(yDistance, 2);
                // r = sqrt(r^2)
                radius = sqrt(radiusx2);

                // net force = G*m1*m2 / r squared
                netForce = ((gravity * planets_[i]->get_mass() *
                    planets_[j]->get_mass()) / radiusx2);

                // sum up all x and y forces on each body
                // updated force = prior force + netforce*distance / radius
                fx = fx + netForce * xDistance / radius;
                fy = fy + netForce * yDistance / radius;

                // set forces
                planets_[i]->set_xForce(fx);
                planets_[i]->set_yForce(fy);
            }
        }
    }
}

void Universe::run_universe() {
    // create starfield
    generate_stars();

    // read bodies in
    for (int i = 0; i < num_bodies_; i++) {
        Body *planet = new Body();
        std::cin >> *planet;
        planet->set_positions(windowScale_, window_width_);
        planets_.push_back(planet);
    }

    // set up timer
    sf::Clock simClock;
    sf::Font timerFont;
    double endTime = sim_time_;
    if (!timerFont.loadFromFile("arial.ttf")) {
        throw std::runtime_error("Error loading text font file");
    }
    sf::Text timerText;
    timerText.setFont(timerFont);
    timerText.setPosition(5, 5);
    timerText.setCharacterSize(20);
    timerText.setColor(sf::Color::White);



    // main window loop
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // timer loop
        int timer = simClock.getElapsedTime().asMicroseconds();
        if (timer < endTime) {
            std::string simTime = boost::lexical_cast<std::string>(timer);
            timerText.setString(simTime);
        } else {
            window.close();
        }

        // calculate forces between bodies
        update_bodies();

        // step bodies
        for (int i = 0; i < num_bodies_; i++) {
            (planets_[i])->step(deltaT_);
            (planets_[i])->set_positions(windowScale_, window_width_);
        }

        // draw to window
        window.clear();
        window.draw(starfieldSprite_);
        window.draw(timerText);
        for (int i = 0; i < num_bodies_; i++) {
            window.draw(*(planets_[i]));
        }
        window.display();


        // twinkle twinkle!
        twinkle();
    }

    // end state of universe
    std::cout << "Number of bodies: " << num_bodies_ << std::endl;
    std::cout << "Universe radius: " << radius_ << std::endl;
    std::cout << " ...xpos...  ...ypos...  ...xvel...  ...yvel..."
                 "  ...mass...  filename\n";
    for (int i = 0; i < num_bodies_; i++) {
        std::cout << (*(planets_[i])) << std::endl;
    }
}

void Universe::set_starfield_sprite(sf::Sprite starfieldSprite) {
    starfieldSprite_ = starfieldSprite;
}

void Universe::generate_stars() {
    unsigned int seed = time(NULL);
    // random amount of stars between 300 and 600
    int numStars = (300 + (rand_r(&seed) % (600 - 300 + 1)));

    starfield_.create(window_width_, window_height_);
    starfield_.clear(sf::Color::Black);

    // fill stars vector
    while (static_cast<int>(stars_.size()) <= numStars) {
        sf::CircleShape newStar;
        newStar.setPosition((rand_r(&seed) %
                static_cast<int>(window_width_)),
                (rand_r(&seed) % static_cast<int>(window_height_)));
        newStar.setFillColor(sf::Color::White);

        // create random radius for each star
        double newRadius = fmod(rand_r(&seed), (1.5 - 0.1)) + 0.1;
        newStar.setRadius(newRadius);

        Star starObject(newStar);
        stars_.push_back(starObject);
    }

    // draw stars to texture
    for (std::vector<Star>::iterator it = stars_.begin(); it != stars_.end();
         ++it) {
        starfield_.draw((*it).get_star());
    }

    // load texture to sprite for drawing
    sf::Sprite starSprite(starfield_.getTexture());
    set_starfield_sprite(starSprite);
}

void Universe::twinkle() {
    unsigned int seed = time(NULL);

    sf::CircleShape newStar;

    for (std::vector<Star>::iterator it = stars_.begin(); it != stars_.end();
         ++it) {
        newStar = (*it).get_star();
        if ((rand_r(&seed) % 2) == 0) {
            newStar.setFillColor(sf::Color::White);
        } else {
            newStar.setFillColor(sf::Color::Black);
        }

        starfield_.draw(newStar);
    }
    // load texture to sprite for drawing
    sf::Sprite starSprite(starfield_.getTexture());
    set_starfield_sprite(starSprite);
}
}  // namespace DancePlanetsDance


////////////////
