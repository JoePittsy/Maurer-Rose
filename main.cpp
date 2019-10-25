#include <SFML/Graphics.hpp>
#include <random>
#include <utility>


using namespace  sf;
using namespace std;

#include <cmath>
#define PI 3.14159265



class SFML_Window{
public:
    int window_width;
    int window_height;
    string window_title;
    float angle;
    float zoomLevel;
    RenderWindow window;

    explicit SFML_Window(int width = 800, int height = 600, string title = "Empty Window"){
        window_width = width;
        window_height = height;
        window_title = std::move(title);
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;
        angle = 0;
        zoomLevel = 0.01;

        window.create(VideoMode(window_width, window_height), window_title, sf::Style::Default, settings);
    }

    void Main_Loop(){
        while (window.isOpen()){
            Event event{};
            while (window.pollEvent(event)){
                if (event.type == Event::Closed)
                    window.close();
            }
            window.clear(Color::Black);
            Users_Code();
            window.display();
        }
    }
    static void rotatePoint(sf::Vector2f* point_pointer, sf::Vector2f origin, float angle){
        double s = sin(angle* PI / 180.0);
        double c = cos(angle* PI / 180.0);

        // translate point back to origin:
        (*point_pointer).x -= origin.x;
        (*point_pointer).y -= origin.y;

        // rotate point
        double xnew = (*point_pointer).x * c - (*point_pointer).y * s;
        double ynew = (*point_pointer).x * s + (*point_pointer).y * c;

        // translate point back:
        (*point_pointer).x = xnew + origin.x;
        (*point_pointer).y = ynew + origin.y;
    }
    void Users_Code(){


        zoomLevel +=0.1;
        angle += (float)50/(float)zoomLevel;
        if(angle > 360){ angle = 0;}

        int n = 6;
        int d = 71;

        sf::ConvexShape rose;
        rose.setFillColor(sf::Color::Transparent);
        rose.setOutlineColor(sf::Color::White);
        rose.setOutlineThickness(0.5);
        rose.setPointCount(361);




        for (int i = 0; i < 361; ++i) {
            int k = i * d;
            double r = zoomLevel * sin((n*k)* PI / 180.0);
            double x = r * cos(k * PI / 180.0);
            double y = r * sin(k * PI / 180.0);
            sf::Vector2f point = sf::Vector2f(x, y);
            rotatePoint(&point, sf::Vector2f(0, 0), angle);
            rose.setPoint(i, point);
        }

        rose.setPosition(200, 200);
        window.draw(rose);

    }

};


int main(){
    SFML_Window myWindow(400, 400, "Maurer Rose");
    myWindow.Main_Loop();
}
