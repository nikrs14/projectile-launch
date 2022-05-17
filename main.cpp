#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>

double getAngle(double a[2], double b[2]) {
    double angle = atan2((a[0]-b[0]), (a[1]-b[1]));
    angle = angle * (180/3.14159265);
    return -angle + 90;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(900, 600), "Gravity Simulator");
    window.setFramerateLimit(60);

    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("./assets/background.png");
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(0, 0);

    sf::Texture cannonTexture;
    cannonTexture.loadFromFile("./assets/cannon.png");
    sf::Sprite cannonSprite;
    cannonSprite.setTexture(cannonTexture);
    cannonSprite.setOrigin(24, 24);
    cannonSprite.setPosition(70, 540);

    sf::CircleShape support(20, 3);
    support.setFillColor(sf::Color::Black);
    support.setPosition(50, 540);

    sf::CircleShape projectile(6);
    projectile.setFillColor(sf::Color::Red);
    projectile.setOrigin(3, 3);
    int projectileXPos = 68; int projectileYPos = 540;
    double projectileXVel; double projectileYVel;
    int velocity = 15;
    double projectileAngle = 0;
    bool falling = false;

    sf::Font font;
    font.loadFromFile("/usr/share/fonts/opentype/noto/NotoSansCJK-Bold.ttc");  // This may not work on different PCs
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(20, 20);

    while (window.isOpen()) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        double mouseCoordinates[2];
        mouseCoordinates[0] = mousePosition.x; mouseCoordinates[1] = mousePosition.y;
        double cannonPosition[2] = {128, 541};
        double mouseAngle = getAngle(mouseCoordinates, cannonPosition);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                projectileXPos = 68; projectileYPos = 540;
                projectileAngle = -mouseAngle/(180/3.14159265);
                projectileXVel = cos(projectileAngle)*velocity;
                projectileYVel = sin(projectileAngle)*velocity;
                falling = true;
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::W) {
                    velocity++;
                }
                if (event.key.code == sf::Keyboard::S) {
                    velocity--;
                }
            }
        }

        if (!(mouseAngle > 27 and mouseAngle < 158)) {
            cannonSprite.setRotation(mouseAngle);
        }

        if (projectileYPos >= 560) {
            projectileYVel *= -0.75;
            projectileXVel *= 0.75;
            projectileYPos -= 3;
        }

        if (falling == true) {
            projectileYVel -= 0.5;
            projectileXPos += projectileXVel;
            projectileYPos -= projectileYVel;
        }
        
        projectile.setPosition(projectileXPos, projectileYPos);

        text.setString("Velocity = " + std::to_string(velocity));

        window.clear(sf::Color::Black);

        window.draw(backgroundSprite);
        window.draw(projectile);
        window.draw(cannonSprite);
        window.draw(support);
        window.draw(text);

        window.display();
    }
}