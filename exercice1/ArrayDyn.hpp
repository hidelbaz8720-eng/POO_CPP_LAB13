#ifndef ARRAYDYN_HPP
#define ARRAYDYN_HPP

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <iostream>


template <typename T>
class ArrayDyn {
public:
    // ============================================================
    // Itérateur bidirectionnel
    // ============================================================
    class Iterator {
    public:
        // --- Tags requis par std::iterator_traits (facultatif mais propre) ---
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;

        explicit Iterator(T* ptr = nullptr) : m_ptr(ptr) {}

        reference operator*() const  { return *m_ptr; }
        pointer   operator->() const { return  m_ptr; }

        Iterator& operator++()    { ++m_ptr; return *this; }   // pré-incrément
        Iterator  operator++(int) { Iterator tmp = *this; ++m_ptr; return tmp; }

        Iterator& operator--()    { --m_ptr; return *this; }   // pré-décrément
        Iterator  operator--(int) { Iterator tmp = *this; --m_ptr; return tmp; }

        bool operator==(const Iterator& o) const { return m_ptr == o.m_ptr; }
        bool operator!=(const Iterator& o) const { return m_ptr != o.m_ptr; }

    private:
        T* m_ptr;
    };

    // ============================================================
    // Constructeurs / destructeur (Règle des trois)
    // ============================================================
    ArrayDyn() : m_data(nullptr), m_size(0), m_capacity(0) {}

    explicit ArrayDyn(std::size_t initialCapacity)
        : m_data(initialCapacity ? new T[initialCapacity] : nullptr),
          m_size(0),
          m_capacity(initialCapacity) {}

    // Copie
    ArrayDyn(const ArrayDyn& other)
        : m_data(other.m_capacity ? new T[other.m_capacity] : nullptr),
          m_size(other.m_size),
          m_capacity(other.m_capacity) {
        for (std::size_t i = 0; i < m_size; ++i)
            m_data[i] = other.m_data[i];
    }

    // Affectation par copie (copy-and-swap)
    ArrayDyn& operator=(const ArrayDyn& other) {
        if (this != &other) {
            ArrayDyn tmp(other);
            swap(tmp);
        }
        return *this;
    }

    ~ArrayDyn() { delete[] m_data; }

    // Optionnel : move (bonus — non demandé, mais propre)
    ArrayDyn(ArrayDyn&& other) noexcept
        : m_data(other.m_data), m_size(other.m_size), m_capacity(other.m_capacity) {
        other.m_data = nullptr; other.m_size = 0; other.m_capacity = 0;
    }

    ArrayDyn& operator=(ArrayDyn&& other) noexcept {
        if (this != &other) {
            delete[] m_data;
            m_data = other.m_data;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            other.m_data = nullptr; other.m_size = 0; other.m_capacity = 0;
        }
        return *this;
    }

    // ============================================================
    // Interface publique
    // ============================================================
    void push_back(const T& value) {
        if (m_size == m_capacity) grow();
        m_data[m_size++] = value;
    }

    void pop_back() {
        if (m_size == 0)
            throw std::out_of_range("ArrayDyn::pop_back : conteneur vide");
        --m_size;
    }

    T& operator[](std::size_t index) {
        if (index >= m_size)
            throw std::out_of_range("ArrayDyn::operator[] : indice hors bornes");
        return m_data[index];
    }

    const T& operator[](std::size_t index) const {
        if (index >= m_size)
            throw std::out_of_range("ArrayDyn::operator[] : indice hors bornes");
        return m_data[index];
    }

    std::size_t size()     const noexcept { return m_size; }
    std::size_t capacity() const noexcept { return m_capacity; }
    bool        empty()    const noexcept { return m_size == 0; }

    // Itérateurs
    Iterator begin() noexcept             { return Iterator(m_data); }
    Iterator end()   noexcept             { return Iterator(m_data + m_size); }
    Iterator begin() const noexcept       { return Iterator(m_data); }
    Iterator end()   const noexcept       { return Iterator(m_data + m_size); }

private:

    T*          m_data;
    std::size_t m_size;
    std::size_t m_capacity;


    void grow() {
        std::size_t newCap = (m_capacity == 0) ? 4 : m_capacity * 2;
        T* newData = new T[newCap];
        for (std::size_t i = 0; i < m_size; ++i)
            newData[i] = m_data[i];
        delete[] m_data;
        m_data = newData;
        m_capacity = newCap;
    }

    void swap(ArrayDyn& other) noexcept {
        std::swap(m_data,     other.m_data);
        std::swap(m_size,     other.m_size);
        std::swap(m_capacity, other.m_capacity);
    }
};

#endif