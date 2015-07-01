/*
 * Texas Instruments DS92LX1622 deserializer driver
 *
 * Copyright (C) 2015 Digger DTR
 * Alexandre Schnegg <aschnegg@digger.ch>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef DS92LX1622_H_
#define DS92LX1622_H_

#define DEVICE_ID_REG_ADDR 0x0
#define OSS_SEL_REG_ADDR 0x2
#define OSS_SEL_MASK 0x10
#define RRFB_REG_ADDR 0x3
#define RRFB_MASK 0x1
#define BCC_REG_ADDR 0x27
#define TARGET_ID_O_REG_ADDR 0x8
#define ALIAS_ID_O_REG_ADDR 0x10

#endif /* DS92LX1622_H_ */
