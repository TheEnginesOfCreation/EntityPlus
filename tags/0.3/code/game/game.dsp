# Microsoft Developer Studio Project File - Name="game" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102
# TARGTYPE "Win32 (ALPHA) Dynamic-Link Library" 0x0602

CFG=game - Win32 Debug TA
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "game.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "game.mak" CFG="game - Win32 Debug TA"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "game - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "game - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "game - Win32 Debug Alpha" (based on "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "game - Win32 Release Alpha" (based on "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "game - Win32 Release TA" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "game - Win32 Debug TA" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/MissionPack/code/game", CYAAAAAA"
# PROP Scc_LocalPath "."

!IF  "$(CFG)" == "game - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir "."
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir "."
CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /G6 /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "GLOBALRANK" /YX /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib winmm.lib /nologo /base:"0x20000000" /subsystem:windows /dll /map /machine:I386 /out:"../Release/qagamex86.dll"
# SUBTRACT LINK32 /incremental:yes /debug

!ELSEIF  "$(CFG)" == "game - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir "."
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir "."
CPP=cl.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /G5 /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "BUILDING_REF_GL" /D "DEBUG" /D "GLOBALRANK" /FR /YX /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib winmm.lib /nologo /base:"0x20000000" /subsystem:windows /dll /map /debug /machine:I386 /out:"../Debug/qagamex86.dll"
# SUBTRACT LINK32 /incremental:no

!ELSEIF  "$(CFG)" == "game - Win32 Debug Alpha"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug Alpha"
# PROP BASE Intermediate_Dir "Debug Alpha"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\DebugAxp"
# PROP Intermediate_Dir ".\DebugAxp"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /MTd /c
# ADD CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "C_ONLY" /YX /FD /QA21164 /MTd /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /base:"0x20000000" /subsystem:windows /dll /debug /machine:ALPHA
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib winmm.lib /nologo /base:"0x20000000" /subsystem:windows /dll /debug /machine:ALPHA /out:"..\DebugAxp/qagameaxp.dll"

!ELSEIF  "$(CFG)" == "game - Win32 Release Alpha"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "game___W"
# PROP BASE Intermediate_Dir "game___W"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\ReleaseAXP"
# PROP Intermediate_Dir ".\ReleaseAXP"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MT /Gt0 /W3 /GX /Zd /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /Gt0 /W3 /GX /Zd /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "C_ONLY" /YX /FD /QA21164 /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /base:"0x20000000" /subsystem:windows /dll /machine:ALPHA /out:"..\Release/gamex86.dll"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winmm.lib /nologo /base:"0x20000000" /subsystem:windows /dll /machine:ALPHA /out:"..\ReleaseAXP/qagameaxp.dll"

!ELSEIF  "$(CFG)" == "game - Win32 Release TA"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "game___Win32_Release_TA"
# PROP BASE Intermediate_Dir "game___Win32_Release_TA"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release_TA"
# PROP Intermediate_Dir "Release_TA"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /G6 /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /G6 /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "MISSIONPACK" /YX /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib winmm.lib /nologo /base:"0x20000000" /subsystem:windows /dll /map /machine:I386 /out:"..\Release/qagamex86.dll"
# SUBTRACT BASE LINK32 /incremental:yes /debug
# ADD LINK32 kernel32.lib user32.lib winmm.lib /nologo /base:"0x20000000" /subsystem:windows /dll /map /machine:I386 /def:".\game.def" /out:"../Release_TA/qagamex86.dll"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "game - Win32 Debug TA"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "game___Win32_Debug_TA"
# PROP BASE Intermediate_Dir "game___Win32_Debug_TA"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug_TA"
# PROP Intermediate_Dir "Debug_TA"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /G5 /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "BUILDING_REF_GL" /D "DEBUG" /FR /YX /FD /c
# ADD CPP /nologo /G5 /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "BUILDING_REF_GL" /D "DEBUG" /D "MISSIONPACK" /D "QAGAME" /FR /YX /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib winmm.lib /nologo /base:"0x20000000" /subsystem:windows /dll /map /debug /machine:I386 /out:"..\Debug/qagamex86.dll"
# SUBTRACT BASE LINK32 /incremental:no
# ADD LINK32 kernel32.lib user32.lib winmm.lib /nologo /base:"0x20000000" /subsystem:windows /dll /map /debug /machine:I386 /def:".\game.def" /out:"..\Debug_TA\qagamex86.dll"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "game - Win32 Release"
# Name "game - Win32 Debug"
# Name "game - Win32 Debug Alpha"
# Name "game - Win32 Release Alpha"
# Name "game - Win32 Release TA"
# Name "game - Win32 Debug TA"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\ai_chat.c

!IF  "$(CFG)" == "game - Win32 Release"

!ELSEIF  "$(CFG)" == "game - Win32 Debug"

!ELSEIF  "$(CFG)" == "game - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release TA"

!ELSEIF  "$(CFG)" == "game - Win32 Debug TA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ai_cmd.c

!IF  "$(CFG)" == "game - Win32 Release"

!ELSEIF  "$(CFG)" == "game - Win32 Debug"

!ELSEIF  "$(CFG)" == "game - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release TA"

!ELSEIF  "$(CFG)" == "game - Win32 Debug TA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ai_dmnet.c

!IF  "$(CFG)" == "game - Win32 Release"

!ELSEIF  "$(CFG)" == "game - Win32 Debug"

!ELSEIF  "$(CFG)" == "game - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release TA"

!ELSEIF  "$(CFG)" == "game - Win32 Debug TA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ai_dmq3.c

!IF  "$(CFG)" == "game - Win32 Release"

!ELSEIF  "$(CFG)" == "game - Win32 Debug"

!ELSEIF  "$(CFG)" == "game - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release TA"

!ELSEIF  "$(CFG)" == "game - Win32 Debug TA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ai_main.c

!IF  "$(CFG)" == "game - Win32 Release"

!ELSEIF  "$(CFG)" == "game - Win32 Debug"

!ELSEIF  "$(CFG)" == "game - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release TA"

!ELSEIF  "$(CFG)" == "game - Win32 Debug TA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ai_team.c

!IF  "$(CFG)" == "game - Win32 Release"

!ELSEIF  "$(CFG)" == "game - Win32 Debug"

!ELSEIF  "$(CFG)" == "game - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release TA"

!ELSEIF  "$(CFG)" == "game - Win32 Debug TA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ai_vcmd.c

!IF  "$(CFG)" == "game - Win32 Release"

!ELSEIF  "$(CFG)" == "game - Win32 Debug"

!ELSEIF  "$(CFG)" == "game - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release TA"

!ELSEIF  "$(CFG)" == "game - Win32 Debug TA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\bg_lib.c

!IF  "$(CFG)" == "game - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "game - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "game - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release TA"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "game - Win32 Debug TA"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\bg_misc.c

!IF  "$(CFG)" == "game - Win32 Release"

!ELSEIF  "$(CFG)" == "game - Win32 Debug"

!ELSEIF  "$(CFG)" == "game - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release TA"

!ELSEIF  "$(CFG)" == "game - Win32 Debug TA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\bg_pmove.c

!IF  "$(CFG)" == "game - Win32 Release"

!ELSEIF  "$(CFG)" == "game - Win32 Debug"

!ELSEIF  "$(CFG)" == "game - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release TA"

!ELSEIF  "$(CFG)" == "game - Win32 Debug TA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\bg_slidemove.c

!IF  "$(CFG)" == "game - Win32 Release"

!ELSEIF  "$(CFG)" == "game - Win32 Debug"

!ELSEIF  "$(CFG)" == "game - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release TA"

!ELSEIF  "$(CFG)" == "game - Win32 Debug TA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\g_active.c

!IF  "$(CFG)" == "game - Win32 Release"

!ELSEIF  "$(CFG)" == "game - Win32 Debug"

!ELSEIF  "$(CFG)" == "game - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release TA"

!ELSEIF  "$(CFG)" == "game - Win32 Debug TA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\g_arenas.c

!IF  "$(CFG)" == "game - Win32 Release"

!ELSEIF  "$(CFG)" == "game - Win32 Debug"

!ELSEIF  "$(CFG)" == "game - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release TA"

!ELSEIF  "$(CFG)" == "game - Win32 Debug TA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\g_bot.c

!IF  "$(CFG)" == "game - Win32 Release"

!ELSEIF  "$(CFG)" == "game - Win32 Debug"

!ELSEIF  "$(CFG)" == "game - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release TA"

!ELSEIF  "$(CFG)" == "game - Win32 Debug TA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\g_client.c

!IF  "$(CFG)" == "game - Win32 Release"

!ELSEIF  "$(CFG)" == "game - Win32 Debug"

!ELSEIF  "$(CFG)" == "game - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release TA"

!ELSEIF  "$(CFG)" == "game - Win32 Debug TA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\g_cmds.c

!IF  "$(CFG)" == "game - Win32 Release"

!ELSEIF  "$(CFG)" == "game - Win32 Debug"

!ELSEIF  "$(CFG)" == "game - Win32 Debug Alpha"

NODEP_CPP_G_CMD=\
	".\bot.h"\
	".\g_local.h"\
	".\game.h"\
	".\m_player.h"\
	".\q_shared.h"\
	

!ELSEIF  "$(CFG)" == "game - Win32 Release Alpha"

NODEP_CPP_G_CMD=\
	".\bot.h"\
	".\g_local.h"\
	".\game.h"\
	".\m_player.h"\
	".\q_shared.h"\
	

!ELSEIF  "$(CFG)" == "game - Win32 Release TA"

!ELSEIF  "$(CFG)" == "game - Win32 Debug TA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\g_combat.c

!IF  "$(CFG)" == "game - Win32 Release"

!ELSEIF  "$(CFG)" == "game - Win32 Debug"

!ELSEIF  "$(CFG)" == "game - Win32 Debug Alpha"

NODEP_CPP_G_COM=\
	".\bot.h"\
	".\g_local.h"\
	".\game.h"\
	".\q_shared.h"\
	

!ELSEIF  "$(CFG)" == "game - Win32 Release Alpha"

NODEP_CPP_G_COM=\
	".\bot.h"\
	".\g_local.h"\
	".\game.h"\
	".\q_shared.h"\
	

!ELSEIF  "$(CFG)" == "game - Win32 Release TA"

!ELSEIF  "$(CFG)" == "game - Win32 Debug TA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\g_items.c

!IF  "$(CFG)" == "game - Win32 Release"

!ELSEIF  "$(CFG)" == "game - Win32 Debug"

!ELSEIF  "$(CFG)" == "game - Win32 Debug Alpha"

NODEP_CPP_G_ITE=\
	".\bot.h"\
	".\g_local.h"\
	".\game.h"\
	".\q_shared.h"\
	

!ELSEIF  "$(CFG)" == "game - Win32 Release Alpha"

NODEP_CPP_G_ITE=\
	".\bot.h"\
	".\g_local.h"\
	".\game.h"\
	".\q_shared.h"\
	

!ELSEIF  "$(CFG)" == "game - Win32 Release TA"

!ELSEIF  "$(CFG)" == "game - Win32 Debug TA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\g_main.c

!IF  "$(CFG)" == "game - Win32 Release"

!ELSEIF  "$(CFG)" == "game - Win32 Debug"

!ELSEIF  "$(CFG)" == "game - Win32 Debug Alpha"

NODEP_CPP_G_MAI=\
	".\bot.h"\
	".\g_local.h"\
	".\game.h"\
	".\q_shared.h"\
	

!ELSEIF  "$(CFG)" == "game - Win32 Release Alpha"

NODEP_CPP_G_MAI=\
	".\bot.h"\
	".\g_local.h"\
	".\game.h"\
	".\q_shared.h"\
	

!ELSEIF  "$(CFG)" == "game - Win32 Release TA"

!ELSEIF  "$(CFG)" == "game - Win32 Debug TA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\g_mem.c

!IF  "$(CFG)" == "game - Win32 Release"

!ELSEIF  "$(CFG)" == "game - Win32 Debug"

!ELSEIF  "$(CFG)" == "game - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release TA"

!ELSEIF  "$(CFG)" == "game - Win32 Debug TA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\g_misc.c

!IF  "$(CFG)" == "game - Win32 Release"

!ELSEIF  "$(CFG)" == "game - Win32 Debug"

!ELSEIF  "$(CFG)" == "game - Win32 Debug Alpha"

NODEP_CPP_G_MIS=\
	".\bot.h"\
	".\g_local.h"\
	".\game.h"\
	".\q_shared.h"\
	

!ELSEIF  "$(CFG)" == "game - Win32 Release Alpha"

NODEP_CPP_G_MIS=\
	".\bot.h"\
	".\g_local.h"\
	".\game.h"\
	".\q_shared.h"\
	

!ELSEIF  "$(CFG)" == "game - Win32 Release TA"

!ELSEIF  "$(CFG)" == "game - Win32 Debug TA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\g_missile.c

!IF  "$(CFG)" == "game - Win32 Release"

!ELSEIF  "$(CFG)" == "game - Win32 Debug"

!ELSEIF  "$(CFG)" == "game - Win32 Debug Alpha"

NODEP_CPP_G_MISS=\
	".\bot.h"\
	".\g_local.h"\
	".\game.h"\
	".\q_shared.h"\
	

!ELSEIF  "$(CFG)" == "game - Win32 Release Alpha"

NODEP_CPP_G_MISS=\
	".\bot.h"\
	".\g_local.h"\
	".\game.h"\
	".\q_shared.h"\
	

!ELSEIF  "$(CFG)" == "game - Win32 Release TA"

!ELSEIF  "$(CFG)" == "game - Win32 Debug TA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\g_mover.c

!IF  "$(CFG)" == "game - Win32 Release"

!ELSEIF  "$(CFG)" == "game - Win32 Debug"

!ELSEIF  "$(CFG)" == "game - Win32 Debug Alpha"

NODEP_CPP_G_MOV=\
	".\bot.h"\
	".\g_local.h"\
	".\game.h"\
	".\q_shared.h"\
	

!ELSEIF  "$(CFG)" == "game - Win32 Release Alpha"

NODEP_CPP_G_MOV=\
	".\bot.h"\
	".\g_local.h"\
	".\game.h"\
	".\q_shared.h"\
	

!ELSEIF  "$(CFG)" == "game - Win32 Release TA"

!ELSEIF  "$(CFG)" == "game - Win32 Debug TA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\g_session.c

!IF  "$(CFG)" == "game - Win32 Release"

!ELSEIF  "$(CFG)" == "game - Win32 Debug"

!ELSEIF  "$(CFG)" == "game - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release TA"

!ELSEIF  "$(CFG)" == "game - Win32 Debug TA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\g_spawn.c

!IF  "$(CFG)" == "game - Win32 Release"

!ELSEIF  "$(CFG)" == "game - Win32 Debug"

!ELSEIF  "$(CFG)" == "game - Win32 Debug Alpha"

NODEP_CPP_G_SPA=\
	".\bot.h"\
	".\g_local.h"\
	".\game.h"\
	".\q_shared.h"\
	

!ELSEIF  "$(CFG)" == "game - Win32 Release Alpha"

NODEP_CPP_G_SPA=\
	".\bot.h"\
	".\g_local.h"\
	".\game.h"\
	".\q_shared.h"\
	

!ELSEIF  "$(CFG)" == "game - Win32 Release TA"

!ELSEIF  "$(CFG)" == "game - Win32 Debug TA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\g_svcmds.c

!IF  "$(CFG)" == "game - Win32 Release"

!ELSEIF  "$(CFG)" == "game - Win32 Debug"

!ELSEIF  "$(CFG)" == "game - Win32 Debug Alpha"

NODEP_CPP_G_SVC=\
	".\bot.h"\
	".\g_local.h"\
	".\game.h"\
	".\q_shared.h"\
	

!ELSEIF  "$(CFG)" == "game - Win32 Release Alpha"

NODEP_CPP_G_SVC=\
	".\bot.h"\
	".\g_local.h"\
	".\game.h"\
	".\q_shared.h"\
	

!ELSEIF  "$(CFG)" == "game - Win32 Release TA"

!ELSEIF  "$(CFG)" == "game - Win32 Debug TA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\g_syscalls.c

!IF  "$(CFG)" == "game - Win32 Release"

!ELSEIF  "$(CFG)" == "game - Win32 Debug"

!ELSEIF  "$(CFG)" == "game - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release TA"

!ELSEIF  "$(CFG)" == "game - Win32 Debug TA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\g_target.c

!IF  "$(CFG)" == "game - Win32 Release"

!ELSEIF  "$(CFG)" == "game - Win32 Debug"

!ELSEIF  "$(CFG)" == "game - Win32 Debug Alpha"

NODEP_CPP_G_TAR=\
	".\bot.h"\
	".\g_local.h"\
	".\game.h"\
	".\q_shared.h"\
	

!ELSEIF  "$(CFG)" == "game - Win32 Release Alpha"

NODEP_CPP_G_TAR=\
	".\bot.h"\
	".\g_local.h"\
	".\game.h"\
	".\q_shared.h"\
	

!ELSEIF  "$(CFG)" == "game - Win32 Release TA"

!ELSEIF  "$(CFG)" == "game - Win32 Debug TA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\g_team.c

!IF  "$(CFG)" == "game - Win32 Release"

!ELSEIF  "$(CFG)" == "game - Win32 Debug"

!ELSEIF  "$(CFG)" == "game - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release TA"

!ELSEIF  "$(CFG)" == "game - Win32 Debug TA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\g_trigger.c

!IF  "$(CFG)" == "game - Win32 Release"

!ELSEIF  "$(CFG)" == "game - Win32 Debug"

!ELSEIF  "$(CFG)" == "game - Win32 Debug Alpha"

NODEP_CPP_G_TRI=\
	".\bot.h"\
	".\g_local.h"\
	".\game.h"\
	".\q_shared.h"\
	

!ELSEIF  "$(CFG)" == "game - Win32 Release Alpha"

NODEP_CPP_G_TRI=\
	".\bot.h"\
	".\g_local.h"\
	".\game.h"\
	".\q_shared.h"\
	

!ELSEIF  "$(CFG)" == "game - Win32 Release TA"

!ELSEIF  "$(CFG)" == "game - Win32 Debug TA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\g_utils.c

!IF  "$(CFG)" == "game - Win32 Release"

!ELSEIF  "$(CFG)" == "game - Win32 Debug"

!ELSEIF  "$(CFG)" == "game - Win32 Debug Alpha"

NODEP_CPP_G_UTI=\
	".\bot.h"\
	".\g_local.h"\
	".\game.h"\
	".\q_shared.h"\
	

!ELSEIF  "$(CFG)" == "game - Win32 Release Alpha"

NODEP_CPP_G_UTI=\
	".\bot.h"\
	".\g_local.h"\
	".\game.h"\
	".\q_shared.h"\
	

!ELSEIF  "$(CFG)" == "game - Win32 Release TA"

!ELSEIF  "$(CFG)" == "game - Win32 Debug TA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\g_weapon.c

!IF  "$(CFG)" == "game - Win32 Release"

!ELSEIF  "$(CFG)" == "game - Win32 Debug"

!ELSEIF  "$(CFG)" == "game - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release TA"

!ELSEIF  "$(CFG)" == "game - Win32 Debug TA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\game.def

!IF  "$(CFG)" == "game - Win32 Release"

!ELSEIF  "$(CFG)" == "game - Win32 Debug"

!ELSEIF  "$(CFG)" == "game - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release TA"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "game - Win32 Debug TA"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\q_math.c

!IF  "$(CFG)" == "game - Win32 Release"

!ELSEIF  "$(CFG)" == "game - Win32 Debug"

!ELSEIF  "$(CFG)" == "game - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release Alpha"

!ELSEIF  "$(CFG)" == "game - Win32 Release TA"

!ELSEIF  "$(CFG)" == "game - Win32 Debug TA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\q_shared.c

!IF  "$(CFG)" == "game - Win32 Release"

!ELSEIF  "$(CFG)" == "game - Win32 Debug"

!ELSEIF  "$(CFG)" == "game - Win32 Debug Alpha"

NODEP_CPP_Q_SHA=\
	"..\client\anorms.h"\
	".\q_shared.h"\
	

!ELSEIF  "$(CFG)" == "game - Win32 Release Alpha"

NODEP_CPP_Q_SHA=\
	"..\client\anorms.h"\
	".\q_shared.h"\
	

!ELSEIF  "$(CFG)" == "game - Win32 Release TA"

!ELSEIF  "$(CFG)" == "game - Win32 Debug TA"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\ai_chat.h
# End Source File
# Begin Source File

SOURCE=.\ai_cmd.h
# End Source File
# Begin Source File

SOURCE=.\ai_dmnet.h
# End Source File
# Begin Source File

SOURCE=.\ai_dmq3.h
# End Source File
# Begin Source File

SOURCE=.\ai_main.h
# End Source File
# Begin Source File

SOURCE=.\ai_team.h
# End Source File
# Begin Source File

SOURCE=.\ai_vcmd.h
# End Source File
# Begin Source File

SOURCE=.\be_aas.h
# End Source File
# Begin Source File

SOURCE=.\be_ai_char.h
# End Source File
# Begin Source File

SOURCE=.\be_ai_chat.h
# End Source File
# Begin Source File

SOURCE=.\be_ai_gen.h
# End Source File
# Begin Source File

SOURCE=.\be_ai_goal.h
# End Source File
# Begin Source File

SOURCE=.\be_ai_move.h
# End Source File
# Begin Source File

SOURCE=.\be_ai_weap.h
# End Source File
# Begin Source File

SOURCE=.\be_ea.h
# End Source File
# Begin Source File

SOURCE=.\bg_local.h
# End Source File
# Begin Source File

SOURCE=.\bg_public.h
# End Source File
# Begin Source File

SOURCE=.\botlib.h
# End Source File
# Begin Source File

SOURCE=.\chars.h
# End Source File
# Begin Source File

SOURCE=.\g_local.h
# End Source File
# Begin Source File

SOURCE=.\g_public.h
# End Source File
# Begin Source File

SOURCE=.\g_team.h
# End Source File
# Begin Source File

SOURCE=.\inv.h
# End Source File
# Begin Source File

SOURCE=.\match.h
# End Source File
# Begin Source File

SOURCE=.\q_shared.h
# End Source File
# Begin Source File

SOURCE=.\surfaceflags.h
# End Source File
# Begin Source File

SOURCE=.\syn.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
