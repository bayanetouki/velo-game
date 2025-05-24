#ifndef MENU_H
#define MENU_H

// Bibliothèques nécessaires pour utiliser SDL, les images et le texte
#include <SDL.h>         // SDL pour les fenêtres, événements, rendu...
#include <SDL_image.h>   // SDL_image pour charger des images (jpg/png)
#include <SDL_ttf.h>     // SDL_ttf pour le rendu du texte avec des polices
#include <string>        // Pour manipuler les chemins d'accès en texte

// Déclaration de la classe Menu
class Menu {
public:
    // Constructeur : initialise les pointeurs à null
    Menu();

    // Destructeur : libère la mémoire et les ressources utilisées
    ~Menu();

    // Fonction principale pour lancer et afficher le menu (logique incluse dans le .cpp)
    void lancer();

private:
    // Pointeurs SDL pour la fenêtre et le rendu du menu
    SDL_Window* window;         // Fenêtre principale du menu
    SDL_Renderer* renderer;     // Rendu graphique

    // Police utilisée pour afficher du texte dans le menu
    TTF_Font* font;

    // Textures pour les différentes images du menu
    SDL_Texture* menuNormal;    // Image du menu par défaut (aucun bouton survolé)
    SDL_Texture* menuJouer;     // Image affichée quand "Jouer" est survolé
    SDL_Texture* menuApropos;   // Image affichée quand "À propos" est survolé
    SDL_Texture* menuQuitter;   // Image affichée quand "Quitter" est survolé
    SDL_Texture* aproposPage;   // Image de la page "À propos"

    // Méthode pour charger toutes les images nécessaires (menu, à propos...)
    void chargerTextures();

    // Méthode pour libérer la mémoire occupée par les textures
    void detruireTextures();

    // Méthode utilitaire pour charger une image et la convertir en texture SDL
    SDL_Texture* chargerImage(const std::string& path);
};

#endif
