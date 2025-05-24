#include "Timer.h"

// Constructeur : initialise la durée et démarre le chrono
Timer::Timer(int secondes) : duration(secondes) {
    // On récupère le temps actuel (en millisecondes depuis le lancement de SDL)
    startTime = SDL_GetTicks();
}

// Réinitialise le chrono en redémarrant à partir de maintenant
void Timer::reset() {
    startTime = SDL_GetTicks(); // Réenregistre l’heure actuelle
}

// Calcule et retourne le nombre de secondes restantes
int Timer::getRemainingTime() const {
    // Temps écoulé = différence entre maintenant et le moment où le chrono a commencé
    Uint32 elapsed = (SDL_GetTicks() - startTime) / 1000; // Converti en secondes

    // Temps restant = durée totale - temps écoulé
    int remaining = duration - elapsed;

    // Si le temps est négatif (chrono terminé), on retourne 0
    return (remaining > 0) ? remaining : 0;
}

// Affiche le temps restant à l’écran en haut à gauche
void Timer::render(SDL_Renderer* renderer, TTF_Font* font) {
    // Récupère le temps restant
    int timeLeft = getRemainingTime();

    // Crée un texte dynamique avec le nombre de secondes restantes
    std::stringstream ss;
    ss << "Temps restant : " << timeLeft << "s";

    // Définition de la couleur du texte (blanc)
    SDL_Color white = { 255, 255, 255 };

    // Rend le texte avec la police TTF
    SDL_Surface* surface = TTF_RenderText_Blended(font, ss.str().c_str(), white);

    // Convertit la surface texte en texture pour l’afficher avec SDL_Renderer
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    // Position du texte à l’écran (coin supérieur gauche)
    SDL_Rect rect = { 10, 10, surface->w, surface->h };

    // Affiche le texte à l’écran
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    // Nettoyage : libère la mémoire utilisée
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
