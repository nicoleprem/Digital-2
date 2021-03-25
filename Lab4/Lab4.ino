//Nicole Prem 18337 
//Lab 4: Juego Carrera en Tiva C

//********************************************************************************
//Variables
//********************************************************************************
#define LEDR PF_1 //Led rojo para el semáforo
#define LEDV PF_3 //Led verde del semáforo
#define LEDA PF_2 //Led azul para mostrar el ganador
#define BotonJ1 PUSH1 //Botón del jugador 1
#define BotonJ2 PUSH2 //Botón del jugador 2
//#define RESET PF_RST //Botón de reset

unsigned char C1; //parámetro de entrada para función de leds J1
unsigned char C2; //parámetro de entrada para función de leds J2
unsigned char contadorJ1 = 0; //Contador del jugador 1, si llega a 8 gana
unsigned char contadorJ2 = 0; //Contador del jugador 2, si llega a 8 gana
unsigned int bandera = 1; //bandera para identificar al ganador
unsigned int banderaJ1=0; //bandera para identificar si se apachó el botón del J1
unsigned int banderaJ2=0; //bandera para identificar si se apachó el botón del J2
char debounce=0; //bandera utilizada para implementar el antirrebote
int BotonJ1_State=0; //Estado del botón 1
int BotonJ2_State=0; //Estado del boton 2
int flagJ=0; //bandera para el antirrebote del semáforo la cual cambia dependiendo quién presionó el botón


//********************************************************************************
//Prototipos de funciones
//********************************************************************************
void semaforo (void); //función del semáforo
void ledsJ1 (unsigned char C1); //función para mostrar los leds del jugador 1
void ledsJ2 (unsigned char C2); //función para mostrar los leds del jugador 2


void setup() {
  pinMode(LEDR, OUTPUT); //Definición del led rojo como output
  pinMode(LEDV, OUTPUT); //Definición del led verde como output
  pinMode(BotonJ1, INPUT_PULLUP); //Definición del botón del jugador 1 como input en pullup
  pinMode(BotonJ2, INPUT_PULLUP); //Definición del botón del jugador 2 como input en pullup
//  pinMode(RESET, INPUT_PULLUP);
  //PINES PARA LOS LEDS JUGADOR 1
  pinMode(PB_5, OUTPUT); //Led0 del jugador 1
  pinMode(PB_0, OUTPUT); //Led1 del jugador 1
  pinMode(PB_1, OUTPUT); //Led2 del jugador 1
  pinMode(PE_4, OUTPUT); //Led3 del jugador 1
  pinMode(PE_5, OUTPUT); //Led4 del jugador 1
  pinMode(PB_4, OUTPUT); //Led5 del jugador 1
  pinMode(PA_5, OUTPUT); //Led6 del jugador 1
  pinMode(PA_6, OUTPUT); //Led7 del jugador 1
  //PINES PARA LOS LEDS JUGADOR 2
  pinMode(PD_0, OUTPUT); //Led0 del jugador 2
  pinMode(PD_1, OUTPUT); //Led1 del jugador 2
  pinMode(PD_2, OUTPUT); //Led2 del jugador 2
  pinMode(PD_3, OUTPUT); //Led3 del jugador 2
  pinMode(PE_1, OUTPUT); //Led4 del jugador 2
  pinMode(PE_2, OUTPUT); //Led5 del jugador 2
  pinMode(PE_3, OUTPUT); //Led6 del jugador 2
  pinMode(PD_6, OUTPUT); //Led7 del jugador 2
}

void loop() {
   //Condiciones iniciales:
   contadorJ1 = 0;
   contadorJ2 = 0;
   ledsJ1(contadorJ1);
   ledsJ2(contadorJ2);
   banderaJ1=0;
   banderaJ2=0;
   BotonJ1_State=digitalRead(BotonJ1);
   BotonJ2_State=digitalRead(BotonJ2);
   debounce=0;
   flagJ=0;
   //Determinación de quién presionó el botón de inicio junto con antirrebote del mismo botón
   if(BotonJ1_State==LOW or BotonJ2_State==LOW){
    if (BotonJ1_State==LOW){
      flagJ=2;
    }
    else if (BotonJ2_State==LOW){
      flagJ=1;
    }
    while (debounce==0){ //antirrebote
      BotonJ1_State=digitalRead(BotonJ1);
      BotonJ2_State=digitalRead(BotonJ2);
      if(BotonJ1_State==HIGH and flagJ==2){
      debounce=1;
      }
      else if(BotonJ2_State==HIGH and flagJ==1){
        debounce=1;
      }
    }  
  
   semaforo();
    bandera=1;
    
          while (bandera == 1) {
            BotonJ1_State=digitalRead(BotonJ1);
            BotonJ2_State=digitalRead(BotonJ2);
            debounce=0;
              if (BotonJ1_State == LOW) { //Se presiona botón J1
                  while(debounce==0){//Antirrebote
                    BotonJ1_State=digitalRead(BotonJ1);
                    BotonJ2_State=digitalRead(BotonJ2);
                    if(BotonJ1_State==HIGH){
                      debounce=1;
                      }
                    }
                     delay(200);    
                      contadorJ1++; //se incrementa el contador 
                      ledsJ1(contadorJ1); //se va a la función ledsJ1 para encender los leds del jugador 1
                      
                      if (contadorJ1 == 8) { //verificación si ya ganó
                          bandera = 2; //se sale del ciclo 
                      }
                  }
               else if (BotonJ2_State == LOW) { //Se presiona botón J2
                 while(debounce==0){//Antirrebote
                  BotonJ1_State=digitalRead(BotonJ1);
                  BotonJ2_State=digitalRead(BotonJ2);
                    if(BotonJ2_State==HIGH){
                      debounce=1;
                      }
                 }
                      delay(200);
                      contadorJ2++; //se incrementa el contador
                      ledsJ2(contadorJ2); //se va a la función ledsJ2 para encender los leds del jugador 2

                      if (contadorJ2 == 8) { //verificación si ya ganó
                          bandera = 2; //se sale del ciclo

                  }

                }

            }
    
    
    }
}


