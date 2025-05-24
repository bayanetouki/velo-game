#ifndef PLAYER_H
#define PLAYER_H

// Inclusion de la bibliothèque SDL pour utiliser SDL_Texture, SDL_Rect, etc.
#include <SDL.h>

// Inclusion du fichier de constantes (dimensions du joueur, sol, etc.)
#include "Constantes.h"

// Déclaration anticipée de la classe Obstacle
// Cela évite d'inclure Obstacle.h ici, ce qui limite les dépendances circulaires
class Obstacle;

// Définition de la classe Player qui représente le joueur (cycliste)
class Player {
public:
    // Constructeur : initialise les valeurs de base
    Player();

    // Destructeur : libère la texture chargée
    ~Player();

    // Initialise la texture du joueur et sa position de départ
    void init(SDL_Renderer* renderer);

    // Gère les entrées clavier, notamment pour déclencher le saut
    void handleInput();

    // Met à jour la position verticale du joueur (effet de gravité et saut)
    void update();

    // Affiche le joueur à l’écran avec sa texture actuelle
    void render(SDL_Renderer* renderer);

    // Réinitialise le joueur à sa position et son état d’origine (utilisé après un Game Over ou quand on rejoue)
    void reset();

    // Vérifie si le joueur entre en collision avec un obstacle
    bool collidesWith(const Obstacle& obs) const;

private:
    // Texture du joueur (image chargée depuis un fichier)
    SDL_Texture* texture;

    // Rectangle de position et taille du joueur (x, y, w, h)
    SDL_Rect rect;

    // Vitesse verticale du joueur (utilisée pour le saut et la gravité)
    float velocityY;

    // Booléen pour savoir si le joueur est actuellement en train de sauter
    bool isJumping;
};

#endif // PLAYER_H
