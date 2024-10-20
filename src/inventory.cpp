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
    // Rectangle bleu nuit avec un alpha de 128
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(1880, 1040));
    rect.setPosition(20, 20);
    rect.setFillColor(sf::Color(0, 0, 128, 128));
    window.draw(rect);

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