//définition d'un forfait
typedef struct {
    char category;
    double price;
    double out;
    int maxDuration;
} Package;

//définition d'une voiture stationnée
typedef struct {
    char matriculation[7];
    int duration;
    Package p;
} Car;

//définition d'une requete serveur
typedef struct {
    char type;
    char serverName[25];
    int available;
    int present;
    double pricetopay;
    Car c;
} Request;