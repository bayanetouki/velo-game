#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SDL.h>
#include <string>
#include "Constantes.h"

class Obstacle {
protected:
    SDL_Texture* texture;   // Texture de l'obstacle (image � afficher)
    SDL_Rect rect;          // Rectangle de position (x, y, w, h) sur l��cran
    std::string type;       // Type d�obstacle ("caillou", "barriere", etc.)


public:
public:
    // Constructeur : initialise l�image, la position et la taille de l�obstacle
    Obstacle(const std::string& imagePath, int x, int y, int w, int h);

    // Destructeur : lib�re la m�moire (la texture)
    virtual ~Obstacle();


    // Charge la texture (image) de l�obstacle
    virtual void loadTexture(SDL_Renderer* renderer);

    // Met � jour la position de l�obstacle (ex: le faire avancer vers la gauche)
    virtual void update();

    // Affiche l�obstacle � l��cran
    virtual void render(SDL_Renderer* renderer) const;

    // Retourne la position et taille de l�obstacle
    virtual SDL_Rect getRect() const;

    // Retourne le type d�obstacle
    virtual std::string getType() const;


    // V�rifie si deux obstacles sont identiques (utile pour les comparaisons)
    bool operator==(const Obstacle& other) const;

};

#endif

