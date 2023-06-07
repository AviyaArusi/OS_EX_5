Encrypted Memory Kernel Module
Overview
This is a kernel module that manages encrypted memory. It provides various interfaces for interaction,
allowing for reading, writing, and modifying encrypted memory.

Building the Module
To build the module, navigate to the source code directory and run the make command:

make
This will compile the source code and generate a kernel module named encryptedmem.ko.

Running the Module
To load the module into the kernel, use the insmod command:


sudo insmod encryptedmem.ko
You can now interact with the module. For example, to write to the module, you can use the echo command:


echo "Hello" | sudo tee /dev/encryptedmem > /dev/null
or (for getting the output to the terminal)
echo "Hello" | sudo tee /dev/encryptedmem

To read from the module, you can use the cat command:


cat /dev/encryptedmem
When you are done with the module, unload it from the kernel using the rmmod command:


sudo rmmod encryptedmem

make clean
This command will delete the files that the make creat.