// example of AS5047D_register_read usage when reading an angle in degrees
void a_function(void)
{
	//...

	#define NO_OF_BYTES	3
	uint8_t				SPI_return;
	uint8_t 			RX_DATA[NO_OF_BYTES];
	uint8_t 			TX_DATA[] = {ERRFL_ADDR, ANGLECOM_ADDR};
	uint8_t				error;
	uint16_t			angle = 0, angleRaw = 0;
	uint32_t			angleTemp = 0;

	SPI_TRANSFER_T 		transfer;
	transfer->rx_data = RX_DATA;
	transfer->tx_data = TX_DATA;
	transfer->number_of_bytes = NO_OF_BYTES;

	//...

	SPI_return = SPI_transferBlocking(transfer);
	error =  RX_DATA[0];
	angleRaw = RX_DATA[1];
	angleRaw += RX_DATA[2] << 8;
	angleTemp = angleRaw << 12;
	angle = angleTemp / (45 << 12); // (16,383 / 360)

	//...
}