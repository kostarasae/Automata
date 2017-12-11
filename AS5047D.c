/*
 * AS5047D.c
 *
 *  Created on: 7 Dec 2017
 *      Author: Kostas Stamatakis
 */


#include "AS5047D.h"


AS5047D_RETURN_T AS5047D_checkNullPointer(void* pointer)
{
	if (pointer == NULL) return AS5047D_RETURN_T::AS5047D_RETURN_nullptr;
	return  AS5047D_RETURN_T::AS5047D_RETURN_ok;
}


AS5047D_RETURN_T AS5047D_checkConfiguration(const AS5047D_CONFIG_T *config)
{
	if (!(config->SETTINGS1 & 1) ||
	     (config->SETTINGS1 & 2))
	{
		return AS5047D_RETURN_T::AS5047D_RETURN_invalid_arg;
	}
	return  AS5047D_RETURN_T::AS5047D_RETURN_ok;
}


int32_t has_even_parity(uint32_t x)
{
	uint8_t shift=1;
	while (shift < (sizeof(x)*8))
	{
		x ^= (x>>shift);
		shift<<=1;
	}
	return !(x & 0x1);
}



AS5047D_RETURN_T AS5047D_checkFrame(const uint8_t *data, uint32_t bytes)
{
	uint32_t i;
	for (i = 0; i < bytes; i++)
	{
		if ((data + i) & 2) return AS5047D_RETURN_T::AS5047D_RETURN_invalid_arg;
		if (has_even_parity((data + i) & ~0x8000) != ((data + i) & 0x8000)) return AS5047D_RETURN_T::AS5047D_RETURN_invalid_arg;
	}	
	return  AS5047D_RETURN_T::AS5047D_RETURN_ok;
}



/* AS5047D configuration function */
AS5047D_RETURN_T AS5047D_configure(const AS5047D_CONFIG_T *config, const AS5047D_TRANSFER_T *transfer)
{
	if(AS5047D_checkNullPointer(config)) return AS5047D_RETURN_T::AS5047D_RETURN_nullptr;	
	if(AS5047D_checkNullPointer(transfer)) return AS5047D_RETURN_T::AS5047D_RETURN_nullptr;

	if(AS5047D_checkConfiguration(config) ||
	   AS5047D_checkFrame(transfer->tx_data, transfer->number_of_bytes) ||
	   AS5047D_transferBlocking(transfer) ||
	   AS5047D_checkFrame(transfer->rx_data, transfer->number_of_bytes))
	{
		return AS5047D_RETURN_T::AS5047D_RETURN_invalid_arg;
	}

	return  AS5047D_RETURN_T::AS5047D_RETURN_ok;
}

