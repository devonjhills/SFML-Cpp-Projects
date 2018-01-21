#ifndef DANCE_PLANETS_HPP
#define DANCE_PLANETS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <string>

/**
 * @brief  namespace for the NBody simulation
 */
namespace DancePlanetsDance {

/**
 * @brief  SpaceObject class
 */
class SpaceObject : public sf::Drawable {
 public:
    /**    Default SpaceObject Constructor
    *
    * @brief Creates a new SpaceObject
    *
    * @params none
    *
    * @return none
    */
    SpaceObject();

    /**    SpaceObject Destructor
    *
    * @brief Destroys the SpaceObject!
    *
    * @params none
    *
    * @return none
    */
    ~SpaceObject();

    /**    SpaceObject Constructor
    *
    * @brief custom SpaceObject
    *
    * @params x,y position of object
    * @params x,y velocity of object
    * @params mass of object
    *
    * @return none
    */
    SpaceObject(sf::Vector2f position, sf::Vector2f velocity, double mass);

    /**    set_location
    *
    * @brief location setter
    *
    * @params location vector
    *
    * @return none
    */
    void set_location(sf::Vector2f location);

    /**    set_velocity
    *
    * @brief velocity setter
    *
    * @params velocity vector
    *
    * @return none
    */
    void set_velocity(sf::Vector2f velocity);

    /**    set_mass
    *
    * @brief mass setter
    *
    * @params mass
    *
    * @return none
    */
    void set_mass(double mass);

    /**    set_sprite
    *
    * @brief sprite setter
    *
    * @params sf sprite
    *
    * @return none
    */
    void set_sprite(sf::Sprite sprite);

    /**    set_texture
    *
    * @brief texture setter
    *
    * @params sf texture
    *
    * @return none
    */
    void set_texture(sf::Texture texture);

    /**    set_start_positions
    *
    * @brief set starting positions of bodies
    *
    * @params scale value
    * @params window size
    *
    * @return none
    */
    void set_positions(double windowScale, double winSize);

    /**    get_xlocation
    *
    * @brief x location getter
    *
    * @params none
    *
    * @return x location
    */
    double get_xlocation();

    /**    get_ylocation
    *
    * @brief y location getter
    *
    * @params none
    *
    * @return y location
    */
    double get_ylocation();

    /**    get_xvelocity
    *
    * @brief x velocity getter
    *
    * @params none
    *
    * @return x velocity
    */
    double get_xvelocity();

    /**    get_yvelocity
    *
    * @brief y velocity getter
    *
    * @params none
    *
    * @return y velocity
    */
    double get_yvelocity();

    /**    get_mass
    *
    * @brief mass getter
    *
    * @params none
    *
    * @return mass
    */
    double get_mass();

    /**    get_sprite
    *
    * @brief sprite getter
    *
    * @params none
    *
    * @return sprite pointer
    */
    sf::Sprite* get_sprite();

    /**    get_texture
    *
    * @brief texture getter
    *
    * @params none
    *
    * @return texture pointer
    */
    sf::Texture* get_texture();

 protected:
    /**    draw
    *
    * @brief sfml draw function to be overloaded
    *
    * @params target to draw
    * @params states
    *
    * @return none
    */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; //NOLINT
    sf::Texture sText_;  ///< the texture of the object
    sf::Sprite sSprite_;  ///< the sprite of the object
    sf::Vector2f location_;  ///< the location of the object
    sf::Vector2f velocity_;  ///< the velocity of the object
    double mass_;  ///< the mass of the object
};




/**
* @brief Body class
*/
class Body : public SpaceObject {
 public:
    /**    Default Body Constructor
    *
    * @brief default body constructor
    *
    * @params none
    *
    * @return none
    */
    Body() {}

    /**    Body Destructor
    *
    * @brief destroys the body!
    *
    * @params none
    *
    * @return none
    */
    ~Body() {}

    /**    Body Constructor
    *
    * @brief custom constructor for body
    *
    * @params body location
    * @params body velocity
    * @params body mass
    * @params body file name
    *
    * @return none
    */
    Body(sf::Vector2f location, sf::Vector2f velocity, double mass,
        std::string fileName);

