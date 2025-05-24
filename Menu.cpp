#include "Menu.h"
#include "Game.h"
#include "Constantes.h"
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>

// ✅ Fonction utilitaire : vérifie si la souris est sur un bouton
bool isMouseOver(const SDL_Rect& rect, int x, int y) {
    return x >= rect.x && x <= rect.x + rect.w &&
        y >= rect.y && y <= rect.y + rect.h;
}
// Cette fonction vérifie si le pointeur de la souris (x, y)
// se trouve à l’intérieur d’un rectangle SDL (comme un bouton).


Menu::Menu() : window(nullptr), renderer(nullptr), font(nullptr),
menuNormal(nullptr), menuJouer(nullptr), menuApropos(nullptr),
menuQuitter(nullptr), aproposPage(nullptr) {
}
// Initialise tous les pointeurs à nullptr (bonne pratique avant leur création)


Menu::~Menu() {
    detruireTextures();                // Libère les textures images
    TTF_CloseFont(font);              // Ferme la police
    SDL_DestroyRenderer(renderer);    // Détruit le renderer
    SDL_DestroyWindow(window);        // Détruit la fenêtre
    TTF_Quit(); IMG_Quit(); SDL_Quit(); // Libère toutes les libs SDL
}


void Menu::lancer() {
    // Initialisation des bibliothèques
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    TTF_Init();

    // Création de la fenêtre
    window = SDL_CreateWindow("Velo Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR_FENETRE, HAUTEUR_FENETRE, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    font = TTF_OpenFont("fonts/FreeSans.ttf", 20);

    // Chargement des images
    chargerTextures();

    // Définition des zones interactives des boutons
    SDL_Rect jouerBtn = { 640, 300, 160, 50 };
    SDL_Rect aproposBtn = { 640, 360, 160, 50 };
    SDL_Rect quitterBtn = { 640, 420, 160, 50 };
    SDL_Rect retourBtn = { 650, 500, 120, 40 };

    bool running = true;    // Le menu est actif
    bool inApropos = false; // Sommes-nous sur la page "À propos" ?
    SDL_Event event;

    while (running) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);  // Coordonnées de la souris

        SDL_Texture* currentMenu = menuNormal;

        // On change l’image du menu selon le survol
        if (!inApropos) {
            if (isMouseOver(jouerBtn, mouseX, mouseY))
                currentMenu = menuJouer;
            else if (isMouseOver(aproposBtn, mouseX, mouseY))
                currentMenu = menuApropos;
            else if (isMouseOver(quitterBtn, mouseX, mouseY))
                currentMenu = menuQuitter;
        }

        // Gestion des événements (clics, fermeture)
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;

            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                if (!inApropos) {
                    // Clic sur "Jouer"
                    if (isMouseOver(jouerBtn, mouseX, mouseY)) {
                        Game jeu;
                        if (jeu.init()) jeu.run();
                    }
                    // Clic sur "À propos"
                    else if (isMouseOver(aproposBtn, mouseX, mouseY)) {
                        inApropos = true;
                    }
                    // Clic sur "Quitter"
                    else if (isMouseOver(quitterBtn, mouseX, mouseY)) {
                        running = false;
                    }
                }
                // Dans la page "À propos", clic sur "Retour"
                else {
                    if (isMouseOver(retourBtn, mouseX, mouseY)) {
                        inApropos = false;
                    }
                }
            }
        }

        // 🎨 Rendu graphique
        SDL_RenderClear(renderer);

        if (inApropos) {
            // Affichage de l'image "À propos"
            SDL_RenderCopy(renderer, aproposPage, NULL, NULL);

            // Affichage du bouton Retour
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(renderer, 135, 206, 250, isMouseOver(retourBtn, mouseX, mouseY) ? 200 : 255);
            SDL_RenderFillRect(renderer, &retourBtn);

            // Texte "Retour"
            SDL_Color white = { 255, 255, 255 };
            SDL_Surface* textSurface = TTF_RenderText_Blended(font, "Retour", white);
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

            int tw = 0, th = 0;
            SDL_QueryTexture(textTexture, NULL, NULL, &tw, &th);
            SDL_Rect textRect = {
                retourBtn.x + (retourBtn.w - tw) / 2,
                retourBtn.y + (retourBtn.h - th) / 2,
                tw, th
            };

            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
            SDL_FreeSurface(textSurface);
            SDL_DestroyTexture(textTexture);
        }
        else {
            // Affichage du menu interactif (image normale ou survolée)
            SDL_RenderCopy(renderer, currentMenu, NULL, NULL);
        }

        SDL_RenderPresent(renderer); // Affiche à l’écran
    }
}


void Menu::chargerTextures() {
    menuNormal = chargerImage("image/menu.jpg");
    menuJouer = chargerImage("image/menu-jouer.JPG");
    menuApropos = chargerImage("image/menu-apropos.JPG");
    menuQuitter = chargerImage("image/menu-quitter.JPG");
    aproposPage = chargerImage("image/apropos.png");
}
// Charge toutes les images du menu en textures SDL


void Menu::detruireTextures() {
    SDL_DestroyTexture(menuNormal);
    SDL_DestroyTexture(menuJouer);
    SDL_DestroyTexture(menuApropos);
    SDL_DestroyTexture(menuQuitter);
    SDL_DestroyTexture(aproposPage);
}
// Libère la mémoire utilisée par chaque texture chargée


SDL_Texture* Menu::chargerImage(const std::string& path) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) throw std::runtime_error("Erreur image : " + path);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}
// Charge une image depuis un fichier et la convertit en texture utilisable par SDL
// Si l’image ne se charge pas, une exception est lancée

