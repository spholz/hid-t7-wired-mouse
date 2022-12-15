# SPDX-FileCopyrightText: 2022 Sönke Holz <sholz8530@gmail.com>
#
# SPDX-License-Identifier: GPL-2.0-or-later

obj-m += hid-t7-wired-mouse.o

.PHONY: all clean

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
