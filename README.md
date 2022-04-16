# Graphite_2022_GUICHANE_BENIMELIS
Projet "Capteur de Graphite", dans le contexte de l'UF **"Du capteur au banc de test"**, département de Génie Physique de l'INSA Toulouse.
***
L'objectif de ce projet est de reprendre les recherches scientifiques sur un capteur low-tech, le **"Pencil Draw Strain Gauges"**. Le fonctionnement de ce capteur est simple. Il suffit de dessiner au crayon à papier sur une feuille et d'appliquer ensuite une contrainte sur celle-ci. La contrainte appliquée va modifiée la distance entre les particules de graphique et par conséquent la résistance au passage du courant. Nous avons donc notre capteur. 

<p align="center">
<img width="466" alt="papier graphite" src="https://user-images.githubusercontent.com/98837554/163389962-011f1dfb-cacf-4c84-9b36-a27d5e313081.png">
</p>
Nous avons donc décidé de fabriquer nous-même ce capteur et de le tester. Les étapes et le matériel nécessaire à cette réalisation son détaillés ci-dessous. 

## Sommaire
* [1. Livrables](#PremiereSection)
* [2. Matériel nécessaire](#DeuxiemeSection)
* [3. Simulation sous LTspice](#TroisiemeSection)
* [4. Code Arduino](#SeptiemeSection)
* [5. Application Android](#QuatriemeSection)
* [6. KICAD](#CinquiemeSection)
  * [6.1. Les composants](#CinquiemeSection1)
  * [6.2. La schématique](#CinquiemeSection2)
  * [6.3. Le placement des composants](#CinquiemeSection3)
  * [6.4. La visualisation 3D](#CinquiemeSection4)
* [7. Fabrication du PCB designer sur KICAD](#SixiemeSection)
* [8. Banc de test](#HuigtiemeSection)
  * [8.1. Création du banc](#HuigtiemeSection1)
  * [8.2. Tests effectués](#HuigtiemeSection2)
* [9. Datasheet](#NeuviemeSection)
* [Contacts](#DixiemeSection)

## 1. Livrables <a id="PremiereSection"></a>
Ce projet sera évalué au sein de l'UF **"Du capteur au banc de test"**. 
Nous sommes donc amenés à rendre tout un ensemble de livrables que voici:
- Un **code Arduino** permettant de mesurer la déformation du capteur et de piloter à minima un module bluetooth, un encodeur rotatoire et un écran OLED
- Une **carte PCB** se connectant au module **Arduino UNO** contenant à minima un amplificateur transimpédance, un module bluetooth, un écran OLED et un encodeur rotatoire
- Une **application Android APK**
- Une **simulation sous LTspice**
- Un **banc de test** 
- La **datasheet** du capteur de déformation

## 2. Matériel nécessaire
Afin de mener à bien ce projet nous avons eu besoin de: 

* 2 résistance 100kΩ
* 2 résistance 1kΩ
* 1 résistance 10kΩ
* 1 capacité 1μF
* 3 capacité 100nF
* 1 amplificateur opérationnel LTC1050
* 1 module Bluetooth HC05
* 1 écran OLED I2C 0.91
* 1 encodeur rotatoire KY_040
* une feuille de papier avec du graphite (crayon à papier) comme ci-dessous


## 3. Simulation Sous LTspice <a id="TroisiemeSection"></a>
Le capteur de graphite que nous voulons créer délivre un signal de courant très faible, d'environ 100 nA. Le microcontroleur ne peut donc pas mesurer directement ce courant. Nous choisissons donc d'utiliser un amplificateur transimpédance pour convertir une variation de courant en variation de tension suivi de plusieurs filtres afin que ce faible signal ne soit pas perturbé par le bruit.

Voici le schéma que nous avons réalisé:
<p align="center">
<img width="959" alt="image" src="https://user-images.githubusercontent.com/98837554/163421444-e54a7c67-e4bf-4253-9246-cfc406340a29.png">
<p/>

Voici les fonctionnalités des différents composants: 
- R5 protège l'amplificateur opérationnel contre les décharges électrostatiques, avec C1 forme un filtre pour les bruits en tension
- C1 avec R1 forment un filtre pour le bruit en courant 
- R2 est interchangeable pour permettre une adaptation du calibre
- C4 avec R3 forment un filtre actif
- C2 avec R6 forment un filtre de sortie 
- C3 filtre le bruit de l'alimentation

Nous avons simulé notre circuit dans les **conditions nominales**, c'est à dire sans bruit. Voici la réponse de notre circuit:
<p align="center">
<img width="398" alt="image" src="https://user-images.githubusercontent.com/98837554/163636090-f7b55e91-c3a8-494e-a684-dcd89eaaba78.png">
</p>
Le capteur est fonctionnel et ne sature pas car la hauteur du plateau est à 1V (inférieur à 5V).

La datasheet de l'amplificateur LTC1050C nous indique que sa tension d'offset est de l'ordre 5 µV et que le maximum d’offset de décalage est de l’ordre se 0,05µV/°C. Ces valeurs nous semblent acceptables. 
En effet le gain de l’AOP est de 160 dB. Pour une tension d’entrée de 10mV, nous avons donc en sortie 106V. L’offset de sortie est quant à lui de 50V. L’offset de l'amplificateur est donc négligeable et son incidence est donc acceptable. 

De même le courant d’offset indiqué dans la datasheet est de 160 pA. Cette valeur semble acceptable devant le courant circulant dans R1 par exemplequi est de l’ordre de 100 nA. Cette valeur est 625 fois supérieure à la tension d’offset qu’on peut donc négliger. 

Nous devons aussi prendre en compte les caractéristiques de la carte Arduino que nous utilisons:
- Résolution: 10-13 bits
- Vref: 1,1V to 5,0V
- Impédence maximale: 1kOhm-10kOhm
- Fréquence d'échantillonage max: 15kHz

Si nous utilisons l'Arduinon Uno à sa fréquence max (15kHz). La limite de repliement autrement appelée fréquence de Nyquist, est égale à la moitié de la fréquence d'échantillonage choisie, ici 15kHz, donc 7,5kHz. 

Nous avons ensuite calculé les **fréquences de courpure des différents filtres**:
- Filtre d'entrée (R5 associée à C1) 
<p align="center">
<img width="960" alt="simulation_ac_filtre1" src="https://user-images.githubusercontent.com/98837554/163541380-68267eba-4612-4d09-b9eb-7c492514d345.png">
</p>
On obtient à -3dB, une fréquence de coupure de 20Hz ce qui fonctionne bien pour l'entrée du capteur. 

- Filtre actif (R3 associée à C4) 
<p align="center">
<img width="959" alt="simulation_ac_filtre2" src="https://user-images.githubusercontent.com/98837554/163541957-834a4d79-2858-4d12-aa25-55f55f7cb285.png">
</p>
On obtient à -3dB, une fréquence de coupure de 2Hz qui permet de couper le bruit induit par le secteur 50Hz.

- Filtre de sortie (R6 associée à C2) 
<p align="center">
<img width="959" alt="simulation_ac_filtre3" src="https://user-images.githubusercontent.com/98837554/163542460-0e609e20-6055-4db2-8078-0ccc3461a577.png">
</p>
On obtient à -3dB, une fréquence de coupure de 1,5kHz ce qui fonctionne bien pour l'échantillonage de l'ARDUINO.

En faisant varier C1, nous avons pu observer l'infuence de cette capacité sur l'atténuation globale d'un bruit de courant de 50Hz. 
- C1= 1u:
<p align="center">
<img width="529" alt="image" src="https://user-images.githubusercontent.com/98837554/163641065-caad8153-dde2-4825-a69c-691940c0eabf.png">
</p>
-C1=100n:
<p align="center">
<img width="572" alt="image" src="https://user-images.githubusercontent.com/98837554/163643246-57700a0b-bc04-400c-982a-ee6651a95a20.png">
</p>

CONCLURE

## 4. Code Arduino <a id="SeptiemeSection"></a> 

L’objectif de ce projet est de mesurer une valeur de résistance. La première étape du code est donc de lire cette valeur. C’est pourquoi nous utilisons la fonction getResistance(int pin) qui permet de lire une valeur analogique sur le pin A0. Cette valeur est ensuite convertie en tension. Nous relions la valeur de la tension de sortie à la résistance en entrée du circuit.

Une fois cette valeur récupérée, il faut l’afficher sur un écran OLED. Nous avons réfléchi à un menu que nous pourrions actualiser à l’aide d’un encodeur rotatoire.

Notre menu est défini par une fonction updateMenu() dans lequel 4 cas sont observés. Le premier correspond à l'affichage de la résistance, le second de la date, le troisième de l’heure et le dernier est un mini jeu que nous détaillerons plus tard. Pour chaque « case » du menu, une action différente est effectuée. 

L’encodeur rotatoire va avoir un rôle à jouer dans la sélection et l’affichage de ses fonctions. En effet, nous lions les pins CLK et SW de l’encodeur à la commande attachInterrupt(pin, fonction(), état). Chaque fois que l’état est déclenché, fonction() est appelée. Chaque fois que l’état du pin CLK passe de 0 à 1, la fonction doEncoder est appelée. Cette fonction incrémente la variable « menu » qui permet de choisir un des cas observés précédemment. De même, chaque fois que l’état de SW change, la fonction Action() est appelée. Cette fonction commande la variable « menuState » aux valeurs 1 et 0. Lorsque « menuState » == 0, la boucle loop() met à jour le menu en appelant updateMenu(). Lorsque « menuState » == 1, la boucle loop() rentre dans un des choix du menu en appelant executeAction(). 

La fonction graphique est un mini-jeu dont le but est d’aller d’un bout à l’autre de l’écran. On redimensionne la valeur de la résistance sur l’écran OLED puis on augmente ou diminue la résistance pour aller plus haut ou plus bas et esquiver les traits bleus sur le chemin. Si nous touchons une ligne, nous avons perdu.

Pour finir, nous ajoutons le module Bluetooth. Par l’intermédiaire de ce module, nous envoyons la valeur de la résistance à l’application créée sur MIT App Inventor.


## 5. Application Android <a id="QuatriemeSection"></a>
Nous avons ensuite cherché à afficher les valeurs de résistance du capteur sur un téléphone mobile Android. Pour cela nous avons crée une application grâce au site MIT App Inventor. 
Notre interface comprend:
- Un bouton de connexion au bluetooth et devient vert quand la connexion est établie ou rouge quand elle ne l'ai pas
- Un menu déroulant qui permet de choisir ce que l'on veut afficher (valeur de la résistance, graphe de la résistance en fonction du temps ou les deux)
- La valeur de la résistance du capteur de graphène
- Un graphe ou s'affiche le tracé de la résistance du capteur en fonction du temps
- Un bouton "Reset" qui permet d'effacer le graphe 
- Une information sur les bits contenus dans le buffer

<p align="center">
<img width="254" alt="image" src="https://user-images.githubusercontent.com/98837554/163391196-81fc7854-eb26-422d-8320-28e765e18411.png">
</p>

## 6. KICAD <a id="CinquiemeSection"></a>
Nous avons modélisé notre shield PCB sur le logiciel KICAD. Pour cela nous avons **designer tous les composants du PCB et crée leur empreinte** (l'aplificateur, l'écran OLED, le module Bluetooth et l'encodeur rotatoire). Nous avons ensuite crée les **connexions** entre tous les composants et avec la carte Arduino sur le logiciel. Enfin nous avons **modélisé la carte PCB** et crée un **modèle 3D** de l'ensemble. 
### 6.1. Les composants <a id="CinquiemeSection1"></a>
* L'amplificateur LTC1050

<img width="300" alt="image" src="https://user-images.githubusercontent.com/98837554/163401160-f208acc8-349f-49ba-b0c7-000f3a158738.png">

* L'écran OLED

<img width="300" alt="image" src="https://user-images.githubusercontent.com/98837554/163401706-46fd2dd1-ec94-4548-9da3-912de15763de.png">

* L'encodeur rotatoire KY_040

<img width="300" alt="image" src="https://user-images.githubusercontent.com/98837554/163401994-82856cc4-527f-4971-bb78-71ddba364be5.png">

* Le module bluetooth HC05

<img width="300" alt="image" src="https://user-images.githubusercontent.com/98837554/163401866-f06dca7b-75d8-41d6-840c-57c505550f2c.png">


### 6.2. Schématique <a id="CinquiemeSection2"></a>
Une fois les composants crées nous les relions entre eux et avec les broches de la carte Arduino. 
<p align="center">
<img width="460" alt="image" src="https://user-images.githubusercontent.com/98837554/163402315-645bc16a-a514-4546-9f56-441b44ba24c2.png">
</p>

### 6.3. Placement des composants <a id="CinquiemeSection3"></a>
Nous plaçons ensuite les composants sur le shield et traçons les connexions de sorte que les fils ne se croisent pas. 
<p align="center">
<img width="371" alt="image" src="https://user-images.githubusercontent.com/98837554/163403713-bcfc0a7a-aec5-4fe9-b39b-f4e81aa0f183.png">
 </p>

### 6.4. Visualisation 3D <a id="CinquiemeSection4"></a>
Nous avons enfin téléchargé les modèles 3D de nos composants afin de visualiser notre PCB en 3D. Cela nous permet aussi d'effectuer une dernière vérification et de voir qu'aucuns composants ne se chevauchent. 
<p align="center">
<img width="410" alt="image" src="https://user-images.githubusercontent.com/98837554/163404554-31852afe-2a49-4ad8-9f45-724db81acd6a.png">
<p/>

## 7. Fabrication du shield <a id="SixiemeSection"></a>

Avec l'aide de Catherine Crouzet, nous avons réalisé le PCB à partir d'une plaquette d'époxy recouverte d'une fine couche de cuivre.
Premièrement nous avons imprimé la modélisation du PCB que nous avions faites sur le logiciel KICAD. Cela joue le rôle de masque lors de l'insolation de la plaquette sous UVs. A l'aide d'unrévélateur nous retirons la partie de la résine qui n'a pas été insolée. Ensuite, la plaquette est placée dans un bain de perchlorure de fer pour la gravure. Le cuivre non protégé par la résine s'enlève et nous obtenons le PCB tel que nous l'avions desingner sur KICAD. 
Pour éliminer les dernières traces de résine, on lave le PCB à l'acétone. 
<p align="center">
<img width="300" alt="image" src="https://user-images.githubusercontent.com/98837554/163410624-d3a69000-6d83-496a-a13e-ba1b7dd018cd.png"> <img width="300" alt="image" src="https://user-images.githubusercontent.com/98837554/163410525-d537f93b-4770-4442-b086-9202968aa3f9.png">
<p/>

Nous avons ensuite percé notre PCB afin d'y insérer les différents composants. Le diamètre des trous varie selon les composants à placer :
* ⌀ 0.8mm : pour l'Amplificateur LTC1050, les résistances et les capacités
* ⌀ 1.0mm : Pour les broches de connexion de la carte Arduino Uno et les différents modules (OLED, bluetooth, encodeur rotatoire)








## 8. Banc de test <a id="HuigtiemeSection"></a> 
### 8.1. Banc de test <a id="HuigtiemeSection1"></a> 
Nous avons imaginé un banc de test afin de pouvoir tester notre capteur. Nous utilisons un rail sur lequel nous rajoutons deux supports. Entre ces-derniers nous mettrons notre capteur sur une réglette flexible. En faisant varier la distance entre les deux supports, la réglette flexible se courbe. Nous relevons cette courbure et la résistance du capteur associée.
Nous avons imprimé deux pièces 3D afin de réaliser ce banc de test. Ce sont des support pour la réglette flexibles. La partie arrière est légèrement inclinée afin que la réglette ne parte pas lors de la flexion.  
<p align="center">
<img width="300" alt="image" src="https://user-images.githubusercontent.com/98837554/163570728-51250161-7a48-498d-9d0b-daf20a6fe5a1.png">
<img width="300" alt="image" src="https://user-images.githubusercontent.com/98837554/163624850-82fe3e1e-3f73-463d-8121-c7a0c9c3ff4d.png">
</p>

### 8.2. Résultats obtenus <a id="SeptiemeSection2"></a> 
Nous avons fait plusieurs mesures en flexion, en donnant à notre capteur une forme concave puis convexe. Nous utilisons un crayon a papier de type critérium avec une mine HB.
<p align="center">
<img width="425" alt="image" src="https://user-images.githubusercontent.com/98837554/163680895-0f0f1b88-399c-4482-af65-45ff1b7ff46f.png">
<img width="440" alt="image" src="https://user-images.githubusercontent.com/98837554/163680946-25f5141c-d18b-4687-a459-ead8596fb05c.png">
</p>
On remarque que la résistance diminue lorsqu'on donne une forme convexe à notre capteur et inversement pour le cas concave. Cela est dû au rapprochement ou à léloignement des molécules de graphite comme nous l'expliquions plus au plus haut. 

## 9. Datasheet <a id="NeuviemeSection"></a> 
A l'aide de nos résultats obtenus lors de nos essais avec le banc de test, nous avons pu mettre au point une datasheet de notre capteur. Celle-ci se trouve dans les fichiers à télécharger. 

## Contacts <a id="DixiemeSection"></a> 
Pour toutes questions n'hésitez pas à nous contacter !
* Marie Bénimélis : benimeli@insa-toulouse.fr
* Mathys Guichané : guichane@insa-toulouse.fr
