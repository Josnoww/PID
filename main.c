/* Copyright (C) 2021 Jos de Koning - All Rights Reserved
 *
 * You may use, distribute and modify this code under the
 * terms of the BSD-3-Clause license.
 *
 * SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <stdlib.h>

#include "pid.h"


int main(int argc, char *argv[]) {
    pid_handle_t pid_handle;
    pid_gain_t pid_gains;

    // Set the gains for the pid.
    pid_gains.p = 3;
    pid_gains.i = 0.01;
    pid_gains.d = 10;

    // Add the gains to the handle.
    pid_handle.k = pid_gains;

    // Set output saturation values.
    pid_handle.cv_max = 255;
    pid_handle.cv_min = 0;

    // Set the previous pv to prevent derivative kick.
    pid_handle.pv_previous = 10; // TODO: Replace by current pv.

    float cv;
    float sp = 10; // Setpoint.
    float pv = 11; // Replace by some sensor reading.

    cv = pid_calc(&pid_handle, pv, sp);
    printf("%f\n",cv);

    return 0;
}
