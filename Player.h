#ifndef PLAYER_H
#define PLAYER_H

// Inclusion de la biblioth�que SDL pour utiliser SDL_Texture, SDL_Rect, etc.
#include <SDL.h>

// Inclusion du fichier de constantes (dimensions du joueur, sol, etc.)
#include "Constantes.h"

// D�claration anticip�e de la classe Obstacle
// Cela �vite d'inclure Obstacle.h ici, ce qui limite les d�pendances circulaires
class Obstacle;

// D�finition de la classe Player qui repr�sente le joueur (cycliste)
class Player {
public:
    // Constructeur : initialise les valeurs de base
    Player();

    // Destructeur : lib�re la texture charg�e
    ~Player();

    // Initialise la texture du joueur et sa position de d�part
    void init(SDL_Renderer* renderer);

    // G�re les entr�es clavier, notamment pour d�clencher le saut
    void handleInput();

    // Met � jour la position verticale du joueur (effet de gravit� et saut)
    void update();

    // Affiche le joueur � l��cran avec sa texture actuelle
    void render(SDL_Renderer* renderer);

    // R�initialise le joueur � sa position et son �tat d�origine (utilis� apr�s un Game Over ou quand on rejoue)
    void reset();

    // V�rifie si le joueur entre en collision avec un obstacle
    bool collidesWith(const Obstacle& obs) const;

private:
    // Texture du joueur (image charg�e depuis un fichier)
    SDL_Texture* texture;

    // Rectangle de position et taille du joueur (x, y, w, h)
    SDL_Rect rect;

    // Vitesse verticale du joueur (utilis�e pour le saut et la gravit�)
    float velocityY;

    // Bool�en pour savoir si le joueur est actuellement en train de sauter
    bool isJumping;
};

#endif // PLAYER_H
