# Microsoft Developer Studio Project File - Name="ucos_vc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=ucos_vc - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ucos_vc.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ucos_vc.mak" CFG="ucos_vc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ucos_vc - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "ucos_vc - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ucos_vc - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib winmm.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "ucos_vc - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "OUTPUT/Debug"
# PROP Intermediate_Dir "OUTPUT/Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /ML /W3 /Gm /GX /ZI /I "UCOS/CPU" /I "UCOS/SOURCE" /I "USER" /I "UCOS/CONFIG" /I "FS/API" /I "FS/CLIB" /I "FS/CONFIG/WIN32" /I "FS/DEVICE/RAM" /I "FS/FSL/FAT" /I "FS/LBL" /I "FS/OS" /I "UCOS/shell" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /I /GZ "user" /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib winmm.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ucos_vc - Win32 Release"
# Name "ucos_vc - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "UCOS"

# PROP Default_Filter ""
# Begin Group "cpu"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\UCOS\CPU\os_cpu.c
# End Source File
# Begin Source File

SOURCE=.\UCOS\CPU\OS_CPU.H
# End Source File
# End Group
# Begin Group "cfg"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\UCOS\Config\INCLUDES.H
# End Source File
# Begin Source File

SOURCE=.\UCOS\Config\OS_CFG.H
# End Source File
# End Group
# Begin Group "core"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\UCOS\SOURCE\os_core.c
# End Source File
# Begin Source File

SOURCE=.\UCOS\SOURCE\os_flag.c
# End Source File
# Begin Source File

SOURCE=.\UCOS\SOURCE\os_mbox.c
# End Source File
# Begin Source File

SOURCE=.\UCOS\SOURCE\os_mem.c
# End Source File
# Begin Source File

SOURCE=.\UCOS\SOURCE\os_mutex.c
# End Source File
# Begin Source File

SOURCE=.\UCOS\SOURCE\os_q.c
# End Source File
# Begin Source File

SOURCE=.\UCOS\SOURCE\os_sem.c
# End Source File
# Begin Source File

SOURCE=.\UCOS\SOURCE\os_task.c
# End Source File
# Begin Source File

SOURCE=.\UCOS\SOURCE\os_time.c
# End Source File
# Begin Source File

SOURCE=.\UCOS\SOURCE\os_tmr.c
# End Source File
# Begin Source File

SOURCE=.\UCOS\SOURCE\uCOS_II.H
# End Source File
# End Group
# End Group
# Begin Group "user"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\user\user.c
# End Source File
# Begin Source File

SOURCE=.\user\user.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\main.c
# End Source File
# End Group
# End Target
# End Project
