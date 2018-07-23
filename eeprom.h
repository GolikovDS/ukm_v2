

#ifndef EEPROM_H
#define	EEPROM_H
#include <htc.h>
#include "util.h"

byte readMemori (byte address);
void saveMemori (byte address, byte data);

#endif	/* EEPROM_H */

