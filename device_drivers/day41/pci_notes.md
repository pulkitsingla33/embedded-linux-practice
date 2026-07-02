### Vendor ID
- 0x1234

### Device ID
- 0x11e8

### BAR Addresses
0x00000000fea00000 0x00000000feafffff 0x0000000000040200
0x0000000000000000 0x0000000000000000 0x0000000000000000
0x0000000000000000 0x0000000000000000 0x0000000000000000
0x0000000000000000 0x0000000000000000 0x0000000000000000
0x0000000000000000 0x0000000000000000 0x0000000000000000
0x0000000000000000 0x0000000000000000 0x0000000000000000
0x0000000000000000 0x0000000000000000 0x0000000000000000
0x0000000000000000 0x0000000000000000 0x0000000000000000
0x0000000000000000 0x0000000000000000 0x0000000000000000
0x0000000000000000 0x0000000000000000 0x0000000000000000
0x0000000000000000 0x0000000000000000 0x0000000000000000
0x0000000000000000 0x0000000000000000 0x0000000000000000
0x0000000000000000 0x0000000000000000 0x0000000000000000

### IRQ Line
- 11

### Kernel Driver
- None

### What happens inside `probe()`?
The `probe()` function is executed by the kernel the moment it detects a physical PCI device matching the driver's ID table. Inside this function, the driver actively initializes the hardware by enabling the device, claiming its memory regions, and mapping its Base Address Registers (BARs) into the kernel's virtual memory space. It also allocates any necessary internal data structures, registers character devices, and requests an IRQ interrupt line to handle asynchronous hardware events. If any initialization step fails, it executes a strict, structured teardown sequence to undo prior successful steps in reverse order.

### What happens inside `remove()`?
The `remove()` function handles the graceful teardown of the driver whenever the device is physically unplugged, the virtual machine is modified, or the user unloads the kernel module via `rmmod`. It performs the exact inverse operations of the `probe()` function to prevent resource and memory leaks within the kernel space. Specifically, it releases the assigned IRQ interrupt lines, unmaps any mapped BAR memory pointers, frees allocated driver memory buffers, and tells the kernel to safely disable the physical device on the PCI bus.

### Why is the ID table required?
The ID table (`struct pci_device_id`) serves as the registration index or "hardware fingerprint match engine" that the Linux kernel uses to link physical equipment to software drivers. It contains an array of specific hexadecimal Vendor ID and Device ID pairings that the driver officially knows how to control. When the system boots or a new device is plugged into the PCI bus, the core kernel scans this table; if the device's hardcoded signature matches an entry, the kernel establishes a bind and triggers the driver's `probe()` function.