//Nicole Prem 18337 
//Lab 4: Juego Carrera en Tiva C

//********************************************************************************
//Variables
//********************************************************************************
#define LEDR PF_1 //Led rojo para el semáforo
#define LEDV PF_3 //Led verde del semáforo
#define BotonJ1 PF_4 //Botón del jugador 1
#define BotonJ2 PF_0 //Botón del jugador 2

unsigned char C1; //parámetro de entrada para función de leds J1
unsigned char C2; //parámetro de entrada para función de leds J2
unsigned char contadorJ1 = 0; //Contador del jugador 1, si llega a 8 gana
unsigned char contadorJ2 = 0; //Contador del jugador 2, si llega a 8 gana
unsigned int bandera = 1; //bandera para identificar al ganador



//********************************************************************************
//Prototipos de funciones
//********************************************************************************
void semaforo (void);



void setup() {
  pinMode(LEDR, OUTPUT);
  pinMode(LEDV, OUTPUT);
  semaforo ();

}

void loop() {
   // if (BotonJ1 == 0){
   // digitalWrite(LEDR, HIGH);
    //}
}

//********************************************************************************
//Funciones
//********************************************************************************
void semaforo (void){
  digitalWrite(LEDR, HIGH); //Encender led rojo
  delay(1000); //esperamos 1 segundo
  digitalWrite(LEDV, HIGH); //Encender led rojo y verde al mismo tiempo para crar color amarillo
  delay(1000); //esperamos 1 segundo
  digitalWrite(LEDR, LOW);
  delay(1000);
  digitalWrite(LEDV, LOW);
  delay(1000);
  
  
  
  }
