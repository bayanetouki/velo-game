#include "Player.h"
#include "Obstacle.h"
#include <SDL_image.h>
#include <stdexcept>

// Constructeur du joueur : initialise ses attributs de base
Player::Player()
    : texture(nullptr), // Aucun visuel chargé pour l’instant
    // On place le joueur à x = 100 (à gauche de l’écran)
    // y = GROUND_Y (niveau du sol), taille = définie par les constantes
    rect{ 100, GROUND_Y, PLAYER_WIDTH, PLAYER_HEIGHT },
    velocityY(0),      // Pas de mouvement vertical au début
    isJumping(false)   // Le joueur commence sans sauter
{
}

// Destructeur : appelé automatiquement quand l’objet est détruit
Player::~Player() {
    // Libération de la texture (important pour éviter les fuites mémoire)
    SDL_DestroyTexture(texture);
}

// Initialise le joueur : charge l’image, convertit en texture, définit la position
void Player::init(SDL_Renderer* renderer) {
    // Charge une image depuis le fichier (bike.png)
    SDL_Surface* surface = IMG_Load("image/bike.png");

    // Si l’image n’est pas trouvée, on déclenche une erreur
    if (!surface) throw std::runtime_error("Erreur chargement bike.png");

    // Crée une texture optimisée à partir de la surface
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    // Libère la surface temporaire (plus besoin après avoir créé la texture)
    SDL_FreeSurface(surface);
}

// Gère les entrées clavier : ici ↑ ou ESPACE pour faire sauter le joueur
void Player::handleInput() {
    // Récupère l’état de toutes les touches
    const Uint8* state = SDL_GetKeyboardState(NULL);

    // Si la touche flèche ↑ ou espace est pressée et que le joueur n’est pas déjà en saut
    if ((state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_SPACE]) && !isJumping) {
        velocityY = -18;     // On donne une vitesse vers le haut pour sauter
        isJumping = true;    // On marque que le joueur est en train de sauter
    }
}

// Met à jour la position verticale du joueur (simulation d’un saut)
void Player::update() {
    // Gravité : à chaque frame, le joueur tombe un peu plus vite
    velocityY += 1;

    // On applique la vitesse verticale à la position Y
    rect.y += (int)velocityY;

    // Si le joueur est retombé au sol ou plus bas (par sécurité)
    if (rect.y >= GROUND_Y) {
        rect.y = GROUND_Y;     // On le remet exactement sur le sol
        velocityY = 0;         // On arrête tout mouvement vertical
        isJumping = false;     // Il peut sauter à nouveau
    }
}

// Affiche le joueur à l’écran (appelé à chaque frame)
void Player::render(SDL_Renderer* renderer) {
    // Affiche la texture du joueur à la position rect (x, y, w, h)
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

// Remet le joueur à sa position et état d’origine (utile après un Game Over)
void Player::reset() {
    rect.x = 100;          // Position horizontale initiale
    rect.y = GROUND_Y;     // Au niveau du sol
    velocityY = 0;         // Pas de vitesse verticale
    isJumping = false;     // Peut sauter à nouveau
}

bool Player::collidesWith(const Obstacle& obs) const {
    // Zone de collision réduite du joueur (plus fine)
    SDL_Rect playerBox = {
        rect.x + 20,         // Réduction horizontale (décalage intérieur)
        rect.y + 30,         // Décalage vertical pour éviter le haut
        rect.w - 40,         // Réduction de largeur
        rect.h - 55          // Réduction de hauteur
    };

    // Zone de collision réduite de l'obstacle (facultatif mais utile)
    SDL_Rect obsBox = obs.getRect();
    obsBox.x += 10;
    obsBox.y += 10;
    obsBox.w -= 20;
    obsBox.h -= 20;

    // Test d’intersection
    return SDL_HasIntersection(&playerBox, &obsBox);
}
