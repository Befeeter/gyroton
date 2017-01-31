



/* Este codigo será utilizado para poder visualizar los valores 
 *  del girospcopio a la vez de los que mandamos a las cordenadas 
 *  X e Y de nuestro ratón, de modo que podamos calibrar (ajustar)
 *  estos valores para cada persona y cada pantalla que estemos utilizando.
*/

#include <Wire.h>
#include <I2Cdev.h>
#include <LSM303.h>
#include <Mouse.h>
#include <Adafruit_L3GD20.h>



Adafruit_L3GD20 gyro;
int16_t ax, ay, az, gx, gy, gz;
int vx, vy;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  gyro.begin(gyro.L3DS20_RANGE_250DPS);
}

void loop() {
  gyro.read();

  vx = -(gyro.data.x); // Se establece el valor del eje x
  vy = -(gyro.data.z); // Se establece el valor dle eje y

  Serial.print("gx = ");
  Serial.print( gyro.data.x);
  Serial.print(" | gz = ");
  Serial.print(gyro.data.y);

  Serial.print("        | X = ");
  Serial.print(vx);
  Serial.print(" | Y = ");
  Serial.println(vy);

  Mouse.move(vx, vy);

  delay(20);
}
