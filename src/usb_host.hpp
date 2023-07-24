//
// Created by jbs on 7/19/23.
//

#ifndef CH375HID_USB_HOST_H
#define CH375HID_USB_HOST_H

#include <stdint.h>


#pragma pack(push, 1)
struct usb_dev_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint16_t bcdUSB;
    uint8_t bDeviceClass;
    uint8_t bDeviceSubClass;
    uint8_t bDeviceProtocol;
    uint8_t bMaxPacketSize0;
    uint16_t idVendor;
    uint16_t idProduct;
    uint16_t bcdDevice;
    uint8_t iManufacturer;
    uint8_t iProduct;
    uint8_t iSerialNumber;
    uint8_t bNumConfigurations;

    inline void pretty_print(FILE *fp) {
        fprintf(fp, "bLength: %d\n", bLength);
        fprintf(fp, "bDescriptorType: %d\n", bDescriptorType);
        fprintf(fp, "bcdUSB: %d\n", bcdUSB);
        fprintf(fp, "bDeviceClass: %d\n", bDeviceClass);
        fprintf(fp, "bDeviceSubClass: %d\n", bDeviceSubClass);
        fprintf(fp, "bDeviceProtocol: %d\n", bDeviceProtocol);
        fprintf(fp, "bMaxPacketSize0: %d\n", bMaxPacketSize0);
        fprintf(fp, "idVendor: %d\n", idVendor);
        fprintf(fp, "idProduct: %d\n", idProduct);
        fprintf(fp, "bcdDevice: %d\n", bcdDevice);
        fprintf(fp, "iManufacturer: %d\n", iManufacturer);
        fprintf(fp, "iProduct: %d\n", iProduct);
        fprintf(fp, "iSerialNumber: %d\n", iSerialNumber);
        fprintf(fp, "bNumConfigurations: %d\n", bNumConfigurations);
    }
};

struct usb_config {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint16_t wTotalLength;
    uint8_t bNumInterfaces;
    uint8_t bConfigurationvalue;
    uint8_t iConfiguration;
    uint8_t bmAttributes;
    uint8_t MaxPower;

    inline void pretty_print(FILE *fp) {
        printf("bLength: %d\n", bLength);
        printf("bDescriptorType: %d\n", bDescriptorType);
        printf("wTotalLength: %d\n", wTotalLength);
        printf("bNumInterfaces: %d\n", bNumInterfaces);
        printf("bConfigurationvalue: %d\n", bConfigurationvalue);
        printf("iConfiguration: %d\n", iConfiguration);
        printf("bmAttributes: %d\n", bmAttributes);
        printf("MaxPower: %d\n", MaxPower);
    }
};

struct usb_interface {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bInterfaceNumber;
    uint8_t bAlternateSetting;
    uint8_t bNumEndpoints;
    uint8_t bInterfaceClass;
    uint8_t bInterfaceSubClass;
    uint8_t bInterfaceProtocol;
    uint8_t iInterface;

    inline void pretty_print(FILE *fp) {
        printf("usb_interface:\n");
        printf("\tbLength: %d\n", bLength);
        printf("\tbDescriptorType: %d\n", bDescriptorType);
        printf("\tbInterfaceNumber: %d\n", bInterfaceNumber);
        printf("\tbAlternateSetting: %d\n", bAlternateSetting);
        printf("\tbNumEndpoints: %d\n", bNumEndpoints);
        printf("\tbInterfaceClass: %d\n", bInterfaceClass);
        printf("\tbInterfaceSubClass: %d\n", bInterfaceSubClass);
        printf("\tbInterfaceProtocol: %d\n", bInterfaceProtocol);
        printf("\tiInterface: %d\n", iInterface);
    }
};

struct usb_endpoint {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bEndpointAddress;
    uint8_t bmAttributes;
    uint16_t wMaxPacketSize;
    uint8_t bInterval;

