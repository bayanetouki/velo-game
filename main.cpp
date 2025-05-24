#include <iostream>
#include "Game.h"
#include "Menu.h"

int main(int argc, char* argv[]) {
    try {
        Menu menu;
        menu.lancer();
    }
    catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
