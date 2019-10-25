#include <SFML/Graphics.hpp>
#include <random>
#include <utility>


using namespace  sf;
using namespace std;



class SFML_Window{
public:
    int window_width;
    int window_height;
    string window_title;
    RenderWindow window;

    explicit SFML_Window(int width = 800, int height = 600, string title = "Empty Window"){
        window_width = width;
        window_height = height;
        window_title = std::move(title);
        window.create(VideoMode(window_width, window_height), window_title);
    }

    void Main_Loop(){
        while (window.isOpen()){
            Event event{};
            while (window.pollEvent(event)){
                if (event.type == Event::Closed)
                    window.close();
            }

            window.clear(Color::White);
            window.display();
        }
    }

};


int main(){
    SFML_Window myWindow;
    myWindow.Main_Loop();
}
