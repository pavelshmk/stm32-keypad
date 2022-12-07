add_library(tinyusb INTERFACE)
target_sources(tinyusb INTERFACE
        tusb.c
        class/hid/hid_device.c
        class/msc/msc_device.c
        common/tusb_fifo.c
        common/tusb_fifo.c
        device/usbd.c
        device/usbd_control.c
        portable/synopsys/dwc2/dcd_dwc2.c
        )
target_include_directories(tinyusb INTERFACE
        .)