    inline void pretty_print(FILE *fp) {
        fprintf(fp, "usb_endpoint:\n");
        fprintf(fp, "\tbLength: %d\n", bLength);
        fprintf(fp, "\tbDescriptorType: %d\n", bDescriptorType);
        fprintf(fp, "\tbEndpointAddress: %d\n", bEndpointAddress);
        fprintf(fp, "\tbmAttributes: %d\n", bmAttributes);
        fprintf(fp, "\twMaxPacketSize: %d\n", wMaxPacketSize);
        fprintf(fp, "\tbInterval: %d\n", bInterval);
    }
};

struct usb_conf_long {
    usb_config cfg_descr;
    usb_interface itf_descr;
    usb_endpoint endp_descr[4];

    inline void pretty_print(FILE *fp) {
        cfg_descr.pretty_print(fp);
        itf_descr.pretty_print(fp);
        for (int i = 0; i < 4; i++) {
            endp_descr[i].pretty_print(fp);
        }
    }
};

struct mouse_report_t {
    struct {
        uint8_t button_left: 1;
        uint8_t button_right: 1;
        uint8_t button_middle: 1;
        uint8_t button_4: 1;
        uint8_t button_5: 1;
        uint8_t reserved: 3;
    } button;
    int8_t dx;
    int8_t dy;

    inline void pretty_print(FILE *fp) {
        fprintf(fp, "mouse_report_t: <%d,%d,%d>, (%d,%d)\n", button.button_left, button.button_middle,
                button.button_right, dx, dy);
    }
};

#pragma pack(pop)


/**
 * Class: MeUSBHost
 * \par Description
 * Declaration of Class MeUSBHost.
 */
class MeUSBHost {
public:
    /* max package length */
    const static uint16_t CH375_MAX_DATA_LEN = 0x80;
    const static uint16_t CH375_PORT_CMD = 0x261;
    const static uint16_t CH375_PORT_DATA = 0x260;


    const static int8_t USB2_0 = 1;
    const static int8_t USB1_0 = 0;

