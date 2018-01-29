/*
 * SPI.h
 *
 *  Created on: Jan 27, 2018
 *      Author: maxime
 */

#ifndef SPI_H_
#define SPI_H_

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <iostream>
#include <string>

class SPI {
private:
	int file_descriptor;

	int set_config(int config, int value);
public:
	SPI(std::string spi_dev, int SPI_MODE, int LSB_FIRST, int WORD_LEN, int MAX_SPEED);
	int transmit(spi_ioc_transfer* spi_struct);
	virtual ~SPI();
};

#endif /* SPI_H_ */
