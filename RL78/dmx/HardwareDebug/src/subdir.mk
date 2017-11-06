################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
..\src/cstart.asm \
..\src/stkinit.asm 

C_SRCS += \
..\src/r_cg_cgc.c \
..\src/r_cg_cgc_user.c \
..\src/r_cg_port.c \
..\src/r_cg_port_user.c \
..\src/r_cg_serial.c \
..\src/r_cg_serial_user.c \
..\src/r_cg_timer.c \
..\src/r_cg_timer_user.c \
..\src/r_cg_wdt.c \
..\src/r_cg_wdt_user.c \
..\src/r_main.c \
..\src/r_systeminit.c 

C_DEPS += \
./src/r_cg_cgc.d \
./src/r_cg_cgc_user.d \
./src/r_cg_port.d \
./src/r_cg_port_user.d \
./src/r_cg_serial.d \
./src/r_cg_serial_user.d \
./src/r_cg_timer.d \
./src/r_cg_timer_user.d \
./src/r_cg_wdt.d \
./src/r_cg_wdt_user.d \
./src/r_main.d \
./src/r_systeminit.d 

OBJS += \
./src/cstart.obj \
./src/r_cg_cgc.obj \
./src/r_cg_cgc_user.obj \
./src/r_cg_port.obj \
./src/r_cg_port_user.obj \
./src/r_cg_serial.obj \
./src/r_cg_serial_user.obj \
./src/r_cg_timer.obj \
./src/r_cg_timer_user.obj \
./src/r_cg_wdt.obj \
./src/r_cg_wdt_user.obj \
./src/r_main.obj \
./src/r_systeminit.obj \
./src/stkinit.obj 

ASM_DEPS += \
./src/cstart.d \
./src/stkinit.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.obj: ../src/%.asm
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Assembler'
	ccrl  -asmopt=-MM -asmopt=-MP -asmopt=-MF="$(@:%.obj=%.d)" -asmopt=-MT="$(@:%.obj=%.obj)" -asmopt=-MT="$(@:%.obj=%.d)" -o "$(@:%.d=%.obj)" -cpu=S2 -c -dev="C:/Renesas/e2_studio/DebugComp/RL78\Common\DR5F102A8.DVF"  -msg_lang=english -g   "$<"
	ccrl -o "$(@:%.d=%.obj)" -cpu=S2 -c -dev="C:/Renesas/e2_studio/DebugComp/RL78\Common\DR5F102A8.DVF"  -msg_lang=english -g   "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

src/%.obj: ../src/%.c
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	ccrl  -MM -MP -o "$(@:%.obj=%.d)" -MT="$(@:%.obj=%.obj)" -MT="$(@:%.obj=%.d)"  -cpu=S2 -dev="C:/Renesas/e2_studio/DebugComp/RL78\Common\DR5F102A8.DVF"  -msg_lang=english -I "C:\PROGRA~2\Renesas\RL78\1_4_0/inc" -g -Ointermodule -Ospeed -Oinline_level=2 -Oinline_size -Opipeline   "$<"
	ccrl -o "$(@:%.d=%.obj)" -cpu=S2 -c -dev="C:/Renesas/e2_studio/DebugComp/RL78\Common\DR5F102A8.DVF"  -msg_lang=english -I "C:\PROGRA~2\Renesas\RL78\1_4_0/inc" -g -Ointermodule -Ospeed -Oinline_level=2 -Oinline_size -Opipeline   "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

