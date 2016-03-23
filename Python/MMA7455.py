# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# MMA7455L
# This code is designed to work with the MMA7455L_I2CS I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/content/Accelorometer?sku=MMA7455_I2CS#tabs-0-product_tabset-2

import smbus
import time

# Get I2C bus
bus = smbus.SMBus(1)

# MMA7455L address, 0x1D(16)
# Select mode control register, 0x16(22)
#		0x01(01)	Measurement Mode, +/- 8g
bus.write_byte_data(0x1D, 0x16, 0x01)

time.sleep(0.5)

# MMA7455L address, 0x1D(16)
# Read data back from 0x00(00), 6 bytes
# X-Axis LSB, X-Axis MSB, Y-Axis LSB, Y-Axis MSB, Z-Axis LSB, Z-Axis MSB
data=bus.read_i2c_block_data(0x1D, 0x00, 6)

# Convert the data to 10-bits
xAccl = (data[1] & 0x03) * 256 + data [0]
if xAccl > 511 :
	xAccl -= 1024
yAccl = (data[3] & 0x03) * 256 + data [2]
if yAccl > 511 :
	yAccl -= 1024
zAccl = (data[5] & 0x03) * 256 + data [4]
if zAccl > 511 :
	zAccl -= 1024

# Output data to screen
print "Acceleration in X-Axis : %d" %xAccl
print "Acceleration in Y-Axis : %d" %yAccl
print "Acceleration in Z-Axis : %d" %zAccl
