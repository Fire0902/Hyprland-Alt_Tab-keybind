#!/bin/bash

# Demander à l'utilisateur s'il souhaite effectuer l'action
read -p "Voulez-vous effectuer cette action ? Attention valider ceci supprimera vos ancien keybind et les remplaceras (o/n) : " response

# Vérifier la réponse de l'utilisateur
if [ "$response" = "o" ] || [ "$response" = "O" ]; then
    echo "Action confirmée. Exécution du programme..."
    echo "Deplacement du fichier 1/2"
    cp -f alttab.c ~/.config/hypr/configs/
    gcc -o Move_Fluently.out ~/.config/hypr/configs/alttab.c
    echo "Compilation du fichier gcc"
    echo "Deplacement du fichier 2/2"
    cp -f Keybinds.conf ~/.config/hypr/configs/
elif [ "$response" = "n" ] || [ "$response" = "N" ]; then
    echo "Action annulée."
else
    echo "Réponse invalide. Veuillez saisir 'o' pour Oui ou 'n' pour Non."
fi

