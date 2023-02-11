// Basic demo for accelerometer readings from Adafruit MPU6050

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

float AcX,AcY,AcZ;
float ax_offset, ay_offset, az_offset;
float GcX,GcY,GcZ;
float gx_offset, gy_offset, gz_offset;

Adafruit_MPU6050 mpu;

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }
  Serial.println("");
  delay(100);
}

void loop() {

  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  int samples = 500;
  float ax_sum = 0, ay_sum = 0, az_sum = 0;
  for (int i = 0; i < samples; i++) {
    AcX=a.acceleration.x;
    AcY=a.acceleration.y;
    AcZ=a.acceleration.z;
    ax_sum += AcX;
    ay_sum += AcY;
    az_sum += AcZ;
    delay(2);
  }
  ax_offset = ax_sum / samples;
  ay_offset = ay_sum / samples;
  az_offset = az_sum / samples;

  float gx_sum = 0, gy_sum = 0, gz_sum = 0;

  for (int i = 0; i < samples; i++) {
    GcX=g.gyro.x;
    GcY=g.gyro.y;
    GcZ=g.gyro.z;
    gx_sum += GcX;
    gy_sum += GcY;
    gz_sum += GcZ;
    delay(10);
  }
  gx_offset = gx_sum / samples;
  gy_offset = gy_sum / samples;
  gz_offset = gz_sum / samples;

  /* Print out the values */
  Serial.print("Offset Acceleration X: ");
  Serial.print(ax_offset);
  Serial.print(", Y: ");
  Serial.print(ay_offset);
  Serial.print(", Z: ");
  Serial.print(az_offset);
  Serial.println(" m/s^2");

  Serial.print("Offset Rotation X: ");
  Serial.print(gx_offset);
  Serial.print(", Y: ");
  Serial.print(gy_offset);
  Serial.print(", Z: ");
  Serial.print(gz_offset);
  Serial.println(" rad/s");

}