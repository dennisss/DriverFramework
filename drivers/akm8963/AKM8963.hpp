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

#include "MagSensor.hpp"

namespace DriverFramework
{

#define MAG_DEVICE_PATH "/dev/i2c-akm8963"

// 100Hz measurement frequency
#define AKM8963_MEASURE_INTERVAL_US 10000 // TODO check setting

#define DRV_DF_DEVTYPE_AKM8963 0x46 // TODO check setting

#define AKM8963_SLAVE_ADDRESS 0xCH // TODO check setting


class AKM8963 : public MagSensor
{
public:
	AKM8963(const char *device_path) :
		MagSensor(device_path, AKM8963_MEASURE_INTERVAL_US)
	{
		m_id.dev_id_s.devtype = DRV_DF_DEVTYPE_AKM8963;
		m_id.dev_id_s.address = AKM8963_SLAVE_ADDRESS;
	}

	// @return 0 on success, -errno on failure
	virtual int start();

	// @return 0 on success, -errno on failure
	virtual int stop();

protected:
	virtual void _measure();
	virtual int _publish(struct mag_sensor_data &data);

private:
	int loadCalibration();

	// returns 0 on success, -errno on failure
	int akm8963_init();
};

}; // namespace DriverFramework