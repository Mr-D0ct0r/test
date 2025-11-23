#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>

using namespace sf;
using namespace std;

int main()
{
    srand(time(nullptr));

	VideoMode vm(1920, 1080);                                       // needed for RenderWindow.
	RenderWindow window(vm, "Chaos Game!!", Style::Default);        // create and open a window for the game.

	vector<Vector2f> vertices;
	vector<Vector2f> points;

	Font my_font;                                                   // try to load font.
    if (!my_font.loadFromFile("ZallmanCaps.TTF"))                   //
        cout << "didnt open." << endl;                              //

    Text my_text;                                                   // adjust font.
    my_text.setFont(my_font);                                       //
    my_text.setCharacterSize(50);                                   //
    my_text.setFillColor(sf::Color::White);                         //

    int shape;                                                      // for amount of vertices, and algorithm.
    cout << "Choose shape: 1. traingle; 2. square." << endl;        //
    cin >> shape;                                                   //


    int rand_verx = -1;                                             // for the square loop to not generate the same point at each new frame.
    int last_verx = -1;                                             //
    while (window.isOpen())
    {
        Event event;                                                                                    // used for tracking current events.
        while (window.pollEvent(event))                                                                 //
        {                                                                                               //
            if (event.type == Event::Closed)                                                            // for closing;
                window.close();                                                                         // (marks isOpen() to false)
                                                                                                        //
            if (event.type == Event::MouseButtonPressed)                                                // for pressing the mouse;
                if (event.mouseButton.button == Mouse::Left)                                            //
                {                                                                                       //
                    cout << "the left button was pressed" << endl;                                      //
                    cout << "mouse x: " << event.mouseButton.x << endl;                                 //
                    cout << "mouse y: " << event.mouseButton.y << endl;                                 //
                                                                                                        //
                    if(shape == 1 && vertices.size() < 3)                                                   // fill the vertices vector.
                    {                                                                                       //
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));             //
                    }                                                                                       //
                    else if(shape == 2 && vertices.size() < 4)                                              //
                    {                                                                                       //
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));             //
                    }                                                                                   //
                    else if(points.size() == 0)                                                         //
                    {                                                                                   //
                        //forth click                                                                   //
                        if (shape == 1)                                                                 //
                            my_text.setString("click on the forth point to start the algorithm.");      //
                        else                                                                            //
                            my_text.setString("click on the fifth point to start the algorithm.");      //
                                                                                                        //
                        window.draw(my_text);                                                           //
                                                                                                        //
                        if (event.mouseButton.button == Mouse::Left)                                    //
                        {                                                                               //
                            cout << "the left button was pressed" << endl;                              //
                            cout << "mouse x: " << event.mouseButton.x << endl;                         //
                            cout << "mouse y: " << event.mouseButton.y << endl;                         //
                        }                                                                               //
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));               // begin to fill the points vector.
                    }
                }
        }
        if  (Keyboard::isKeyPressed(Keyboard::Escape))
            window.close();

        if (points.size() > 0)                                                      // continue to fill the points vector
        {                                                                           // using an algorithm.
            int mid_pt_x;                                                           //
            int mid_pt_y;                                                           //
            int speed_gen = 100;                                                    //
                                                                                    //
            for(int i = 0; i < speed_gen; i++)                                          // loop for generation speed.
            {                                                                       //
                if (shape == 1)                                                     //
                {                                                                   //
                    rand_verx = rand() % vertices.size();                           //
                }                                                                   //
                else                                                                //
                {                                                                       // algorithm for square shape:
                    while(rand_verx == last_verx)                                       // first loop is started becuase they are the same (-1);
                    {                                                                   //
                        rand_verx = rand() % vertices.size();                           // generate a random vertex;
                    }                                                                   //
                    last_verx = rand_verx;                                              // specify the last vertex so next point is different.
                }                                                                   //
                                                                                    //
                mid_pt_x = (vertices[rand_verx].x + points.back().x) / 2.0;         //
                mid_pt_y = (vertices[rand_verx].y + points.back().y) / 2.0;         //
                                                                                    //
                points.push_back(Vector2f(mid_pt_x, mid_pt_y));                     //
            }
        }
        window.clear();                                                         // clears the screen of any images.

        if (shape == 1)                                                         // prepares text for user to be drawn.
            my_text.setString("GREETINGS TRAVELER \nCLICK ON FOUR POINTS");     //
        else                                                                    //
            my_text.setString("GREETINGS TRAVELER \nCLICK ON FIVE POINTS");     //
                                                                                //
        window.draw(my_text);                                                   //

        for(int i = 0; i < vertices.size(); i++)                                // prepares the vertices to be drawn.
        {                                                                       //
            RectangleShape rect(Vector2f(1, 1));                                //
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));           //
            rect.setFillColor(Color::Red);                                      //
            window.draw(rect);                                                      // does not draw right away, just prepares the drawing.
        }
        for(int i = 0; i < points.size(); i++)                              // prepares the points to be drawn.
        {                                                                   //
            RectangleShape rect(Vector2f(1, 1));                            //
            rect.setPosition(points[i]);                                    //
            rect.setFillColor(Color::White);                                //
            window.draw(rect);                                              //
        }                                                                   //
        window.display();                                                       // draws or displays everything prepared by window.draw.
    }
}
