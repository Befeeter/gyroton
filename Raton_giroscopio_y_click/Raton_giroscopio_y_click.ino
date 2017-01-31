/* Codig para controlar el ratón y poder hacer click con el giroscopio.
 * cambia los valores de procesado de vx e vy para ajustarlo a tus datos 
 * obtenidos en el calibrador.
*/

#include <Wire.h>
#include <I2Cdev.h>
#include <Adafruit_L3GD20.h>
#include <Mouse.h>


Adafruit_L3GD20 gyro;
int vx, vy, vx_prec, vy_prec;
int count=0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  gyro.begin(gyro.L3DS20_RANGE_250DPS);
}

void loop() {
 gyro.read();

  vx = -(gyro.data.x); // Se establece el valor del eje x
  vy = -(gyro.data.z); // Se establece el valor dle eje y

  
  Mouse.move(vx, vy);
  
  
  if ( (vx_prec-5)<=vx && vx<=vx_prec+5 && (vy_prec-5)<=vy && vy<=vy_prec+5) { // Comprobamos que el ratón no se ha movido en un area mayor de 10 pixeles en los ultimos segundos
    count++;                                                                  
    if(count == 100){ // Se producirá el click despues de pasar 2 segundos sin salir de un cuadrado de 10 pixeles: 20ms de retraso 100 veces hacen 2000ms = 2s
      if (!Mouse.isPressed(MOUSE_LEFT)) {
        Mouse.press(MOUSE_LEFT);
        count = 0;
      }
    }
    else {
      if (Mouse.isPressed(MOUSE_LEFT)) {
        Mouse.release(MOUSE_LEFT);
      }
    }
  }
  else {
    vx_prec = vx; // actualizando valores para permitir el click.
    vy_prec = vy;
    count = 0;
    }
  
  delay(20);
}
