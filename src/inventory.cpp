#include "inventory.h"
#include "librairies.h"

/*
    * Constructeur de la classe Inventory
    * Chargement de l'inventaire du Joueur
*/
Inventory::Inventory(){
}

/*
    * Dessin de l'inventaire
    * @param window : Fenêtre de rendu
    * Affiche l'inventaire du joueur
*/
void Inventory::draw(sf::RenderWindow& window){
    // Chargement de l'image de l'inventaire du joueur 
    sf::Texture textureInventory;
    if (!textureInventory.loadFromFile("../assets/UI/Inventory.png")) {
        std::cerr << "Failed to load inventory texture!" << std::endl;
        return;
    }
    sf::Sprite spriteInventory;
    spriteInventory.setTexture(textureInventory);
    spriteInventory.setPosition(1920 / 2 - textureInventory.getSize().x / 2 * 7.5f, 1040 - textureInventory.getSize().y * 7.5f);
    spriteInventory.setScale(7.5f, 7.5f);

    // Ajout du sprite du joueur : 
    sf::Texture texturePlayer;
    if (!texturePlayer.loadFromFile("../assets/Perso/Perso_Basique.png")) {
        std::cerr << "Failed to load player texture!" << std::endl;
        return;
    }
    sf::Sprite spritePlayer;
    spritePlayer.setTexture(texturePlayer);
    spritePlayer.setPosition(1920 / 2 - 130, 1080 / 2 - 395);
    spritePlayer.setScale(16, 16);

    window.draw(spriteInventory);
    window.draw(spritePlayer);

    return;
}

/*
    * Ajout d'un item dans l'inventaire
    * @param item : Nom de l'item à ajouter
    * Ajoute un item dans l'inventaire du joueur
*/
void Inventory::addItem(const std::string& item){
    return;
}

/*
    * Suppression d'un item dans l'inventaire
    * @param item : Nom de l'item à supprimer
    * Supprime un item dans l'inventaire du joueur
*/
void Inventory::removeItem(const std::string& item){
    return;
}

/*
    * Vérification de la présence d'un item dans l'inventaire
    * @param item : Nom de l'item à vérifier
    * @return : true si l'item est présent, false sinon
    * Vérifie si un item est présent dans l'inventaire du joueur
*/
bool Inventory::hasItem(const std::string& item) const{
    return false;
}