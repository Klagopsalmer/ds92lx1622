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

#include "ds92lx1622.h"
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/delay.h>

static int ds92lx1622_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	s32 temp;
	s32 deviceId = i2c_smbus_read_byte_data(client, DEVICE_ID_REG_ADDR);
	if (deviceId > 0)
	{
		pr_info("device id: %d\n", deviceId);
	}
	else
	{
		pr_err("error reading ID\n");
	}

	temp = i2c_smbus_read_byte_data(client, 0x7);
	if (temp > 0)
	{
		pr_info("ser id: %d\n", temp);
	}
	else
	{
		pr_err("error ser ID\n");
	}

	if (0 > i2c_smbus_write_byte_data(client, BCC_REG_ADDR, 0xE0))
	{
		pr_err("error BCC\n");
	}

	if (0 > i2c_smbus_write_byte_data(client, OSS_SEL_REG_ADDR, OSS_SEL_MASK))
	{
		pr_err("error OSS_SEL\n");
	}

	temp = i2c_smbus_read_byte_data(client, RRFB_REG_ADDR);
	if (temp > 0)
	{
		i2c_smbus_write_byte_data(client, RRFB_REG_ADDR, temp & ~RRFB_MASK);
	}
	else
	{
		pr_err("error RRFB\n");
	}

	//Set target
	if (0 > i2c_smbus_write_byte_data(client, TARGET_ID_O_REG_ADDR, 0x42))
	{
		pr_err("error TARGET_ID\n");
	}
	if (0 > i2c_smbus_write_byte_data(client, ALIAS_ID_O_REG_ADDR, 0x42))
	{
		pr_err("error ALIAS_ID\n");
	}

	temp = i2c_smbus_read_byte_data(client, TARGET_ID_O_REG_ADDR);
	if (temp > 0)
	{
		pr_info("target id: %d\n", temp);
	}
	else
	{
		pr_err("error target ID\n");
	}

	//Remote wake up
	if (0 > i2c_smbus_write_byte_data(client, 0x26, 0xC0))
	{
		pr_err("error wake 0\n");
	}
	if (0 > i2c_smbus_write_byte_data(client, 0x01, 0x04))
	{
		pr_err("error wake 1\n");
	}
	if (0 > i2c_smbus_write_byte_data(client, 0x26, 0x0))
	{
		pr_err("error wake 2\n");
	}
	return 0;
}

static int ds92lx1622_remove(struct i2c_client *client)
{

	return 0;
}

static const struct of_device_id ds92lx1622_camera_of_match[] =
{
{ .compatible = "ti,ds92lx1622", },
{ }, };
MODULE_DEVICE_TABLE( of, ds92lx1622_camera_of_match);

static const struct i2c_device_id ds92lx1622_id[] =
{
{ "ds92lx1622", 0 },
{ } };

MODULE_DEVICE_TABLE( i2c, ds92lx1622_id);

static struct i2c_driver ds92lx1622_driver =
{ .probe = ds92lx1622_probe, .remove = ds92lx1622_remove, .id_table = ds92lx1622_id, .driver =
{ .name = "ds92lx1622", .owner = THIS_MODULE, .of_match_table = of_match_ptr(ds92lx1622_camera_of_match), }, };

module_i2c_driver( ds92lx1622_driver);

MODULE_AUTHOR("Alexandre Schnegg <aschnegg@digger.ch>");
MODULE_DESCRIPTION("DS92LX1622 driver");
MODULE_LICENSE("GPL v2");
