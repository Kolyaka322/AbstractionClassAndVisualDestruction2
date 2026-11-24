#include <iostream>
#include <fstream>
#include <string>

class Shape {
public:
    virtual ~Shape() = default;
    virtual void Show() const = 0;
    virtual void Save(std::ostream& out) const = 0;
    virtual void Load(std::istream& in) = 0;
};

class Square : public Shape {
private:
    double x;
    double y;
    double side;

public:
    Square(double x = 0.0, double y = 0.0, double side = 0.0)
        : x(x), y(y), side(side) {
    }

    void Show() const override {
        std::cout << "Square: top-left=(" << x << ", " << y << "), side=" << side << "\n";
    }

    void Save(std::ostream& out) const override {
        out << "Square " << x << " " << y << " " << side << "\n";
    }

    void Load(std::istream& in) override {
        in >> x >> y >> side;
    }
};

class Rectangle : public Shape {
private:
    double x;
    double y;
    double width;
    double height;

public:
    Rectangle(double x = 0.0, double y = 0.0, double width = 0.0, double height = 0.0)
        : x(x), y(y), width(width), height(height) {
    }

    void Show() const override {
        std::cout << "Rectangle: top-left=(" << x << ", " << y
            << "), width=" << width << ", height=" << height << "\n";
    }

    void Save(std::ostream& out) const override {
        out << "Rectangle " << x << " " << y << " " << width << " " << height << "\n";
    }

    void Load(std::istream& in) override {
        in >> x >> y >> width >> height;
    }
};

class Circle : public Shape {
private:
    double cx;
    double cy;
    double radius;

public:
    Circle(double cx = 0.0, double cy = 0.0, double radius = 0.0)
        : cx(cx), cy(cy), radius(radius) {
    }

    void Show() const override {
        std::cout << "Circle: center=(" << cx << ", " << cy << "), radius=" << radius << "\n";
    }

    void Save(std::ostream& out) const override {
        out << "Circle " << cx << " " << cy << " " << radius << "\n";
    }

    void Load(std::istream& in) override {
        in >> cx >> cy >> radius;
    }
};

class Ellipse : public Shape {
private:
    double x;
    double y;
    double width;
    double height;

public:
    Ellipse(double x = 0.0, double y = 0.0, double width = 0.0, double height = 0.0)
        : x(x), y(y), width(width), height(height) {
    }

    void Show() const override {
        std::cout << "Ellipse: bounding box top-left=(" << x << ", " << y
            << "), width=" << width << ", height=" << height << "\n";
    }

    void Save(std::ostream& out) const override {
        out << "Ellipse " << x << " " << y << " " << width << " " << height << "\n";
    }

    void Load(std::istream& in) override {
        in >> x >> y >> width >> height;
    }
};

Shape* CreateShapeByType(const std::string& type) {
    if (type == "Square") return new Square();
    if (type == "Rectangle") return new Rectangle();
    if (type == "Circle") return new Circle();
    if (type == "Ellipse") return new Ellipse();
    return nullptr;
}

int main() {
    system("chcp 1251>null");
    const int count = 4;
    Shape* shapes[count] = {
        new Square(1.0, 2.0, 5.0),
        new Rectangle(0.0, 0.0, 10.0, 4.0),
        new Circle(3.0, 3.0, 2.5),
        new Ellipse(-2.0, 5.0, 8.0, 6.0)
    };

    const char* filename = "shapes.txt";

    {
        std::ofstream out(filename);
        out << count << "\n";
        for (int i = 0; i < count; ++i) {
            shapes[i]->Save(out);
        }
    }

    int loadedCount = 0;
    Shape** loadedShapes = nullptr;

    {
        std::ifstream in(filename);
        if (in >> loadedCount) {
            loadedShapes = new Shape * [loadedCount];
            for (int i = 0; i < loadedCount; ++i) {
                std::string type;
                in >> type;
                loadedShapes[i] = CreateShapeByType(type);
                if (loadedShapes[i]) {
                    loadedShapes[i]->Load(in);
                }
            }
        }
    }

    for (int i = 0; i < loadedCount; ++i) {
        if (loadedShapes[i]) {
            loadedShapes[i]->Show();
        }
    }

    for (int i = 0; i < count; ++i) {
        delete shapes[i];
    }

    for (int i = 0; i < loadedCount; ++i) {
        delete loadedShapes[i];
    }
    delete[] loadedShapes;

    return 0;
}
