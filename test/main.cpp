#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

// triangle[0].position = sf::Vector2f(10.f, 10.f);
// triangle[1].position = sf::Vector2f(100.f, 10.f);
// triangle[2].position = sf::Vector2f(100.f, 100.f);

// define the color of the triangle's points
// triangle[0].color = sf::Color::Red;
// triangle[1].color = sf::Color::Blue;
// triangle[2].color = sf::Color::Green;

bool checkCollisionLocal(sf::CircleShape &shape,vector<sf::CircleShape> &entities) {
  vector<sf::CircleShape> check;
  for (sf::CircleShape &s : entities) {
    if ((abs(s.getPosition().x - shape.getPosition().x) < 40) &&
        (abs(s.getPosition().y - shape.getPosition().y) < 40)) {
      check.push_back(s);
    }
  }
  for (sf::CircleShape &s : check) {
    if (shape.getGlobalBounds().intersects(s.getGlobalBounds()) &&
        shape.getPosition() != s.getPosition()) {
      return true;
    }
  }
  return false;
}

bool checkCollisionMonolith(sf::CircleShape &shape,vector<sf::CircleShape> entities) {

  return false;
}

bool checkCollisionColumns(sf::CircleShape &shape,vector<sf::RectangleShape> columns) {
  for ( auto &col: columns) {
    if (shape.getGlobalBounds().intersects(col.getGlobalBounds())) {
      col.setSize(sf::Vector2f(50.f, col.getSize().y + 25.f));
      return true;
    }
  }
  return false;
}

// void assimilate(sf::CircleShape &shape, sf :://insert custom shape type
// here);

// TODO: new new collision idea: use columns to only check collision of the highest circle!!!!

int main() {
  sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML");
  window.setVerticalSyncEnabled(true);

  sf::Font font;
  font.loadFromFile("Roboto-Regular.ttf");
  sf::Text ballCounter;
  //Note: ~800 balls is the point where my laptop overheats :)
  ballCounter.setFont(font);
  ballCounter.setCharacterSize(24);
  ballCounter.setFillColor(sf::Color::White);
  ballCounter.setPosition(sf::Vector2f(1050.f,0));
  sf::Text fpsCounter;
  fpsCounter.setFont(font);
  fpsCounter.setCharacterSize(24);
  fpsCounter.setFillColor(sf::Color::White);
  fpsCounter.setPosition(sf::Vector2f(1050.f,25.f));
  //  vector<unique_ptr<sf::CircleShape>> balls;
  vector<sf::CircleShape> balls;
  vector<sf::RectangleShape> collisionColumns;
  for (int i = 0; i <= 20; i++) {
    sf::RectangleShape col = sf::RectangleShape(sf::Vector2f(50.f, 1.f));
    col.setPosition(i * 50.f, 800.f);
    col.setOutlineColor(sf::Color::Red);
    col.setOutlineThickness(2.f);
    collisionColumns.push_back(col);
  }
  
  int frame = 0;
  std::chrono::high_resolution_clock::time_point start;
  std::chrono::high_resolution_clock::time_point end;
  float fps =0;
  int xcolor = 0;
  int ycolor = 0;
  const int gravity = 10.f;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    frame += 1;
    if (frame % 6 == 0) {
      sf::CircleShape ball(25.f);
      ball.setPosition(rand() % 1000, 0);
      balls.push_back(ball);
    }
    // auto ball = make_unique<sf::CircleShape>((24.f));
    // ball->setFillColor(sf::Color(rand() % 254, rand() % 255, rand() % 255));
    // ball->setPosition(500, 1000);
    // balls.push_back(move(ball));
    // window.draw(ball);
    //for (auto &c : collisionColumns) {
    //  window.draw(c);
    //}
    start = std::chrono::high_resolution_clock::now();
    for (auto &s : balls) {
      /// if (!(checkCollisionAll(s, balls))) {
      // s.move(0.f, gravity);
      // }
      // s.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
      if ((s.getPosition().y < 1000) &&(!(checkCollisionLocal(s , balls)))) {
        xcolor = (s.getPosition().x) / 7.529;

        ycolor = (s.getPosition().y) / 4.235;
        s.setFillColor(sf::Color(xcolor, ycolor, (xcolor + ycolor) / 2));

        s.move(0.f, gravity);
      }
      window.draw(s);
    }
    ballCounter.setString(to_string(balls.size()));
    window.draw(ballCounter);
    fpsCounter.setString(to_string(fps));
    window.draw(fpsCounter);
    window.display();
    end = std::chrono::high_resolution_clock::now();
    fps = (float)1e9/(float)std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    window.clear();
  }
  return 0;
}
