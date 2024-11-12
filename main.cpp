#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <iostream>

int main()
{
    std::string pusty = "0000000000000000000000000000000000000000000000000000";
    std::vector<std::string> T1 (52);
    std::vector<std::string> T2 (52);
    std::fstream plik;
    plik.open("tablica.txt");
    std::string tekst;

    for(int i = 0; i < 52; i++)
    {
        plik >> tekst;
        T1[i] = tekst;    
    }
    plik.close();

    for(int i = 0; i < 52; i++)
    {
        T2[i] = pusty;    
    }

    sf::RenderWindow window(sf::VideoMode(752, 752), "Game of Life");

    sf::RectangleShape live (sf::Vector2f(15, 15));
    live.setFillColor(sf::Color::White);

    sf::RectangleShape dead (sf::Vector2f(15, 15));
    dead.setFillColor(sf::Color::Black);

    live.setOutlineThickness(1);
    live.setOutlineColor(sf::Color::White);

    dead.setOutlineThickness(1);
    dead.setOutlineColor(sf::Color(94, 94, 94));

    bool isPaused = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

    
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
                isPaused = true;
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
                isPaused = false;

        
            if (isPaused && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                int x = event.mouseButton.x / 15 + 1;
                int y = event.mouseButton.y / 15 + 1;
                
                if (x >= 1 && x <= 50 && y >= 1 && y <= 50)
                {
                    T1[y][x] = (T1[y][x] == '1') ? '0' : '1';  
                }
            }
        }

        window.clear();

        for(int i = 1; i <= 50; i++)
        {
            for(int j = 1; j <= 50; j++)
            {
                if(T1[i][j] == '1')
                {
                    live.setPosition((j-1)*15+1, (i-1)*15+1);
                    window.draw(live);
                }
                else{
                    dead.setPosition((j-1)*15+1, (i-1)*15+1);
                    window.draw(dead);
                }
            }
        }

    
        if (!isPaused)
        {
            for(int i = 1; i <= 50; i++)
            {
                for(int j = 1; j <= 50; j++)
                {
                    int count = 0;
                    int isAlive = (T1[i][j] == '1') ? 1 : 0;

                    for(int m = -1; m <= 1; m++)
                    {
                        for(int n = -1; n <= 1; n++)
                        {
                            if(T1[i+m][j+n] == '1')
                                count++;
                        }
                    }

                    count -= isAlive;

                    if(isAlive && count < 2)
                        T2[i][j] = '0';
                    else if(isAlive && (count == 2 || count == 3))
                        T2[i][j] = '1';
                    else if(isAlive && count > 3)
                        T2[i][j] = '0';
                    else if(!isAlive && count == 3)
                        T2[i][j] = '1';
                }
            }

            T1 = T2;

            for(int i = 0; i < 52; i++)
            {
                T2[i] = pusty;    
            }

            sf::sleep(sf::seconds(0.07));
        }

        window.display();
    }

    return 0;
}
