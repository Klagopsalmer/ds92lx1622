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

#include <linux/module.h>

static int __init ds92lx1622_init(void)
{
	pr_info("ds92lx1622 driver loaded\n");
	return 0;
}

static void __exit ds92lx1622_exit(void)
{
	pr_info("ds92lx1622 driver unloaded\n");

}

module_init(ds92lx1622_init);
module_exit(ds92lx1622_exit);

MODULE_AUTHOR("Alexandre Schnegg <aschnegg@digger.ch>");
MODULE_DESCRIPTION("DS92LX1622 driver");
MODULE_LICENSE("GPL2");
