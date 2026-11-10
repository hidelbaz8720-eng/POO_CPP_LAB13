#include "Matrice.hpp"
#include <iostream>

int main() {
    // ---------- Entiers ----------
    std::cout << "===== Matrices d'entiers 3x3 =====\n";
    Matrice<int, 3, 3> A{{1, 2, 3},
                         {4, 5, 6},
                         {7, 8, 9}};
    Matrice<int, 3, 3> B{{9, 8, 7},
                         {6, 5, 4},
                         {3, 2, 1}};

    std::cout << "A =\n" << A;
    std::cout << "B =\n" << B;
    std::cout << "A + B =\n" << (A + B);
    std::cout << "A - B =\n" << (A - B);
    std::cout << "A * B =\n" << (A * B);

    // ---------- Dimensions différentes ----------
    Matrice<int, 2, 3> C{{1, 2, 3},
                         {4, 5, 6}};
    Matrice<int, 3, 2> D{{1, 0},
                         {0, 1},
                         {1, 1}};
    std::cout << "C (2x3) =\n" << C;
    std::cout << "D (3x2) =\n" << D;
    std::cout << "C * D (2x2) =\n" << (C * D);

    // ---------- Doubles ----------
    std::cout << "\n===== Matrices de doubles 2x2 =====\n";
    Matrice<double, 2, 2> E{{1.5, 2.5},
                            {3.5, 4.5}};
    Matrice<double, 2, 2> F{{0.5, 1.0},
                            {1.5, 2.0}};
    std::cout << "E =\n" << E;
    std::cout << "F =\n" << F;
    std::cout << "E + F =\n" << (E + F);
    std::cout << "E * F =\n" << (E * F);

    // ---------- Booléens (produit logique) ----------
    std::cout << "\n===== Matrices de bool 2x2 (logique) =====\n";
    Matrice<bool, 2, 2> P{{true,  false},
                          {true,  true}};
    Matrice<bool, 2, 2> Q{{true,  true},
                          {false, true}};
    std::cout << "P =\n" << P;
    std::cout << "Q =\n" << Q;
    std::cout << "P OU Q (P + Q) =\n" << (P + Q);
    std::cout << "P ET Q logique (P * Q) =\n" << (P * Q);

    return 0;
}