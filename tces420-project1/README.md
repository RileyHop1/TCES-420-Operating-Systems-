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

The system call writes a message to the kernel log using `printk()` and returns zero upon successful execution.

For this implementation, I modified four kernel files:

- `scripts/syscall.tbl` - Registered the new syscall in the table
- `kernel/sys.c` - Added the implementation for the syscall
- `include/linux/syscall.h` - Declares the new syscall in the header
- `kernel/sys_ni.c` -  Adds a fallback registration

## Testing 

I was able to successfully launch the modified kernel on the Raspberry Pi 5. A userspace C application was developed to invoke the new syscall.

Giving the following output:
```bash
./test_syscall
sudo dmesg | grep "TCES420:"
```

## Technical Challenges


During the development, I ran into a compatibility issue which prevented the Raspberry Pi's Wi-Fi driver from correctly running. When I inspected the kernel logs, I got a symbol version mismatch involving `bpf_trace_run1`. I resolved the issue by rebuilding the kernel and modules together, reinstalling them, and regenerating the initramfs.

## Alternative approach 

From the reading that I have done, it does look like it may be possible. Within this article: https://linuxvox.com/blog/procfs-linux/ it talks about `procfs` a runtime way for userspace code to interact with the kernel through a virtual filesystem. Processes are treated as files, so you could register a new process to do something similar to what we have done with the syscall. 


## Repository Structure

- `patches/` - Linux kernel source modifications.
- `userspace/` - User space syscall test application.
- `solution/` - Kernel logs and execution evidence.

## Contributors 

There were no other contributors for this assignment; I worked on it on my own.

## Results

Successfully demonstrated communication between a user-space application and a custom Linux kernel system call on physical ARM64 hardware.



