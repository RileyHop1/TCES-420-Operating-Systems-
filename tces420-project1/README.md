# Linux Kernel Custom System Call - Raspberry Pi 5

A custom Linux system call implemented and deployed on a Raspberry Pi 5 running a modified ARM64 Linux kernel. Developed as part of a class project at the University of Washington. This project explores basic kernel development, system call dispatching, and communication between user space and kernel space.


## Development Environment 

- Hardware: Raspberry Pi 5 Model B
- Target architecture: ARM64
- Kernel: Raspberry Pi Linux 6.18
- Development host: macOS
- Build environment: Ubuntu ARM64 in VirtualBox
- Base commit hash: 80d4218cb877ccb07d09a9f21f0678e78d8b36f5
- Repository: https://github.com/raspberrypi/linux
- Branch: rpi-6.18.y

## Implementation 

Implemented a custom system call, `tces420_hello`, assigned the syscall number 470.

The system call writes a message to the kernel log using `printk()` and returns a zero upon successful execution.

For this implementation I modified four kernel files:

- `scripts/syscall.tbl` - Registered the new syscall in the table
- `kernel/sys.c` - Added the implimentation for the syscall
- `include/linux/syscall.h` - Declares the new syscall in the header
- `kernel/sys_ni.c` -  Adds a fallback registration

## Testing 

I was able to successfully launch the modified kernel of the Raspberry Pi 5. A users space C application was developed to invoke the new syscall.

Giving the following output:
```bash
./test_syscall
sudo dmesg | grep "TCES420:"
```

## Technical Challenges


During the development, I ran into a compatibility issue which prevented the Raspberry Pi's Wi-Fi driver from correctly running. When I inspected the kernel logs I got a symbol version mismatch involving `bpf_trace_run1`. I resolved the issue by rebuilding the kernel and modules together, reinstalling them, and regenerating the initramfs.

## Repository Structure

- `patches/` - Linux kernel source modifications.
- `userspace/` - User space syscall test application.
- `solution/` - Kernel logs and execution evidence.

## Results

Successfully demonstrated communication between a user-space application and a custom Linux kernel system call on a physical ARM64 hardware.



