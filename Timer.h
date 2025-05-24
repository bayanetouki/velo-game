#ifndef TIMER_H
#define TIMER_H
#include <SDL.h>
#include <SDL_ttf.h>

// Bibliothèques pour manipuler du texte
#include <string>      // Pour les chaînes de caractères
#include <sstream>     // Pour convertir un int en string (utile pour afficher le chrono)

// Définition de la classe Timer qui gère un minuteur simple
class Timer {
private:
    Uint32 startTime; // Temps de départ du chrono (en millisecondes depuis le lancement du programme)
    int duration;     // Durée totale du jeu ou du chrono (en secondes)

public:
    // Constructeur : on peut définir une durée personnalisée (60s par défaut)
    Timer(int secondes = 60);

    // Redémarre le chrono depuis maintenant
    void reset();

    // Retourne le nombre de secondes restantes avant la fin
    int getRemainingTime() const;

    // Affiche le temps restant à l'écran avec une police TTF
    void render(SDL_Renderer* renderer, TTF_Font* font);
};

#endif // TIMER_H
