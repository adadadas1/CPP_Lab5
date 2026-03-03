#pragma once
#include <istream>

class Color {
  public:
    Color();
    Color(double red, double green, double blue);
    double red() const;
    double green() const;
    double blue() const;

  private:
    double r{};
    double g{};
    double b{};
};

// Читаем цвет из потока: "red green blue"
inline std::istream& operator>>(std::istream& is, Color& c) {
    double r, g, b;
    is >> r >> g >> b;
    c = Color(r, g, b);
    return is;
}
