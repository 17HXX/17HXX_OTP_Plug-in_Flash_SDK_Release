/***************************************************
 *	File name:		e2prom.h
 *	Author:			
 *	Created Data:	3/08/2015
 *	Description:    Interfaces  for user application invoke
 */
#pragma once

/***************************
 * @brief	EEPROM initiate, call this function to initiate the whole storage space
 *
 * @param	none
 *
 * @return	none
 */
void e2prom_init();

/***************************
 * @brief	write variable length data to the e2prom
 *
 * @param	adr:	destination e2prom address
 * 			p:		stored data space address
 * 			len:	data length need to be stored
 *
 * @return	none
 */
void e2prom_write (int adr, u8 *p, int len);

/***************************
 * @brief	read variable length data to from e2prom
 *
 * @param	adr:	destination address
 * 			p:		address used to store read bytes
 * 			len:	read byte length
 *
 * @return	none
 */
void e2prom_read (int adr, u8 *p, int len);