//********************************************************************************
//Funciones
//********************************************************************************
//Función del semáfoto
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

 
// Rutina para desplegar los leds del J1
void ledsJ1(unsigned char C1) {
    if (C1 == 8) { //se verifica si ya presionó el botón 8 veces y si ya ganó entonces se enciende el led azul trez veces
        digitalWrite(PA_5,LOW); //se apaga el led 6
        digitalWrite(PA_6, HIGH); //se enciende led 7
        digitalWrite(LEDV, HIGH);
        delay(1000);
        digitalWrite(LEDV, LOW);
        delay(1000);
        digitalWrite(LEDV, HIGH);
        delay(1000);
        digitalWrite(LEDV, LOW);
        delay(1000);
        digitalWrite(LEDV, HIGH);
        delay(1000);
        digitalWrite(LEDV, LOW);
        delay(1000);  
        digitalWrite(PA_6, LOW);      
    }
/*Case que indica el led que se enciende dependiendo de la cantidad de veces
 que ha presionado el botón */
        switch (C1) {
          case 0:
            digitalWrite(PB_5, LOW); //Led0 del jugador 1
           digitalWrite(PB_0, LOW); //Led1 del jugador 1
           digitalWrite(PB_1, LOW); //Led2 del jugador 1
           digitalWrite(PE_4, LOW); //Led3 del jugador 1
           digitalWrite(PE_5, LOW); //Led4 del jugador 1
           digitalWrite(PB_4, LOW); //Led5 del jugador 1
           digitalWrite(PA_5, LOW); //Led6 del jugador 1
           digitalWrite(PA_6, LOW); //Led7 del jugador 1          
          break;
            case 1: //se enciende led 0
                digitalWrite(PB_5, HIGH);
                break;
            case 2: //se enciende led 1
                digitalWrite(PB_5, LOW);
                digitalWrite(PB_0, HIGH);
                break;
            case 3: //se enciende led 2
                digitalWrite(PB_0, LOW);
                digitalWrite(PB_1, HIGH);
                break;
            case 4: //se enciente led 3
                digitalWrite(PB_1, LOW);
                digitalWrite(PE_4, HIGH);
                break;
            case 5: //se enciente led 4
                digitalWrite(PE_4, LOW);
                digitalWrite(PE_5, HIGH);
                break;
            case 6: //se enciende led 5
                digitalWrite(PE_5, LOW);
                digitalWrite(PB_4, HIGH);
                break;
            case 7: //se enciende led 6
                digitalWrite(PB_4, LOW);
                digitalWrite(PA_5, HIGH);
                break;
            
        }
}

// Rutina para desplegar los leds del J2
void ledsJ2(unsigned char C2) {
    if (C2 == 8) { //se verifica si ya presionó 8 veces el botón y si ya ganó se enciende el led rojo tres veces para mostrar que el es el ganador
        digitalWrite(PE_3, LOW); //se apaga el led 6
        digitalWrite(PD_6, HIGH); //se enciende led 7
        digitalWrite(LEDR, HIGH);
        delay(1000);
        digitalWrite(LEDR, LOW);
        delay(1000);
        digitalWrite(LEDR, HIGH);
        delay(1000);
        digitalWrite(LEDR, LOW);
        delay(1000);
        digitalWrite(LEDR, HIGH);
        delay(1000);
        digitalWrite(LEDR, LOW);
        delay(1000);
        digitalWrite(PD_6, LOW);
    }
/*Case que indica el led que se enciende dependiendo de la cantidad de veces
 que ha presionado el botón */
    switch (C2) {
      case 0:
       digitalWrite(PD_0, LOW); //Led0 del jugador 2
      digitalWrite(PD_1, LOW); //Led1 del jugador 2
      digitalWrite(PD_2, LOW); //Led2 del jugador 2
      digitalWrite(PD_3, LOW); //Led3 del jugador 2
     digitalWrite(PE_1, LOW); //Led4 del jugador 2
     digitalWrite(PE_2, LOW); //Led5 del jugador 2
      digitalWrite(PE_3, LOW); //Led6 del jugador 2
     digitalWrite(PD_6, LOW); //Led7 del jugador 2
     break;
       case 1: //se enciende led 0
                digitalWrite(PD_0, HIGH);
                break;
            case 2: //se enciende led 1
                digitalWrite(PD_0, LOW);
                digitalWrite(PD_1, HIGH);
                break;
            case 3: //se enciende led 2
                digitalWrite(PD_1, LOW);
                digitalWrite(PD_2, HIGH);
                break;
            case 4: //se enciente led 3
                digitalWrite(PD_2, LOW);
                digitalWrite(PD_3, HIGH);
                break;
            case 5: //se enciente led 4
                digitalWrite(PD_3, LOW);
                digitalWrite(PE_1, HIGH);
                break;
            case 6: //se enciende led 5
                digitalWrite(PE_1, LOW);
                digitalWrite(PE_2, HIGH);
                break;
            case 7: //se enciende led 6
                digitalWrite(PE_2, LOW);
                digitalWrite(PE_3, HIGH);
                break;
    }
}
