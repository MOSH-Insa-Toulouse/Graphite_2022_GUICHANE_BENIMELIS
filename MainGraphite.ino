#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

int ResistancePin = A0; //the analog pin the TMP36's Vout (sense) pin is connected to
                        //the resolution is 10 mV / degree centigrade
                        //(500 mV offset) to make negative temperatures an option

float R5 = 10000.0;
float R1 = 100000.0;
float Rcal = 1000.0;
float R3 = 100000.0;
float R6 = 1000.0;
float Vcc = 5.0;

#include <Adafruit_SSD1306.h>

#define nombreDePixelsEnLargeur 128         // Taille de l'écran OLED, en pixel, au niveau de sa largeur
#define nombreDePixelsEnHauteur 64          // Taille de l'écran OLED, en pixel, au niveau de sa hauteur
#define brocheResetOLED         -1          // Reset de l'OLED partagé avec l'Arduino (d'où la valeur à -1, et non un numéro de pin)
#define adresseI2CecranOLED     0x3C        // Adresse de "mon" écran OLED sur le bus i2c (généralement égal à 0x3C ou 0x3D)

Adafruit_SSD1306 ecranOLED(nombreDePixelsEnLargeur, nombreDePixelsEnHauteur, &Wire, brocheResetOLED);

/////////Encodeur/////////
#define encoder0PinA  3  //CLK 
#define encoder0PinB  4  //DT 
#define sw 2 // Switch 

/////////Bluetooth/////////
#include <SoftwareSerial.h>
#define rxPin 11 //Broche 5 en tant que RX, � raccorder sur TX du HC-05
#define txPin 10 //Broche 6 en tant que RX, � raccorder sur TX du HC-05
#define baudrate 9600
SoftwareSerial mySerial(rxPin ,txPin);

/////////Variables/////////
int menu = 1; //Variable permettant de choisir le menu
int menuState = 0; //Booléen: Si = 0: update le menu, si = 1: rentre dans la fonction

/////////Variables Debounce/////////
int lastButtonState = LOW; //Stocke la dernière valeur du pin DT
long lastDebounceTime1 = 0; //Première Variable de stockage de temps
long lastDebounceTime2 = 0; //Deuxième variable de stockage de temps


void setup()
{ 
  pinMode(encoder0PinA, INPUT); 
  digitalWrite(encoder0PinA, HIGH);  

  pinMode(encoder0PinB, INPUT); 
  digitalWrite(encoder0PinB, HIGH);      

  pinMode(sw, INPUT_PULLUP);

  attachInterrupt(1, doEncoder, RISING); // Appelle la fonction doEncoder qui incrémente la variable menu
  attachInterrupt(0, Action, CHANGE); //Appelle la fonction Action qui incrémente ou décrémente le booléen menuState

  if(!ecranOLED.begin(SSD1306_SWITCHCAPVCC, adresseI2CecranOLED)) // Arrêt du programme (boucle infinie) si échec d'initialisation 
    while(1);
    ecranOLED.setTextColor(WHITE);
    
  pinMode(rxPin,INPUT); // variable de reception de donnée via RX
  pinMode(txPin,OUTPUT); // variable de transmission de données via TX  
  mySerial.begin(9600);
  
  updateMenu();
  Serial.begin(9600);
  
}

void loop() {
  float resistance = getResistance(ResistancePin); //Récupération de la valeur de résistance provenant du pin A0
  
  if (menuState == 1){      //Condition si le booléen=1: affiche la fonction décrite par la variable menu
    executeAction();
    if (menu == 4){       //Initialise le booléen à 0 lorsqu'on sort de la fonction 4 (Graphique)
      menuState = 0;
    }
  }
  if (menuState == 0){      //Update le menu tant que le booléen est à 0
  updateMenu();
  }
  
  mySerial.write(getResistance(ResistancePin)/1000000);  //Écriture sur le port bluetooth
  Serial.println(getResistance(ResistancePin)/1000000);  //Écriture sur le port série
  while (mySerial.available()){
  Serial.print((char)mySerial.read());  
  }
  delay(1000);
}           

