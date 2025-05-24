#ifndef CONSTANTES_H
#define CONSTANTES_H

// Largeur de la fenêtre du jeu (en pixels)
// C'est la taille horizontale totale de la fenêtre affichée à l'écran.
const int LARGEUR_FENETRE = 800;

// Hauteur de la fenêtre du jeu (en pixels)
// C'est la taille verticale totale de la fenêtre affichée à l'écran.
const int HAUTEUR_FENETRE = 600;

// Position verticale du sol (ground) dans la fenêtre
// C'est la coordonnée Y à partir de laquelle le joueur "marche" ou roule.
// En SDL, Y=0 est en haut de l'écran et Y augmente vers le bas.
// Donc ici, le sol est situé à 480 pixels du haut de la fenêtre.B
const int GROUND_Y = 480;

// Largeur du joueur (en pixels)
// Cela permet de dessiner correctement la texture du joueur sur l’écran.
const int PLAYER_WIDTH = 100;

// Hauteur du joueur (en pixels)
// Cette constante est utilisée pour définir la taille verticale de la texture du joueur.
const int PLAYER_HEIGHT = 100;

// Largeur d’un obstacle (en pixels)
// Sert à définir la taille des obstacles qui apparaissent sur le parcours.
const int OBSTACLE_WIDTH = 50;

// Hauteur d’un obstacle (en pixels)
// Détermine la hauteur verticale des obstacles sur le trajet du joueur.
const int OBSTACLE_HEIGHT = 60;

#endif
