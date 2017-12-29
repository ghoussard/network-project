//Initialisation des voitures stockées
Car storedCars[NB_SERVERS][2] = {
    {{"AD456UI", 3, {'A'}}, {"BV905NB", 2, {'C'}}},
    {{"PO954VC", 1, {'E'}}, {"HG675OI", 2, {'A'}}},
    {{"GT631BG", 6, {'D'}}, {"AQ032HG", 10, {'B'}}}
};

//Initialisation des forfaits
Package packages[NB_SERVERS][5] = {
    {
        {'A', 2, 5},
        {'B', 3, 7},
        {'C', 4, 9},
        {'D', 5, 11},
        {'E', 6, 13}
    },
    {
        {'A', 1, 2},
        {'B', 2, 3},
        {'C', 3, 4},
        {'D', 4, 5},
        {'E', 5, 6}
    },
    {
        {'A', 3, 4},
        {'B', 5, 6},
        {'C', 7, 8},
        {'D', 9, 10},
        {'E', 11, 12}
    }
};

//Durée max avant hors forfait
int maxDuration[NB_SERVERS] = {5, 4, 7};

//Places disponibles par classe
int availableSpaces[NB_SERVERS][5] = {
    {1, 0, 1, 1, 1},
    {1, 1, 0, 0, 1},
    {0, 1, 1, 0, 0}
};

//Noms des parkings
char serverNames[NB_SERVERS][25] = {"Parking du Chateau", "Parking St-Pierre", "Parking de l'Université"};