#ifndef MENU_H
#define MENU_H

// Biblioth�ques n�cessaires pour utiliser SDL, les images et le texte
#include <SDL.h>         // SDL pour les fen�tres, �v�nements, rendu...
#include <SDL_image.h>   // SDL_image pour charger des images (jpg/png)
#include <SDL_ttf.h>     // SDL_ttf pour le rendu du texte avec des polices
#include <string>        // Pour manipuler les chemins d'acc�s en texte

// D�claration de la classe Menu
class Menu {
public:
    // Constructeur : initialise les pointeurs � null
    Menu();

    // Destructeur : lib�re la m�moire et les ressources utilis�es
    ~Menu();

    // Fonction principale pour lancer et afficher le menu (logique incluse dans le .cpp)
    void lancer();

private:
    // Pointeurs SDL pour la fen�tre et le rendu du menu
    SDL_Window* window;         // Fen�tre principale du menu
    SDL_Renderer* renderer;     // Rendu graphique

    // Police utilis�e pour afficher du texte dans le menu
    TTF_Font* font;

    // Textures pour les diff�rentes images du menu
    SDL_Texture* menuNormal;    // Image du menu par d�faut (aucun bouton survol�)
    SDL_Texture* menuJouer;     // Image affich�e quand "Jouer" est survol�
    SDL_Texture* menuApropos;   // Image affich�e quand "� propos" est survol�
    SDL_Texture* menuQuitter;   // Image affich�e quand "Quitter" est survol�
    SDL_Texture* aproposPage;   // Image de la page "� propos"

    // M�thode pour charger toutes les images n�cessaires (menu, � propos...)
    void chargerTextures();

    // M�thode pour lib�rer la m�moire occup�e par les textures
    void detruireTextures();

    // M�thode utilitaire pour charger une image et la convertir en texture SDL
    SDL_Texture* chargerImage(const std::string& path);
};

#endif
