#include "Game.h"
#include <iostream>
#include <sstream>
#include <ctime>

// Constructeur : initialise tous les pointeurs et variables du jeu
Game::Game()
    : window(nullptr),
    renderer(nullptr),
    font(nullptr),
    background(nullptr),
    gameOverImage(nullptr),
    victoryImage(nullptr),
    gameOver(false),
    gameWon(false),
    retryButton{ 250, 500, 100, 40 },  // Position et taille du bouton "Rejouer"
    quitButton{ 450, 500, 100, 40 },   // Position et taille du bouton "Quitter"
    finishLine(nullptr),
    bgOffsetX(0),// Position du fond pour le défilement horizontal
    score(0),
    scrollSpeed(2.0f)

{
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Initialisation du générateur aléatoire
}

// Destructeur : libère les ressources
Game::~Game() {
    clean();
}
// Initialisation de SDL, de la fenêtre, du rendu, des images et de la police

bool Game::init() {
    // Initialisation de SDL (vidéo)
    if (SDL_Init(SDL_INIT_VIDEO) != 0) return false;

    // Initialisation des images (PNG/JPG)
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0) return false;

    // Initialisation des polices TTF
    if (TTF_Init() != 0) return false;

    // Création de la fenêtre du jeu
    window = SDL_CreateWindow("Course a Velo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    if (!window) return false;

    // Création du moteur de rendu
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) return false;

    // Chargement de la police
    font = TTF_OpenFont("fonts/FreeSans.ttf", 24);
    if (!font) return false;

    // Chargement des images
    background = loadTexture("image/bg.jpg");
    gameOverImage = loadTexture("image/gameover.jpeg");
    victoryImage = loadTexture("image/win.jpg");

    if (!background || !gameOverImage || !victoryImage) return false;

    // Initialisation du joueur
    player.init(renderer);

    // Création de la ligne d'arrivée (obstacle spécial)
    finishLine = new Obstacle("image/win.png", 5500, 500, 80, 100);
    finishLine->loadTexture(renderer);

    return true;
}

// Boucle principale du jeu : gère les événements, met à jour la logique et affiche tout à l'écran
void Game::run() {
    bool running = true;
    while (running) {
        handleEvents(running); // Gestion des événements
        if (!gameOver && !gameWon) update(); // Mise à jour si le jeu est en cours
        render(); // Affichage
        if (timer.getRemainingTime() <= 0 && !gameWon) gameOver = true;
        SDL_Delay(16); // Pause (~60 FPS)
    }
}
// Gestion des événements : clics, touches, etc.
void Game::handleEvents(bool& running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) running = false;

        // Si on a perdu ou gagné et qu'on clique
        if ((gameOver || gameWon) && event.type == SDL_MOUSEBUTTONDOWN) {
            int x = event.button.x, y = event.button.y;
            // Si on clique sur "Rejouer"
            if (x >= retryButton.x && x <= retryButton.x + retryButton.w &&
                y >= retryButton.y && y <= retryButton.y + retryButton.h) {

                obstacles.clear();         // Supprime les obstacles
                player.reset();            // Réinitialise le joueur
                timer.reset();             // Réinitialise le chrono
                gameOver = false;
                gameWon = false;
                score = 0;                 // Remet le score à zéro
                scrollSpeed = 2.0f;        // Réinitialise la vitesse de fond

                // Supprime et recrée la ligne d’arrivée
                delete finishLine;
                finishLine = new Obstacle("image/win.png", 5500, GROUND_Y, 80, 100);
                finishLine->loadTexture(renderer);
            }

            // Si on clique sur "Quitter"
            if (x >= quitButton.x && x <= quitButton.x + quitButton.w && y >= quitButton.y && y <= quitButton.y + quitButton.h)
                running = false;
        }
    }

    // Gestion du clavier pour le joueur
    player.handleInput();
}
// Mise à jour de la logique du jeu

void Game::update() {
    // Défilement du fond
    bgOffsetX -= 2;
    if (bgOffsetX < -800) bgOffsetX = 0;

    player.update();

    // Mise à jour des obstacles et détection de collision
    for (auto& obs : obstacles) {
        obs->update();
        if (player.collidesWith(*obs)) {
            gameOver = true;
            return;
        }
    }

    // Si le joueur atteint la ligne d'arrivée
    if (player.collidesWith(*finishLine)) gameWon = true;

    // Génération de nouveaux obstacles si nécessaire
    if (obstacles.empty() || obstacles.back()->getRect().x < 500)
        generateObstacle();

    finishLine->update();

    score += 1;// Incrémentation du score
    bgOffsetX -= (int)scrollSpeed;

    if (SDL_GetTicks() % 10000 < 16 && scrollSpeed < 10.0f) {
        scrollSpeed += 0.5f; // augmente toutes les 10 secondes
    }

}
// Affichage de tout à l'écran

