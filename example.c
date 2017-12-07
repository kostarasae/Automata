/*
 * example.c
 *
 *  Created on: 7 Dec 2017
 *      Author: Kostas Stamatakis
 */


/* AS5047D Register Addresses */
#define ERRFL_ADDR		0x0001
#define ANGLECOM_ADDR	0x3FFF
#define SETTINGS1_ADDR	0x0018
#define SETTINGS2_ADDR	0x0019



// example of AS5047D_register_read usage when reading an angle in degrees
void a_function(void)
{
	//...
	#define NO_OF_BYTES	3
	uint8_t				Returns;
	uint8_t 			RX_DATA[NO_OF_BYTES];
	uint8_t 			TX_DATA[] = {ERRFL_ADDR, ANGLECOM_ADDR};
	uint8_t				error;
	uint16_t			angle = 0, angleRaw = 0;
	uint32_t			angleTemp = 0;
	//...
	SPI_CONFIG_T				configSPI;
	//...
	SPI_TRANSFER_T 				transfer;
	transfer->rx_data 			= RX_DATA;
	transfer->tx_data 			= TX_DATA;
	transfer->number_of_bytes 	= NO_OF_BYTES;
	//...
	AS5047D_CONFIG_T			configAS5047D;
	//...
	Returns = SPI_configureTransfer(configSPI);
	Returns = AS5047D_configure(configAS5047D, transfer);
	error =  RX_DATA[0];
	angleRaw = RX_DATA[1];
	angleRaw += RX_DATA[2] << 8;
	angleTemp = angleRaw << 12;
	angle = angleTemp / (45 << 12); // (16,383 / 360)
	//...
}
