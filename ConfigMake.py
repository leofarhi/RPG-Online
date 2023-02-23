#make UI for configuring make
import os, sys
from tkinter import *
from tkinter import ttk
from tkinter import messagebox
from tkinter import filedialog
from tkinter import scrolledtext
from tkinter import Menu
import json
#subprocess
import subprocess

Make = Tk()
Make.title("Configure Make")
Make.geometry("400x400")
#Make.resizable(0,0)

#make DropDownMenu with buttons DS, 3DS, WII, ...
DropDownMenu = ttk.Combobox(Make, state="readonly")
#pack on top and fill x
DropDownMenu.pack(side=TOP, fill=X)
DropDownMenu["values"] = ("Windows","Linux","DS", "3DS", "WII", "Switch", "PSP", "Casio Graph90", "Casio Graph35+")
DropDownMenu.current(0)


#make MainFrame
MainFrame = Frame(Make)
MainFrame.pack(side=TOP, fill=BOTH, expand=1)

AppNameString = StringVar()
AppVersionString = StringVar()
AppAuthorString = StringVar()


class Distribution:
    def __init__(self, MainFrame,name):
        self.name = name
        self.notebook = ttk.Notebook(MainFrame)
        self.notebook.pack(side=TOP, fill=BOTH, expand=1)
       
        self.addGeneral()
        #self.addTextures()
        #self.addFonts()
        #self.addAudio()
        self.addMake()

    def addGeneral(self):
        self.TabGeneral = ttk.Frame(self.notebook)
        self.TabGeneral.pack(side=TOP, fill=BOTH, expand=1)
        self.notebook.add(self.TabGeneral, text="General")
        #text fields for AppName, AppVersion, AppAuthor
        self.AppName = Label(self.TabGeneral, text="App Name")
        self.AppName.pack(side=TOP, fill=X)
        self.AppNameString = AppNameString
        self.AppNameEntry = Entry(self.TabGeneral, textvariable=self.AppNameString)
        self.AppNameEntry.pack(side=TOP, fill=X)

        self.AppVersion = Label(self.TabGeneral, text="App Version")
        self.AppVersion.pack(side=TOP, fill=X)
        self.AppVersionString = AppVersionString
        self.AppVersionEntry = Entry(self.TabGeneral, textvariable=self.AppVersionString)
        self.AppVersionEntry.pack(side=TOP, fill=X)

        self.AppAuthor = Label(self.TabGeneral, text="App Author")
        self.AppAuthor.pack(side=TOP, fill=X)
        self.AppAuthorString = AppAuthorString
        self.AppAuthorEntry = Entry(self.TabGeneral, textvariable=self.AppAuthorString)
        self.AppAuthorEntry.pack(side=TOP, fill=X)     

    def addTextures(self):
        pass

    def addFonts(self):
        pass

    def addAudio(self):
        pass

    def addMake(self):
        self.TabMake = ttk.Frame(self.notebook)
        self.TabMake.pack(side=TOP, fill=BOTH, expand=1)
        self.notebook.add(self.TabMake, text="Make")
        #make fields for cmd to make, cmd to clean, cmd to run
        self.MakeCmd = Label(self.TabMake, text="Make Command")
        self.MakeCmd.pack(side=TOP, fill=X)
        self.MakeCmdString = StringVar()
        self.MakeCmdEntry = Entry(self.TabMake, textvariable=self.MakeCmdString)
        self.MakeCmdEntry.pack(side=TOP, fill=X)

        self.CleanCmd = Label(self.TabMake, text="Clean Command")
        self.CleanCmd.pack(side=TOP, fill=X)
        self.CleanCmdString = StringVar()
        self.CleanCmdEntry = Entry(self.TabMake, textvariable=self.CleanCmdString)
        self.CleanCmdEntry.pack(side=TOP, fill=X)

        self.RunCmd = Label(self.TabMake, text="Run Command")
        self.RunCmd.pack(side=TOP, fill=X)
        self.RunCmdString = StringVar()
        self.RunCmdEntry = Entry(self.TabMake, textvariable=self.RunCmdString)
        self.RunCmdEntry.pack(side=TOP, fill=X)

    def get(self):
        return {
            "AppName": self.AppNameString.get(),
            "AppVersion": self.AppVersionString.get(),
            "AppAuthor": self.AppAuthorString.get(),
            "MakeCmd": self.MakeCmdString.get(),
            "CleanCmd": self.CleanCmdString.get(),
            "RunCmd": self.RunCmdString.get()
        }

    def set(self, data):
        self.AppNameString.set(data["AppName"])
        self.AppVersionString.set(data["AppVersion"])
        self.AppAuthorString.set(data["AppAuthor"])
        self.MakeCmdString.set(data["MakeCmd"])
        self.CleanCmdString.set(data["CleanCmd"])
        self.RunCmdString.set(data["RunCmd"])

    def show(self):
        self.notebook.pack(side=TOP, fill=BOTH, expand=1)

    def hide(self):
        self.notebook.pack_forget()

    def ReplaceVars(self, cmd):
        cmd = cmd.replace("$(AppName)", self.AppNameString.get())
        cmd = cmd.replace("$(AppVersion)", self.AppVersionString.get())
        cmd = cmd.replace("$(AppAuthor)", self.AppAuthorString.get())
        return cmd

    def ReplaceVarsInFile(self, filename, varName, line):
        #add line in file between #/*<VAR>*/ and #/*</VAR>*/ with varName
        Text = ""
        with open(filename, "r") as f:
            Text = f.read()
        #find start and end of var
        start = Text.find("#/*<" + varName + ">*/")
        end = Text.find("#/*</" + varName + ">*/")
        LEN = len("#/*<" + varName + ">*/")
        if start == -1 or end == -1:
            start = Text.find("//*<" + varName + ">*/")
            end = Text.find("//*</" + varName + ">*/")
        if start == -1 or end == -1:
            print("Error: could not find var " + varName + " in " + filename)
            return
        #add line to text but dont remove start and end
        Text = Text[:start + LEN] + line + Text[end:]
        #write text to file
        with open(filename, "w") as f:
            f.write(Text)

    def Make(self):
        cmdString = self.ReplaceVars(self.MakeCmdString.get())
        print("Running: " + cmdString)
        os.system(cmdString)

    def Clean(self):
        cmdString = self.ReplaceVars(self.CleanCmdString.get())
        print("Running: " + cmdString)
        os.system(cmdString)

    def Run(self):
        cmdString = self.ReplaceVars(self.RunCmdString.get())
        print("Running: " + cmdString)
        os.system(cmdString)

