# TP 13 — Templates et généricité (C++)

> **Cours** : Programmation orientée objet : C++  
> **Plateforme** : MLIAEdu  
> **Auteur** : HAMZA ID EL BAZ  
> **Progression** : 100 % — 4/4 exercices complétés

---

##  Objectifs

| Objectif | Exercice |
|---|---|
| Concevoir un conteneur maison avec itérateur personnalisé | Ex. 1 |
| Templates à paramètres multiples + spécialisation partielle | Ex. 2 |
| Combiner templates et `std::unique_ptr` | Ex. 3 |
| Concepts C++20 pour restreindre les templates | Ex. 4 |

---

## Exercice 1 — Conteneur dynamique générique (`ArrayDyn<T>`)

**Fonctionnalités** : constructeurs (défaut, capacité, copie), `push_back`, `pop_back`, `operator[]` avec contrôle de bornes, itérateur bidirectionnel (`*`, `++`, `--`, `!=`), `begin()`/`end()`, règle des trois, compatibilité `range-based for`.

**Test** : `ArrayDyn<int>`, `ArrayDyn<std::string>`, `ArrayDyn<Point>` + parcours avant/arrière.

###  Capture — Exécution exercice 1
<img width="1366" height="768" alt="image1" src="https://github.com/user-attachments/assets/71fc239d-15f3-4f2e-8e3d-28f271452ef7" />




##  Exercice 2 — Matrice générique (`Matrice<T, N, M>`)

**Fonctionnalités** : constructeur par défaut (init à 0), constructeur `initializer_list`, `operator+`, `operator-`, `operator*` générique (`Matrice<T,N,M> * Matrice<T,M,P> → Matrice<T,N,P>`), `operator<<` (ami), spécialisation `bool` (produit logique OU-de-ET), `operator()`.

**Test** : matrices `int` 3×3, produit 2×3 × 3×2, matrices `double` 2×2, matrices `bool` 2×2.

###  Capture — Exécution exercice 2
<img width="1366" height="768" alt="ex2_1" src="https://github.com/user-attachments/assets/ec5e1c31-61ea-46a0-bb9b-6fd4091e24e6" />
<img width="1366" height="768" alt="ex2_2" src="https://github.com/user-attachments/assets/de07a562-bb17-40e9-8d78-c0055088a62c" />



##  Exercice 3 — Pile générique sécurisée (`Stack<T>`)

**Fonctionnalités** : `std::unique_ptr<T[]>` pour la mémoire, attributs `capacity`/`top`, `push`, `pop`, `peek`, `empty`, exceptions `StackOverflow`/`StackUnderflow`, constructeur `(begin, end)`, règle des cinq (copy deleted, move enabled).

**Test** : int, string, liste, stress-test 100 000 objets avec compteur d'instances, vérification **0 fuite mémoire**.

### Capture — Exécution exercice 3
<img width="1366" height="768" alt="ex3" src="https://github.com/user-attachments/assets/7f32c600-5064-4c9a-a746-a4a4baff4c0a" />




## Exercice 4 — `quickSort` avec contraintes (`Sortable`, `Comparator`)

**Fonctionnalités** : concept/trait `Sortable`, concept/trait `Comparator`, foncteurs `Asc`/`Desc`, `quickSort` (algorithme de Lomuto), variante avec comparateur personnalisé, tests unitaires automatisés.

**Double version fournie** :
- `Sortable.hpp` — **C++20** (concepts natifs) → GCC ≥ 10
- `Sortable_cpp14.hpp` — **C++14** (SFINAE + `static_assert`) → compatible **GCC 6.3**

**Test** : `vector<int>`, `vector<string>`, `vector<Personne>` (avec `operator<` et lambda par nom), cas limites (vide, 1 élément, égaux, déjà trié) → **9 OK / 0 KO**.


> **Emplacement réservé** — remplacer par :
> ```markdown
> ![Ex4 - C++14](docs/captures/ex4_cpp14.png)
> ```
> *(Capture : compilation et exécution avec `-std=c++14` réussies)*

---

## Compilation rapide (récapitulatif)

```bash
# Exercices 1, 2, 3 (C++20)
g++ -std=c++20 -Wall -Wextra main.cpp -o exN && ./exN

# Exercice 3 avec sanitizers
g++ -std=c++20 -Wall -Wextra -fsanitize=address,undefined main.cpp -o ex3 && ./ex3

# Exercice 4 (C++20, GCC >= 10)
g++ -std=c++20 -Wall -Wextra main.cpp -o ex4 && ./ex4

# Exercice 4 (C++14, GCC 6.3 compatible)
g++ -std=c++14 -Wall -Wextra main.cpp -o ex4 && ./ex4
