# Toy Rasberry Pi 4 Operating System


## Introduction
This repository contains a toy operating system I am writing for my Raspberry Pi
as a project to learn more about how operating systems work at a low level. 


## To compile
[The ARM cross compiler](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads) is required to build the kernel image. 

The Makefile includes the option to run the kernel in a Raspberry Pi 2 VM using [QEMU](https://www.qemu.org/). While this currently works, it is not guaranteed to be supported in the future if further differences between the Pi 2 and 4 break compatibility. 

## Credit
[This tutorial](https://jsandler18.github.io/tutorial/wrangling-mem.html) 
was used as a guide and a reference. 