# 🚴 Vélo Game – Jeu de course en C++ / SDL2

## 🎯 Introduction

Ce projet a été réalisé dans le cadre du module de Programmation Orientée Objet (POO). L’objectif était de mettre en œuvre les concepts clés de la POO en C++ à travers le développement d’un jeu interactif utilisant la bibliothèque SDL2.

Nous avons mobilisé des notions telles que :
- Conception en classes, héritage, polymorphisme
- Fonctions amies, templates, exceptions
- Utilisation de la STL
- Structuration modulaire du code

Ce jeu a été également une opportunité de renforcer nos compétences en travail d’équipe, planification et résolution de problèmes.

---

## 🧠 Conception et modélisation

### 📌 Schéma de classes (UML)

- `Game` est la classe principale, orchestrant l’ensemble du jeu.
- `Player`, `Obstacle`, `Timer`, `Menu`, et `Constantes` sont des composants utilisés par `Game`.
- `Game` possède un `Timer` (composition).
- Les autres classes sont utilisées via des associations simples.

---

## 🧩 Description des classes

### `Game`
- Gère la logique du jeu : `init()`, `run()`, `render()`, `handleEvents()`, etc.
- Gère les boutons de fin avec `renderButtons()`.

### `Player`
- Représente le cycliste.
- Méthodes : `handleInput()`, `update()`, `render()`, `collidesWith()`...

### `Obstacle`
- Représente des obstacles sur la route.
- Méthodes : `update()`, `render()`, `getType()`...

### `Timer`
- Gère le compte à rebours.
- Méthodes : `reset()`, `getRemainingTime()`, `render()`

### `Menu`
- Affiche l’écran d’accueil, les boutons, et la page À propos.

### `Constantes.h`
- Contient les valeurs de configuration globales (dimensions, vitesses, chemins...).

---

## ⚙️ Environnement de travail

### 🧰 Microsoft Visual Studio
- IDE principal utilisé.
- Supporte bien C++ et SDL2.
- Gestion efficace des projets complexes.

### 🎮 SDL2
- Bibliothèque multimédia pour l’affichage graphique, les événements clavier/souris, etc.
- Open source, multiplateforme, très utilisée pour les jeux.

---

## 🛠️ Implémentation

Le projet est découpé en plusieurs fichiers :
- `main.cpp`, `Game.cpp/.h`, `Player.cpp/.h`, `Obstacle.cpp/.h`, `Timer.cpp/.h`, `Menu.cpp/.h`, `Constantes.h`

### 🔁 Fonctionnement
- **Initialisation** : chargement des images, polices, textures
- **Boucle principale** : événements → mise à jour → rendu
- **Obstacles** : générés dynamiquement, certains fatals, d’autres ralentissants
- **Joueur** : peut sauter, collisions détectées

---

## 🖥️ Interfaces du jeu

### 🎮 Écran principal
- Joueur, obstacles, fond animé, chrono, victoire/défaite

### ❌ Écran Game Over / Victoire
- Image + boutons `Rejouer` et `Quitter`

### 🏠 Menu principal
- Boutons : `Jouer`, `À propos`, `Quitter` avec survol

### ℹ️ Page À propos
- Règles du jeu, touches, conseils

---

## 💣 Obstacles

- Obstacles fatals, générés dynamiquement
- Collision → `Game Over` immédiat

---

## ✅ Conclusion

Ce projet nous a permis de :
- Consolider nos acquis en C++
- Gérer un projet de bout en bout
- Résoudre des défis concrets en autonomie
- Collaborer efficacement et structurer notre travail

C’est une étape importante dans notre parcours, et un tremplin vers d'autres projets professionnels ou personnels.
