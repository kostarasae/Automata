#ifndef _AUTOMATA_SPI_H
#define _AUTOMATA_SPI_H

#include <stdint.h>
#include <stdbool.h>

/* SPI transfer return values */
typedef enum _SPI_RETURN {
  SPI_RETURN_ok = 0,        /* OK/success */
  SPI_RETURN_nullptr,       /* Argument contains a null pointer */
  SPI_RETURN_invalid_arg    /* Argument out of range/invalid */
} SPI_RETURN_T;

typedef enum _POLARITY {
  SPI_ACTIVE_LOW = 0,       /* Signal active low*/
  SPI_ACTIVE_HIGH           /* Signal active high */
} SPI_POLARITY_T;


typedef enum _CPOL {
  SPI_IDLE_LOW = 0,         /* CLK idle low */
  SPI_IDLE_HIGH             /* CLK idle high */
} SPI_CPOL_T;

typedef enum _CHPA {
  SPI_EDGE_RISING = 0,      /* Data latch on rising falling */
  SPI_EDGE_FALLING          /* Data latch on falling rising */
} SPI_CHPA_T;

/* SPI transfer configuration structure */
typedef struct _SPI_CONFIG {
  SPI_POLARITY_T cs_pol;    /* Chip select polarity */
  SPI_CPOL_T cpol;          /* CPOL */
  SPI_CHPA_T cpha;          /* CHPA */
  uint8_t bits_per_frame;   /* Bits per frame, min 4 - max 16 */
  uint32_t baudrate;        /* Transfer baud rate (bits/second) */
  uint32_t cs_to_sck;       /* Time (ns) between asserting CS & SCK edge */
  uint32_t sck_to_cs;       /* Time (ns) between SCK edge & releasing CS */
} SPI_CONFIG_T;

/* SPI transfer structure */
typedef struct _SPI_TRANSFER {
  uint8_t *tx_data;          /* Send buffer. */
  uint8_t *rx_data;          /* Receive buffer. */
  uint32_t number_of_bytes;  /* Transfer size in bytes */
} SPI_TRANSFER_T;

/* Configure the SPI transfer */
SPI_RETURN_T SPI_configureTransfer(const SPI_CONFIG_T *config);

/* SPI transfer */
SPI_RETURN_T SPI_transferBlocking(const SPI_TRANSFER_T *transfer);

#endif /* _AUTOMATA_SPI_H */