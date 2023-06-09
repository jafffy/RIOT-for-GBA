/*
 * Copyright (C) 2017 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     sys_phydat
 * @{
 *
 * @file
 * @brief       Convert phydat_t structs to human readable JSON strings
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 *
 * @}
 */

#include <string.h>

#include "assert.h"
#include "flash_utils.h"
#include "fmt.h"
#include "phydat.h"

#define STATIC_LEN      (14U)

/**
 * @note    @p buf must be at least 5 bytes of size
 */
static size_t _bool_to_str(int16_t val, char *buf)
{
    if (val) {
        flash_memcpy(buf, TO_FLASH("true"), 4);
        return 4;
    }
    else {
        flash_memcpy(buf, TO_FLASH("false"), 5);
        return 5;
    }
}

size_t phydat_to_json(const phydat_t *data, size_t dim, char *buf)
{
    assert((dim > 0) && (dim <= PHYDAT_DIM));

    size_t pos = 0;

    if (buf == NULL) {
        pos = STATIC_LEN;
        if (dim > 1) {
            pos += (2 + (dim - 1));       /* array parens + separating commas */
        }
        for (size_t i = 0; i < dim; i++) {
            if (data->unit != UNIT_BOOL) {
                pos += fmt_s16_dfp(NULL, data->val[i], (int)data->scale);
            }
            else {
                pos += (data->val[i]) ? 4 : 5;  /* true: 4, false: 5 */
            }
        }
        pos += phydat_unit_write(NULL, 0, data->unit);
    }
    else {
        flash_memcpy(buf, TO_FLASH("{\"d\":"), 5);
        pos += 5;
        /* write data */
        if (dim > 1) {
            buf[pos++] = '[';
        }
        for (size_t i = 0; i < dim; i++) {
            if (data->unit != UNIT_BOOL) {
                pos += fmt_s16_dfp(&buf[pos], data->val[i], (int)data->scale);
            }
            else {
                pos += _bool_to_str(data->val[i], &buf[pos]);
            }
            buf[pos++] = ',';
        }
        /* override last comma if needed */
        if (dim > 1) {
            buf[pos - 1] = ']';
            buf[pos++] = ',';
        }
        /* add unit */
        flash_memcpy(&buf[pos], TO_FLASH("\"u\":\""), 5);
        pos += 5;
        pos += phydat_unit_write(&buf[pos], SIZE_MAX, data->unit);
        /* terminate the JSON string */
        flash_memcpy(&buf[pos], TO_FLASH("\"}"), 2);
        pos += 2;
        buf[pos++] = '\0';
    }

    return pos;
}
