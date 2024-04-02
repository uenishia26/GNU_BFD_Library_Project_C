Compilation and Testing Instructions
*Please insure all tools have been installed like the bfd library. 

Task A: Static Library and Utilities
To compile the project, run: make
If you need to clean the build directory (remove executables and object files), use: make clean
For analyzing binary sections, execute: ./getsections <binary-file>
For analyzing binary symbols, execute: ./getsyms <binary-file>


Task B: Dynamic Library and Utilities
The same make command prepares the dynamic utilities as well.
To run the dynamic utilities with RTLD_LAZY, use: (This can be replaced with RTLD_NOW also)
    ./getsections_dl <binary-file> RTLD_LAZY 
    ./getsyms_dl <binary-file> RTLD_LAZY
For benchmarking with the provided script and to get the average timing, execute: 
./run_test.sh <binary-file> RTLD_LAZY or RTLD_NOW
The four stats file that already exist was pre executed with <getsections_d1.o> 
**CPU Config 2.20 GHZ, CPU Cores: 1
Used base clock speed cause stays consistent instead of current speed in Mhz 


Task C: objcopy Utility
To run the objcopy utility and dump the .text section of an ELF binary, use: ./objcopy <binary-file>
To compare the output with GNU objcopy, first convert the output to a human-readable format and then compare: 
    od -tx1 text-output > text-output.od 
    objcopy -O binary --only-section=.text <binary-file> terminal-output (Using GNU objcopy for comparing) 
    od -tx1 terminal-output > terminal-output.od 
    diff text-output.od terminal-output.od (Comparing) 
Verifying Library Contents for objcopy.o:
To list the object files contained in the static library libobjdata.a, use: ar -t libobjdata.a (To verify objcopy is part of .a lib)
To verify the objcopy.o also exists in the dynamic library, link a test executable against libobjdata.so and execute.
**Before running ./objcopy you for testing functionaly match with GNU objcopy you must make objcopy an exectuable: 
    Thus, objcopy has been included in Makefile to be made an exectuable
    This was on purpose to be able to test and match the result with GNU objcopy 
    The binary objcopy.o still exists in the two libraries. Just also made an exectuable version for testing purposes 

***The code needed to generate the corresponding libaries is all part of the Makefile as
my libraries are created at make and deleted at make clean to ensure updated libraries please take 
a look at Makefile for code 
