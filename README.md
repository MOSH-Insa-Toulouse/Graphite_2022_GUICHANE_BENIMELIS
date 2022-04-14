# Graphite_2022_GUICHANE_BENIMELIS
Projet "Capteur de Graphite", dans le contexte de l'UF **"Du capteur au banc de test"**, département de Génie Physique de l'INSA Toulouse.
***
L'objectif de ce projet est de reprendre les recherches scientifiques sur un capteur low-tech, le **"Pencil Draw Strain Gauges"**. Le fonctionnement de ce capteur est simple. Il suffit de dessiner au crayon à papier sur une feuille et d'appliquer ensuite une contrainte sur celle-ci. La contrainte appliquée va modifiée la distance entre les particules de graphique et par conséquent la résistance au passage du courant. Nous avons donc notre capteur. 

<img src="C:\Users\Marie\OneDrive - insa-toulouse.fr\Documents\Insa\4ème année\2nd semestre\Capteur\Dossier final\Github\papier graphite.png">

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

## 5. KICAD <a id="CinquiemeSection"></a>
### 5.1. Symboles et empreintes des composants <a id="CinquiemeSection1"></a>
* Amplificateur LTC1050

<img src="/Images/LTC1050_schematic.png" height="200"> <img src="/Images/LTC1050_footprint.png" height="200">

* Ecran OLED

<img src="/Images/OLED_schematic.png" height="200"> <img src="/Images/OLED_footprint.png" height="200">

* Encodeur rotatoire KY_040

<img src="/Images/KY_040_schematic.png" height="200"> <img src="/Images/KY_040_footprint.png" height="200">

* Module bluetooth HC05

<img src="/Images/Bluetooth-HC05_schematic.png" height="200"> <img src="/Images/Bluetooth_HC05_footprint.png" height="200">


### 5.2. Schématique <a id="CinquiemeSection2"></a>
<img src="/Images/Schematic.png">

Une fois les empreintes créées, nous avons réalisé le schéma de notre shield. En haut à droite sont représentées les broches de la carte Arduino. En haut au milieu est représenté l'amplificateur transimpédance et en bas du schématique se trouvent l'écran OLED, le module bluetooth et l'encodeur rotatoire.

### 5.3. Placement des composants <a id="CinquiemeSection3"></a>
<img src="/Images/PCB_2D.png">

### 5.4. Visualisation 3D <a id="CinquiemeSection4"></a>
<img src="/Images/PCB_3D.png">

## 6. Fabrication du shield <a id="SixiemeSection"></a>
<img src="/Images/PCB_front.png" height="300"> <img src="/Images/PCB_back.png" height="300">

### 6.1. Réalisation du PCB <a id="SixiemeSection1"></a> 
Le PCB a été réalisé au sein des départements de Génie Physique (GP) et Génie Électrique et Informatique (GEI) de l'INSA Toulouse avec l'aide de Catherine Crouzet. Notre PCB à été fabriqué à partir d'une plaquette d'epoxy recouverte d'une fine couche de cuivre (environ 60μm). 
Nous avons imprimé sur du papier calque la modélisation de notre PCB effectuée sur le logiciel *KICAD* pour ensuite insoler aux UV notre plaquette avec la silouhette par-dessus pendant quelques minutes. À l'aide d'un révelateur, nous avons retiré la partie de la résine non insolée.
La plaquette d'expoxy est ensuite placée dans un bain de perchlorure de fer pour la gravure, opération durant 7 minutes. Le cuivre non protégé par la résine est ainsi retiré de la plaquette ce qui nous permet d'obtenir le PCB avec les pistes souhaitées.
Enfin, de l'acétone est appliquée sur la plaquette pour éliminer les dernières traces de résine.

### 6.2. Perçage et soudure <a id="SixiemeSection2"></a> 
Nous avons ensuite percé notre PCB aux endroits où les différents composants seront insérés à l'aide d'une perceuse électrique. Le diamètre des trous dépend des différents composants à placer :
* ⌀ 0.8mm : AOP LTC1050, résistances et capacités
* ⌀ 1.0mm : Broches de connexion de la carte Arduino Uno et headers des différents modules (OLED, bluetooth, encodeur rotatoire)
* ⌀ 1.2mm : Broches de connexion du capteur de déformation

Notre PCB ayant été imprimé en face avant, certains composants ont été placé en face avant et d'autres en face arrière pour faciliter la soudure et la connexion à la carte Arduino Uno.

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
