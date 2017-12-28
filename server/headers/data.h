//Initialisation des voitures stockées
Car storedCars[NB_SERVERS][2] = {
    {{"AD456UI", 'B', 3}},
    {{"PO954VC", 'A', 1}, {"HG67589", 'D', 2}}
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
int durationMax[NB_SERVERS] = {5, 4, 7};