    enum Commands {
        CMD_RESET_ALL = 0x05,
        CMD_CHECK_EXIST = 0x06,
        CMD_SET_USB_ID = 0x12,
        CMD_SET_USB_ADDR = 0x13,
        CMD_SET_USB_MODE = 0x15,
        CMD_SET_ENDP2 = 0x18,
        CMD_SET_ENDP3 = 0x19,
        CMD_SET_ENDP4 = 0x1A,
        CMD_SET_ENDP5 = 0x1B,
        CMD_SET_ENDP6 = 0x1C,
        CMD_SET_ENDP7 = 0x1D,
        CMD_GET_TOGGLE = 0x0A,
        CMD_GET_STATUS = 0x22,
        CMD_UNLOCK_USB = 0x23,
        CMD_RD_USB_DATA = 0x28,
        CMD_WR_USB_DATA3 = 0x29,
        CMD_WR_USB_DATA5 = 0x2A,
        CMD_WR_USB_DATA7 = 0x2B,
        CMD_SET_BAUDRATE = 0x02,
        CMD_ABORT_NAK = 0x17,
        CMD_SET_RETRY = 0x0B,
        CMD_ISSUE_TOKEN = 0x4F,
        CMD_CLR_STALL = 0x41,
        CMD_SET_ADDRESS = 0x45,
        CMD_GET_DESCR = 0x46,
        CMD_SET_CONFIG = 0x49,
        CMD_DISK_INIT = 0x51,
        CMD_DISK_RESET = 0x52,
        CMD_DISK_SIZE = 0x53,
        CMD_DISK_READ = 0x54,
        CMD_DISK_RD_GO = 0x55,
        CMD_DISK_WRITE = 0x56,
        CMD_DISK_WR_GO = 0x57,
        CMD_GET_IC_VER = 0x01,
        CMD_ENTER_SLEEP = 0x03,
        CMD_RD_USB_DATA0 = 0x27,
        CMD_DELAY_100US = 0x0F,
        CMD_CHK_SUSPEND = 0x0B,
        CMD_SET_SYS_FREQ = 0x04,
        CMD_TEST_CONNECT = 0x16,
        CMD_AUTO_SETUP = 0x4D,
        CMD_ISSUE_TKN_X = 0x4E,
        CMD_RET_SUCCESS = 0x51,
        CMD_RET_ABORT = 0x5F,
        USB_INT_USB_SUSPEND = 0x05,
        USB_INT_WAKE_UP = 0x06,
        USB_INT_EP0_SETUP = 0x0C,
        USB_INT_EP0_OUT = 0x00,
        USB_INT_EP0_IN = 0x08,
        USB_INT_EP1_OUT = 0x01,
        USB_INT_EP1_IN = 0x09,
        USB_INT_EP2_OUT = 0x02,
        USB_INT_EP2_IN = 0x0A,
        USB_INT_BUS_RESET1 = 0x03,
        USB_INT_BUS_RESET2 = 0x07,
        USB_INT_BUS_RESET3 = 0x0B,
        USB_INT_BUS_RESET4 = 0x0F,
        USB_INT_SUCCESS = 0x14,
        USB_INT_CONNECT = 0x15,
        USB_INT_DISCONNECT = 0x16,
        USB_INT_BUF_OVER = 0x17,
        USB_INT_DISK_READ = 0x1D,
        USB_INT_DISK_WRITE = 0x1E,
        USB_INT_DISK_ERR = 0x1F,
        DEF_USB_PID_NULL = 0x00,
        DEF_USB_PID_SOF = 0x05,
        DEF_USB_PID_SETUP = 0x0D,
        DEF_USB_PID_IN = 0x09,
        DEF_USB_PID_OUT = 0x01,
        DEF_USB_PID_ACK = 0x02,
        DEF_USB_PID_NAK = 0x0A,
        DEF_USB_PID_STALL = 0x0E,
        DEF_USB_PID_DATA0 = 0x03,
        DEF_USB_PID_DATA1 = 0x0B,
        DEF_USB_PID_PRE = 0x0C,
        DEF_USB_REQ_READ = 0x80,
        DEF_USB_REQ_WRITE = 0x00,
        DEF_USB_REQ_TYPE = 0x60,
        DEF_USB_REQ_STAND = 0x00,
        DEF_USB_REQ_CLASS = 0x20,
        DEF_USB_REQ_VENDOR = 0x40,
        DEF_USB_REQ_RESERVE = 0x60,
        DEF_USB_CLR_FEATURE = 0x01,
        DEF_USB_SET_FEATURE = 0x03,
        DEF_USB_GET_STATUS = 0x00,
        DEF_USB_SET_ADDRESS = 0x05,
        DEF_USB_GET_DESCR = 0x06,
        DEF_USB_SET_DESCR = 0x07,
        DEF_USB_GET_CONFIG = 0x08,
        DEF_USB_SET_CONFIG = 0x09,
        DEF_USB_GET_INTERF = 0x0A,
        DEF_USB_SET_INTERF = 0x0B,
        DEF_USB_SYNC_FRAME = 0x0C
    };

    bool ch375_online;
    bool device_online;
    bool device_ready;
    int8_t usbtype;
    FILE *debug_fp;

    uint8_t RECV_BUFFER[CH375_MAX_DATA_LEN];

    MeUSBHost() : ch375_online(false), device_ready(false), device_online(false), usbtype(USB1_0), debug_fp(NULL) {}

    inline usb_conf_long *p_cfg_descr() { return reinterpret_cast<usb_conf_long *>(RECV_BUFFER); }

    inline usb_dev_descriptor *p_dev_descr() { return reinterpret_cast<usb_dev_descriptor *>(RECV_BUFFER); }

