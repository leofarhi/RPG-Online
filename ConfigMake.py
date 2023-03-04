#make UI for configuring make
import os, sys
from tkinter import *
from tkinter import ttk
from tkinter import messagebox
from tkinter import filedialog
from tkinter import scrolledtext
from tkinter import Menu
from tkinter import Spinbox
from tkinter import Checkbutton
import json
import shutil
import uuid
#subprocess
import subprocess
from PIL import Image

def GetTrueSizeImage(path):
    #les images sont remplis avec des pixels transparents a la fin
    #pour avoir la taille de l'image sans les pixels transparents
    #on ouvre l'image avec PIL et on recupere la taille de l'image
    #sans les pixels transparents
    img = Image.open(path)
    #detecter si l'image est en mode RGBA
    if img.mode == "RGBA":
        #detecter la derniere ligne horizontale sans pixels transparents
        #et la derniere colonne verticale sans pixels transparents
        x = 0
        y = 0
        for i in range(img.size[0]):
            for j in range(img.size[1]):
                if img.getpixel((i,j))[3] != 0:
                    x = max(x, i)
                    y = max(y, j)
        #on retourne la taille de l'image sans les pixels transparents
        return (x+1, y+1)
    else:
        return img.size


Make = Tk()
Make.title("Configure Make")
#Make.geometry("400x400")
#Make.resizable(0,0)

#make DropDownMenu with buttons DS, 3DS, WII, ...
DropDownMenu = ttk.Combobox(Make, state="readonly")
#pack on top and fill x
DropDownMenu.pack(side=TOP, fill=X)
DropDownMenu["values"] = ("Windows","Linux","DS", "3DS", "WII", "Switch", "PSP", "Casio CG", "Casio FX")
DropDownMenu.current(0)


#make MainFrame
MainFrame = Frame(Make)
MainFrame.pack(side=TOP, fill=BOTH, expand=1)

AppNameString = StringVar()
AppVersionString = StringVar()
AppAuthorString = StringVar()

class DirectoryFileCheck(Frame):
    def __init__(self, parent, path=None, modes=None, filetypes=None):
        Frame.__init__(self, parent)
        self.parent = parent
        self.path = path
        self.modes = modes
        if self.modes == None:
            self.modes = []
        self.filetypes = filetypes
        #list of check buttons at left and labels in center and Comboboxes at right foreach check button
        #make list with grid and scroll bar
        
        #make Scrollbar and canvas
        self.scrollbar = Scrollbar(self)
        self.scrollbar.pack(side=RIGHT, fill=Y)
        self.canvas = Canvas(self, yscrollcommand=self.scrollbar.set)
        self.canvas.pack(side=LEFT, fill=BOTH, expand=1)
        self.scrollbar.config(command=self.canvas.yview)
        #make frame for canvas
        self.frame = Frame(self.canvas)
        self.canvas.create_window((0,0), window=self.frame, anchor=NW)
        #make list of Frames for each file
        self.CheckButtons = []
        self.UpdateDir()
    
    def UpdateDir(self):
        #clear list
        for i in self.CheckButtons:
            i[0].destroy()
        self.CheckButtons = [] #list of tuples (frame, checkbutton, combobox)
        if self.path == None or self.path == "":
            return
        #check if path is a directory
        if not os.path.isdir(self.path):
            return
        #get list of files in directory recursively
        self.files = []
        for root, dirs, files in os.walk(self.path):
            for file in files:
                if self.filetypes == None or os.path.splitext(file)[1].lower() in self.filetypes:
                    self.files.append(os.path.join(root, file))
        #make check buttons for each file (with label and combobox in frame grid)
        for ind, file in enumerate(self.files):
            fm = Frame(self.frame)
            fm.grid(row=ind, column=0, sticky=W)
            #make check button
            is_checked = IntVar()
            cb = Checkbutton(fm, text=file, variable=is_checked)
            cb.grid(row=0, column=0, sticky=W)
            #make combobox
            cboxString = StringVar()
            cbox = ttk.Combobox(fm, textvariable=cboxString)
            if (len(self.modes) > 0):
                cbox.grid(row=0, column=2, sticky=W)
            cbox["values"] = tuple(self.modes)
            self.CheckButtons.append((fm, cb, cbox, is_checked, cboxString))
        #update canvas
        self.frame.update_idletasks()
        self.canvas.config(scrollregion=self.canvas.bbox("all"))

    def save(self):
        Dico = {}
        for i in self.CheckButtons:
            if i[3].get() == 1:
                Dico[i[1].cget("text")] = i[4].get()
        return Dico
    
    def load(self, Dico):
        self.UpdateDir()
        for i in self.CheckButtons:
            cb = i[1]
            if cb.cget("text") in Dico:
                cb.select()
                i[4].set(Dico[cb.cget("text")])
            else:
                cb.deselect()
                i[4].set("")
        