////////// Menu de l'écran OLED ////////////
void updateMenu() {
  switch (menu) {
    
    case 0:
      menu = 1;
      break;
    case 1:
      ecranOLED.clearDisplay();
      ecranOLED.setTextSize(1);
      ecranOLED.setCursor(0, 0);
      ecranOLED.println(">Resistance");
      ecranOLED.setCursor(0, 10);
      ecranOLED.println("Date");
      ecranOLED.setCursor(0, 20);
      ecranOLED.println("Heure");
      ecranOLED.setCursor(0, 30);
      ecranOLED.println("Graphique");
      ecranOLED.display();
      break;
    case 2:
      ecranOLED.clearDisplay();
      ecranOLED.setTextSize(1);
      ecranOLED.setCursor(0, 0);
      ecranOLED.println("Resistance");
      ecranOLED.setCursor(0, 10);
      ecranOLED.println(">Date");
      ecranOLED.setCursor(0, 20);
      ecranOLED.println("Heure");
      ecranOLED.setCursor(0, 30);
      ecranOLED.println("Graphique");
      ecranOLED.display();
      break;
    case 3:
      ecranOLED.clearDisplay();
      ecranOLED.setTextSize(1);
      ecranOLED.setCursor(0, 0);
      ecranOLED.println("Resistance");
      ecranOLED.setCursor(0, 10);
      ecranOLED.println("Date");
      ecranOLED.setCursor(0, 20);
      ecranOLED.println(">Heure");
      ecranOLED.setCursor(0, 30);
      ecranOLED.println("Graphique");
      ecranOLED.display();
      break;
    case 4:
      ecranOLED.clearDisplay();
      ecranOLED.setTextSize(1);
      ecranOLED.setCursor(0, 0);
      ecranOLED.println("Resistance");
      ecranOLED.setCursor(0, 10);
      ecranOLED.println("Date");
      ecranOLED.setCursor(0, 20);
      ecranOLED.println("Heure");
      ecranOLED.setCursor(0, 30);
      ecranOLED.println(">Graphique");
      ecranOLED.display();
      break;      
    case 5:
      menu = 4;
      break;
    
  }
}

////////// Appel des actions à suivre en fonction des cas ////////////
void executeAction() {
  switch (menu) {
    case 1:
      action1();
      break;
    case 2:
      action2();
      break;
    case 3:
      action3();
      break;
    case 4:
      action4();
      break;
  }
}

////////// Actions à suivre en fonction des cas////////////
void action1() {        //Affichage de la résistance en direct
  ecranOLED.clearDisplay();
  ecranOLED.setTextSize(1);
  ecranOLED.setCursor(0, 0);
  ecranOLED.println("Resistance Graphene");
  
  ecranOLED.setTextSize(1);
  float resistance = getResistance(ResistancePin);
  ecranOLED.setCursor(0, 20);
  ecranOLED.println(resistance);
  ecranOLED.setCursor(100, 20);
  ecranOLED.println("Ohm");
  ecranOLED.setCursor(0,50);
  ecranOLED.println(">Quitter");
  ecranOLED.setCursor(64,50);
  ecranOLED.println(">Suivant");
  ecranOLED.display();
  delay(300);

}

void action2() {        //Affichage de la date
  ecranOLED.clearDisplay();
  ecranOLED.setTextSize(2);
  ecranOLED.setTextSize(2);
  ecranOLED.setCursor(0, 0);
  ecranOLED.println("DATE");
  ecranOLED.setTextSize(1);
  ecranOLED.setCursor(0, 20);
  ecranOLED.println("Joyeux anniversaire Cathy!");
  ecranOLED.setCursor(0,50);
  ecranOLED.println(">Quitter");
  ecranOLED.setCursor(64,50);
  ecranOLED.println(">Suivant");
  ecranOLED.display();
  delay(300);
}

void action3() {        //Affichage de l'heure
  ecranOLED.clearDisplay();
  ecranOLED.setTextSize(2);
  ecranOLED.setCursor(0, 0);
  ecranOLED.println("Heure");
  ecranOLED.setTextSize(1);
  ecranOLED.setCursor(0, 20);
  ecranOLED.println("Il est deja deux secondes de plus par rapport au debut du message");
  ecranOLED.setCursor(0,55);
  ecranOLED.println(">Quitter");
  ecranOLED.setCursor(64,55);
  ecranOLED.println(">Suivant");
  ecranOLED.display();
  delay(300);
}

///////////////////Affichage du graphique//////////////////

