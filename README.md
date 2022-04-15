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
* [4. Application Android](#QuatriemeSection)
* [5. KICAD](#CinquiemeSection)
  * [5.1. Les composants](#CinquiemeSection1)
  * [5.2. La schématique](#CinquiemeSection2)
  * [5.3. Le placement des composants](#CinquiemeSection3)
  * [5.4. La visualisation 3D](#CinquiemeSection4)
* [6. Fabrication du PCB designer sur KICAD](#SixiemeSection)
* [7. Code Arduino](#SeptiemeSection)
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
Le capteur de graphite que nous voulons créer délivre un signal de courant très faible, d'environ 100 nA. Le microcontroleur ne peut donc pas mesurer directement ce courant. Nous choisissons donc d'utiliser un amplificateur transimpédance suivi de plusieurs filtres afin que ce faible signal ne soit pas perturbé par le bruit.

Nous devons aussi prendre en compte les caractéristiques de la carte Arduino que nous utilisons:
- Résolution: 10-12 bits
- Vref: 1,1V to 5,0V
- Impédence maximale: 1kOhm-10kOhm
- Fréquence d'échantillonage max: 15kHz-2,4MHz

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

Nous avons calculé les fréquences de courpure des différents filtres:
- Filtre d'entrée (R5 associée à C1) 
<p align="center">
<img width="960" alt="simulation_ac_filtre1" src="https://user-images.githubusercontent.com/98837554/163541380-68267eba-4612-4d09-b9eb-7c492514d345.png">
</p>
On obtient à -3dB, une fréquence de coupure de 20Hz ce qui fonctionne plutot bien pour l'entrée du capteur. 

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
 
 

En appliquant un PULSE en régime transitoire, on peut bien observer l'action de l'amplificateur transimpédance puis celui de l'étage inverseur :

![Pulse bruité](https://user-images.githubusercontent.com/73793387/162978927-0b9a38e9-b9a7-4a34-8f4f-cad87138f695.PNG)

Notre but est de vérifier si le gain du montage est cohérent avec ce que l'on souhaite obtenir en sortie. Nous allons donc effectuer une simulation fréquentielle en imposant un signal AC :

![Gain basse fréquence](https://user-images.githubusercontent.com/73793387/162979745-465354c0-6dad-428f-a5d5-81b3b237a498.PNG)

On observe un gain à basse fréquence de +140 dB ce qui nous ramène à un gain G=VAOC/Isens = 10^7 ce qui est bien cohérent avec le passage de 100nA à 1V.


## 4. Application Android <a id="QuatriemeSection"></a>
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

## 5. KICAD <a id="CinquiemeSection"></a>
Nous avons modélisé notre shield PCB sur le logiciel KICAD. Pour cela nous avons **designer tous les composants du PCB et crée leur empreinte** (l'aplificateur, l'écran OLED, le module Bluetooth et l'encodeur rotatoire). Nous avons ensuite crée les **connexions** entre tous les composants et avec la carte Arduino sur le logiciel. Enfin nous avons **modélisé la carte PCB** et crée un **modèle 3D** de l'ensemble. 
### 5.1. Les composants <a id="CinquiemeSection1"></a>
* L'amplificateur LTC1050

<img width="300" alt="image" src="https://user-images.githubusercontent.com/98837554/163401160-f208acc8-349f-49ba-b0c7-000f3a158738.png">

* L'écran OLED

<img width="300" alt="image" src="https://user-images.githubusercontent.com/98837554/163401706-46fd2dd1-ec94-4548-9da3-912de15763de.png">

* L'encodeur rotatoire KY_040

<img width="300" alt="image" src="https://user-images.githubusercontent.com/98837554/163401994-82856cc4-527f-4971-bb78-71ddba364be5.png">

* Le module bluetooth HC05

<img width="300" alt="image" src="https://user-images.githubusercontent.com/98837554/163401866-f06dca7b-75d8-41d6-840c-57c505550f2c.png">


### 5.2. Schématique <a id="CinquiemeSection2"></a>
Une fois les composants crées nous les relions entre eux et avec les broches de la carte Arduino. 
<p align="center">
<img width="460" alt="image" src="https://user-images.githubusercontent.com/98837554/163402315-645bc16a-a514-4546-9f56-441b44ba24c2.png">
</p>

### 5.3. Placement des composants <a id="CinquiemeSection3"></a>
Nous plaçons ensuite les composants sur le shield et traçons les connexions de sorte que les fils ne se croisent pas. 
<p align="center">
<img width="371" alt="image" src="https://user-images.githubusercontent.com/98837554/163403713-bcfc0a7a-aec5-4fe9-b39b-f4e81aa0f183.png">
 </p>

### 5.4. Visualisation 3D <a id="CinquiemeSection4"></a>
Nous avons enfin téléchargé les modèles 3D de nos composants afin de visualiser notre PCB en 3D. Cela nous permet aussi d'effectuer une dernière vérification et de voir qu'aucuns composants ne se chevauchent. 
<p align="center">
<img width="410" alt="image" src="https://user-images.githubusercontent.com/98837554/163404554-31852afe-2a49-4ad8-9f45-724db81acd6a.png">
<p/>

## 6. Fabrication du shield <a id="SixiemeSection"></a>

Avec l'aide de Catherine Crouzet, nous avons réalisé le PCB à partir d'une plaquette d'époxy recouverte d'une fine couche de cuivre.
Premièrement nous avons imprimé la modélisation du PCB que nous avions faites sur le logiciel KICAD. Cela joue le rôle de masque lors de l'insolation de la plaquette sous UVs. A l'aide d'unrévélateur nous retirons la partie de la résine qui n'a pas été insolée. Ensuite, la plaquette est placée dans un bain de perchlorure de fer pour la gravure. Le cuivre non protégé par la résine s'enlève et nous obtenons le PCB tel que nous l'avions desingner sur KICAD. 
Pour éliminer les dernières traces de résine, on lave le PCB à l'acétone. 
<p align="center">
<img width="300" alt="image" src="https://user-images.githubusercontent.com/98837554/163410624-d3a69000-6d83-496a-a13e-ba1b7dd018cd.png"> <img width="300" alt="image" src="https://user-images.githubusercontent.com/98837554/163410525-d537f93b-4770-4442-b086-9202968aa3f9.png">
<p/>

Nous avons ensuite percé notre PCB afin d'y insérer les différents composants. Le diamètre des trous varie selon les composants à placer :
* ⌀ 0.8mm : pour l'Amplificateur LTC1050, les résistances et les capacités
* ⌀ 1.0mm : Pour les broches de connexion de la carte Arduino Uno et les différents modules (OLED, bluetooth, encodeur rotatoire)


## 7. Code Arduino <a id="SeptiemeSection"></a> 





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
<img width="413" alt="image" src="https://user-images.githubusercontent.com/98837554/163627435-97af5539-40df-43f8-89ea-0dd6b4d60c05.png">
</p>

## 9. Datasheet <a id="NeuviemeSection"></a> 

## Contacts <a id="DixiemeSection"></a> 
Pour toutes questions n'hésitez pas à nous contacter !
* Marie Bénimélis : benimeli@insa-toulouse.fr
* Mathys Guichané : guichane@insa-toulouse.fr
