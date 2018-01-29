/*
 * SPI.cpp
 *
 *  Created on: Jan 27, 2018
 *      Author: maxime
 */

#include "SPI.h"

SPI::SPI(std::string spi_dev, int SPI_MODE, int LSB_FIRST, int WORD_LEN, int MAX_SPEED)
{
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

int SPI::transmit(spi_ioc_transfer* spi_struct)
{

	return ioctl(file_descriptor, SPI_IOC_MESSAGE(1), spi_struct);
}

int SPI::set_config(int config, int value)
{
	return ioctl(file_descriptor, config, &value);
}