class Distribution:
    def __init__(self, MainFrame,name):
        self.name = name
        self.notebook = ttk.Notebook(MainFrame)
        self.notebook.pack(side=TOP, fill=BOTH, expand=1)
       
        self.addGeneral()
        self.addTextures()
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

    def addTextures(self, Modes=None, FileTypes=[".png",".jpg",".jpeg",".bmp"]):
        self.TabTextures = ttk.Frame(self.notebook)
        self.TabTextures.pack(side=TOP, fill=BOTH, expand=1)
        self.notebook.add(self.TabTextures, text="Textures")
        #make fields for asset folder
        self.AssetFolder = Label(self.TabTextures, text="Asset Folder")
        self.AssetFolder.pack(side=TOP, fill=X)
        self.AssetFolderString = StringVar()
        self.AssetFolderEntry = Entry(self.TabTextures, textvariable=self.AssetFolderString)
        self.AssetFolderEntry.pack(side=TOP, fill=X)
        
        self.dirCheck = DirectoryFileCheck(self.TabTextures,self.AssetFolderString.get(),Modes, FileTypes)
        self.dirCheck.pack(side=TOP, fill=BOTH, expand=1)
        self.AssetFolderString.trace("w", self.UpdateDir)
        self.DataFiles = self.dirCheck.save()

    def UpdateDir(self, *args, **kwargs):
        self.dirCheck.path = self.AssetFolderString.get()
        self.DataFiles = self.dirCheck.save()
        self.dirCheck.load(self.DataFiles)
        self.DataFiles = self.dirCheck.save()

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
        self.UpdateDir()
        return {
            "AppName": self.AppNameString.get(),
            "AppVersion": self.AppVersionString.get(),
            "AppAuthor": self.AppAuthorString.get(),
            "MakeCmd": self.MakeCmdString.get(),
            "CleanCmd": self.CleanCmdString.get(),
            "RunCmd": self.RunCmdString.get(),

            "AssetFolder": self.AssetFolderString.get(),
            "DataFiles": self.DataFiles,
        }

    def set(self, data):
        self.AppNameString.set(data["AppName"])
        self.AppVersionString.set(data["AppVersion"])
        self.AppAuthorString.set(data["AppAuthor"])
        self.MakeCmdString.set(data["MakeCmd"])
        self.CleanCmdString.set(data["CleanCmd"])
        self.RunCmdString.set(data["RunCmd"])
        self.AssetFolderString.set(data["AssetFolder"])
        self.DataFiles = data["DataFiles"]
        self.dirCheck.load(self.DataFiles)

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

    def MakeAssets(self):
        #Make directory for assets if it doesnt exist in bin
        if not os.path.exists("bin/assets"):
            os.makedirs("bin/assets")
        #copy all files in assets to bin/assets
        for file in self.DataFiles:
            desti = "bin/assets/" + file.replace(self.AssetFolderString.get(), "")
            if not os.path.exists(os.path.dirname(desti)):
                os.makedirs(os.path.dirname(desti))
            shutil.copy(file, desti)
            
        

    def Make(self):
        self.UpdateDir()
        self.MakeAssets()
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

    def addTextures(self):
        Modes=["bopti-image"]
        if "cg" in self.name.lower():
            Modes=["rgb565_bopti-image","rgb565a_bopti-image","p8_rgb565_bopti-image","p8_rgb565a_bopti-image","p4_rgb565_bopti-image","p4_rgb565a_bopti-image"]
        #Modes+=["Font","External_bopti-image"]
        FileTypes=[".png",".jpg",".jpeg",".bmp"]
        super().addTextures(Modes, FileTypes)

    def MakeAssets(self):
        textImg = "\n"
        for file in self.DataFiles:
            textImg += file.replace("\\","/")+"\n"
        if "cg" in self.name.lower():
            self.ReplaceVarsInFile("CMakeLists.txt", "IMG_CG", textImg)
        else:
            self.ReplaceVarsInFile("CMakeLists.txt", "IMG_FX", textImg)
        #for all dirs in parent file reset fxconv-metadata.txt or create it
        #list all files and get dir of each file
        DirAss = set()
        for file in self.DataFiles:
            DirAss.add(os.path.dirname(file))
        #for each dir create fxconv-metadata.txt or reset it
        for dir in DirAss:
            with open(dir + "/fxconv-metadata.txt", "w") as f:
                f.write("")
        #for each file add line to fxconv-metadata.txt
        uuids = {}
        for file,key in self.DataFiles.items():
            if key == "":
                print("Error: no key for file " + file)
                continue
            with open(os.path.dirname(file) + "/fxconv-metadata.txt", "a") as f:
                #make switch for different modes
                UUID = str(uuid.uuid4()).replace("-","")
                uuids[file] = UUID
                txt = os.path.basename(file) + ":\n"
                if key == "Font":
                    txt +="  name: IMG_ASSET_"+str(UUID)+"\n"
                    txt +="  type: font\n"
                    txt +="  charset: print\n"
                    txt +="  grid.size: 13x16\n"
                    raise Exception("A terminer!")
                
                elif key == "External_bopti-image":
                    raise Exception("A terminer!")
                
                elif key == "bopti-image":
                    txt +="  name: IMG_ASSET_"+str(UUID)+"\n"
                    txt +="  type: bopti-image\n"

                elif key == "rgb565_bopti-image":
                    txt +="  name: IMG_ASSET_"+str(UUID)+"\n"
                    txt +="  type: bopti-image\n"
                    txt +="  profile: rgb565\n"

                elif key == "rgb565a_bopti-image":
                    txt +="  name: IMG_ASSET_"+str(UUID)+"\n"
                    txt +="  type: bopti-image\n"
                    txt +="  profile: rgb565a\n"

                elif key == "p8_rgb565_bopti-image":
                    txt +="  name: IMG_ASSET_"+str(UUID)+"\n"
                    txt +="  type: bopti-image\n"
                    txt +="  profile: p8\n"

                elif key == "p8_rgb565a_bopti-image":
                    txt +="  name: IMG_ASSET_"+str(UUID)+"\n"
                    txt +="  type: bopti-image\n"
                    txt +="  profile: p8\n"

                elif key == "p4_rgb565_bopti-image":
                    txt +="  name: IMG_ASSET_"+str(UUID)+"\n"
                    txt +="  type: bopti-image\n"
                    txt +="  profile: p4\n"

                elif key == "p4_rgb565a_bopti-image":
                    txt +="  name: IMG_ASSET_"+str(UUID)+"\n"
                    txt +="  type: bopti-image\n"
                    txt +="  profile: p4\n"
                f.write(txt+"\n")
        #add virtual files in Resources.h
        textImg = "\n\t#if defined(CG_MODE) || defined(FX_MODE)\n"
        for file,ID in uuids.items():
            textImg += "extern bopti_image_t IMG_ASSET_"+str(ID)+";\n"
        textImg += "\t#endif\n"
        self.ReplaceVarsInFile("src/ParticuleEngine/Resources.h", "RSC", textImg)
        #add virtual files in Resources.c
        textImg = "\n\t#if defined(CG_MODE) || defined(FX_MODE)\n"
        for file,ID in uuids.items():
            desti = "assets/" + file.replace(self.AssetFolderString.get(), "")
            while desti.find("\\") != -1 or desti.find("//") != -1:
                desti = desti.replace("\\","/")
                desti = desti.replace("//","/")
            textImg += '\tAddTexture((unsigned char*)"'+desti+'", &IMG_ASSET_'+str(ID)+");\n"
        textImg += "\t#endif\n"
        self.ReplaceVarsInFile("src/ParticuleEngine/Resources.c", "RSC_LOAD", textImg)
    def Run(self):
        #remove run button
        pass

    def get(self):
        self.UpdateDir()
        return {
            "AppName": self.AppNameString.get(),
            "AppVersion": self.AppVersionString.get(),
            "AppAuthor": self.AppAuthorString.get(),
            "SrcFolder": self.SrcFolderString.get(),
            "MakeCmd": self.MakeCmdString.get(),

            "AssetFolder": self.AssetFolderString.get(),
            "DataFiles": self.DataFiles,
        }
    
    def set(self, data):
        self.AppNameString.set(data["AppName"])
        self.AppVersionString.set(data["AppVersion"])
        self.AppAuthorString.set(data["AppAuthor"])
        self.SrcFolderString.set(data["SrcFolder"])
        self.MakeCmdString.set(data["MakeCmd"])

        self.AssetFolderString.set(data["AssetFolder"])
        self.DataFiles = data["DataFiles"]
        self.dirCheck.load(self.DataFiles)

    def Make(self):
        self.UpdateDir()
        #find all files in SrcFolder .h and .c and .hpp and .cpp
        srcList = []
        srcFolder = self.SrcFolderString.get()
        for root, dirs, files in os.walk(srcFolder):
            for file in files:
                if file.endswith(".h") or file.endswith(".c") or file.endswith(".hpp") or file.endswith(".cpp"):
                    srcList.append(os.path.join(root, file))
                    #change \\ to /
                    srcList[-1] = srcList[-1].replace("\\", "/")
        srcList.append("Libs/List/List.c")
        srcList.append("Libs/List/List.h")
        srcList.append("Libs/CASIO/MyKeyboard.c")
        srcList.append("Libs/CASIO/MyKeyboard.h")
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
        self.MakeAssets()

        #run make
        cmdString = self.ReplaceVars(self.MakeCmdString.get())
        os.system(cmdString)

    def Clean(self):
        os.system("make clean")

