#ifndef TIMER_H
#define TIMER_H
#include <SDL.h>
#include <SDL_ttf.h>

// Biblioth�ques pour manipuler du texte
#include <string>      // Pour les cha�nes de caract�res
#include <sstream>     // Pour convertir un int en string (utile pour afficher le chrono)

// D�finition de la classe Timer qui g�re un minuteur simple
class Timer {
private:
    Uint32 startTime; // Temps de d�part du chrono (en millisecondes depuis le lancement du programme)
    int duration;     // Dur�e totale du jeu ou du chrono (en secondes)

public:
    // Constructeur : on peut d�finir une dur�e personnalis�e (60s par d�faut)
    Timer(int secondes = 60);

    // Red�marre le chrono depuis maintenant
    void reset();

    // Retourne le nombre de secondes restantes avant la fin
    int getRemainingTime() const;

    // Affiche le temps restant � l'�cran avec une police TTF
    void render(SDL_Renderer* renderer, TTF_Font* font);
};

#endif // TIMER_H
