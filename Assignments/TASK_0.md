# Se familiariser avec l'existant

## A- Exécution

Compilez et lancez le programme.

Allez dans le fichier `tower_sim.cpp` et recherchez la fonction responsable de gérer les inputs du programme.
Sur quelle touche faut-il appuyer pour ajouter un avion ?
Comment faire pour quitter le programme ?
A quoi sert la touche 'F' ?

```
C pour ajouter un avion
F pour passer en plein ecran
Q ou X pour quitter
+ pour zoomer
- pour dezoomer
```

Ajoutez un avion à la simulation et attendez.
Que est le comportement de l'avion ?

```
L'avion atterit, recupere des passagers puis repart
```

Quelles informations s'affichent dans la console ?

```
AF4412 is now landing...
now servicing AF4412...
done servicing AF4412
AF4412 lift off
```


Ajoutez maintenant quatre avions d'un coup dans la simulation.
Que fait chacun des avions ?

```
Il attends que la piste d'atterissage soit libre avant d'atterir
```

## B- Analyse du code

Listez les classes du programme à la racine du dossier src/.
Pour chacune d'entre elle, expliquez ce qu'elle représente et son rôle dans le programme.

```
Airport : s'occupe de reserver des terminaux aux avions et de renvoyer une liste de point de passage
pour l'atterrissage. 

Aircraft : represente les avions.

Terminal : represente le terminal.

Tower : permets de faire l'association entre les avions et l'airport.

Waypoint : Point de passage a suivre par les avions.
```


Pour les classes `Tower`, `Aircaft`, `Airport` et `Terminal`, listez leurs fonctions-membre publiques et expliquez précisément à quoi elles servent.
Réalisez ensuite un schéma présentant comment ces différentes classes intéragissent ensemble.

```
Terminal
-	in_use() : permets de savoir si un terminal est deja utilise ou non.
- in_servicing() : permets de savoir si un avion est en service sur ce terminal ou non.
- assign_craft() : assigne un avion au terminal
- finish_service() : desassigne l'avion courant du terminal

Tower
- get_instructions() : recupere des instructions a donner pour guider les avions en vol
- arrived_at_terminal() : associe un avion a un terminal

Aircraft
- get_flight_num() : recupere l'identifiant du vol
- distance_to() : calcule la distance vers un point 3D
- display() : affiche l'avion
- move() : deplace l'avion

Airport
- get_tower() : recupere la tour de controle associee a l'airport
- display() : affiche l'avion
- move() : deplace l'avion
```

![UML](https://i.ibb.co/k6Cp3MD/1645203937.png)

Quelles classes et fonctions sont impliquées dans la génération du chemin d'un avion ?
Quel conteneur de la librairie standard a été choisi pour représenter le chemin ?
```
Une queue 
```

Expliquez les intérêts de ce choix.

```
La classe Queue permets de mettre des priorites sur les objets ( premier arrive premier servis )

Les classes impliquees dans la generation du chemin d'un avion sont les classes tower et waypoint.
Tower va definir les instructions pour chaque avion en creant un ensemble de waypoint.
Waypoint herite de Point3D qui permets de representer un point dans l'espace.
Les waypoint vont definir des point de passages pour les itineraires des avions.
C'est la fonction get_instructions de la classe Tower qui va creer les chemins a suivre par les avions.
```

## C- Bidouillons !

1) Déterminez à quel endroit du code sont définies les vitesses maximales et accélération de chaque avion.
Le Concorde est censé pouvoir voler plus vite que les autres avions.
Modifiez le programme pour tenir compte de cela.

```
Dans le fichier aircraft_types.hpp
C'est la classe AircraftType
```

2) Identifiez quelle variable contrôle le framerate de la simulation.
Ajoutez deux nouveaux inputs au programme permettant d'augmenter ou de diminuer cette valeur.
Essayez maintenant de mettre en pause le programme en manipulant ce framerate. Que se passe-t-il ?\
Ajoutez une nouvelle fonctionnalité au programme pour mettre le programme en pause, et qui ne passe pas par le framerate.

```
La variable de controle est GL::ticks_per_sec
```

3) Identifiez quelle variable contrôle le temps de débarquement des avions et doublez-le.

```
#TODO
```

