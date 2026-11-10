#include "ArrayDyn.hpp"
#include <iostream>
#include <string>
#include <cassert>


struct Point {
    int x, y;
    Point(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}
    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        return os << "(" << p.x << "," << p.y << ")";
    }
};

int main() {

    std::cout << "===== 1) ArrayDyn<int> =====\n";
    ArrayDyn<int> ints(2);
    for (int i = 1; i <= 6; ++i) ints.push_back(i * 10);
    std::cout << "size=" << ints.size()
              << "  capacity=" << ints.capacity() << "\n";
    std::cout << "Contenu  : ";
    for (auto& e : ints) std::cout << e << ' ';
    std::cout << "\n";

    std::cout << "Acces [2] : " << ints[2] << "\n";
    ints.pop_back();
    std::cout << "Apres pop_back, size=" << ints.size() << "\n";

 
    std::cout << "\n===== 2) ArrayDyn<std::string> =====\n";
    ArrayDyn<std::string> mots;
    mots.push_back("bonjour");
    mots.push_back("le");
    mots.push_back("monde");
    for (const auto& m : mots) std::cout << m << ' ';
    std::cout << "\n";

 
    std::cout << "\n===== 3) ArrayDyn<Point> =====\n";
    ArrayDyn<Point> pts;
    pts.push_back(Point(1, 2));
    pts.push_back(Point(3, 4));
    pts.push_back(Point(5, 6));
    for (auto& p : pts) std::cout << p << ' ';
    std::cout << "\n";

 
    std::cout << "\n===== 4) Copie =====\n";
    ArrayDyn<int> copie = ints;                 // constructeur de copie
    copie.push_back(999);                       // ne modifie pas ints
    std::cout << "ints  : "; for (auto& e : ints)  std::cout << e << ' '; std::cout << "\n";
    std::cout << "copie : "; for (auto& e : copie) std::cout << e << ' '; std::cout << "\n";

    ArrayDyn<int> autre;
    autre = ints;                               // opérateur d'affectation
    std::cout << "autre = ints : "; for (auto& e : autre) std::cout << e << ' '; std::cout << "\n";


    std::cout << "\n===== 5) Iterateur -- =====\n";
    std::cout << "ints en arriere : ";
    auto it = ints.end();
    while (it != ints.begin()) {
        --it;
        std::cout << *it << ' ';
    }
    std::cout << "\n";

   
    std::cout << "\n===== 6) Bornes =====\n";
    try {
        std::cout << ints[100];
    } catch (const std::out_of_range& e) {
        std::cout << "Exception attrapee : " << e.what() << "\n";
    }

    std::cout << "\nFin des tests.\n";
    return 0;
}