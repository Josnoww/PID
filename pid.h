/* Copyright (C) 2021 Jos de Koning - All Rights Reserved
 *
 * You may use, distribute and modify this code under the
 * terms of the BSD-3-Clause license.
 *
 * SPDX-License-Identifier: BSD-3-Clause */

#ifndef PID_H
#define PID_H


typedef struct {
    float p;
    float i;
    float d;
} pid_gain_t;

typedef struct {
    pid_gain_t k; // k is used as symbol for gain
    float p;
    float i;
    float d;
    float pv_previous;
    float sp;
    float pv; // process variable - input
    float cv; // control variable - output
    float cv_min;
    float cv_max;
} pid_handle_t;

float pid_calc(pid_handle_t* pid, float pv, float sp);

#endif