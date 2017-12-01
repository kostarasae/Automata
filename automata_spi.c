/*
 * automata_spi.c
 *
 *  Created on: 28 Nov 2017
 *      Author: Kostas Stamatakis
 */


#include "automata_spi.h"


/* Configure the SPI transfer */
SPI_RETURN_T SPI_configureTransfer(const SPI_CONFIG_T *config)
{
	if (config == NULL)
	{
		return SPI_RETURN_T::SPI_RETURN_nullptr;
	}
	else
	{
		if (config.cs_pol < SPI_POLARITY_T::SPI_ACTIVE_LOW ||
			config.cs_pol > SPI_POLARITY_T::SPI_ACTIVE_HIGH)
		{
			return SPI_RETURN_T::SPI_RETURN_invalid_arg;
		}

		if (config.cpol < SPI_CPOL_T::SPI_IDLE_LOW ||
			config.cpol > SPI_CPOL_T::SPI_IDLE_HIGH)
		{
			return SPI_RETURN_T::SPI_RETURN_invalid_arg;
		}

		if (config.cpha < SPI_CHPA_T::SPI_EDGE_RISING ||
			config.cpha > SPI_CHPA_T::SPI_EDGE_FALLING)
		{
			return SPI_RETURN_T::SPI_RETURN_invalid_arg;
		}

		#define MIN_BITS_PER_FRAME	4
		#define MAX_BITS_PER_FRAME	16

		if (config.bits_per_frame < MIN_BITS_PER_FRAME ||
			config.bits_per_frame > MAX_BITS_PER_FRAME)
		{
			return SPI_RETURN_T::SPI_RETURN_invalid_arg;
		}

		#define MAX_BAUDRATE	895522389	// tBUS = (1 / fBUS) = 17 ns
											// DS1 = 4 * tBUS = 67 ns (minimum clock cycle time)
											// BaudRateMAX = 60 / DS1 = 895,522,388 clock pulses per minute

		if (config.baudrate < MAX_BAUDRATE)
		{
			return SPI_RETURN_T::SPI_RETURN_invalid_arg;
		}

		#define MIN_CS_TO_SCK	350 /* Time (ns) between asserting CS & SCK edge */

		if (config.cs_to_sck > MIN_CS_TO_SCK)
		{
			return SPI_RETURN_T::SPI_RETURN_invalid_arg;
		}

		#define MIN_SCK_TO_CS	350 /* Time (ns) between SCK edge & releasing CS */

		if (config.sck_to_cs > MIN_SCK_TO_CS)
		{
			return SPI_RETURN_T::SPI_RETURN_invalid_arg;
		}
	}
	return  SPI_RETURN_T::SPI_RETURN_ok;
}


/* SPI transfer */
SPI_RETURN_T SPI_transferBlocking(const SPI_TRANSFER_T *transfer)
{
	if (transfer == NULL)
	{
		return SPI_RETURN_T::SPI_RETURN_nullptr;
	}
	else if (transfer.number_of_bytes == 0)
	{
		return SPI_RETURN_T::SPI_RETURN_invalid_arg;
	}
	else
	{
		#define SPI_ERROR	-1

		if (SPI_Send_Receive_Bytes(transfer->tx_data, transfer->rx_data, transfer.number_of_bytes) // MCU dependent SPI function to send and receive bytes
		{
			return SPI_ERROR;
		}
	}

	return  SPI_RETURN_T::SPI_RETURN_ok;
}