class PspDistribution(Distribution):
    def __init__(self, MainFrame, name):
        super().__init__(MainFrame, name)

    def Make(self):
        self.UpdateDir()
        self.MakeAssets()
        textProgName = '\n#define PROJECT_NAME "' + self.AppNameString.get() + '"\n'
        self.ReplaceVarsInFile("src/ParticuleEngine/Resources.c", "PROJECT_NAME", textProgName)
        super().Make()

    def MakeAssets(self):
        super().MakeAssets()
        #add virtual size files in Resources.c
        textImg = "\n\t#if defined(PSP_MODE)\n"
        for file in self.DataFiles:
            print(file)
            #open image and get size
            #img = Image.open(file)
            #width, height = img.size
            width, height = GetTrueSizeImage(file)
            print(width, height)
            desti = "assets/" + file.replace(self.AssetFolderString.get(), "")
            while desti.find("\\") != -1 or desti.find("//") != -1:
                desti = desti.replace("\\","/")
                desti = desti.replace("//","/")
            textImg += '\tAddTexture((unsigned char*)"'+desti+'", '+str(width)+", "+str(height)+");\n"
        textImg += "\t#endif\n"
        self.ReplaceVarsInFile("src/ParticuleEngine/Resources.c", "RSC_LOAD", textImg)

