#ifndef MATRICE_HPP
#define MATRICE_HPP

#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <type_traits>

template <typename T, std::size_t N, std::size_t M>
class Matrice {
private:
    T data[N][M]{};

public:
    // Constructeur par défaut : initialise à 0
    Matrice() {
        for (std::size_t i = 0; i < N; ++i)
            for (std::size_t j = 0; j < M; ++j)
                data[i][j] = T{};
    }

    // Constructeur par liste d'initialisation
    Matrice(std::initializer_list<std::initializer_list<T>> init) {
        if (init.size() != N)
            throw std::invalid_argument("Nombre de lignes incorrect");

        std::size_t i = 0;
        for (const auto& ligne : init) {
            if (ligne.size() != M)
                throw std::invalid_argument("Nombre de colonnes incorrect");
            std::size_t j = 0;
            for (const auto& val : ligne)
                data[i][j++] = val;
            ++i;
        }
    }

    // Accès
    T& operator()(std::size_t i, std::size_t j)       { return data[i][j]; }
    const T& operator()(std::size_t i, std::size_t j) const { return data[i][j]; }

    // Addition élément par élément
    Matrice operator+(const Matrice& autre) const {
        Matrice res;
        for (std::size_t i = 0; i < N; ++i)
            for (std::size_t j = 0; j < M; ++j)
                res.data[i][j] = data[i][j] + autre.data[i][j];
        return res;
    }

    // Soustraction
    Matrice operator-(const Matrice& autre) const {
        Matrice res;
        for (std::size_t i = 0; i < N; ++i)
            for (std::size_t j = 0; j < M; ++j)
                res.data[i][j] = data[i][j] - autre.data[i][j];
        return res;
    }

    // Produit matriciel : Matrice<T,N,M> * Matrice<T,M,P> -> Matrice<T,N,P>
    template <std::size_t P>
    Matrice<T, N, P> operator*(const Matrice<T, M, P>& autre) const {
        Matrice<T, N, P> res;  // initialisé à 0
        for (std::size_t i = 0; i < N; ++i)
            for (std::size_t j = 0; j < P; ++j)
                for (std::size_t k = 0; k < M; ++k)
                    res(i, j) = res(i, j) + data[i][k] * autre(k, j);
        return res;
    }

    // Ami pour l'affichage
    friend std::ostream& operator<<(std::ostream& os, const Matrice& m) {
        for (std::size_t i = 0; i < N; ++i) {
            os << "[ ";
            for (std::size_t j = 0; j < M; ++j) {
                os << m.data[i][j];
                if (j + 1 < M) os << "  ";
            }
            os << " ]\n";
        }
        return os;
    }
};

// ============================================================
// Spécialisation pour bool : produit logique (ET / OU)
// ============================================================
template <std::size_t N, std::size_t M>
class Matrice<bool, N, M> {
private:
    bool data[N][M]{};

public:
    Matrice() = default;

    Matrice(std::initializer_list<std::initializer_list<bool>> init) {
        if (init.size() != N)
            throw std::invalid_argument("Nombre de lignes incorrect");
        std::size_t i = 0;
        for (const auto& ligne : init) {
            if (ligne.size() != M)
                throw std::invalid_argument("Nombre de colonnes incorrect");
            std::size_t j = 0;
            for (bool v : ligne) data[i][j++] = v;
            ++i;
        }
    }

    bool operator()(std::size_t i, std::size_t j) const { return data[i][j]; }
    bool& operator()(std::size_t i, std::size_t j)      { return data[i][j]; }

    // OU logique
    Matrice operator+(const Matrice& autre) const {
        Matrice res;
        for (std::size_t i = 0; i < N; ++i)
            for (std::size_t j = 0; j < M; ++j)
                res.data[i][j] = data[i][j] || autre.data[i][j];
        return res;
    }

    // ET logique
    Matrice operator-(const Matrice& autre) const {
        Matrice res;
        for (std::size_t i = 0; i < N; ++i)
            for (std::size_t j = 0; j < M; ++j)
                res.data[i][j] = data[i][j] && !autre.data[i][j];
        return res;
    }

    // Produit "logique" (ET / OU) : res[i][j] = OU_k ( A[i][k] ET B[k][j] )
    template <std::size_t P>
    Matrice<bool, N, P> operator*(const Matrice<bool, M, P>& autre) const {
        Matrice<bool, N, P> res;
        for (std::size_t i = 0; i < N; ++i)
            for (std::size_t j = 0; j < P; ++j) {
                bool acc = false;
                for (std::size_t k = 0; k < M; ++k)
                    acc = acc || (data[i][k] && autre(k, j));
                res(i, j) = acc;
            }
        return res;
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrice& m) {
        for (std::size_t i = 0; i < N; ++i) {
            os << "[ ";
            for (std::size_t j = 0; j < M; ++j) {
                os << (m.data[i][j] ? "1" : "0");
                if (j + 1 < M) os << "  ";
            }
            os << " ]\n";
        }
        return os;
    }
};

#endif