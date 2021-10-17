import serial
from tkinter import *

# importing the choosecolor package
from tkinter import colorchooser


def choose_color():

    color_code = colorchooser.askcolor(title="Choose color")
    command1 = "C" + str(color_code[0][0])+":" + \
        str(color_code[0][1]) + ":" + str(color_code[0][2])+"\n"
    command2 = "1" + str(color_code[0][0])+":" + \
        str(color_code[0][1]) + ":" + str(color_code[0][2])+"\n"
    bytesCommand1 = bytes(command1, "UTF-8")
    bytesCommand2 = bytes(command2, "UTF-8")
    ser = serial.Serial('COM17', 9600)
    ser.write(bytesCommand1)
    ser.write(bytesCommand2)
    ser.close()


root = Tk()
button = Button(root, text="Select color",
                command=choose_color)
button.pack()
root.geometry("300x50")
root.mainloop()
