<!--
SPDX-FileCopyrightText: 2022 Sönke Holz <sholz8530@gmail.com>

SPDX-License-Identifier: GPL-2.0-or-later
-->

# Linux USB HID driver for the T7 Wired Gaming Mouse

A modified version of the in-tree `hid-glorious` Linux USB HID driver by Samuel Čavoj adapted for the "T7 Wired Gaming Mouse".

## Building (with dkms)
- copy the contents of this repo to `/usr/src/hid-t7-wired-mouse-0.1`
```sh
dkms add -m hid-t7-wired-mouse -v 0.1
dkms build -m hid-t7-wired-mouse -v 0.1
dkms install -m hid-t7-wired-mouse -v 0.1
```
