from tkinter import filedialog
from tkinter import *
import pathlib
import csv
import os
from pathlib import Path
import subprocess as sub
from tkinter import messagebox
import webbrowser

class Window:       
    def __init__(self, master):     
        csvfile=Label(root, text="File").grid(row=1, column=0)
        self.bar=Entry(master)
        self.bar.grid(row=1, column=1, columnspan=2,  sticky = W + E) 
        self.filetype = []

        #Buttons  
        self.cbutton= Button(root, text="Get QA", command=self.processQA)
        self.cbutton.grid(row=3, column=3, sticky = W + E + N + S)

        self.bbutton= Button(root, text="Browse", command=self.browsefile)
        self.bbutton.grid(row=1, column=3)

        self.resetbutton= Button(root, text="RESET", command=self.reset)
        self.resetbutton.grid(row=4, column=2, columnspan=1, sticky = W + E)

        self.exitbutton= Button(root, text="EXIT", command=self.endProgam)
        self.exitbutton.grid(row=4, column=1, columnspan=1, sticky = W + E)

        self.bg = PhotoImage( file = "./aamcc.png")
        self.bg = self.bg.subsample(10, 10)  
        self.aamccbutton= Button(root, image=self.bg, command= self.my_command, borderwidth=0)
        self.aamccbutton.grid(row=4, column=3, sticky = W + E)

        self.text = Text(width=50, height=10)
        self.text.grid(row=3, column=1, rowspan=1, columnspan=2, sticky = W + E)

        self.var=IntVar()
        self.var.set(0) # Default is AAMCC
        self.aamcc_tick = Radiobutton(root, text="AAMCC", variable=self.var, value=0)
        self.aamcc_tick.grid(row=2, column=1)
        self.dcmsmm_tick = Radiobutton(root, text="DCMSMM", variable=self.var, value=1)
        self.dcmsmm_tick.grid(row=2, column=2)

        self.reset()

    def browsefile(self):
        self.file = filedialog.askopenfilenames(title='Please select root file')
        if(self.file):
            self.text.delete('1.0', END)
            for i in self.file:
                file_extension = os.path.splitext(i)[1]
                filename = os.path.basename(i)
                if (file_extension == ".root"):
                    self.bar.delete(0, 'end')
                    self.bar.insert(0, filename)
                    self.text.insert(1.0, Path(i).stem + ".root" + "\t\n")
                else:
                    self.bar.delete(0, 'end')
                    self.bar.insert(0, 'BAD FILE')
                    self.text.delete('1.0', END)
                    break
        else:
            self.bar.delete(0, 'end')
            self.bar.insert(0, '.root file was not selected')
    def processQA(self):
            if (self.var.get() == 0):
                if ((len(self.file)) == 1):
                    for i in self.file:
                        file_extension = os.path.splitext(i)[1]
                        if (file_extension == ".root"):
                            file_extension = os.path.splitext(i)[1]
                            sub.call(['./QA_script', Path(i).stem, str(self.var.get()), str(1)])
                            self.text.insert(1.0, Path(i).stem + ".root" + " done 100%" + "\t\n")
                        else:
                            self.bar.delete(0, 'end')
                            self.bar.insert(0, 'BAD FILE')
                            self.text.delete('1.0', END)
                            self.text.insert(1.0, "please select files again, bad file was found")
                            break;
                else:
                    for i in self.file:
                        file_extension = os.path.splitext(i)[1]
                        if (file_extension == ".root"):
                            file_extension = os.path.splitext(i)[1]
                            sub.call(['./mult_aamcc_to_mcini', Path(i).stem, str(1)])
                            self.text.insert(1.0, Path(i).stem + ".root" + " done 100%" + "\t\n")
                        else:
                            self.bar.delete(0, 'end')
                            self.bar.insert(0, 'BAD FILE')
                            self.text.delete('1.0', END)
                            self.text.insert(1.0, "please select files again, bad file was found")
                            break;
                    sub.call(['./mult_pdf', str(len(self.file))])

            else:
                for i in self.file:
                    file_extension = os.path.splitext(i)[1]
                    if (file_extension == ".root"):
                        file_extension = os.path.splitext(i)[1]
                        sub.call(['./QA_script', Path(i).stem, str(self.var.get()), str(len(self.file))])
                        self.text.insert(1.0, Path(i).stem + ".root" + " done 100%" + "\t\n")
                        break
                    else:
                        self.bar.delete(0, 'end')
                        self.bar.insert(0, 'BAD FILE')
                        self.text.delete('1.0', END)
                        self.text.insert(1.0, "please select files again, bad file was found")
                        break;
    def reset(self):
        self.filetype = []
        self.bar.delete(0, 'end')
        self.bar.insert(0, 'no file')
        self.text.delete('1.0', END)
        self.text.insert(1.0, "\n note that your input files must be located in \n AAMCC: ../aamcc_to_mcini/input \n DCMSMM: ../mcini_to_aamcc/input \n")
        self.text.insert(1.0, "Before usage please change \n PathToMcini, PathToDcmAamcc, PathToQA variables \n to your system paths in \"QA_script\" \n")
    def my_command(self):
       webbrowser.open('https://github.com/Spectator-matter-group-INR-RAS/AAMCC')
    def endProgam(self):
        root.destroy()  

root = Tk()
root.title("QA tool") 
root.geometry("540x280")
window=Window(root)
root.mainloop() 