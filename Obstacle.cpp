#include "Obstacle.h"
#include <SDL_image.h>
#include <stdexcept>

Obstacle::Obstacle(const std::string& imagePath, int x, int y, int w, int h)
    : texture(nullptr), rect{ x, y, w, h }, type(imagePath) {
}
// Initialise l�obstacle avec sa position (x, y), sa taille (w, h), 
// et le chemin de l�image (imagePath).
// La texture sera charg�e plus tard avec loadTexture().


Obstacle::~Obstacle() {
    SDL_DestroyTexture(texture);
}
// Lib�re la m�moire occup�e par la texture de l�obstacle.
// Important pour �viter les fuites m�moire.


void Obstacle::loadTexture(SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(type.c_str()); // Charge l�image � partir du chemin contenu dans type
    if (!surface) throw std::runtime_error("Erreur chargement : " + type); // Gestion d�erreur si l�image est introuvable

    texture = SDL_CreateTextureFromSurface(renderer, surface); // Cr�ation de la texture
    SDL_FreeSurface(surface); // Lib�re la surface temporaire
}


void Obstacle::update() {
    rect.x -= 5; // L�obstacle se d�place vers la gauche de 5 pixels � chaque frame
}
// Cela cr�e l�effet de "d�filement" vers le joueur.


void Obstacle::render(SDL_Renderer* renderer) const {
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
// Affiche l�obstacle � l��cran avec sa texture, aux coordonn�es sp�cifi�es par rect


SDL_Rect Obstacle::getRect() const {
    return rect;
}
// Permet d'acc�der � la position et taille de l�obstacle (utile pour les collisions)


std::string Obstacle::getType() const {
    return type;
}
// Renvoie le type (ex: "image/barriere.png") pour identifier l'obstacle

bool Obstacle::operator==(const Obstacle& other) const {
    return rect.x == other.rect.x && rect.y == other.rect.y;
}
// Permet de comparer si deux obstacles sont � la m�me position
// (utile si tu veux �viter les doublons dans une liste, par exemple)
