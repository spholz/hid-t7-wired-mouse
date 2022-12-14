// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * USB HID driver for T7 Wired Gaming Mouse
 *
 * Copyright (c) 2022 Sönke Holz <sholz8530@gmail.com>
 *
 * based on hid-glorious.c
 *  Copyright (c) 2020 Samuel Čavoj <sammko@sammserver.com>
 */

/*
 */

#include <linux/hid.h>
#include <linux/module.h>

#define USB_VENDOR_ID_258A			0x258a
#define USB_DEVICE_ID_258A_1007		0x1007

/*
 * The mouse specifies the const flag in the consumer input
 * report descriptor, which leads to inputs being ignored. Fix this
 * by patching the descriptor.
 */
static u8 *t7_wired_mouse_report_fixup(struct hid_device *hdev, u8 *rdesc,
		unsigned int *rsize)
{
	if (*rsize == 213 &&
		rdesc[84] == 129 && rdesc[112] == 129 && rdesc[140] == 129 &&
		rdesc[85] == 3   && rdesc[113] == 3   && rdesc[141] == 3) {
		hid_info(hdev, "patching T7 Wired gaming mouse consumer control report descriptor\n");
		rdesc[85] = rdesc[113] = rdesc[141] = \
			HID_MAIN_ITEM_VARIABLE | HID_MAIN_ITEM_RELATIVE;
	}
	return rdesc;
}

static void t7_wired_mouse_update_name(struct hid_device *hdev)
{
	strscpy(hdev->name, "T7 Wired Gaming Mouse", sizeof(hdev->name));
}

static int t7_wired_mouse_probe(struct hid_device *hdev,
		const struct hid_device_id *id)
{
	int ret;

	hdev->quirks |= HID_QUIRK_INPUT_PER_APP;

	ret = hid_parse(hdev);
	if (ret)
		return ret;

	t7_wired_mouse_update_name(hdev);

	return hid_hw_start(hdev, HID_CONNECT_DEFAULT);
}

static const struct hid_device_id t7_wired_mouse_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOR_ID_258A,
		USB_DEVICE_ID_258A_1007) },
	{ }
};
MODULE_DEVICE_TABLE(hid, t7_wired_mouse_devices);

static struct hid_driver t7_wired_mouse_driver = {
	.name = "t7_wired_mouse",
	.id_table = t7_wired_mouse_devices,
	.probe = t7_wired_mouse_probe,
	.report_fixup = t7_wired_mouse_report_fixup
};

module_hid_driver(t7_wired_mouse_driver);

MODULE_AUTHOR("Sönke Holz <sholz8530@gmail.com>>");
MODULE_DESCRIPTION("USB HID driver for T7 Wired Gaming Mouse");
MODULE_LICENSE("GPL");
