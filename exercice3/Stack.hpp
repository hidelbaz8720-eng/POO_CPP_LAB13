#ifndef STACK_HPP
#define STACK_HPP

#include <memory>
#include <cstddef>
#include <stdexcept>
#include <utility>
#include <string>

// ============================================================
// Exceptions spécifiques
// ============================================================
class StackOverflow : public std::runtime_error {
public:
    explicit StackOverflow(const std::string& msg = "Stack overflow : capacité maximale atteinte")
        : std::runtime_error(msg) {}
};

class StackUnderflow : public std::runtime_error {
public:
    explicit StackUnderflow(const std::string& msg = "Stack underflow : la pile est vide")
        : std::runtime_error(msg) {}
};

// ============================================================
// Pile générique
// ============================================================
template <typename T>
class Stack {
public:
    static constexpr std::size_t DEFAULT_CAPACITY = 64;

private:
    std::size_t capacity;
    std::size_t top;
    std::unique_ptr<T[]> data;

public:
    // Constructeur par défaut
    explicit Stack(std::size_t cap = DEFAULT_CAPACITY)
        : capacity(cap), top(0), data(std::make_unique<T[]>(cap)) {
        if (cap == 0)
            throw std::invalid_argument("Stack : capacité nulle interdite");
    }

    // Constructeur à partir d'une collection [first, last)
    template <typename InputIt>
    Stack(InputIt first, InputIt last, std::size_t cap = DEFAULT_CAPACITY)
        : capacity(cap), top(0), data(std::make_unique<T[]>(cap)) {
        if (cap == 0)
            throw std::invalid_argument("Stack : capacité nulle interdite");
        for (auto it = first; it != last; ++it)
            push(*it);   // lève StackOverflow si la collection est trop grande
    }

    // Règle des 5 : unique_ptr gère seul la mémoire → copie interdite,
    // déplacement possible
    Stack(const Stack&)            = delete;
    Stack& operator=(const Stack&) = delete;
    Stack(Stack&&) noexcept        = default;
    Stack& operator=(Stack&&) noexcept = default;
    ~Stack() = default;

    // ----------------------------------------------------------
    // Opérations
    // ----------------------------------------------------------
    void push(const T& value) {
        if (top >= capacity) throw StackOverflow();
        data[top++] = value;
    }

    void push(T&& value) {
        if (top >= capacity) throw StackOverflow();
        data[top++] = std::move(value);
    }

    T pop() {
        if (top == 0) throw StackUnderflow();
        return std::move(data[--top]);
    }

    const T& peek() const {
        if (top == 0) throw StackUnderflow();
        return data[top - 1];
    }

    bool empty() const noexcept { return top == 0; }
    std::size_t size() const noexcept { return top; }
    std::size_t getCapacity() const noexcept { return capacity; }
};

#endif