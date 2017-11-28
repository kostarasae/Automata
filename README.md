# Automata
Automata Embedded Test

Function Usage:
1) Use the SPI_configureTransfer to validate the configuration settings for the SPI
2) Once the SPI is ready, use the AS5047D_configure to configure the AS5047D speed position sensor
3) Once the AS5047D is ready, use the AS5047D_register_read to read the AS5047D speed position sensor error code and the angle
4) If the angle is needed in degrees, refer to the a_function example
