#ifndef GAME_H
#define GAME_H

// Inclusion des bibliothèques nécessaires
#include <SDL.h>          // Bibliothèque principale de SDL pour gérer la fenêtre, les événements, le rendu...
#include <SDL_image.h>    // Pour charger les images (PNG, JPG, etc.)
#include <SDL_ttf.h>      // Pour afficher du texte avec des polices
#include <vector>         // Pour stocker dynamiquement une liste d'obstacles
#include <string>         // Pour manipuler des chaînes de caractères

// Inclusion de tes classes personnalisées
#include "Player.h"       // Classe représentant le joueur
#include "Obstacle.h"     // Classe représentant un obstacle
#include "Timer.h"        // Classe pour la gestion du temps dans le jeu

// Déclaration de la classe principale Game
class Game {
public:
    Game();              // Constructeur : prépare les valeurs initiales
    ~Game();             // Destructeur : libère la mémoire

    // Méthodes principales du cycle de vie du jeu
    bool init();         // Initialise SDL, la fenêtre, les images, la police, etc.
    void run();          // Boucle principale du jeu (événements -> mise à jour -> rendu)
    void clean();        // Nettoie toutes les ressources utilisées (textures, fenêtres, etc.)

private:
    // Pointeurs SDL pour la fenêtre et le rendu graphique
    SDL_Window* window;          // Fenêtre de jeu
    SDL_Renderer* renderer;      // Rendu graphique

    // Police utilisée pour afficher du texte
    TTF_Font* font;

    // Textures pour les différentes images utilisées
    SDL_Texture* background;     // Image de fond (background)
    SDL_Texture* gameOverImage;  // Image affichée à la fin quand on perd
    SDL_Texture* victoryImage;   // Image affichée quand on gagne

    // Joueur principal du jeu
    Player player;

    // Liste dynamique d’obstacles (pointeurs pour plus de flexibilité)
    std::vector<Obstacle*> obstacles;

    // Ligne d’arrivée pour détecter si le joueur a gagné
    Obstacle* finishLine;

    // Timer pour gérer le temps qui passe dans le jeu
    Timer timer;

    int score;  // Score du joueur
    float scrollSpeed;

    // Décalage horizontal du fond pour créer un effet de défilement
    int bgOffsetX;

    // Booléens pour savoir si le joueur a perdu ou gagné
    bool gameOver;
    bool gameWon;

    // Zones cliquables pour les boutons (utilisés sur l’écran Game Over / Victoire)
    SDL_Rect retryButton;   // Bouton "Rejouer"
    SDL_Rect quitButton;    // Bouton "Quitter"

    // Méthodes privées internes à la logique du jeu :

    // Charge une image et la convertit en texture SDL
    SDL_Texture* loadTexture(const std::string& path);

    // Gère les événements clavier/souris (déplacement, clic, etc.)
    void handleEvents(bool& running);

    // Met à jour la logique du jeu : position du joueur, collision, score, etc.
    void update();

    // Affiche tout à l’écran : fond, joueur, obstacles, texte, boutons...
    void render();

    // Crée dynamiquement un nouvel obstacle et l’ajoute à la liste
    void generateObstacle();

    // Affiche les boutons "Rejouer" et "Quitter" sur l’écran de fin
    void renderButtons();
};

#endif
