#ifndef GAME_H
#define GAME_H

// Inclusion des biblioth�ques n�cessaires
#include <SDL.h>          // Biblioth�que principale de SDL pour g�rer la fen�tre, les �v�nements, le rendu...
#include <SDL_image.h>    // Pour charger les images (PNG, JPG, etc.)
#include <SDL_ttf.h>      // Pour afficher du texte avec des polices
#include <vector>         // Pour stocker dynamiquement une liste d'obstacles
#include <string>         // Pour manipuler des cha�nes de caract�res

// Inclusion de tes classes personnalis�es
#include "Player.h"       // Classe repr�sentant le joueur
#include "Obstacle.h"     // Classe repr�sentant un obstacle
#include "Timer.h"        // Classe pour la gestion du temps dans le jeu

// D�claration de la classe principale Game
class Game {
public:
    Game();              // Constructeur : pr�pare les valeurs initiales
    ~Game();             // Destructeur : lib�re la m�moire

    // M�thodes principales du cycle de vie du jeu
    bool init();         // Initialise SDL, la fen�tre, les images, la police, etc.
    void run();          // Boucle principale du jeu (�v�nements -> mise � jour -> rendu)
    void clean();        // Nettoie toutes les ressources utilis�es (textures, fen�tres, etc.)

private:
    // Pointeurs SDL pour la fen�tre et le rendu graphique
    SDL_Window* window;          // Fen�tre de jeu
    SDL_Renderer* renderer;      // Rendu graphique

    // Police utilis�e pour afficher du texte
    TTF_Font* font;

    // Textures pour les diff�rentes images utilis�es
    SDL_Texture* background;     // Image de fond (background)
    SDL_Texture* gameOverImage;  // Image affich�e � la fin quand on perd
    SDL_Texture* victoryImage;   // Image affich�e quand on gagne

    // Joueur principal du jeu
    Player player;

    // Liste dynamique d�obstacles (pointeurs pour plus de flexibilit�)
    std::vector<Obstacle*> obstacles;

    // Ligne d�arriv�e pour d�tecter si le joueur a gagn�
    Obstacle* finishLine;

    // Timer pour g�rer le temps qui passe dans le jeu
    Timer timer;

    int score;  // Score du joueur
    float scrollSpeed;

    // D�calage horizontal du fond pour cr�er un effet de d�filement
    int bgOffsetX;

    // Bool�ens pour savoir si le joueur a perdu ou gagn�
    bool gameOver;
    bool gameWon;

    // Zones cliquables pour les boutons (utilis�s sur l��cran Game Over / Victoire)
    SDL_Rect retryButton;   // Bouton "Rejouer"
    SDL_Rect quitButton;    // Bouton "Quitter"

    // M�thodes priv�es internes � la logique du jeu :

    // Charge une image et la convertit en texture SDL
    SDL_Texture* loadTexture(const std::string& path);

    // G�re les �v�nements clavier/souris (d�placement, clic, etc.)
    void handleEvents(bool& running);

    // Met � jour la logique du jeu : position du joueur, collision, score, etc.
    void update();

    // Affiche tout � l��cran : fond, joueur, obstacles, texte, boutons...
    void render();

    // Cr�e dynamiquement un nouvel obstacle et l�ajoute � la liste
    void generateObstacle();

    // Affiche les boutons "Rejouer" et "Quitter" sur l��cran de fin
    void renderButtons();
};

#endif
