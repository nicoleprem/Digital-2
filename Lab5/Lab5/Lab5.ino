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
void printDirectory(File dir, int numTabs); //Función obtenida del ejemplo para imprimir lo que hay en la SD
void menu (int personajes); //Función para mostrar lo que hay en la SD
//**************************************************************************************************************
//Variables
//**************************************************************************************************************
int inByte; //variable que tiene el valor de lo que se ingresa en la terminal
int personajes; //variable para desplegar los personajes disponibles

void setup() {
  //Inicia código para abrir los archivos en SD******************//
  // Open serial communications and wait for port to open:

  Serial.begin(115200);
  SPI.setModule(0); //Activar la comunicación SPI

  Serial.print("Initializing SD card...");
  pinMode(PA_3, OUTPUT);

  if (!SD.begin(PA_3)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  menu(1);
}

void loop() {
  //Comprobar disponibilidad la comunicación
  if (Serial.available()) {
    //char inByte;
    inByte = Serial.read();

  }
  //Para mostrar a Yoshi se debe de mandar 1 a la terminal
  if (inByte == '1') {
    myFile = SD.open("Fondo.txt"); //Abrir la imagen de Yoshi
    if (myFile) {

      //leer el archivo
      while (myFile.available()) {
        Serial.write(myFile.read());
      }
      //cerrar el archivo
      myFile.close();
      menu(1);
    } else {
      //si no se abre el archivo mostrar que hubo un error
      Serial.println("error opening Yoshi.txt");
      menu(1);
    }
    inByte = 0;
  }

  //Para mostrar a Toad se debe mandar 2 a la terminal
  else if (inByte == '2') {
    myFile = SD.open("Toad.txt"); //Abrir la imagen de Toad
    if (myFile) {

      //leer el archivo
      while (myFile.available()) {
        Serial.write(myFile.read());
      }
      //cerrar el archivo
      myFile.close();
      menu(1);
    } else {
      //si no se abre el archivo mostrar que hubo un error
      Serial.println("error opening Toad.txt");
      menu(1);
    }
    inByte = 0;
  }
 //Para mostrar a Boo se debe mandar 3 a la terminal
  else if (inByte == '3') {
    myFile = SD.open("Boo.txt"); //Abrir la imagen de Boo
    if (myFile) {

      //leer el archivo
      while (myFile.available()) {
        Serial.write(myFile.read());
      }
      //cerrar el archivo
      myFile.close();
      menu(1);
    } else {
      //si no se abre el archivo mostrar que hubo un error
      Serial.println("error opening Boo.txt");
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
    while (true) {
      //Abrir los archivos que existen en la SD
      File entry =  root.openNextFile();
      if (! entry) {
        // no more files
        break;
      }
      //Imprimir los nombres de los archivos en la SD
      Serial.println(entry.name());
      //Cerrar los archivos en la SD
      entry.close();
    }
    //Serial.println("done!");
  }

}
