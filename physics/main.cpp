#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdlib>
#include <memory>

using namespace std;

int main() {
  sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");

  vector<unique_ptr<sf::CircleShape>> balls;

  for (int i = 0; i < 20; i++) {
    balls.push_back(std::make_unique<sf::CircleShape>(25.f, 25.f));
    balls[i]->setPosition(sf::Vector2f((rand() % 1000), 0.f));
    balls[i]->setFillColor(sf::Color(rand() % 255, 75, 79));
  }

  sf::RectangleShape barrier(sf::Vector2f(500.f, 1000.f));
  barrier.setPosition(0, 0);
  barrier.setOutlineColor(sf::Color(255, 0, 0));

  while (window.isOpen()) {
    sf::Event event;
    window.draw(barrier);
    for (int i = 0; i < balls.size(); i++) {
      if (balls[i].get()->getGlobalBounds().intersects(
              barrier.getGlobalBounds())) {
        balls[i].reset();
        i--;
      } else {
        window.draw(*balls[i].get());
      }
    }

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.display();
    window.clear();
  }

  return 0;
}