    /**    step
    *
    * @brief updates position of bodies
    *
    * @params delta time used to update positions
    *
    * @return none
    */
    void step(double seconds);


    /**    set_file_name
    *
    * @brief file name setter
    *
    * @params file name string
    *
    * @return none
    */
    void set_file_name(std::string fileName);

    /**    istream operator
    *
    * @brief overloaded >> operator
    *
    * @params istream reference
    * @params body object reference
    *
    * @return istream
    */
    friend std::istream &operator >>(std::istream &in, Body &body);

    /**    ostream operator
    *
    * @brief overloaded << operator
    *
    * @params ostream reference
    * @params body object reference
    *
    * @return ostream
    */
    friend std::ostream &operator <<(std::ostream &in, const Body &body);

    /**    set x force
    *
    * @brief set x force on body
    *
    * @params x force
    *
    * @return none
    */
    void set_xForce(double xForce);

    /**    set y force
    *
    * @brief set y force on body
    *
    * @params y force
    *
    * @return none
    */
    void set_yForce(double yForce);

 private:
    sf::Vector2f prevPosition_;  ///< saves the last position for calcs
    std::string fileName_;  ///< file name to be loaded into planet texture
    double xForce_;
    double yForce_;
};




/**
* @brief Star class
*/
class Star {
 public:
    /**    Default Star Constructor
    *
    * @brief default star constructor
    *
    * @params none
    *
    * @return none
    */
    Star() {}

    /**    Star Destructor
    *
    * @brief destroys the star!
    *
    * @params none
    *
    * @return none
    */
    ~Star() {}

    /**    Custom Star Constructor
    *
    * @brief star constructor
    *
    * @params sf circle shape
    *
    * @return none
    */
    explicit Star(sf::CircleShape star);

    /**    get_star
    *
    * @brief star getter
    *
    * @params none
    *
    * @return star's sf circleshape
    */
    sf::CircleShape get_star();

 private:
    sf::CircleShape star_;  ///< star represented as an sf circle
};



/**
* @brief Universe class
*/
class Universe {
 public:
    /**    Default Universe Constructor
    *
    * @brief Creates a new Universe obeject
    *
    * @params none
    *
    * @return none
    */
    Universe();

    /**    Universe Constructor
    *
    * @brief Creates a new star obeject
    *
    * @params number of bodies
    * @params universe radius
    * @params size of window
    * @params total sim time
    * @params delta time for planet movement
    *
    * @return a new body object
    */
    Universe(int num_bodies, double radius, double windowSize,
            double simTime, double deltaTime);

    /**    Universe Destructor
    *
    * @brief Deletes the universe object
    *
    * @params none
    *
    * @return none
    */
    ~Universe();

    /**    generate_stars
    *
    * @brief creates the stars for the universe background
    *
    * @params none
    *
    * @return none
    */
    void generate_stars();

    /**    twinkle
    *
    * @brief twinkle twinkle little star(s)
    *
    * @params none
    *
    * @return none
    */
    void twinkle();

    void update_bodies();

    /**    run_universe
    *
    * @brief run all universe elements
    *
    * @params none
    *
    * @return none
    */
    void run_universe();

    /**    set_starfield_sprite
    *
    * @brief loads sprite for drawing
    *
    * @params sf::sprite for starfield
    *
    * @return none
    */
    void set_starfield_sprite(sf::Sprite starfieldSprite);

 private:
     std::vector<Body*> planets_;  ///< the vector of planets in the system
     std::vector<Star> stars_;  ///< the vector of stars for the universe
     sf::RenderTexture starfield_;  ///< starfield texture
     sf::Sprite starfieldSprite_;  ///< starfield sprite for drawing
     sf::RenderWindow window;  ///< sfml window
     sf::Event event;  ///< sfml event
     int num_bodies_;  ///< the number of planets in the universe
     double windowScale_;  ///< scale of the universe in the window
     double radius_;  ///< the radius of the simulator
     double window_width_;  ///< the width of the window
     double window_height_;  ///< the height of the window
     double sim_time_;  ///< simulation runtime
     double deltaT_;  ///< delta time
};
}  // namespace DancePlanetsDance


#endif  // DANCE_PLANETS_HPP
