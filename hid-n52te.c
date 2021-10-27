#include <linux/module.h>
#include <linux/slab.h>
#include <linux/kernel.h>
#include <asm/unaligned.h>
#include <asm/byteorder.h>

#include <linux/hid.h>

/*

*/

#define HID_VENDOR_ID       ( 0x050D )
#define HID_PRODUCT_ID      ( 0x0200 )
#define NUMBER_OF_BUTTONS   20

static struct hid_driver hid_n52te;

static bool hid_n52te_match(struct hid_device *hdev,
			      bool ignore_special_driver)
{
	if (ignore_special_driver)
		return true;

	if (hdev->quirks & HID_QUIRK_HAVE_SPECIAL_DRIVER)
		return false;

	return true;
}

static int hid_n52te_probe(struct hid_device *hdev,
			     const struct hid_device_id *id)
{
	int ret;

	hdev->quirks |= HID_QUIRK_INPUT_PER_APP;

	ret = hid_parse(hdev);
	if (ret)
		return ret;

	return hid_hw_start(hdev, HID_CONNECT_DEFAULT);
}

static int hid_n52te_input_mapping(struct hid_device *dev,
                             struct hid_input *input,
                             struct hid_field *field,
                             struct hid_usage *usage,
                             unsigned long **bit,
                             int *max)
{
    return -1;
}

static int hid_n52te_input_configured(struct hid_device *dev,
                                struct hid_input *input)
{
    struct input_dev * input_dev = input->input;
    int i;

    hid_set_drvdata(dev, input_dev);

    set_bit(EV_KEY, input_dev->evbit);

    // Set some stuff
    for (i = 0; i < NUMBER_OF_BUTTONS; i++) {
        set_bit(BTN_TRIGGER_HAPPY1 + i, input_dev->keybit);
    }

    return 0;
}

static int hid_n52te_raw_event(struct hid_device *dev,
                         struct hid_report *report, u8 *data, int len)
{
    struct input_dev *input_dev = hid_get_drvdata(dev);
    //int ret;
    int i;

    /*
    Indexes:
    [0] 11 and thump
    [1] unknown
    [2] - [7] 01 - 10, 12 - 15, arrows
	So it's a keyboard eh?
    That's not helpful! Make this a joys stick!
    */
    for (i = 2; i < 7; i++) {
        input_report_key(input_dev, BTN_TRIGGER_HAPPY1, data[i] == 0x2B);
        input_report_key(input_dev, BTN_TRIGGER_HAPPY2, data[i] == 0x14);
        input_report_key(input_dev, BTN_TRIGGER_HAPPY3, data[i] == 0x1A);
        input_report_key(input_dev, BTN_TRIGGER_HAPPY4, data[i] == 0x08);
        input_report_key(input_dev, BTN_TRIGGER_HAPPY5, data[i] == 0x15);
        input_report_key(input_dev, BTN_TRIGGER_HAPPY6, data[i] == 0x39);
        input_report_key(input_dev, BTN_TRIGGER_HAPPY7, data[i] == 0x04);
        input_report_key(input_dev, BTN_TRIGGER_HAPPY8, data[i] == 0x16);
        input_report_key(input_dev, BTN_TRIGGER_HAPPY9, data[i] == 0x07);
        input_report_key(input_dev, BTN_TRIGGER_HAPPY10, data[i] == 0x09);
        input_report_key(input_dev, BTN_TRIGGER_HAPPY12, data[i] == 0x1D);
        input_report_key(input_dev, BTN_TRIGGER_HAPPY13, data[i] == 0x1B);
        input_report_key(input_dev, BTN_TRIGGER_HAPPY14, data[i] == 0x06);
        input_report_key(input_dev, BTN_TRIGGER_HAPPY15, data[i] == 0x2C);
        input_report_key(input_dev, BTN_TRIGGER_HAPPY16, data[i] == 0x50); // UP
        input_report_key(input_dev, BTN_TRIGGER_HAPPY17, data[i] == 0x4F); // DOWN
        input_report_key(input_dev, BTN_TRIGGER_HAPPY18, data[i] == 0x51); // LEFT
        input_report_key(input_dev, BTN_TRIGGER_HAPPY19, data[i] == 0x52); // RIGHT
    }
    input_report_key(input_dev, BTN_TRIGGER_HAPPY11, data[0] == 0x02);
    input_report_key(input_dev, BTN_TRIGGER_HAPPY20, data[0] == 0x04);


    input_sync(input_dev);

    //return ret;
    return 0; // Meh
}

static const struct hid_device_id hid_table[] = {
	{ HID_USB_DEVICE(HID_VENDOR_ID, HID_PRODUCT_ID) },
	{ }
};
MODULE_DEVICE_TABLE(hid, hid_table);

static struct hid_driver hid_n52te = {
	.name = "hid-n52te",
	.id_table = hid_table,
	.match = hid_n52te_match,
	.probe = hid_n52te_probe,
    .input_mapping = hid_n52te_input_mapping,
    .input_configured = hid_n52te_input_configured,
    .raw_event = hid_n52te_raw_event,
};
module_hid_driver(hid_n52te);

MODULE_AUTHOR("UntrustedRoot");
MODULE_DESCRIPTION("Simple n52te Driver for Linux");
MODULE_LICENSE("GPL");
