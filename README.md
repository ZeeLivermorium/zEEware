#GCC Tools for TI TM4C123GXL MCU

## Introduction
This is a gcc tools for embedded system projects with TI TM4C123GXL Microcontroller on Mac OS and Linux. We hate IDEs.

## Installation
### Mac OS
#### ARM GCC Tools
```bash
    brew tap PX4/homebrew-px4
    brew update
    brew install gcc-arm-none-eabi
```
You might run into problems when *arm-none-eabi-gcc* command is not found after installation. Try 
```bash
    brew link gcc-arm-none-eabi
```
see what homebrew tells you to fix linking problem.

**NOTE**: The old magic command
```bash
    brew cask install gcc-arm-embedded
```
does not work anymore. They removed it from cask. Put it here in case you are wondering or you are trying to use [UT-Rasware](https://github.com/ut-ras/Rasware) installation guide.

#### Lm4tools
```bash
    brew install lm4tools
```
#### OpenOCD
```bash
    brew install open-ocd
```

### Linux (Need to be tested)
Please refer to Josh Minor's Linux set up [script](https://github.com/jishminor/ee445l-linux/blob/master/setup-linux.sh)

### Test
Go to proj/_blink folder to do a *make* to see if it can compile. Try *make flash* if you want to test it on board to see some RGBs. 

## Run Projects
As the last step in the installation, you should run the test [blink project](proj/_blink) by running *make* in the project folder to make sure it compiles properly. You need to run *make clean* when you try to clean up your build product. By running *make flash* you should be able to flash it on to your TM4C123G Launchpad.
To run your own project, you can use the [template Makefile](proj/Makefile) and your configuration to it. Please refer to my other projects to see how I write my makefile.
1. Add project name
In [template Makefile](proj/Makefile#L35) put your project name here.
2. Add include paths
In [template Makefile](proj/Makefile#L57), add where your h files are. 
3. Add the c files you are tyring to use
In [template Makefile](proj/Makefile#L83), add c files used in your project in terms of object files.
4. make (flash)

## Acknowledgment
[Josh Minor](https://github.com/jishminor)'s linux tools has been a super valuable referenece when I tried to tackle problems. You can find his tools [here](https://github.com/jishminor/ee445l-linux).

