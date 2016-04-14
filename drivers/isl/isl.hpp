/****************************************************************************
*
*   Copyright (C) 2016 PX4 Development Team. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* 1. Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in
*    the documentation and/or other materials provided with the
*    distribution.
* 3. Neither the name PX4 nor the names of its contributors may be
*    used to endorse or promote products derived from this software
*    without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
* OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
* AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
****************************************************************************/

#pragma once

#include "I2CDevObj.hpp"

/* Configuration Constants */

#define ISL_DEVICE_PATH   "/dev/iic-9"  // J15
#define ISL_CLASS_PATH  	"/dev/isl"

/* Device limits in m*/
#define ISL_MIN_DISTANCE (0.20f)
#define ISL_MAX_DISTANCE (14.00f)

#define ISL_MEASURE_INTERVAL_US 100000

#define ISL_SLAVE_ADDRESS		(0x54)

// up to 100kHz
#define ISL_BUS_FREQUENCY_IN_KHZ	(400)

#define ISL_TRANSFER_TIMEOUT_IN_USECS (9000)

namespace DriverFramework
{
struct range_sensor_data {
	float dist; // the distance in m
	float temperature;
};

class ISL : public I2CDevObj
{
public:
	ISL(const char *device_path) :
		I2CDevObj("RangeFinder", device_path, ISL_CLASS_PATH, ISL_MEASURE_INTERVAL_US),
		_detected(false)
	{
		set_slave_addr(ISL_SLAVE_ADDRESS);
	}

	// @return 0 on success, -errno on failure
	virtual int start();

	// @return 0 on success, -errno on failure
	virtual int stop();

	// @return 0 on success
	int probe() { return 0; }

	void set_slave_addr(uint8_t slave);

	int write_reg(uint8_t address, uint8_t data);
	uint8_t read_reg(uint8_t address);
	int calc_sample_delay(unsigned char value);
	int init_params();
	int calibration();
protected:
	virtual void _measure();
	virtual int _publish(struct range_sensor_data &data);

	struct range_sensor_data		m_sensor_data;
	uint32_t isl_sample_delay;
private:
	// returns 0 on success, -errno on failure
	int isl_init();
	int _detect();
	bool _detected;
	int slave_addr;
};

}; // namespace DriverFramework