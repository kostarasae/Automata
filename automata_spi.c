#include "automata_spi.h"


/* Configure the SPI transfer */
SPI_RETURN_T SPI_configureTransfer(const SPI_CONFIG_T *config)
{
	if (config == NULL)
	{
		return _SPI_RETURN.SPI_RETURN_nullptr;
	}
	else
	{
		if (config.cs_pol < SPI_POLARITY_T.SPI_ACTIVE_LOW ||
			config.cs_pol > SPI_POLARITY_T.SPI_ACTIVE_HIGH)
		{
			return _SPI_RETURN.SPI_RETURN_invalid_arg;
		}
		
		if (config.cpol < SPI_CPOL_T.SPI_IDLE_LOW ||
			config.cpol > SPI_CPOL_T.SPI_IDLE_HIGH)
		{
			return _SPI_RETURN.SPI_RETURN_invalid_arg;
		}		
				
		if (config.cpha < SPI_CHPA_T.SPI_EDGE_RISING ||
			config.cpha > SPI_CHPA_T.SPI_EDGE_FALLING)
		{
			return _SPI_RETURN.SPI_RETURN_invalid_arg;
		}
		
		#define MIN_BITS_PER_FRAME	4
		#define MAX_BITS_PER_FRAME	16
		
		if (config.bits_per_frame < MIN_BITS_PER_FRAME ||
			config.bits_per_frame > MAX_BITS_PER_FRAME)
		{
			return _SPI_RETURN.SPI_RETURN_invalid_arg;
		}
		
		#define MAX_BAUDRATE	895522389	// tBUS = (1 / fBUS) = 17 ns 
											// DS1 = 4 * tBUS = 67 ns (minimum clock cycle time)
											// BaudRateMAX = 60 / DS1 = 895,522,388 clock pulses per minute
		
		if (config.baudrate < MAX_BAUDRATE)
		{
			return _SPI_RETURN.SPI_RETURN_invalid_arg;
		}
		
		#define MIN_CS_TO_SCK	350 /* Time (ns) between asserting CS & SCK edge */
		
		if (config.cs_to_sck > MIN_CS_TO_SCK)
		{
			return _SPI_RETURN.SPI_RETURN_invalid_arg;
		}
	
		#define MIN_SCK_TO_CS	350 /* Time (ns) between SCK edge & releasing CS */
	
		if (config.sck_to_cs > MIN_SCK_TO_CS)
		{
			return _SPI_RETURN.SPI_RETURN_invalid_arg;
		}
		
		return  _SPI_RETURN.SPI_RETURN_ok;
	}
}


/* SPI transfer */
SPI_RETURN_T SPI_transferBlocking(const SPI_TRANSFER_T *transfer)
{
	if (transfer == NULL)
	{
		return _SPI_RETURN.SPI_RETURN_nullptr;
	}
	else if (config.number_of_bytes == 0)
	{
		return _SPI_RETURN.SPI_RETURN_invalid_arg;
	}
	else
	{
		SPI_Send_Receive_Bytes(config.tx_data, config.rx_data, config.number_of_bytes); // MCU dependent SPI function to send and receive bytes
		
		return  _SPI_RETURN.SPI_RETURN_ok;
	}
}


/* AS5047D Register Addresses */
#define ERRFL_ADDR		0x0001
#define ANGLECOM_ADDR	0x3FFF
#define SETTINGS1_ADDR	0x0018
#define SETTINGS2_ADDR	0x0019


/* AS5047D configuration structure */
typedef struct _AS5047D_CONFIG {
	uint8_t SETTINGS1;
	uint8_t SETTINGS2;
} AS5047D_CONFIG_T;


/* AS5047D configuration function */
SPI_RETURN_T AS5047D_configure(const AS5047D_CONFIG_T *config)
{
	if (config == NULL)
	{
		return _SPI_RETURN.SPI_RETURN_nullptr;
	}
	else if (!(config.SETTINGS1 & 1) ||
			  (config.SETTINGS1 & 2))
	{
		return _SPI_RETURN.SPI_RETURN_invalid_arg;		
	}
	else
	{
		uint8_t TX_DATA[] = {SETTINGS1_ADDR, config.SETTINGS1, SETTINGS2_ADDR, config.SETTINGS2};
		
		SPI_TRANSFER_T *transfer;
		
		transfer->tx_data = TX_DATA;
		transfer->number_of_bytes = 4;
		
		SPI_transferBlocking(transfer);
	}
}


/* AS5047D register read function */
uint8_t * AS5047D_register_read(void)
{
	uint8_t TX_DATA[] = {ERRFL_ADDR, ANGLECOM_ADDR};
	
	SPI_TRANSFER_T *transfer;
	
	transfer->tx_data = TX_DATA;
	transfer->number_of_bytes = 3;
	
	SPI_transferBlocking(transfer);
	
	return transfer->rx_data;
}

// example of angle reading in degrees
void a_function(void)
{
	//...
	uint8_t 	AS5047D_values[3]; // read bytes buffer
	uint16_t	angle = 0;
	//...
	AS5047D_values = AS5047D_register_read();
	angle = AS5047D_values[1];
	angle += AS5047D_values[2] << 8;
	angle = angle / (double)45.0; // (16,383 / 360)
	//...
}