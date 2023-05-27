#include <iostream>
#include <libusb-1.0/libusb.h>

int main() {
    libusb_context* context = nullptr;  // libusb context
    libusb_device** device_list = nullptr;  // list of devices

    // Initialize libusb
    int result = libusb_init(&context);
    if (result != LIBUSB_SUCCESS) {
        std::cerr << "Failed to initialize libusb." << std::endl;
        return 1;
    }

    // Set debug level to get detailed information (optional)
    libusb_set_option(context, LIBUSB_OPTION_LOG_LEVEL, LIBUSB_LOG_LEVEL_DEBUG);

    // Get the list of USB devices
    ssize_t count = libusb_get_device_list(context, &device_list);
    if (count < 0) {
        std::cerr << "Failed to get USB device list." << std::endl;
        libusb_exit(context);
        return 1;
    }

    // Iterate over each device
    for (ssize_t i = 0; i < count; ++i) {
        libusb_device* device = device_list[i];
        libusb_device_descriptor descriptor;

        // Get device descriptor
        result = libusb_get_device_descriptor(device, &descriptor);
        if (result != LIBUSB_SUCCESS) {
            std::cerr << "Failed to get device descriptor." << std::endl;
            continue;
        }

        // Check if the device is a USB device you want to disconnect
        if (true) {
            // Open the device
            libusb_device_handle* handle = nullptr;
            result = libusb_open(device, &handle);
            if (result != LIBUSB_SUCCESS) {
                std::cerr << "Failed to open USB device." << std::endl;
                continue;
            }

            // Detach the kernel driver from the device
                if (libusb_attach_kernel_driver(handle, 0) != LIBUSB_SUCCESS) {
        std::cerr << "Failed to attach kernel driver" << std::endl;
    }
            

            // Close the device
            libusb_close(handle);

            // Device is disconnected
            std::cout << "USB device disconnected." << std::endl;
        }
    }

    // Free the device list
    libusb_free_device_list(device_list, 1);

    // Exit libusb
    libusb_exit(context);

    return 0;
}
