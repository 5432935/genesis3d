; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CRfvfsDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "rfvfs.h"

ClassCount=6
Class1=CRfvfsApp
Class2=CRfvfsDlg

ResourceCount=6
Resource2=IDD_RENAME_DIALOG
Resource1=IDR_MAINFRAME
Class3=CRename
Resource3=IDD_MAKEDIR_DIALOG
Class4=CDelete
Resource4=IDD_DELETE_DIALOG
Class5=CMakeDir
Resource5=IDD_RFVFS_DIALOG
Class6=CEncryptKey
Resource6=IDD_ENCRYPTKEY_DIALOG

[CLS:CRfvfsApp]
Type=0
HeaderFile=rfvfs.h
ImplementationFile=rfvfs.cpp
Filter=N

[CLS:CRfvfsDlg]
Type=0
HeaderFile=rfvfsDlg.h
ImplementationFile=rfvfsDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CRfvfsDlg



[DLG:IDD_RFVFS_DIALOG]
Type=1
Class=CRfvfsDlg
ControlCount=10
Control1=IDC_TREE1,SysTreeView32,1350631431
Control2=IDC_BUTTON1,button,1342242816
Control3=IDC_BUTTON2,button,1342242816
Control4=IDC_BUTTON3,button,1342242816
Control5=IDC_BUTTON4,button,1342242816
Control6=IDC_BUTTON5,button,1342242816
Control7=IDC_BUTTON6,button,1342242816
Control8=IDC_BUTTON7,button,1342242816
Control9=IDC_BUTTON8,button,1342242816
Control10=IDC_CHECK1,button,1342242819

[DLG:IDD_RENAME_DIALOG]
Type=1
Class=CRename
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT2,edit,1342244992
Control6=IDC_STATIC,button,1342177287

[CLS:CRename]
Type=0
HeaderFile=Rename.h
ImplementationFile=Rename.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CRename

[DLG:IDD_DELETE_DIALOG]
Type=1
Class=CDelete
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1342244992
Control5=IDC_STATIC,button,1342177287

[CLS:CDelete]
Type=0
HeaderFile=Delete.h
ImplementationFile=Delete.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT1

[DLG:IDD_MAKEDIR_DIALOG]
Type=1
Class=CMakeDir
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_EDIT2,edit,1342244992
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,button,1342177287

[CLS:CMakeDir]
Type=0
HeaderFile=MakeDir.h
ImplementationFile=MakeDir.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CMakeDir

[DLG:IDD_ENCRYPTKEY_DIALOG]
Type=1
Class=CEncryptKey
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_STATIC,static,1342308352

[CLS:CEncryptKey]
Type=0
HeaderFile=EncryptKey.h
ImplementationFile=EncryptKey.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CEncryptKey