void Game::render() {
    SDL_RenderClear(renderer);

    // Affichage du fond défilant
    SDL_Rect bgRect1 = { bgOffsetX, 0, 800, 600 };
    SDL_Rect bgRect2 = { bgOffsetX + 800, 0, 800, 600 };
    SDL_RenderCopy(renderer, background, NULL, &bgRect1);
    SDL_RenderCopy(renderer, background, NULL, &bgRect2);

    // Affichage des obstacles
    for (auto& obs : obstacles) obs->render(renderer);

    // Ligne d'arrivée et joueur
    finishLine->render(renderer);
    player.render(renderer);


    // 🎨 Fond discret pour le score (à gauche)
    SDL_Rect scoreBox = { 20, 15, 150, 30 };
    SDL_SetRenderDrawColor(renderer, 204, 255, 255, 230); // Bleu très clair
    SDL_RenderFillRect(renderer, &scoreBox);

    // Affichage du score
    std::stringstream ssScore;
    ssScore << "Score: " << score;
    SDL_Color black = { 0, 0, 0 };
    SDL_Surface* scoreSurface = TTF_RenderText_Blended(font, ssScore.str().c_str(), black);
    if (scoreSurface) {
        SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
        SDL_Rect scoreRect = { 30, 20, scoreSurface->w, scoreSurface->h };
        SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
        SDL_FreeSurface(scoreSurface);
        SDL_DestroyTexture(scoreTexture);
    }

    // 🎨 Fond discret pour le temps restant (à droite)
    SDL_Rect timeBox = { 630, 15, 150, 30 };
    SDL_SetRenderDrawColor(renderer, 255, 255, 204, 230); // Jaune pâle
    SDL_RenderFillRect(renderer, &timeBox);

    // Affichage du temps
    std::stringstream ssTime;
    ssTime << "Temps: " << timer.getRemainingTime() << "s";
    SDL_Surface* timeSurface = TTF_RenderText_Blended(font, ssTime.str().c_str(), black);
    if (timeSurface) {
        SDL_Texture* timeTexture = SDL_CreateTextureFromSurface(renderer, timeSurface);
        SDL_Rect timeRect = { 640, 20, timeSurface->w, timeSurface->h };
        SDL_RenderCopy(renderer, timeTexture, NULL, &timeRect);
        SDL_FreeSurface(timeSurface);
        SDL_DestroyTexture(timeTexture);
    }


    // Affichage de l'image de fin si besoin
    if (gameOver) SDL_RenderCopy(renderer, gameOverImage, NULL, NULL);
    else if (gameWon) SDL_RenderCopy(renderer, victoryImage, NULL, NULL);

    // Affichage des boutons si le jeu est terminé
    if (gameOver || gameWon) renderButtons();

    SDL_RenderPresent(renderer); // Mise à jour de l’écran
}

// Génération d'un nouvel obstacle aléatoire
void Game::generateObstacle() {
    std::string type = (std::rand() % 2 == 0) ? "caillou" : "barriere";
    int x = 800 + std::rand() % 200; // Position horizontale décalée
    Obstacle* obs = new Obstacle("image/" + type + ".png", x, 520, 40, 60);
    obs->loadTexture(renderer);
    obstacles.push_back(obs);
}
// Chargement d'une image et conversion en texture SDL

SDL_Texture* Game::loadTexture(const std::string& path) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) return nullptr;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

// Affichage des boutons "Rejouer" et "Quitter" sur l'écran de fin
void Game::renderButtons() {
    // Dessin des rectangles des boutons
    SDL_SetRenderDrawColor(renderer, 205, 133, 63, 255); // Marron clair
    SDL_RenderFillRect(renderer, &retryButton);
    SDL_SetRenderDrawColor(renderer, 101, 67, 33, 255);  // Marron foncé
    SDL_RenderFillRect(renderer, &quitButton);

    // Création du texte des boutons
    SDL_Color white = { 255, 255, 255 };
    SDL_Surface* surf1 = TTF_RenderText_Blended(font, "Rejouer", white);
    SDL_Surface* surf2 = TTF_RenderText_Blended(font, "Quitter", white);
    SDL_Texture* tex1 = SDL_CreateTextureFromSurface(renderer, surf1);
    SDL_Texture* tex2 = SDL_CreateTextureFromSurface(renderer, surf2);

    // Positionnement du texte dans les boutons
    SDL_Rect r1 = { retryButton.x + 10, retryButton.y + 10, surf1->w, surf1->h };
    SDL_Rect r2 = { quitButton.x + 10, quitButton.y + 10, surf2->w, surf2->h };
    SDL_RenderCopy(renderer, tex1, NULL, &r1);
    SDL_RenderCopy(renderer, tex2, NULL, &r2);

    // Nettoyage
    SDL_FreeSurface(surf1);
    SDL_FreeSurface(surf2);
    SDL_DestroyTexture(tex1);
    SDL_DestroyTexture(tex2);
}
// Libération de toutes les ressources utilisées

void Game::clean() {
    // Libération des obstacles
    for (auto& obs : obstacles) delete obs;
    delete finishLine;

    // Libération des textures
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(gameOverImage);
    SDL_DestroyTexture(victoryImage);

    // Fermeture de la police
    TTF_CloseFont(font);

    // Destruction du rendu et de la fenêtre
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // Fermeture des bibliothèques
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
// Fin du fichier Game.cpp
