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
SPI_RETURN_T AS5047D_configure(const AS5047D_CONFIG_T *config, const SPI_TRANSFER_T *transfer);