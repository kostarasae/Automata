/*
 * AS5047D.h
 *
 *  Created on: 7 Dec 2017
 *      Author: Kostas Stamatakis
 */

#ifndef AS5047D_H_
#define AS5047D_H_


/* AS5047D return values */
typedef enum _AS5047D_RETURN {
  AS5047D_RETURN_ok = 0,        /* OK/success */
  AS5047D_RETURN_nullptr,       /* Argument contains a null pointer */
  AS5047D_RETURN_invalid_arg    /* Argument out of range/invalid */
} AS5047D_RETURN_T;


/* AS5047D configuration structure */
typedef struct _AS5047D_CONFIG {
	uint8_t SETTINGS1;
	uint8_t SETTINGS2;
	uint8_t SETTINGS1_ADDR;
	uint8_t SETTINGS2_ADDR;
} AS5047D_CONFIG_T;


/* SPI transfer structure */
typedef struct _AS5047D_TRANSFER {
  uint8_t *tx_data;          /* Send buffer. */
  uint8_t *rx_data;          /* Receive buffer. */
  uint32_t number_of_bytes;  /* Transfer size in bytes */
} AS5047D_TRANSFER_T;


/* AS5047D configuration function */
SPI_RETURN_T AS5047D_configure(const AS5047D_CONFIG_T *config, const SPI_TRANSFER_T *transfer);

/* SPI transfer */
extern SPI_RETURN_T SPI_transferBlocking(const SPI_TRANSFER_T *transfer);

#endif /* AS5047D_H_ */