void action4() {
  ecranOLED.clearDisplay();
  float Rmax = 80000000;  //On définit Rmax et Rminpour pouvoir ramener la valeur de la résistance de 0 à 64 (pixels)
  float Rmin = 10000000;
  int i = 0;
  float resistance;
  
  ecranOLED.drawLine(7,3,7,40,WHITE);  //On dessine les limites du jeu, on doit éviter ces lignes verticales
  ecranOLED.drawLine(15,64,15,49,WHITE);
  ecranOLED.drawLine(30,20,30,40,WHITE);
  ecranOLED.drawLine(47,54,47,34,WHITE);
  ecranOLED.drawLine(64,0,64,64,WHITE);

  
  //unsigned long currentMillis = millis();  //On définit les variables de temps
  unsigned long previousMillis = 0;
  const long interval = 1000;
  int x = 0;
  
  //Tant qu'on a pas appuyé sur l'interrupteur, la boucle continu
  while (millis() != 64){
    //Déclenchement de la condition toutes les 1s
    if (millis() - previousMillis >= interval) {
      resistance = getResistance(ResistancePin);
      previousMillis = millis();
      
      x++;  //Norme de temps sur 1s et non 1000ms
      int resistanceNormee = 64 - (((resistance-Rmin)/(Rmax-Rmin))*64);  //On définit la resistance Normée de 0 à 64 pixels. On rajoute 64 - ... devant pour que le graphique ne soit pas inversé
      
      if (resistanceNormee > 64){
        resistanceNormee = 64;
      }
      if (resistanceNormee < 10){
        resistanceNormee = 10;
      }
      
      Serial.print("Rnorm :");
      Serial.print(resistanceNormee);
      Serial.print("x:");
      Serial.print(x);
      ecranOLED.drawPixel(x, resistanceNormee, WHITE);  //On dessine un pixel toutes les secondes à y=resistanceNormee en fonction de x=t (s) 
      ecranOLED.display();

      //Si le pixel touche la première ligne, on perd
      if ((resistanceNormee >= 3) && (resistanceNormee <= 40) && (x == 7)){
        ecranOLED.clearDisplay();
        ecranOLED.setTextSize(2);
        ecranOLED.setCursor(0, 0);
        ecranOLED.println("PERDU!");
        ecranOLED.setCursor(0,50);
        ecranOLED.println(">Quitter");
        ecranOLED.display();
        delay(5000);
        updateMenu();
        break;
      }

      //Si le pixel touche la troisième ligne, on perd
      if ((resistanceNormee >= 49) && (resistanceNormee <= 64) && (x == 15)){
        ecranOLED.clearDisplay();
        ecranOLED.setTextSize(2);
        ecranOLED.setCursor(0, 0);
        ecranOLED.println("PERDU!");
        ecranOLED.setCursor(0,50);
        ecranOLED.println(">Quitter");
        ecranOLED.display();
        delay(5000);
        updateMenu();
        break;
      }
      
      //Si le pixel touche la quatrième ligne, on perd
      if ((resistanceNormee >= 20) && (resistanceNormee <= 40) && (x == 30)){
        ecranOLED.clearDisplay();
        ecranOLED.setTextSize(2);
        ecranOLED.setCursor(0, 0);
        ecranOLED.println("PERDU!");
        ecranOLED.setCursor(0,50);
        ecranOLED.println(">Quitter");
        ecranOLED.display();
        delay(5000);
        updateMenu();
        break;
      }

      if ((resistanceNormee >= 34) && (resistanceNormee <= 54) && (x == 46)){
        ecranOLED.clearDisplay();
        ecranOLED.setTextSize(2);
        ecranOLED.setCursor(0, 0);
        ecranOLED.println("PERDU!");
        ecranOLED.setCursor(0,50);
        ecranOLED.println(">Quitter");
        ecranOLED.display();
        delay(5000);
        updateMenu();
        break;
      }

      //Si le pixel est arrivé au bout, on gagne
      if(x == 64){
        ecranOLED.clearDisplay();
        ecranOLED.setTextSize(2);
        ecranOLED.setCursor(0, 0);
        ecranOLED.println("GAGNE!");
        ecranOLED.setCursor(0,50);
        ecranOLED.println(">Quitter");
        ecranOLED.display();
        delay(5000);
        updateMenu();
        break;
      }
    }
    delay(300);
    //Si on appuie sur l'interrupteur, on quitte la boucle
    if (digitalRead(sw)==LOW){
    break;
    }
  }
  ecranOLED.clearDisplay();
}

void doEncoder(){
  int reading = digitalRead(encoder0PinB);
  int Temps = millis(); //Temps depuis lequel s'est exécuté le programme
  if (((Temps - lastDebounceTime1) > 200) && (reading != lastButtonState)){  //1er debounce du DT et de la CLK
    lastDebounceTime1 = Temps;  //Stockage de la dernière valeur de temps
    if (reading==HIGH){
      menu++;  //Incrémentation du menu
      if (menu > 4){  //Si on dépasse le nombre de variables dans le menu, on revient à la 1ère variable
        menu = 1;
      }
      lastButtonState = LOW;  //Stockage du dernier état du DT
    } 
  }
}


void Action(){
  int Time = millis(); //Temps depuis lequel s'est exécuté le programme
  if (((Time - lastDebounceTime1) > 500)){  //2ème debounce du SW
    lastDebounceTime1 = Time;
    menuState++;
    if (menuState == 2){  //Si on dépasse 1, on revient à 0: on veut un booléen
      menuState = 0;
    }  
  } 
}                

float getResistance(int pin) {        //Récupération de la valeur de tension sur A0 puis conversion en résistance
  float voltage = analogRead(pin)*0.004882814;  //Conversion * 5(Tension) / 1024(Nombre de bits)
return ((1+(R3/Rcal))*R1*Vcc/voltage-R1-R5);  //Relation entre la tension d'entrée et de sortie 
}