class WinDistribution(Distribution):
    def __init__(self, MainFrame, name):
        super().__init__(MainFrame, name)

    def addTextures(self):
        Modes=None
        FileTypes=[".png",".jpg",".jpeg",".bmp",".ttf"]
        super().addTextures(Modes, FileTypes)

class NdsDistribution(Distribution):
    def __init__(self, MainFrame, name):
        super().__init__(MainFrame, name)

    def addTextures(self):
        Modes=[]
        FileTypes=[".png",".jpg",".jpeg",".bmp"]
        super().addTextures(Modes, FileTypes)

    def MakeAssets(self):
        uuids = {}
        #remove build/assets folder if exist (remove all files and folder)
        if os.path.exists("build/assets"):
            shutil.rmtree("build/assets")
        #create build/assets folder
        os.makedirs("build/assets/GraphicsData")
        os.makedirs("build/assets/nitrodata")
        for file in self.DataFiles:
            UUID = str(uuid.uuid4()).replace("-", "")
            #make grit file
            gname = "build/assets/GraphicsData/IMG_ASSET_" + UUID + ".grit"
            with open(gname, "w") as f:
                txt = "# Set the warning/log level to 3\n-W3\n#bitmap mode\n-gb\n# Set the bit depth to 8 (256 colors)\n-gB8\n#include pal\n-p"
                f.write(txt)
            #copy file in build/assets
            fname = file.replace(self.AssetFolderString.get(), "").replace("\\", "/").replace("//", "/")
            fname = fname.replace("/", "_")
            fname = "build/assets/GraphicsData/IMG_ASSET_" + UUID + os.path.splitext(fname)[1]
            shutil.copyfile(file, fname)

            uuids[file] = UUID
        #add virtual files in Resources.h
        textImg = "\n\t#if defined(NDS_MODE)\n"
        for file,ID in uuids.items():
            textImg += "#include \"IMG_ASSET_" + ID + ".h\"\n"
        textImg += "\t#endif"
        self.ReplaceVarsInFile("src/ParticuleEngine/Resources.h", "RSC", textImg)
        #add virtual files in Resources.c
        textImg = "\n\t#if defined(NDS_MODE)\n"
        for file,ID in uuids.items():
            print(file)
            #open image and get size
            #img = Image.open(file)
            #width, height = img.size
            width, height = GetTrueSizeImage(file)
            print(width, height)
            desti = "assets/" + file.replace(self.AssetFolderString.get(), "")
            while desti.find("\\") != -1 or desti.find("//") != -1:
                desti = desti.replace("\\","/")
                desti = desti.replace("//","/")
            textImg += '\tAddTexture((unsigned char*)"'+desti+'", IMG_ASSET_'+str(ID)+"Bitmap,IMG_ASSET_"+str(ID)+"Pal,"+str(width)+","+str(height)+");\n"
        textImg += "\t#endif\n"
        self.ReplaceVarsInFile("src/ParticuleEngine/Resources.c", "RSC_LOAD", textImg)

DictSpecialDistributions = {
    "Casio CG": CasioDistribution,
    "Casio FX": CasioDistribution,
    "PSP": PspDistribution,
    "Windows": WinDistribution,
    "DS": NdsDistribution,
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
    SaveConfig()
    print("Make")
    #get distribution currently selected
    Dist = Distribs[DropDownMenu.current()]
    print(Dist.name)
    Dist.Make()

def clean(event, *args):
    SaveConfig()
    print("Clean")
    #get distribution currently selected
    Dist = Distribs[DropDownMenu.current()]
    print(Dist.name)
    Dist.Clean()

def run(event, *args):
    SaveConfig()
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

