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
* [3. Code Arduino](#TroisiemeSection)
* [4. Application Android](#QuatriemeSection)
* [5. KICAD](#CinquiemeSection)
  * [5.1. Les composants](#CinquiemeSection1)
  * [5.2. La schématique](#CinquiemeSection2)
  * [5.3. Le placement des composants](#CinquiemeSection3)
  * [5.4. La visualisation 3D](#CinquiemeSection4)
* [6. Fabrication du PCB designer sur KICAD](#SixiemeSection)
* [7. Simulations sous LTspice](#SeptiemeSection)
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


## 3. Arduino <a id="TroisiemeSection"></a>
### 3.1. Librairies utilisées <a id="TroisiemeSection1"></a>
Nous avons utilisé différentes librairies dans notre code Arduino. La librarie ["Adafruit_SSD1306"](/Libraries/Adafruit_SSD1306) permet de contrôller l'écran OLED. La librairie [""Adafruit_BusIO"](/Libraries/Adafruit_busIO) permet de gérer la connexion en I2C et SPI.

### 3.2. Code Arduino <a id="TroisiemeSection2"></a>
Le code Arduino permet la communication entre la carte Arduino et les éléments ajoutés sur le shield tel que l'écran OLED, le module bluetooth ou l'encodeur rotatoire. 

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

<img width="371" alt="image" src="https://user-images.githubusercontent.com/98837554/163403713-bcfc0a7a-aec5-4fe9-b39b-f4e81aa0f183.png">

### 5.4. Visualisation 3D <a id="CinquiemeSection4"></a>
Nous avons enfin téléchargé les modèles 3D de nos composants afin de visualiser notre PCB en 3D. Cela nous permet aussi d'effectuer une dernière vérification et de voir si aucun composant ne se chevauche. 
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


## 7. Simulation <a id="SeptiemeSection"></a> 
Nous avons simulé notre amplificateur transimpédance sur le logiciel *LTSpice* afin de savoir le comportement que notre circuit aura une fois branché à de réelles valeurs de tension.

## 8. Banc de test <a id="HuigtiemeSection"></a> 
### 8.1. Banc de test <a id="HuigtiemeSection1"></a> 

### 8.2. Résultats obtenus <a id="SeptiemeSection2"></a> 

### 8.3. Analyse des résultats et pistes d'améliorations <a id="HuigtiemeSection3"></a> 

## 9. Datasheet <a id="NeuviemeSection"></a> 

## Contacts <a id="DixiemeSection"></a> 
Pour toutes questions relatives aux différentes parties du projet, que ce soit du KiCad au code Arduino, n'hésitez pas à nous contacter !
* Luca Paccard : paccard@insa-toulouse.fr
* Arthur Lemaire : a_lemair@insa-toulouse.fr