4) Lorsqu'un avion a décollé, il réattérit peu de temps après.
Faites en sorte qu'à la place, il soit retiré du programme.\
Indices :\
A quel endroit pouvez-vous savoir que l'avion doit être supprimé ?\
Pourquoi n'est-il pas sûr de procéder au retrait de l'avion dans cette fonction ?
A quel endroit de la callstack pourriez-vous le faire à la place ?\

```
Une fois que l'avion a deja atteri une fois et qu'il n'a plus d'objectif.
On pourrais supprimer l'avion dans la fonction get_instructions definie dans tower.cpp,
Mais ce n'est pas pertinent car la fonction move() qui appelle get_instructions() est appelle sur un iterateur d'unordered set
si on supprime un aircraft a cet endroit la il risque d'y avoir un probleme.
Il faut retirer les avions apres les avoir move()
TODO : Supprimer apres le move dans la fonction gl

Autre idee : DynamicObject ont un champ waitForDelete en attente de leur suppression
```

Que devez-vous modifier pour transmettre l'information de la première à la seconde fonction ?
```On transmets un booleen par la fonction move() pour savoir si l'objet doit etre supprime apres ou non```

5) Lorsqu'un objet de type `Displayable` est créé, il faut ajouter celui-ci manuellement dans la liste des objets à afficher.
Il faut également penser à le supprimer de cette liste avant de le détruire.
Faites en sorte que l'ajout et la suppression de `display_queue` soit "automatiquement gérée" lorsqu'un `Displayable` est créé ou détruit.
Pourquoi n'est-il pas spécialement pertinent d'en faire de même pour `DynamicObject` ?


6) La tour de contrôle a besoin de stocker pour tout `Aircraft` le `Terminal` qui lui est actuellement attribué, afin de pouvoir le libérer une fois que l'avion décolle.
Cette information est actuellement enregistrée dans un `std::vector<std::pair<const Aircraft*, size_t>>` (size_t représentant l'indice du terminal).
Cela fait que la recherche du terminal associé à un avion est réalisée en temps linéaire, par rapport au nombre total de terminaux.
Cela n'est pas grave tant que ce nombre est petit, mais pour préparer l'avenir, on aimerait bien remplacer le vector par un conteneur qui garantira des opérations efficaces, même s'il y a beaucoup de terminaux.\
Modifiez le code afin d'utiliser un conteneur STL plus adapté. Normalement, à la fin, la fonction `find_craft_and_terminal(const Aicraft&)` ne devrait plus être nécessaire.

## D- Théorie

1) Comment a-t-on fait pour que seule la classe `Tower` puisse réserver un terminal de l'aéroport ?

2) En regardant le contenu de la fonction `void Aircraft::turn(Point3D direction)`, pourquoi selon-vous ne sommes-nous pas passer par une réference ?
Pensez-vous qu'il soit possible d'éviter la copie du `Point3D` passé en paramètre ?

## E- Bonus

Le temps qui s'écoule dans la simulation dépend du framerate du programme.
La fonction move() n'utilise pas le vrai temps. Faites en sorte que si.
Par conséquent, lorsque vous augmentez le framerate, la simulation s'exécute plus rapidement, et si vous le diminuez, celle-ci s'exécute plus lentement.

Dans la plupart des jeux ou logiciels que vous utilisez, lorsque le framerate diminue, vous ne le ressentez quasiment pas (en tout cas, tant que celui-ci ne diminue pas trop).
Pour avoir ce type de résultat, les fonctions d'update prennent généralement en paramètre le temps qui s'est écoulé depuis la dernière frame, et l'utilise pour calculer le mouvement des entités.

Recherchez sur Internet comment obtenir le temps courant en C++ et arrangez-vous pour calculer le dt (delta time) qui s'écoule entre deux frames.
Lorsque le programme tourne bien, celui-ci devrait être quasiment égale à 1/framerate.
Cependant, si le programme se met à ramer et que la callback de glutTimerFunc est appelée en retard (oui oui, c'est possible), alors votre dt devrait être supérieur à 1/framerate.

Passez ensuite cette valeur à la fonction `move` des `DynamicObject`, et utilisez-la pour calculer les nouvelles positions de chaque avion.
Vérifiez maintenant en exécutant le programme que, lorsque augmentez le framerate du programme, vous n'augmentez pas la vitesse de la simulation.

Ajoutez ensuite deux nouveaux inputs permettant d'accélérer ou de ralentir la simulation.