    /**
     *    initHIDDevice
     */
    int16_t initHIDDevice() {
        int16_t irq, len, address;
        if (usbtype == USB1_0)
            set_freq(); // work on a lower freq, necessary for ch375
        irq = get_desr(1);
        if (irq == USB_INT_SUCCESS) {
            len = rd_usb_data(RECV_BUFFER);
            irq = set_addr(2);
            if (irq == USB_INT_SUCCESS) {
                irq = get_desr(2); // max buf 64byte, todo:config descr overflow
                if (irq == USB_INT_SUCCESS) {
                    len = rd_usb_data(RECV_BUFFER);
                    if (debug_fp != NULL) {
                        p_cfg_descr()->pretty_print(debug_fp);
                    }
                    if (p_cfg_descr()->endp_descr[0].bDescriptorType ==
                        0x21) { // skip hid des
                        tmpEp = (usb_endpoint *) ((int8_t * )(&(p_cfg_descr()->endp_descr[0])) +
                                                  p_cfg_descr()->endp_descr[0]
                                                          .bLength); // get the real ep position


                        if (debug_fp != NULL) {
                            tmpEp->pretty_print(debug_fp);
                        }
                    }
                    endp_out_addr = endp_in_addr = 0;
                    address = tmpEp->bEndpointAddress; /* Address of First EndPoint */
                    // actually we only care about the input end points
                    if (address & 0x80) {
                        endp_in_addr = address & 0x0f; /* Address of IN EndPoint */
                    } else {                         /* OUT EndPoint */
                        endp_out_addr = address & 0x0f;
                        endp_out_size = p_cfg_descr()->endp_descr[0].wMaxPacketSize;
                        /* Length of Package for Received Data EndPoint */
                        if (endp_out_size == 0 || endp_out_size > 64)
                            endp_out_size = 64;
                    }
                    // todo: some joystick with more than 2 node
                    // just assume every thing is fine, bring the device up
                    irq = set_config(p_cfg_descr()->cfg_descr.bConfigurationvalue);
                    if (irq == USB_INT_SUCCESS) {
                        CH375_WR_CMD(CMD_SET_RETRY); // set the retry times
                        CH375_WR_DATA(0x25);
                        CH375_WR_DATA(0x85);
                        device_ready = true;
                        return 1;
                    }
                }
            }
        }
        return 0;
    }

    /**
     * \par Function
     *    probeDevice
     * \par Description
     *    Prode of USB Host Device.
     * \param[in]
     *    None
     * \par Output
     *    None
     * \return
     *    The result of device's probe.
     * \par Others
     *    None
     */
    int16_t probeDevice() {
        int16_t c;
        if (!ch375_online) {
            CH375_WR_CMD(CMD_CHECK_EXIST);
            CH375_WR_DATA(0x5A);
            c = CH375_RD(); // should return 0xA5
            if (c != 0xA5)
                return 0;
            ch375_online = true;
            resetBus();
        }

        c = getIrq();
        if (c != USB_INT_CONNECT)
            return 0;
        resetBus(); // reset bus and wait the device online again
        c = 0;
        while (c != USB_INT_CONNECT) {
            delay(500); // some device may need long time to get ready
            c = getIrq();
        }
        if (initHIDDevice() == 1)
            device_online = true;
        return c;
    }

    /**
     * \par Function
     *    resetBus
     * \par Description
     *    Reset the data Bus.
     * \param[in]
     *    None
     * \par Output
     *    None
     * \return
     *    None
     * \par Others
     *    None
     */
    void resetBus() {
        int16_t c;
        c = set_usb_mode(7);
        delay(10);
        c = set_usb_mode(6);
        delay(10);
    }

    /**
     * \par Function
     *    host_recv
     * \par Description
     *    The USB Host receive data.
     * \param[in]
     *    None
     * \par Output
     *    None
     * \return
     *    Return the length of data.
     * \par Others
     *    None
     */
    uint8_t host_recv() {
        uint8_t irq;
        toggle_recv();
        irq = issue_token((endp_in_addr << 4) | DEF_USB_PID_IN);
        if (irq == USB_INT_SUCCESS) {
            int16_t len = rd_usb_data(RECV_BUFFER);
            stallCount = 0;
            return len;
        } else if (irq == USB_INT_DISCONNECT) {
            device_online = false;
            device_ready = false;
            return 0;
        } else {
            clr_stall6();
            delay(10);
            /*
            stallCount++;
            if(stallCount>10){
              device_online = false;
              device_ready = false;
              resetBus();
            }
            */
            return 0;
        }
    }

private:
    int16_t stallCount;

