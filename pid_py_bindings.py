# Copyright (C) 2021 Jos de Koning - All Rights Reserved
#
# You may use, distribute and modify this code under the
# terms of the BSD-3-Clause license.
#
# SPDX-License-Identifier: BSD-3-Clause

import ctypes

libc = ctypes.CDLL('pid.so')


def wrap_function(lib, funcname, restype, argtypes):
    func = lib.__getattr__(funcname)
    func.restype = restype
    func.argtypes = argtypes
    return func


def newStructType(name=None, fields=None):
    return type(name, (ctypes.Structure, ), { "_fields_" : fields } )


# Create template of pid_gains_t struct
pid_gains_t_config = { "name"   : "pid_gains_t",
                       "fields" : [ ('p', ctypes.c_float),
                                    ('i', ctypes.c_float),
                                    ('d', ctypes.c_float) ] }

# Create pid_gains_t type
pid_gains_t = newStructType(**pid_gains_t_config)

# Create template of pid_handle_t struct
pid_handle_t_config = { "name"   : "pid_handle_t",
                        "fields" : [ ('k',              pid_gains_t),
                                     ('p',              ctypes.c_float),
                                     ('i',              ctypes.c_float),
                                     ('d',              ctypes.c_float),
                                     ('pv_previous',    ctypes.c_float),
                                     ('sp',             ctypes.c_float),
                                     ('pv',             ctypes.c_float),
                                     ('cv',             ctypes.c_float),
                                     ('cv_min',         ctypes.c_float),
                                     ('cv_max',         ctypes.c_float) ] }

# Create pid_handle_t type
pid_handle_t = newStructType(**pid_handle_t_config)



if __name__ == '__main__':

    # # # Example implementation # # #

    # Create pid_calc python interface
    pid_calc = wrap_function(libc, 'pid_calc', ctypes.c_float, [ctypes.POINTER(pid_handle_t), ctypes.c_float, ctypes.c_float])

    # Create gain struct
    pid_gains_s = pid_gains_t(p=5, i=0.5, d=15)

    # Add the gains to the pid handle
    pid_handle_s = pid_handle_t(k=pid_gains_s)


    # Set the saturation limits for the control value
    pid_handle_s.cv_max = 100
    pid_handle_s.cv_min = 0
    pid_handle_s.i = 0
    pid_handle_s.pv_previous = 20

    # Calculate the next control value
    cv = pid_calc(pid_handle_s, 20, 100) # (handle, pv, sp)
