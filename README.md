# Carbon Hypervisor

## What is this?

This is a Custom Hypervisor Implementation for Exynos Devices. <br>
It's Goal is to Implement Workarounds for SoC Quirks.

## Supported SoCs

- Exynos 9810 (S5E9810)

## Components

| Feature   | Notes                  | State |
|:----------|:-----------------------|:-----:|
| PSCI v1.1 | Minimal Implementation | ✅    |

## Compilation

To Compile this Hypervisor, Simply run these 2 Commands:
```bash
make TARGET=[SOC_INTERNAL_NAME] clean
make TARGET=[SOC_INTERNAL_NAME]
```
`SOC_INTERNAL_NAME` is the Internal Name of the Exynos SoC, Building Exynos 9810 for Example would be `s5e9810`. <br>
A new File called `hyp.bin` will show up after the Build, Which is the File you'll use in the UEFI Firmware.

## Credits

- [halal-beef](https://github.com/halal-beef/) for his [exynos990-payloads](https://github.com/halal-beef/exynos990-payloads/), which is used as a Base and for making the Dynamic Trampoline Code.
- [Nikroks](https://github.com/N1kroks/) for his Guidance on How to properly make a Hypervisor.
- [Robotix](https://github.com/Robotix22/) for the Basic Hypervisor Implementation.
