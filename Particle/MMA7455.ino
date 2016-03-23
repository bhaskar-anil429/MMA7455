// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// MMA7455
// This code is designed to work with the MMA7455_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Accelorometer?sku=MMA7455_I2CS#tabs-0-product_tabset-2

#include <application.h>
#include <spark_wiring_i2c.h>

// MMA7455 I2C address is 0x1D(29)
#define Addr 0x1D

int xAccl = 0, yAccl =  0, zAccl = 0;
void setup()
{
    // Set variable
    Particle.variable("i2cdevice","MMA7455");
    Particle.variable("xAccl", xAccl);
    Particle.variable("yAccl", yAccl);
    Particle.variable("zAccl", zAccl);
    
    // Initialise I2C communication as MASTER
    Wire.begin();
    // Initialise Serial Communication, set baud rate = 9600
    Serial.begin(9600);
    
    // Start I2C Transmission
    Wire.beginTransmission(Addr);
    // Select Mode control register
    Wire.write(0x16);
    // Measurement mode, +/- 8g
    Wire.write(0x01);
    // Stop I2C Transmission
    Wire.endTransmission();
    delay(300);
}

void loop()
{
    unsigned int data[6];
    
    // Start I2C Transmission
    Wire.beginTransmission(Addr);
    // Select data register
    Wire.write(0x00);
    // Stop I2C Transmission
    Wire.endTransmission();
    
    // Request 6 bytes
    Wire.requestFrom(Addr, 6);
    
    // Read 6 bytes of data
    // xAccl lsb, xAccl msb, yAccl lsb, yAccl msb, zAccl lsb, zAccl msb
    if(Wire.available() == 6)
    {
        data[0] = Wire.read();
        data[1] = Wire.read();
        data[2] = Wire.read();
        data[3] = Wire.read(); 
        data[4] = Wire.read();
        data[5] = Wire.read(); 
    }
    delay(300);
    
    // Convert the data to 10-bits
    xAccl = (((data[1] & 0x03) * 256) + data[0]);
    if (xAccl > 511)
    { 
        xAccl -= 1024;
    }
    
    yAccl = (((data[2] & 0x03)* 256) + data[2]);
    if (yAccl > 511)
    {
        yAccl -= 1024;
    }
    
    zAccl = (((data[5] & 0x03) * 256) + data[4]);
    if (zAccl > 511)
    { 
        zAccl -= 1024;
    }
    
    // Output data to dashboard
    Particle.publish(" Acceleration in X-Axis is :  ", String(xAccl));
    Particle.publish(" Acceleration in Y-Axis is :  ", String(yAccl));
    Particle.publish(" Acceleration in Z-Axis is :  ", String(zAccl));
    delay(1000);  
}
