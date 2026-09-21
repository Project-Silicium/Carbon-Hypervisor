# Carbon Hypervisor

## What is this?

This is a Custom Hypervisor Implementation for the S5E9810. <br>
It's Goal is to Implement a Compliant PSCI v1.1 Interface on top of the Existing v0.1 Interface.

## Reason

The EL3 Monitor of the S5E9810 Implements a very Old PSCI Version which is not Compatible with Windows. <br>
The `CPU_ON` PSCI Function also lacks the Code to Handle the `context_id` Parameter, Leading it to be unused.

## Compilation

To Compile this Hypervisor, Simply run these 2 Commands:
```bash
make clean
make
```
A new File called `hyp.bin` will show up, Which is the File you'll use in the UEFI Firmware.

## Credits

- [halal-beef](https://github.com/halal-beef/) for his [exynos990-payloads](https://github.com/halal-beef/exynos990-payloads/), which is used as a Base and for making the Dynamic Trampoline Code.
- [Nikroks](https://github.com/N1kroks/) for his Guidance on How to properly make a Hypervisor.
- [Robotix](https://github.com/Robotix22/) for the Basic Hypervisor Implementation.
