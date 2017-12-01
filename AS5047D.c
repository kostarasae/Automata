#include "AS5047D.h"


/* AS5047D configuration function */
SPI_RETURN_T AS5047D_configure(const AS5047D_CONFIG_T *config, const SPI_TRANSFER_T *transfer)
{
	if (config == NULL ||
		transfer == NULL)
	{
		return SPI_RETURN_T::SPI_RETURN_nullptr;
	}
	else if (!(config.SETTINGS1 & 1) ||
			  (config.SETTINGS1 & 2))
	{
		return SPI_RETURN_T::SPI_RETURN_invalid_arg;
	}

	uint8_t TX_DATA[] = {SETTINGS1_ADDR, config.SETTINGS1, SETTINGS2_ADDR, config.SETTINGS2};

	transfer->tx_data = TX_DATA;
	transfer->number_of_bytes = 4;

	SPI_transferBlocking(transfer);

	return  SPI_RETURN_T::SPI_RETURN_ok;
}