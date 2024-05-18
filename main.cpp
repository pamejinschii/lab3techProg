#include <cmath>
#include <iostream>
#include <vector>

class Point {
public:
  virtual void draw() const = 0;
  virtual void remove() = 0;
  virtual void move(double dx, double dy) = 0;
  virtual void rotate(double angle) = 0;
  virtual ~Point() {}
};

class Shape : public Point {
protected:
  std::vector<std::pair<double, double>> vertices;

public:
  void draw() const override {
    std::cout << "Drawing a shape with vertices at:" << std::endl;
    for (const auto &vertex : vertices) {
      std::cout << "(" << vertex.first << ", " << vertex.second << ")"
                << std::endl;
    }
  }

  void remove() override {
    std::cout << "Removing a shape." << std::endl;
    vertices.clear();
  }

  void move(double dx, double dy) override {
    for (auto &vertex : vertices) {
      vertex.first += dx;
      vertex.second += dy;
    }
  }

  void rotate(double angle) override {
 
    double centerX = 0.0;
    double centerY = 0.0;
    for (const auto &vertex : vertices) {
      centerX += vertex.first;
      centerY += vertex.second;
    }
    centerX /= vertices.size();
    centerY /= vertices.size();


    double angleRadian = angle * M_PI / 180;
    for (auto &vertex : vertices) {
      double x = (vertex.first - centerX) * cos(angleRadian) -
                 (vertex.second - centerY) * sin(angleRadian) + centerX;
      double y = (vertex.first - centerX) * sin(angleRadian) +
                 (vertex.second - centerY) * cos(angleRadian) + centerY;
      vertex.first = x;
      vertex.second = y;
    }
  }
};

class Line : public Shape {
public:
  Line(std::pair<double, double> start, std::pair<double, double> end) {
    vertices.push_back(start);
    vertices.push_back(end);
  }

  void draw() const override {
    std::cout << "Drawing a line from (" << vertices[0].first << ", "
              << vertices[0].second << ") to (" << vertices[1].first << ", "
              << vertices[1].second << ")." << std::endl;
  }
};

class Square : public Shape {
protected:
  double sideLength;

public:
  Square(std::pair<double, double> topLeft, double length)
      : sideLength(length) {
    vertices.push_back(topLeft);
    vertices.push_back({topLeft.first + length, topLeft.second});
    vertices.push_back({topLeft.first + length, topLeft.second - length});
    vertices.push_back({topLeft.first, topLeft.second - length});
  }

  void draw() const override {
    std::cout << "Drawing a square with side length " << sideLength
              << " and top left vertex at (" << vertices[0].first << ", "
              << vertices[0].second << ")." << std::endl;
  }
};

class Parallelogram : public Shape {
protected:
  double sideA;
  double sideB;
  double angle;

public:
  Parallelogram(std::pair<double, double> vertex, double a, double b,
                double ang)
      : sideA(a), sideB(b), angle(ang) {
    vertices.push_back(vertex);
    vertices.push_back({vertex.first + sideA, vertex.second});
    vertices.push_back({vertex.first + sideA - sideB * cos(angle * M_PI / 180),
                        vertex.second - sideB * sin(angle * M_PI / 180)});
    vertices.push_back({vertex.first - sideB * cos(angle * M_PI / 180),
                        vertex.second - sideB * sin(angle * M_PI / 180)});
  }

  void draw() const override {
    std::cout << "Drawing a parallelogram with vertices:" << std::endl;
    for (const auto &vertex : vertices) {
      std::cout << "(" << vertex.first << ", " << vertex.second << ")"
                << std::endl;
    }
  }
};

class Rhombus : public Shape {
protected:
  double sideLength;
  double angle;

public:
  Rhombus(std::pair<double, double> vertex, double length, double ang)
      : sideLength(length), angle(ang) {
    vertices.push_back(vertex);
    vertices.push_back({vertex.first + sideLength, vertex.second});
    vertices.push_back(
        {vertex.first + sideLength - sideLength * cos(angle * M_PI / 180),
         vertex.second - sideLength * sin(angle * M_PI / 180)});
    vertices.push_back({vertex.first - sideLength * cos(angle * M_PI / 180),
                        vertex.second - sideLength * sin(angle * M_PI / 180)});
  }

  void draw() const override {
    std::cout << "Drawing a rhombus with vertices:" << std::endl;
    for (const auto &vertex : vertices) {
      std::cout << "(" << vertex.first << ", " << vertex.second << ")"
                << std::endl;
    }
  }
};

class Rectangle : public Shape {
protected:
  double width;
  double height;

public:
  Rectangle(std::pair<double, double> topLeft, double w, double h)
      : width(w), height(h) {
    vertices.push_back(topLeft);
    vertices.push_back({topLeft.first + w, topLeft.second});
    vertices.push_back({topLeft.first + w, topLeft.second - h});
    vertices.push_back({topLeft.first, topLeft.second - h});
  }

  void draw() const override {
    std::cout << "Drawing a rectangle with width " << width << ", height "
              << height << " and top left vertex at (" << vertices[0].first
              << ", " << vertices[0].second << ")." << std::endl;
  }
};

class SquareParallelogram : public Rectangle {
public:
  SquareParallelogram(std::pair<double, double> topLeft, double sideLength)
      : Rectangle(topLeft, sideLength, sideLength) {}

  void draw() const override {
    std::cout << "Drawing a square parallelogram with side length " << width
              << " and top left vertex at (" << vertices[0].first << ", "
              << vertices[0].second << ")." << std::endl;
  }
};

// ������ ������������� ��������
void rotateShape(Point &shape, double angle) {
  shape.rotate(angle);
}

int main() {
  Line line({0, 0}, {1, 1});
  Square square({0, 0}, 2);

  Parallelogram parallelogram({0, 0}, 3, 2, 45);
  Rhombus rhombus({0, 0}, 2, 60);

  line.draw();
  line.move(1, 1);
  line.draw();

  square.draw();
  square.move(2, 2);
  square.draw();

  parallelogram.draw();
  parallelogram.move(1, 1);
  parallelogram.draw();
  rotateShape(parallelogram, 30);
  parallelogram.draw();

  rhombus.draw();
  rhombus.move(2, 2);
  rhombus.draw();
  rotateShape(rhombus, -45);
  rhombus.draw();

  return 0;
}

