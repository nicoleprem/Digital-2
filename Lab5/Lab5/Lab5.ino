//Nicole Prem 18337
//Lab 5: Tarjeta SD
#include <SPI.h>
#include <SD.h>

File root; //Para leer los archivos en SD
File myFile;

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

  root = SD.open("/");

  printDirectory(root, 0);

  Serial.println("done!");

}

void loop() {
  // put your main code here, to run repeatedly: 
  
}

//Código para abrir los archivos presentes en SD
void printDirectory(File dir, int numTabs) {
   while(true) {
     
     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }
     Serial.print(entry.name());
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       // files have sizes, directories do not
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
     }
     entry.close();
   }
}
