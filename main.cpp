#include "Player.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <chrono>
#include "PoetryLine.h"
#include <list>
#include "Poster.h"

int getTime() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

std::list<Poster*> placePosters() {
    std::list<Poster*> posters;

    posters.push_back(new Poster("resources/headlines/voter_suppression.png", sf::Vector2f(-600, 50)));
    posters.push_back(new Poster("resources/headlines/alt_right.png", sf::Vector2f(1100, -200)));
    posters.push_back(new Poster("resources/headlines/eviction.png", sf::Vector2f(460, -450)));
    posters.push_back(new Poster("resources/headlines/police_suppression.png", sf::Vector2f(-700, 1100)));

    posters.push_back(new Poster("resources/jazz_posters/poster1.png", sf::Vector2f(-400, 200)));
    posters.push_back(new Poster("resources/jazz_posters/poster2.png", sf::Vector2f(1050, 0)));
    posters.push_back(new Poster("resources/jazz_posters/poster3.png", sf::Vector2f(500, -100)));
    posters.push_back(new Poster("resources/jazz_posters/poster4.png", sf::Vector2f(-100, -700)));
    posters.push_back(new Poster("resources/jazz_posters/poster5.png", sf::Vector2f(-500, -550)));
    posters.push_back(new Poster("resources/jazz_posters/poster6.png", sf::Vector2f(-800, 500)));
    posters.push_back(new Poster("resources/jazz_posters/poster1.png", sf::Vector2f(900, -500)));
    posters.push_back(new Poster("resources/jazz_posters/poster5.png", sf::Vector2f(1160, 900)));
    posters.push_back(new Poster("resources/jazz_posters/poster3.png", sf::Vector2f(700, 1150)));
    posters.push_back(new Poster("resources/jazz_posters/poster4.png", sf::Vector2f(30, 1200)));

    return posters;
}

std::list<PoetryLine*> makeLines() {
    std::list<PoetryLine*> lines;

    lines.push_back(new PoetryLine("Good morning, daddy!\nAin't you heard\nThe boogie-woogie rumble\nOf a dream deferred?\n\nListen closely: You'll hear their feet\nBeating out and beating out a-", sf::Vector2f(400, 200), 300, .8));
    lines.push_back(new PoetryLine("You think\nIt's a happy beat?", sf::Vector2f(400, 650), 200, .6, 1, (sf::Uint32)sf::Text::Italic));
    lines.push_back(new PoetryLine("Well, they rocked him with road-apples\nbecause he tried to vote", sf::Vector2f(-350, -25), 300, .7));
    lines.push_back(new PoetryLine("And there ain't no Ku Klux\non a 133rd", sf::Vector2f(900, 150), 300, .7));
    lines.push_back(new PoetryLine("Some folks blame high prices on the Jews.\n(Some folks blame too much on Jews.)", sf::Vector2f(1340, -300), 300, .7));
    lines.push_back(new PoetryLine("Sometimes I think\nJews must have heard\nthe music of a\ndream deferred", sf::Vector2f(1400, -70), 300, .7));
    lines.push_back(new PoetryLine("Ten Bucks you say I owe you?\nTen Bucks you say is due?\nWell, that's Ten Bucks more'n I'll pay you\nTill you fix this house up new", sf::Vector2f(680, -270), 300, .7));
    lines.push_back(new PoetryLine("Motorcycle cops,\nwhite,\nwill speed it\nout of sight\nif they can:\n\n\n\n\nSolid black,\ncan't be right.", sf::Vector2f(-400, 1085), 300, .7));

    return lines;
}

int main() {
    // Create window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Boogie Woogie Rumble");

    sf::View view(sf::FloatRect(0.f, 0.f, 800.f, 600.f));
    window.setView(view);

    // Create player
    Player player;

    std::list<PoetryLine*> lines = makeLines();

    std::list<Poster*> posters = placePosters();

    bool paused = false;

    // Music from https://upload.wikimedia.org/wikipedia/commons/d/dc/Mamie_Smith%2C_Crazy_Blues.ogg
    sf::Music jazz;
    jazz.openFromFile("resources/Crazy_Blues.ogg");
    jazz.setLoop(true);
    jazz.play();

    int lastTime = getTime();

    while (window.isOpen()) {
        float delta_t = (float)(getTime() - lastTime);
        lastTime = getTime();

        sf::Event event;

        // Check for events and handle them
        while (window.pollEvent(event))
        {
            // Close the window if the user closes the window
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            else if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Key::Space) {
                    if (!paused) {
                        paused = true;
                        //jazz.pause();
                    }

                    else {
                        paused = false;
                        //jazz.play();
                    }
                }
            }
        }

        if (paused) {
            delta_t = 0;
        }

        // Clear out everything already rendered
        window.clear(sf::Color(140, 140, 140, 255));

        player.move(&window, delta_t);

        if (player.getPosition() != view.getCenter()) {
            view.setCenter(player.getPosition());
            window.setView(view);
        }

        for (Poster* poster : posters) {
            window.draw(poster->getSprite());
        }

        for (PoetryLine* line : lines) {
            line->checkProximity(&player, &jazz);
            window.draw(line->getText());
        }

        window.draw(player.getShape());

        window.display();
    }

    for (PoetryLine* line : lines) {
        delete line;
    }

    for (Poster* poster : posters) {
        delete poster;
    }
}