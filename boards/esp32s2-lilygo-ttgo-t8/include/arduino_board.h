/*
 * Copyright (C)  2022 Gunar Schorcht
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     boards_esp32s2_lilygo_ttgo_t8
 * @{
 *
 * @file
 * @brief       Board specific configuration for the Arduino API
 *
 * @author      Gunar Schorcht <gunar@schorcht.net>
 */

#ifndef ARDUINO_BOARD_H
#define ARDUINO_BOARD_H

#include "arduino_board_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   The on-board LED is not available
 */
#define ARDUINO_LED         (0)

#ifdef __cplusplus
}
#endif

#endif /* ARDUINO_BOARD_H */
/** @} */
