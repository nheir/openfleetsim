Openfleetsim
============

Openfleetsim est un simple simulateur de combat de flottes ogamiennes.
Ce programme est pour l'instant destiné au tournoi de flottes. Il ne gère pas la défense et ne donne que les pertes subies par les deux flottes à l'issue du combat. Il n'y a donc pas de rapport complet mais seulement les quantités de ressources perdues.

Utilisation
-----------

### Fichier de flotte

Un fichier de flotte contient une première ligne indiquant les technologies utilisées (armes, boulier, protection) puis au plus une ligne par type de vaisseaux de la forme `id_vaisseau:nb_vaisseau` où les `id_vaisseau` sont définis par :

    SmallCargoShip	0
    LargeCargoShip	1
    LightFighter	2
    HeavyFighter	3
    Cruiser			4
    Battleship		5
    ColonyShip		6
    Recycler		7
    EspionageProbe	8
    Bomber			9
    Destroyer		10
    Deathstar		11
    Battlecruiser	12

exemple :

    15 10 12
    4:40000
    0:20000

### Ligne de commande

    ./openfleetsim [-n N] [-tf A B P] flotte1 flotte2 [flotte3 [...]]
      flotte1 fichier de flotte
      -n N  nombre de simulation par combat (1 par défaut)
      -tf A B C force les technologies Armes à A, Bouclier à B et Preotection à P, ignore les technologies des flottes si bien définies
      
## Compilation

    make