class CasioDistribution(Distribution):
    def __init__(self, MainFrame, name):
        super().__init__(MainFrame, name)

    def addMake(self):
        self.TabMake = ttk.Frame(self.notebook)
        self.TabMake.pack(side=TOP, fill=BOTH, expand=1)
        self.notebook.add(self.TabMake, text="Make")
        #make fields for src folder and make fields
        self.SrcFolder = Label(self.TabMake, text="Source Folder")
        self.SrcFolder.pack(side=TOP, fill=X)
        self.SrcFolderString = StringVar()
        self.SrcFolderEntry = Entry(self.TabMake, textvariable=self.SrcFolderString)
        self.SrcFolderEntry.pack(side=TOP, fill=X)

        self.MakeCmd = Label(self.TabMake, text="Make Command")
        self.MakeCmd.pack(side=TOP, fill=X)
        self.MakeCmdString = StringVar()
        self.MakeCmdEntry = Entry(self.TabMake, textvariable=self.MakeCmdString)
        self.MakeCmdEntry.pack(side=TOP, fill=X)

    def Run(self):
        #remove run button
        pass

    def get(self):
        return {
            "AppName": self.AppNameString.get(),
            "AppVersion": self.AppVersionString.get(),
            "AppAuthor": self.AppAuthorString.get(),
            "SrcFolder": self.SrcFolderString.get(),
            "MakeCmd": self.MakeCmdString.get()
        }
    
    def set(self, data):
        self.AppNameString.set(data["AppName"])
        self.AppVersionString.set(data["AppVersion"])
        self.AppAuthorString.set(data["AppAuthor"])
        self.SrcFolderString.set(data["SrcFolder"])
        self.MakeCmdString.set(data["MakeCmd"])

    def Make(self):
        #find all files in SrcFolder .h and .c and .hpp and .cpp
        srcList = []
        srcFolder = self.SrcFolderString.get()
        for root, dirs, files in os.walk(srcFolder):
            for file in files:
                if file.endswith(".h") or file.endswith(".c") or file.endswith(".hpp") or file.endswith(".cpp"):
                    srcList.append(os.path.join(root, file))
                    #change \\ to /
                    srcList[-1] = srcList[-1].replace("\\", "/")
        print(srcList)
        textSrc = "\n"
        for i in range(0, len(srcList)):
            textSrc += "    " + srcList[i] + "\n"
        #replace vars in makefile
        self.ReplaceVarsInFile("CMakeLists.txt", "SRC", textSrc)
        textAppName = '\nset(NAME_APP "' + self.AppNameString.get() + '")\n'
        self.ReplaceVarsInFile("CMakeLists.txt", "NAME_APP_FIELD", textAppName)
        textDirOut = '\nset(DIR_OUT "bin")\n'
        self.ReplaceVarsInFile("CMakeLists.txt", "DIR_OUT_FIELD", textDirOut)
        #ParticuleEngine

        #run make
        cmdString = self.ReplaceVars(self.MakeCmdString.get())
        os.system(cmdString)



    def Clean(self):
        os.system("make clean")