    unsigned char endp_out_addr;
    unsigned char endp_out_size;
    unsigned char endp_in_addr;
    unsigned char endp6_mode, endp7_mode;

    usb_endpoint *tmpEp;

    /**
     * \par Function
     *    CH375_RD
     * \par Description
     *    Read data from USB.
     * \param[in]
     *    None
     * \par Output
     *    None
     * \return
     *    Return 0;
     * \par Others
     *    None
     */
    inline uint8_t CH375_RD() { return inp(CH375_PORT_DATA); }

    /**
     * \par Function
     *    CH375_WR_CMD
     * \par Description
     *    Write data to USB device.
     * \param[in]
     *    c - The bytes that wrote to device.
     * \par Output
     *    None
     * \return
     *    None
     * \par Others
     *    None
     */
    void inline CH375_WR_CMD(uint8_t c) { outp(CH375_PORT_CMD, c); }

    /**
     * \par Function
     *    CH375_WR_DATA
     * \par Description
     *    Write data to USB device.
     * \param[in]
     *    c - The bytes that wrote to device.
     * \par Output
     *    None
     * \return
     *    None
     * \par Others
     *    None
     */
    void inline CH375_WR_DATA(uint8_t c) { outp(CH375_PORT_DATA, c); }

    /**
     * \par Function
     *    set_usb_mode
     * \par Description
     *    Set the work mode of USB.
     * \param[in]
     *    mode - The USB's work mode.
     * \par Output
     *    None
     * \return
     *    Return the data that CH375_RD()'s return.
     * \par Others
     *    None
     */
    inline int16_t set_usb_mode(int16_t mode) {
        CH375_WR_CMD(CMD_SET_USB_MODE);
        CH375_WR_DATA(mode);
        endp6_mode = endp7_mode = 0x80;
        return CH375_RD();
    }

    /**
     * \par Function
     *    getIrq
     * \par Description
     *    Get the Interrupt Request of USB.
     * \param[in]
     *    None
     * \par Output
     *    None
     * \return
     *    Return the data that CH375_RD()'s return.
     * \par Others
     *    None
     */
    inline uint8_t getIrq() {
        CH375_WR_CMD(CMD_GET_STATUS);
        delay(20);
        return CH375_RD();
    }

    /**
     * \par Function
     *    toggle_send
     * \par Description
     *    The toggle used to send data.
     * \param[in]
     *    None
     * \par Output
     *    None
     * \return
     *    None
     * \par Others
     *    None
     */
    inline void toggle_send() {
        CH375_WR_CMD(CMD_SET_ENDP7);
        CH375_WR_DATA(endp7_mode);
        endp7_mode ^= 0x40;
    }

    /**
     * \par Function
     *    toggle_recv
     * \par Description
     *    The toggle used to receive data.
     * \param[in]
     *    None
     * \par Output
     *    None
     * \return
     *    None
     * \par Others
     *    None
     */
    inline void toggle_recv() {
        CH375_WR_CMD(CMD_SET_ENDP6);
        CH375_WR_DATA(endp6_mode);
        endp6_mode ^= 0x40;
    }

    /**
     * \par Function
     *    issue_token
     * \par Description
     *    USB Host make a token and perform transactions.
     * \param[in]
     *    endp_and_pid - The token that USB Host used.
     * \par Output
     *    None
     * \return
     *    Return the Interrupt Request.
     * \par Others
     *    None
     */
    inline uint8_t issue_token(uint8_t endp_and_pid) {
        CH375_WR_CMD(CMD_ISSUE_TOKEN);
        CH375_WR_DATA(endp_and_pid); /* Bit7~4 for EndPoint No, Bit3~0 for Token PID */
        delay(2);
        return getIrq();
    }

