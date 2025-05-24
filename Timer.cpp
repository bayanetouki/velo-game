#include "Timer.h"

// Constructeur : initialise la dur�e et d�marre le chrono
Timer::Timer(int secondes) : duration(secondes) {
    // On r�cup�re le temps actuel (en millisecondes depuis le lancement de SDL)
    startTime = SDL_GetTicks();
}

// R�initialise le chrono en red�marrant � partir de maintenant
void Timer::reset() {
    startTime = SDL_GetTicks(); // R�enregistre l�heure actuelle
}

// Calcule et retourne le nombre de secondes restantes
int Timer::getRemainingTime() const {
    // Temps �coul� = diff�rence entre maintenant et le moment o� le chrono a commenc�
    Uint32 elapsed = (SDL_GetTicks() - startTime) / 1000; // Converti en secondes

    // Temps restant = dur�e totale - temps �coul�
    int remaining = duration - elapsed;

    // Si le temps est n�gatif (chrono termin�), on retourne 0
    return (remaining > 0) ? remaining : 0;
}

// Affiche le temps restant � l��cran en haut � gauche
void Timer::render(SDL_Renderer* renderer, TTF_Font* font) {
    // R�cup�re le temps restant
    int timeLeft = getRemainingTime();

    // Cr�e un texte dynamique avec le nombre de secondes restantes
    std::stringstream ss;
    ss << "Temps restant : " << timeLeft << "s";

    // D�finition de la couleur du texte (blanc)
    SDL_Color white = { 255, 255, 255 };

    // Rend le texte avec la police TTF
    SDL_Surface* surface = TTF_RenderText_Blended(font, ss.str().c_str(), white);

    // Convertit la surface texte en texture pour l�afficher avec SDL_Renderer
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    // Position du texte � l��cran (coin sup�rieur gauche)
    SDL_Rect rect = { 10, 10, surface->w, surface->h };

    // Affiche le texte � l��cran
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    // Nettoyage : lib�re la m�moire utilis�e
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
