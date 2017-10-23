#ifndef _IEASY_PORT_H_
#define _IEASY_PORT_H_

#define     IEASYDRIVER_MASK                            0x3001          // Mask interrupt
#define     IEASYDRIVER_UNMASK                          0x3002          // Unmask interrupt
#define     IEASYDRIVER_ALLOC                           0x3003          // Allocated interrupt
#define     IEASYDRIVER_PORT1                           0x3011          // Use local interrupt 1
#define     IEASYDRIVER_PORT2                           0x3012          // Use local interrupt 2
#define     IEASYDRIVER_PORT12                          0x3013          // Use local interrupt 1 and 2

//Error
#define     IEASYDRIVER_ERROR_NO_SUPPORTED_DEVICE       -1              // Not supported device
#define     IEASYDRIVER_ERROR_NO_REGISTERED_DLL         -2              // Not registered dll
#define     IEASYDRIVER_ERROR_NO_SUPPORTED_VERSION      -3              // Not supported version
#define     IEASYDRIVER_ERROR_NO_INIT_DEVICE            -4              // Can not init device
#define     IEASYDRIVER_ERROR_INTERFACE                 -5              // Not created interface
#define     IEASYDRIVER_ERROR_OUT_RANGE                 -6              // Error in parameters

#define     IEASYDRIVER_GETREGSTATE                     0x0015          // Get state register 0x4c for PCI9050
#define     MICRO_TIMEOUT                               1               // Minimal Time Out (ms)

#endif