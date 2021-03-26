//Nicole Prem 18337
//Lab 5: Tarjeta SD
#include <SPI.h>
#include <SD.h>

File root; //Para leer los archivos en SD
File myFile;
//#define int inByte;
//**************************************************************************************************************
//Prototipos de funciones
//**************************************************************************************************************
void printDirectory(File dir, int numTabs); //Prototipo de función
void menu (int personajes);
//**************************************************************************************************************
//Variables
//**************************************************************************************************************
int inByte; //variable que tiene el valor de lo que se ingresa en la terminal
int personajes; //variable para desplegar los personajes disponibles

void setup() {
  // put your setup code here, to run once
  //Inicia código para abrir los archivos en SD******************//
  // Open serial communications and wait for port to open:

  Serial.begin(115200);
  SPI.setModule(0);

  Serial.print("Initializing SD card...");
  pinMode(PA_3, OUTPUT);

  if (!SD.begin(PA_3)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  menu(1);
  //

}

void loop() {

  //personajes=0;
  if (Serial.available()) {
    //char inByte;
    inByte = Serial.read();
    //Para mostrar a Yoshi se debe de mandar 1 a la terminal
  }
  if (inByte == '1') {
    myFile = SD.open("Yoshi.txt"); //"nombre del archivo"
    if (myFile) {

      // read from the file until there's nothing else in it:
      while (myFile.available()) {
        Serial.write(myFile.read());
      }
      // close the file:
      myFile.close();
      menu(1);
    } else {
      // if the file didn't open, print an error:
      Serial.println("error opening test.txt");
      menu(1);
    }
    inByte = 0;
  }

  //Para mostrar a Toad se debe mandar 2 a la terminal
  else if (inByte == '2') {
    myFile = SD.open("Toad.txt"); //"nombre del archivo"
    if (myFile) {

      // read from the file until there's nothing else in it:
      while (myFile.available()) {
        Serial.write(myFile.read());
      }
      // close the file:
      myFile.close();
      menu(1);
    } else {
      // if the file didn't open, print an error:
      Serial.println("error opening test.txt");
      menu(1);
    }
    inByte = 0;
  }

  else if (inByte == '3') {
    myFile = SD.open("Boo.txt"); //"nombre del archivo"
    if (myFile) {

      // read from the file until there's nothing else in it:
      while (myFile.available()) {
        Serial.write(myFile.read());


      }
      // close the file:
      myFile.close();
      menu(1);
    } else {
      // if the file didn't open, print an error:
      Serial.println("error opening test.txt");
      menu(1);
    }
    inByte = 0;
  }



}

//**************************************************************************************************************
//Funciones
//**************************************************************************************************************

//Código para abrir los archivos presentes en SD
void printDirectory(File dir) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }

    Serial.println(entry.name());

    entry.close();
  }
}

void menu (int personajes) {

  if (personajes == 1) {
    Serial.println();
    Serial.println("Escoja la opcion a desplegar");
    root = SD.open("/");
    root.rewindDirectory();
    //printDirectory(root);
    while (true) {

      File entry =  root.openNextFile();
      if (! entry) {
        // no more files
        break;
      }

      Serial.println(entry.name());

      entry.close();
    }
    Serial.println("done!");
  }

}
