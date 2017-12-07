/*
 * automata_spi.c
 *
 *  Created on: 28 Nov 2017
 *      Author: Kostas Stamatakis
 */


#include "automata_spi.h"


SPI_RETURN_T SPI_checkNullPointer(void* pointer)
{
	if (pointer == NULL)
	{
		return SPI_RETURN_T::SPI_RETURN_nullptr;
	}
}


SPI_RETURN_T SPI_checkRange(uint32_t min, uint32_t max, uint32_t var)
{
	if (var < min)
	{
		return SPI_RETURN_T::SPI_RETURN_invalid_arg;
	}

	if (var > max)
	{
		return SPI_RETURN_T::SPI_RETURN_invalid_arg;
	}
}


/* Configure the SPI transfer */
SPI_RETURN_T SPI_configureTransfer(const SPI_CONFIG_T *config)
{
	SPI_checkNullPointer(config);

	SPI_checkRange(SPI_POLARITY_T::SPI_ACTIVE_LOW, SPI_POLARITY_T::SPI_ACTIVE_HIGH, config.cs_pol);

	SPI_checkRange(SPI_CPOL_T::SPI_IDLE_LOW, SPI_CPOL_T::SPI_IDLE_HIGH, config.cpol);

	SPI_checkRange(SPI_CHPA_T::SPI_EDGE_RISING, SPI_CHPA_T::SPI_EDGE_FALLING, config.cpha);


	#define MIN_BITS_PER_FRAME	4
	#define MAX_BITS_PER_FRAME	16
	SPI_checkRange(MIN_BITS_PER_FRAME, MAX_BITS_PER_FRAME, config.bits_per_frame);


	#define MIN_BAUDRATE	1
	#define MAX_BAUDRATE	895522389	// tBUS = (1 / fBUS) = 17 ns
										// DS1 = 4 * tBUS = 67 ns (minimum clock cycle time)
										// BaudRateMAX = 60 / DS1 = 895,522,388 clock pulses per minute
	SPI_checkRange(MIN_BAUDRATE, MAX_BAUDRATE, config.baudrate);


	#define MIN_CS_TO_SCK	350 /* Time (ns) between asserting CS & SCK edge */
	#define MAX_CS_TO_SCK	sizeof(uint32_t)
	SPI_checkRange(MIN_CS_TO_SCK, MAX_CS_TO_SCK, config.cs_to_sck);


	#define MIN_SCK_TO_CS	350 /* Time (ns) between SCK edge & releasing CS */
	#define MAX_SCK_TO_CS	sizeof(uint32_t)
	SPI_checkRange(MIN_SCK_TO_CS, MAX_SCK_TO_CS, config.sck_to_cs);

	return  SPI_RETURN_T::SPI_RETURN_ok;
}


/* SPI transfer */
SPI_RETURN_T SPI_transferBlocking(const SPI_TRANSFER_T *transfer)
{
	SPI_checkNullPointer(transfer);

	#define MIN_BYTES	1
	#define MAX_BYTES	sizeof(uint32_t)

	SPI_checkRange(MIN_BYTES, MAX_BYTES, transfer.number_of_bytes);

	#define SPI_ERROR	-1
	if (SPI_Send_Receive_Bytes(transfer->tx_data, transfer->rx_data, transfer.number_of_bytes) // MCU dependent SPI function to send and receive bytes
	{
		return SPI_ERROR;
	}

	return  SPI_RETURN_T::SPI_RETURN_ok;
}
