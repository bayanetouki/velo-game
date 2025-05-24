#include "Obstacle.h"
#include <SDL_image.h>
#include <stdexcept>

Obstacle::Obstacle(const std::string& imagePath, int x, int y, int w, int h)
    : texture(nullptr), rect{ x, y, w, h }, type(imagePath) {
}
// Initialise l’obstacle avec sa position (x, y), sa taille (w, h), 
// et le chemin de l’image (imagePath).
// La texture sera chargée plus tard avec loadTexture().


Obstacle::~Obstacle() {
    SDL_DestroyTexture(texture);
}
// Libère la mémoire occupée par la texture de l’obstacle.
// Important pour éviter les fuites mémoire.


void Obstacle::loadTexture(SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(type.c_str()); // Charge l’image à partir du chemin contenu dans type
    if (!surface) throw std::runtime_error("Erreur chargement : " + type); // Gestion d’erreur si l’image est introuvable

    texture = SDL_CreateTextureFromSurface(renderer, surface); // Création de la texture
    SDL_FreeSurface(surface); // Libère la surface temporaire
}


void Obstacle::update() {
    rect.x -= 5; // L’obstacle se déplace vers la gauche de 5 pixels à chaque frame
}
// Cela crée l’effet de "défilement" vers le joueur.


void Obstacle::render(SDL_Renderer* renderer) const {
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
// Affiche l’obstacle à l’écran avec sa texture, aux coordonnées spécifiées par rect


SDL_Rect Obstacle::getRect() const {
    return rect;
}
// Permet d'accéder à la position et taille de l’obstacle (utile pour les collisions)


std::string Obstacle::getType() const {
    return type;
}
// Renvoie le type (ex: "image/barriere.png") pour identifier l'obstacle

bool Obstacle::operator==(const Obstacle& other) const {
    return rect.x == other.rect.x && rect.y == other.rect.y;
}
// Permet de comparer si deux obstacles sont à la même position
// (utile si tu veux éviter les doublons dans une liste, par exemple)
