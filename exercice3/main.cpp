#include "Stack.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <string>

// Petit objet instrumenté pour vérifier la bonne destruction
struct Compteur {
    static int vivants;
    int id;
    Compteur(int i = 0) : id(i) { ++vivants; }
    Compteur(const Compteur& o) : id(o.id) { ++vivants; }
    Compteur(Compteur&& o) noexcept : id(o.id) { ++vivants; }
    Compteur& operator=(const Compteur&) = default;
    Compteur& operator=(Compteur&&) noexcept = default;
    ~Compteur() { --vivants; }
};
int Compteur::vivants = 0;

int main() {
    // ---------- 1) Test basique ----------
    std::cout << "===== Test basique =====\n";
    Stack<int> s(5);
    s.push(10); s.push(20); s.push(30);
    std::cout << "peek = " << s.peek() << "  (size=" << s.size() << ")\n";
    std::cout << "pop  = " << s.pop()  << "\n";
    std::cout << "pop  = " << s.pop()  << "\n";
    std::cout << "pop  = " << s.pop()  << "\n";
    std::cout << "vide ? " << std::boolalpha << s.empty() << "\n";

    // ---------- 2) StackOverflow ----------
    std::cout << "\n===== Test StackOverflow =====\n";
    try {
        Stack<int> petit(2);
        petit.push(1);
        petit.push(2);
        petit.push(3);   
    } catch (const StackOverflow& e) {
        std::cout << "Attrape : " << e.what() << "\n";
    }

    // ---------- 3) StackUnderflow ----------
    std::cout << "\n===== Test StackUnderflow =====\n";
    try {
        Stack<int> vide(4);
        vide.pop();      
    } catch (const StackUnderflow& e) {
        std::cout << "Attrape: " << e.what() << "\n";
    }

    // ---------- 4) Constructeur itérateur ----------
    std::cout << "\n===== Test constructeur (begin, end) =====\n";
    std::vector<std::string> mots = {"alpha", "beta", "gamma", "delta"};
    Stack<std::string> smots(mots.begin(), mots.end(), 10);
    std::cout << "size = " << smots.size() << "\n";
    while (!smots.empty())
        std::cout << "  " << smots.pop() << "\n";

    // Depuis une std::list
    std::list<double> ld = {1.1, 2.2, 3.3};
    Stack<double> sd(ld.begin(), ld.end());
    std::cout << "Sommet liste : " << sd.peek() << "\n";

    // ---------- 5) Stress-test + vérification fuites ----------
    std::cout << "\n===== Stress-test (100 000 objets) =====\n";
    {
        Stack<Compteur> sc(100000);
        for (int i = 0; i < 100000; ++i)
            sc.push(Compteur(i));
        std::cout << "vivants apres push : " << Compteur::vivants << "\n";

        // On vide
        while (!sc.empty()) sc.pop();
        std::cout << "vivants apres pop  : " << Compteur::vivants << "\n";
    } // <-- destructeur de sc : unique_ptr libère le tableau
    std::cout << "vivants apres destruction de la pile : "
              << Compteur::vivants << "  (doit valoir 0)\n";

    // ---------- 6) Déplacement ----------
    std::cout << "\n===== Test deplacement =====\n";
    Stack<int> a(3);
    a.push(1); a.push(2);
    Stack<int> b = std::move(a);   // OK car unique_ptr
    std::cout << "b.peek = " << b.peek() << ", b.size = " << b.size() << "\n";
    std::cout << "a.size = " << a.size() << " (deplacee)\n";

    std::cout << "\nAucune fuite memoire ne doit etre detectee par valgrind.\n";
    return 0;
}