    /**
     * \par Function
     *    wr_usb_data
     * \par Description
     *    Write data to USB Host.
     * \param[in]
     *    len - The data's length.
     * \param[in]
     *    buf - Data in buffer.
     * \par Output
     *    None
     * \return
     *    None
     * \par Others
     *    None
     */
    inline void wr_usb_data(uint8_t len, uint8_t *buf) {
        CH375_WR_CMD(CMD_WR_USB_DATA7);
        CH375_WR_DATA(len);
        while (len--) {
            CH375_WR_DATA(*buf++);
        }
    }

    /**
     * \par Function
     *    rd_usb_data
     * \par Description
     *    Read data from USB Host.
     * \param[in]
     *    len - The data's length.
     * \param[in]
     *    buf - Data in buffer.
     * \par Output
     *    None
     * \return
     *    Return the length of read data.
     * \par Others
     *    None
     */
    inline uint8_t rd_usb_data(uint8_t *buf) {
        uint8_t i, len;
        CH375_WR_CMD(CMD_RD_USB_DATA);
        len = CH375_RD();
        for (i = 0; i != len; i++)
            *buf++ = CH375_RD();
        return (len);
    }

    /**
     * \par Function
     *    get_version
     * \par Description
     *    Get version of USB Host.
     * \param[in]
     *    None
     * \par Output
     *    None
     * \return
     *    Return the data that CH375_RD()'s return.
     * \par Others
     *    None
     */
    inline int16_t get_version() {
        CH375_WR_CMD(CMD_GET_IC_VER);
        return CH375_RD();
    }

    /**
     * \par Function
     *    set_freq
     * \par Description
     *    Set frequency of USB Host.
     * \param[in]
     *    None
     * \par Output
     *    None
     * \return
     *    None
     * \par Others
     *    None
     */
    inline void set_freq(void) {
        CH375_WR_CMD(0x0b);
        CH375_WR_DATA(0x17);
        CH375_WR_DATA(0xd8);
    }

    /**
     * \par Function
     *    set_addr
     * \par Description
     *    Set address of USB Host.
     * \param[in]
     *    addr - The address of USB Host.
     * \par Output
     *    None
     * \return
     *    Return the number of Interrupt Request.
     * \par Others
     *    None
     */
    inline uint8_t set_addr(uint8_t addr) {
        uint8_t irq;
        CH375_WR_CMD(CMD_SET_ADDRESS);
        CH375_WR_DATA(addr);
        irq = getIrq();
        if (irq == USB_INT_SUCCESS) {
            CH375_WR_CMD(CMD_SET_USB_ADDR);
            CH375_WR_DATA(addr);
        }
        return irq;
    }

    /**
     * \par Function
     *    set_config
     * \par Description
     *    Set config of USB Host.
     * \param[in]
     *    cfg - The config file of USB Host.
     * \par Output
     *    None
     * \return
     *    Return the number of Interrupt Request.
     * \par Others
     *    None
     */
    inline uint8_t set_config(uint8_t cfg) {
        endp6_mode = endp7_mode = 0x80; // reset the sync flags
        CH375_WR_CMD(CMD_SET_CONFIG);
        CH375_WR_DATA(cfg);
        return getIrq();
    }

    /**
     * \par Function
     *    clr_stall6
     * \par Description
     *    Clear all stall in USB Host.
     * \param[in]
     *    None
     * \par Output
     *    None
     * \return
     *    Return the number of Interrupt Request.
     * \par Others
     *    None
     */
    inline uint8_t clr_stall6(void) {
        CH375_WR_CMD(CMD_CLR_STALL);
        CH375_WR_DATA(endp_out_addr | 0x80);
        endp6_mode = 0x80;
        return getIrq();
    }

    /**
     * \par Function
     *    get_desr
     * \par Description
     *    Get description of USB Host.
     * \param[in]
     *    type - The type of description.
     * \par Output
     *    None
     * \return
     *    Return the number of Interrupt Request.
     * \par Others
     *    None
     */
    inline uint8_t get_desr(uint8_t type) {
        CH375_WR_CMD(CMD_GET_DESCR);
        CH375_WR_DATA(type); /* description type, only 1(device) or 2(config) */
        return getIrq();
    }
};

#endif // CH375HID_USB_HOST_H
