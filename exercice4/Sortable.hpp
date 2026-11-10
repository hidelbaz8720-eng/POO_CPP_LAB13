#ifndef SORTABLE_HPP
#define SORTABLE_HPP

#include <vector>
#include <functional>
#include <type_traits>
#include <utility>
#include <cstddef>

// ============================================================
// Trait "Sortable" : équivalent du concept C++20
// Vérifie que "a < b" existe et renvoie quelque chose de
// convertible en bool.
// ============================================================
template <typename T, typename = void>
struct is_sortable : std::false_type {};

template <typename T>
struct is_sortable<T,
    typename std::enable_if<
        std::is_convertible<
            decltype(std::declval<const T&>() < std::declval<const T&>()),
            bool
        >::value
    >::type
> : std::true_type {};

// ============================================================
// Trait "Comparator" : vérifie que comp(a, b) -> bool
// ============================================================
template <typename Comp, typename T, typename = void>
struct is_comparator : std::false_type {};

template <typename Comp, typename T>
struct is_comparator<Comp, T,
    typename std::enable_if<
        std::is_convertible<
            decltype(std::declval<Comp>()(
                std::declval<const T&>(),
                std::declval<const T&>()
            )),
            bool
        >::value
    >::type
> : std::true_type {};

// ============================================================
// Foncteurs prédéfinis (identiques — compatibles C++11)
// ============================================================
struct Asc {
    template <typename T>
    bool operator()(const T& a, const T& b) const { return a < b; }
};

struct Desc {
    template <typename T>
    bool operator()(const T& a, const T& b) const { return a > b; }
};

// ============================================================
// quickSort générique
// ============================================================
namespace detail {

template <typename T, typename Comp>
std::size_t partition(std::vector<T>& v, std::size_t lo, std::size_t hi, Comp comp) {
    const T pivot = v[hi];
    std::size_t i = lo;
    for (std::size_t j = lo; j < hi; ++j) {
        if (comp(v[j], pivot)) {
            std::swap(v[i], v[j]);
            ++i;
        }
    }
    std::swap(v[i], v[hi]);
    return i;
}

template <typename T, typename Comp>
void quickSortImpl(std::vector<T>& v, std::size_t lo, std::size_t hi, Comp comp) {
    if (lo >= hi) return;
    std::size_t p = partition(v, lo, hi, comp);
    if (p > 0)       quickSortImpl(v, lo, p - 1, comp);
    if (p + 1 <= hi) quickSortImpl(v, p + 1, hi, comp);
}

} // namespace detail

// ------------------------------------------------------------
// Version "par défaut" : quickSort(v)  ->  std::less<T>
// ------------------------------------------------------------
template <typename T>
void quickSort(std::vector<T>& v, std::less<T> comp = std::less<T>{}) {
    static_assert(is_sortable<T>::value,
        "quickSort : T doit definir operator< renvoyant un bool");
    if (v.size() < 2) return;
    detail::quickSortImpl(v, 0, v.size() - 1, comp);
}

// ------------------------------------------------------------
// Version "avec comparateur personnalisé"
// ------------------------------------------------------------
template <typename T, typename Comp>
void quickSortComp(std::vector<T>& v, Comp comp) {
    static_assert(is_sortable<T>::value,
        "quickSort : T doit definir operator<");
    static_assert(is_comparator<Comp, T>::value,
        "quickSort : Comp doit etre appelable comme comp(a, b) -> bool");
    if (v.size() < 2) return;
    detail::quickSortImpl(v, 0, v.size() - 1, comp);
}

#endif