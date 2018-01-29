/*
 * main.cpp
 *
 *  Created on: Jan 27, 2018
 *      Author: maxime
 */

#include <iostream>
#include <bitset>

#include "SPI.h"

const int BUFFER_LEN = 2;

int main()
{
	SPI spi("spidev0.0", SPI_MODE_0, 0, 8, 2000000);

	char buffer[BUFFER_LEN] = {0b10000000 + 0x0F, 0};
	spi_ioc_transfer ftr;
	ftr.tx_buf = (__u64)buffer;
	ftr.rx_buf = (__u64)buffer;
	ftr.len = BUFFER_LEN;
	ftr.bits_per_word = 8;
	ftr.speed_hz = 2000000;

	std::cout << "SPI send: " << spi.transmit(& ftr) << std::endl;
	std::cout << std::bitset<8>(buffer[0]) << " " << std::bitset<8>(buffer[1]) << std::endl;
	return 0;
}



