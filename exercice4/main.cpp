#include "Sortable.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <functional>

// ============================================================
// Structure utilisateur avec operator<
// ============================================================
struct Personne {
    std::string nom;
    int age;

    Personne(std::string n = "", int a = 0) : nom(n), age(a) {}

    bool operator<(const Personne& o) const {
        if (age != o.age) return age < o.age;
        return nom < o.nom;
    }

    friend std::ostream& operator<<(std::ostream& os, const Personne& p) {
        return os << p.nom << "(" << p.age << ")";
    }
};

// ============================================================
// Mini-framework de tests
// ============================================================
static int tests_ok = 0;
static int tests_ko = 0;

template <typename T>
void checkSorted(const std::vector<T>& v,
                 std::function<bool(const T&, const T&)> comp,
                 const std::string& label) {
    bool ok = true;
    for (std::size_t i = 1; i < v.size(); ++i) {
        if (comp(v[i], v[i - 1])) { ok = false; break; }
    }
    std::cout << (ok ? "[OK]   " : "[FAIL] ") << label << "\n";
    ok ? ++tests_ok : ++tests_ko;
}

template <typename T>
void printVec(const std::vector<T>& v) {
    std::cout << "{ ";
    for (typename std::vector<T>::const_iterator it = v.begin(); it != v.end(); ++it)
        std::cout << *it << ' ';
    std::cout << "}\n";
}

// ============================================================
// Tests
// ============================================================
void testInts() {
    std::cout << "\n----- Test 1 : vector<int> -----\n";
    std::vector<int> v;
    v.push_back(5); v.push_back(3); v.push_back(8);
    v.push_back(1); v.push_back(9); v.push_back(2); v.push_back(7);

    std::vector<int> asc = v;
    quickSort(asc);
    std::cout << "asc  : "; printVec(asc);
    checkSorted(asc, std::less<int>(), "ints triés croissant");

    std::vector<int> desc = v;
    quickSortComp(desc, Desc());
    std::cout << "desc : "; printVec(desc);
    checkSorted(desc, std::greater<int>(), "ints triés décroissant");
}

void testStrings() {
    std::cout << "\n----- Test 2 : vector<string> -----\n";
    std::vector<std::string> v;
    v.push_back("kiwi"); v.push_back("apple");
    v.push_back("banana"); v.push_back("cherry");

    std::vector<std::string> asc = v;
    quickSort(asc);
    std::cout << "asc  : "; printVec(asc);
    checkSorted(asc, std::less<std::string>(), "strings triés croissant");

    std::vector<std::string> desc = v;
    quickSortComp(desc, Desc());
    std::cout << "desc : "; printVec(desc);
    checkSorted(desc, std::greater<std::string>(), "strings triés décroissant");
}

void testPersonnes() {
    std::cout << "\n----- Test 3 : vector<Personne> -----\n";
    std::vector<Personne> v;
    v.push_back(Personne("Alice", 30));
    v.push_back(Personne("Bob",   25));
    v.push_back(Personne("Carol", 30));
    v.push_back(Personne("Dave",  20));

    std::vector<Personne> asc = v;
    quickSort(asc);
    std::cout << "asc  : "; printVec(asc);
    checkSorted(asc, std::less<Personne>(), "personnes triées croissant (age, nom)");

    std::vector<Personne> byName = v;
    quickSortComp(byName, [](const Personne& a, const Personne& b) {
        return a.nom < b.nom;
    });
    std::cout << "byName : "; printVec(byName);
    checkSorted(byName,
                [](const Personne& a, const Personne& b) { return a.nom < b.nom; },
                "personnes triées par nom");
}

void testEdgeCases() {
    std::cout << "\n----- Test 4 : cas limites -----\n";

    std::vector<int> vide;
    quickSort(vide);
    checkSorted(vide, std::less<int>(), "vecteur vide");

    std::vector<int> un;
    un.push_back(42);
    quickSort(un);
    checkSorted(un, std::less<int>(), "vecteur à 1 élément");

    std::vector<int> egaux;
    for (int i = 0; i < 4; ++i) egaux.push_back(5);
    quickSort(egaux);
    checkSorted(egaux, std::less<int>(), "vecteur à éléments égaux");

    std::vector<int> deja;
    for (int i = 1; i <= 5; ++i) deja.push_back(i);
    quickSort(deja);
    checkSorted(deja, std::less<int>(), "vecteur déjà trié");
}

int main() {
    std::cout << "===== Exercice 4 : quickSort adapté à GCC 6.3 (C++14) =====\n";

    testInts();
    testStrings();
    testPersonnes();
    testEdgeCases();

    std::cout << "\n===== Bilan : "
              << tests_ok << " OK / "
              << tests_ko << " KO =====\n";

    return tests_ko == 0 ? 0 : 1;
}