DictSpecialDistributions = {
    "Casio Graph90": CasioDistribution,
    "Casio Graph35+": CasioDistribution
}

#make Distribution objects
Distribs = []
for i in range(0, len(DropDownMenu["values"])):
    if DropDownMenu["values"][i] in DictSpecialDistributions:
        Distribs.append(DictSpecialDistributions[DropDownMenu["values"][i]](MainFrame, DropDownMenu["values"][i]))
    else:
        Distribs.append(Distribution(MainFrame, DropDownMenu["values"][i]))

#make function for when DropDownMenu changes
def changeDistribs(*args):
    for i in range(0, len(Distribs)):
        if DropDownMenu.get() == Distribs[i].name:
            Distribs[i].show()
        else:
            Distribs[i].hide()

#set first tab to be shown and hide the rest
Distribs[0].show()
for i in range(1, len(Distribs)):
    Distribs[i].hide()

#bind DropDownMenu to changeDistribs
DropDownMenu.bind("<<ComboboxSelected>>", changeDistribs)

def ReplaceVars(string, data):
    string = string.replace("$(AppName)", data["AppName"])
    string = string.replace("$(AppVersion)", data["AppVersion"])
    string = string.replace("$(AppAuthor)", data["AppAuthor"])
    return string

#make function for when MakeButton is pressed
def make(event, *args):
    print("Make")
    #get distribution currently selected
    Dist = Distribs[DropDownMenu.current()]
    print(Dist.name)
    Dist.Make()

def clean(event, *args):
    print("Clean")
    #get distribution currently selected
    Dist = Distribs[DropDownMenu.current()]
    print(Dist.name)
    Dist.Clean()

def run(event, *args):
    print("Run")
    #get distribution currently selected
    Dist = Distribs[DropDownMenu.current()]
    print(Dist.name)
    Dist.Run()


#make buttons for make, clean, run on bottom
MakeButton = Button(Make, text="Make")
MakeButton.pack(side=BOTTOM, fill=X)
#bind MakeButton to make
MakeButton.bind("<Button-1>", make)

CleanButton = Button(Make, text="Clean")
CleanButton.pack(side=BOTTOM, fill=X)
#bind CleanButton to clean
CleanButton.bind("<Button-1>", clean)

RunButton = Button(Make, text="Run")
RunButton.pack(side=BOTTOM, fill=X)
#bind RunButton to run
RunButton.bind("<Button-1>", run)

def SaveConfig(*args):
    print("Save Config")
    Datas = []
    for i in range(0, len(Distribs)):
        Datas.append(Distribs[i].get())
    with open("config.json", "w") as f:
        json.dump(Datas, f)

def LoadConfig(*args):
    print("Load Config")
    if os.path.isfile("config.json"):
        with open("config.json", "r") as f:
            Datas = json.load(f)
        for i in range(0, len(Distribs)):
            Distribs[i].set(Datas[i])

def WhenCloseMain(*args):
    #if messagebox.askokcancel("Quit", "Do you want to quit?"):
    SaveConfig()
    Make.destroy() 

LoadConfig()
Make.protocol("WM_DELETE_WINDOW", WhenCloseMain)
Make.mainloop()

