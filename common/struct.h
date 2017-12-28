//définition d'un forfait
typedef struct {
    char category;
    double price;
    double out;
    int duration;
} Package;

//définition d'une voiture stationnée
typedef struct {
    char matriculation[7];
    int time;
    Package p;
} Car;

//définition d'une requete serveur
typedef struct {
    char type;
    char trace[20];
    Car c;
} Request;