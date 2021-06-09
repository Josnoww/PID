# PID
> <p>A simple implementation of a PID controller


## Contents
- [Features](#features)
- [Building](#Building)
- [License](#License)


## Features
- Anti integral windup
- Output saturation
- No derivative kick

## Building
Build the example:

```shell
gcc main.c pid.c -o main
```

To build as a shared object:

```shell
gcc -shared -o pid.so pid.c
```

## License
Copyright (C) 2021 Jos de Koning - All Rights Reserved

This file is licenced under BSD-3-clause. See the LICENSE file in the project root for full license information.

SPDX-License-Identifier: BSD-3-Clause
