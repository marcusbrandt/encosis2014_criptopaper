################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../jni/crypto.cpp 

OBJS += \
./jni/crypto.o 

CPP_DEPS += \
./jni/crypto.d 


# Each subdirectory must supply rules for building sources it contributes
jni/%.o: ../jni/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/marcusbrandt/Softwares/android-ndk-r9c/platforms/android-19/arch-arm/usr/include -I/home/marcusbrandt/Softwares/OpenCV-2.4.8-android-sdk/sdk/native/jni/include -I/home/marcusbrandt/Softwares/android-ndk-r9c/sources/cxx-stl/stlport/stlport -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


