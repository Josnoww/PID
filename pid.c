/* Copyright (C) 2021 Jos de Koning - All Rights Reserved
 *
 * You may use, distribute and modify this code under the
 * terms of the BSD-3-Clause license.
 *
 * SPDX-License-Identifier: BSD-3-Clause */

#include "pid.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))


float pid_calc(pid_handle_t* pid, float pv, float sp)
{
    pid->sp = sp;
    pid->pv = pv;

    float error = pid->sp - pid->pv;
    pid->p = error;

    // Calculate the derivative using the pv to prevent
    // derivative kick when the setpoint has changed.
    pid->d = pv - pid->pv_previous;

    // Prevent zero division.
    if (pid->k.i != 0) {

        // Calculate the maximum increase of i to reach staturation.
        float max_i_change;
        float i_change;

        // Stop the integral from winding up when the cv is saturated.
        if (error >= 0) {
            // Calculate the maximal increase of the integral without causing cv to be over saturated.
            max_i_change = (pid->cv_max - (pid->k.p * error + pid->k.d * pid->d + pid->i * pid->k.i) ) / pid->k.i;
            i_change = MAX( 0, MIN(error, max_i_change) );

        } else {
            // Calculate the maximal decrease of the integral without causing cv to be under saturated.
            max_i_change = (pid->cv_min - (pid->k.p * error + pid->k.d * pid->d + pid->i * pid->k.i) ) / pid->k.i;
            i_change = MIN( 0, MAX(error, max_i_change) );
        }
        pid->i = pid->i + i_change;
    }

    pid->cv = (pid->p * pid->k.p) + (pid->i * pid->k.i) + (pid->d * pid->k.d);

    // Apply control value saturation.
    if (pid->cv > pid->cv_max) {
        pid->cv = pid->cv_max;
    } else if (pid->cv < pid->cv_min) {
        pid->cv = pid->cv_min;
    }

    pid->pv_previous = pv;
    return pid->cv;
}
