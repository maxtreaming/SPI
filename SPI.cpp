/*
 * SPI.cpp
 *
 *  Created on: Jan 27, 2018
 *      Author: maxime
 */

#include "SPI.h"

SPI::SPI(std::string spi_dev, int SPI_MODE, int LSB_FIRST, int WORD_LEN, int MAX_SPEED)
{
	transfer_struct.reset(new(spi_ioc_transfer));
	transfer_struct->bits_per_word = WORD_LEN;
	transfer_struct->speed_hz = MAX_SPEED;



	file_descriptor = open(std::string("/dev/" + spi_dev).c_str(), O_RDONLY);
	if(file_descriptor >= 0)
	{
		std::cout << set_config(SPI_IOC_WR_MODE, SPI_MODE) << std::endl;
		std::cout << set_config(SPI_IOC_WR_LSB_FIRST, LSB_FIRST) << std::endl;
		std::cout << set_config(SPI_IOC_WR_BITS_PER_WORD, WORD_LEN) << std::endl;
		std::cout << set_config(SPI_IOC_WR_MAX_SPEED_HZ, MAX_SPEED) << std::endl;

	}
	else
		std::cout << "Could not open " + spi_dev << std::endl;



}

SPI::~SPI()
{
	close(file_descriptor);
}

int SPI::transmit(__u64 tx_buffer, __u64 rx_buffer, int buffer_len)
{
	transfer_struct->tx_buf = tx_buffer;
	transfer_struct->rx_buf = rx_buffer;
	transfer_struct->len = buffer_len;
	return ioctl(file_descriptor, SPI_IOC_MESSAGE(1), transfer_struct.get());
}

int SPI::set_config(int config, int value)
{
	return ioctl(file_descriptor, config, &value);
}

