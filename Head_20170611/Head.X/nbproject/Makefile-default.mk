#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Head.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Head.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=sources/CanTestForBd1.c sources/CanTestForBd1_main.c sources/ecan1.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/sources/CanTestForBd1.o ${OBJECTDIR}/sources/CanTestForBd1_main.o ${OBJECTDIR}/sources/ecan1.o
POSSIBLE_DEPFILES=${OBJECTDIR}/sources/CanTestForBd1.o.d ${OBJECTDIR}/sources/CanTestForBd1_main.o.d ${OBJECTDIR}/sources/ecan1.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/sources/CanTestForBd1.o ${OBJECTDIR}/sources/CanTestForBd1_main.o ${OBJECTDIR}/sources/ecan1.o

# Source Files
SOURCEFILES=sources/CanTestForBd1.c sources/CanTestForBd1_main.c sources/ecan1.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Head.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ128MC804
MP_LINKER_FILE_OPTION=,--script=p33FJ128MC804.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/sources/CanTestForBd1.o: sources/CanTestForBd1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/CanTestForBd1.o.d 
	@${RM} ${OBJECTDIR}/sources/CanTestForBd1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sources/CanTestForBd1.c  -o ${OBJECTDIR}/sources/CanTestForBd1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sources/CanTestForBd1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"sources" -I"." -I"E:/Program/Mplab/ForTestS/Test_Canbus/CanTestForBd1" -I"C:/PROGRA~1/MICROC~1/mplabc30/v3.30c/include" -I"D:/PROGRA~1/MATLAB/R2010b/simulink/include" -I"D:/PROGRA~1/MATLAB/R2010b/extern/include" -I"D:/PROGRA~1/MATLAB/R2010b/rtw/c/src" -I"D:/PROGRA~1/MATLAB/R2010b/rtw/c/ert" -I"D:/PROGRA~1/MATLAB/R2010b/rtw/c/src/ext_mode/common" -I"D:/PROGRA~1/MATLAB/R2010b/rtw/c/src/ext_mode/custom" -I"D:/PROGRA~1/MATLAB/R2010b/rtw/c/src" -I"D:/PROGRA~1/MATLAB/R2010b/simulink/src" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/sources/CanTestForBd1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/sources/CanTestForBd1_main.o: sources/CanTestForBd1_main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/CanTestForBd1_main.o.d 
	@${RM} ${OBJECTDIR}/sources/CanTestForBd1_main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sources/CanTestForBd1_main.c  -o ${OBJECTDIR}/sources/CanTestForBd1_main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sources/CanTestForBd1_main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"sources" -I"." -I"E:/Program/Mplab/ForTestS/Test_Canbus/CanTestForBd1" -I"C:/PROGRA~1/MICROC~1/mplabc30/v3.30c/include" -I"D:/PROGRA~1/MATLAB/R2010b/simulink/include" -I"D:/PROGRA~1/MATLAB/R2010b/extern/include" -I"D:/PROGRA~1/MATLAB/R2010b/rtw/c/src" -I"D:/PROGRA~1/MATLAB/R2010b/rtw/c/ert" -I"D:/PROGRA~1/MATLAB/R2010b/rtw/c/src/ext_mode/common" -I"D:/PROGRA~1/MATLAB/R2010b/rtw/c/src/ext_mode/custom" -I"D:/PROGRA~1/MATLAB/R2010b/rtw/c/src" -I"D:/PROGRA~1/MATLAB/R2010b/simulink/src" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/sources/CanTestForBd1_main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/sources/ecan1.o: sources/ecan1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/ecan1.o.d 
	@${RM} ${OBJECTDIR}/sources/ecan1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sources/ecan1.c  -o ${OBJECTDIR}/sources/ecan1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sources/ecan1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"sources" -I"." -I"E:/Program/Mplab/ForTestS/Test_Canbus/CanTestForBd1" -I"C:/PROGRA~1/MICROC~1/mplabc30/v3.30c/include" -I"D:/PROGRA~1/MATLAB/R2010b/simulink/include" -I"D:/PROGRA~1/MATLAB/R2010b/extern/include" -I"D:/PROGRA~1/MATLAB/R2010b/rtw/c/src" -I"D:/PROGRA~1/MATLAB/R2010b/rtw/c/ert" -I"D:/PROGRA~1/MATLAB/R2010b/rtw/c/src/ext_mode/common" -I"D:/PROGRA~1/MATLAB/R2010b/rtw/c/src/ext_mode/custom" -I"D:/PROGRA~1/MATLAB/R2010b/rtw/c/src" -I"D:/PROGRA~1/MATLAB/R2010b/simulink/src" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/sources/ecan1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/sources/CanTestForBd1.o: sources/CanTestForBd1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/CanTestForBd1.o.d 
	@${RM} ${OBJECTDIR}/sources/CanTestForBd1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sources/CanTestForBd1.c  -o ${OBJECTDIR}/sources/CanTestForBd1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sources/CanTestForBd1.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"sources" -I"." -I"E:/Program/Mplab/ForTestS/Test_Canbus/CanTestForBd1" -I"C:/PROGRA~1/MICROC~1/mplabc30/v3.30c/include" -I"D:/PROGRA~1/MATLAB/R2010b/simulink/include" -I"D:/PROGRA~1/MATLAB/R2010b/extern/include" -I"D:/PROGRA~1/MATLAB/R2010b/rtw/c/src" -I"D:/PROGRA~1/MATLAB/R2010b/rtw/c/ert" -I"D:/PROGRA~1/MATLAB/R2010b/rtw/c/src/ext_mode/common" -I"D:/PROGRA~1/MATLAB/R2010b/rtw/c/src/ext_mode/custom" -I"D:/PROGRA~1/MATLAB/R2010b/rtw/c/src" -I"D:/PROGRA~1/MATLAB/R2010b/simulink/src" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/sources/CanTestForBd1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/sources/CanTestForBd1_main.o: sources/CanTestForBd1_main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/CanTestForBd1_main.o.d 
	@${RM} ${OBJECTDIR}/sources/CanTestForBd1_main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sources/CanTestForBd1_main.c  -o ${OBJECTDIR}/sources/CanTestForBd1_main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sources/CanTestForBd1_main.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"sources" -I"." -I"E:/Program/Mplab/ForTestS/Test_Canbus/CanTestForBd1" -I"C:/PROGRA~1/MICROC~1/mplabc30/v3.30c/include" -I"D:/PROGRA~1/MATLAB/R2010b/simulink/include" -I"D:/PROGRA~1/MATLAB/R2010b/extern/include" -I"D:/PROGRA~1/MATLAB/R2010b/rtw/c/src" -I"D:/PROGRA~1/MATLAB/R2010b/rtw/c/ert" -I"D:/PROGRA~1/MATLAB/R2010b/rtw/c/src/ext_mode/common" -I"D:/PROGRA~1/MATLAB/R2010b/rtw/c/src/ext_mode/custom" -I"D:/PROGRA~1/MATLAB/R2010b/rtw/c/src" -I"D:/PROGRA~1/MATLAB/R2010b/simulink/src" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/sources/CanTestForBd1_main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/sources/ecan1.o: sources/ecan1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/ecan1.o.d 
	@${RM} ${OBJECTDIR}/sources/ecan1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sources/ecan1.c  -o ${OBJECTDIR}/sources/ecan1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sources/ecan1.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"sources" -I"." -I"E:/Program/Mplab/ForTestS/Test_Canbus/CanTestForBd1" -I"C:/PROGRA~1/MICROC~1/mplabc30/v3.30c/include" -I"D:/PROGRA~1/MATLAB/R2010b/simulink/include" -I"D:/PROGRA~1/MATLAB/R2010b/extern/include" -I"D:/PROGRA~1/MATLAB/R2010b/rtw/c/src" -I"D:/PROGRA~1/MATLAB/R2010b/rtw/c/ert" -I"D:/PROGRA~1/MATLAB/R2010b/rtw/c/src/ext_mode/common" -I"D:/PROGRA~1/MATLAB/R2010b/rtw/c/src/ext_mode/custom" -I"D:/PROGRA~1/MATLAB/R2010b/rtw/c/src" -I"D:/PROGRA~1/MATLAB/R2010b/simulink/src" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/sources/ecan1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Head.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Head.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--library-path="sources",--library-path=".",--library-path="E:/Program/Mplab/ForTestS/Test_Canbus/CanTestForBd1",--library-path="C:/PROGRA~1/MICROC~1/mplabc30/v3.30c/include",--library-path="D:/PROGRA~1/MATLAB/R2010b/simulink/include",--library-path="D:/PROGRA~1/MATLAB/R2010b/extern/include",--library-path="D:/PROGRA~1/MATLAB/R2010b/rtw/c/src",--library-path="D:/PROGRA~1/MATLAB/R2010b/rtw/c/ert",--library-path="D:/PROGRA~1/MATLAB/R2010b/rtw/c/src/ext_mode/common",--library-path="D:/PROGRA~1/MATLAB/R2010b/rtw/c/src/ext_mode/custom",--library-path="D:/PROGRA~1/MATLAB/R2010b/rtw/c/src",--library-path="D:/PROGRA~1/MATLAB/R2010b/simulink/src",--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Head.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Head.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--library-path="sources",--library-path=".",--library-path="E:/Program/Mplab/ForTestS/Test_Canbus/CanTestForBd1",--library-path="C:/PROGRA~1/MICROC~1/mplabc30/v3.30c/include",--library-path="D:/PROGRA~1/MATLAB/R2010b/simulink/include",--library-path="D:/PROGRA~1/MATLAB/R2010b/extern/include",--library-path="D:/PROGRA~1/MATLAB/R2010b/rtw/c/src",--library-path="D:/PROGRA~1/MATLAB/R2010b/rtw/c/ert",--library-path="D:/PROGRA~1/MATLAB/R2010b/rtw/c/src/ext_mode/common",--library-path="D:/PROGRA~1/MATLAB/R2010b/rtw/c/src/ext_mode/custom",--library-path="D:/PROGRA~1/MATLAB/R2010b/rtw/c/src",--library-path="D:/PROGRA~1/MATLAB/R2010b/simulink/src",--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Head.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
