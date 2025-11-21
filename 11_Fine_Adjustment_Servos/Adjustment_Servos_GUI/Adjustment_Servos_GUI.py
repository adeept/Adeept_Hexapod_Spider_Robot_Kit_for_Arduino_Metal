#!/usr/bin/python3
# -*- coding: UTF-8 -*-
# File name   : client.py
# Description : client
# Date      : 2025/10/22
import sys
import time
import threading as thread
import tkinter as tk
import json
import os
import serial
import re

ser = 0

init_1 = 84;
init_2 = 87;
init_3 = 81;
init_4 = 72;
init_5 = 81;
init_6 = 87;
init_7 = 84;
init_8 = 84;
init_9 = 96;
init_10 = 84;
init_11 = 93;
init_12 = 117;
init_13 = 84;

def global_init():
    global color_bg, color_text, color_btn, color_line, color_can, color_oval
    color_bg='#000000'      #Set background color
    color_text='#E1F5FE'      #Set text color
    color_btn="#316E91"    #Set button color
    color_line='#01579B'      #Set line color
    color_can='#212121'    #Set canvas color
    color_oval='#2196F3'      #Set oval color

def pwm_show():
    global L1, L2, L3, L4, L5, L6, L7, L8, L9, L10, L11, L12, L13
    L1.config(text=init_1)
    L2.config(text=init_2)
    L3.config(text=init_3)
    L4.config(text=init_4)
    L5.config(text=init_5)
    L6.config(text=init_6)
    L7.config(text=init_7)
    L8.config(text=init_8)
    L9.config(text=init_9)
    L10.config(text=init_10)
    L11.config(text=init_11)
    L12.config(text=init_12)
    L13.config(text=init_13)

def wait_connect():
    global ser
    while 1:
        ser.write("{'start':['setup']}\n".encode("gbk"))
        #print(11)
        line = ser.readline()
        if line:
            break
            
def serial_connect():    #Call this function to connect with the server
    global ser, E1, Btn14
    com=E1.get()       #Get the COM Port from Entry
    ser = serial.Serial(com,115200,timeout = 1,writeTimeout = 10)
    wait_connect()
    print(com+':Succes')
    Btn14.config(text='Connected')
    Btn14.config(bg="#119648")


def connect(event):    #Call this function to connect with the server
    sc=thread.Thread(target=serial_connect) #Define a thread for connection
    sc.setDaemon(True)                    #'True' means it is a front thread,it would close when the mainloop() closes
    sc.start()                            #Thread starts


def three_function(a,b,c):
    global ser
    a = str(a)
    b = str(b)
    c = str(c)
    p1 = "{'start':"+'['+a+','+b+','+c+']'+'}'+'\n'
    ser.write(p1.encode("gbk"))
    
def jsonDS(numInput, adjustInput):
    global init_1, init_2, init_3, init_4, init_5, init_6, init_7, init_8, init_9, init_10, init_11, init_12, init_13, ser
    if numInput == 1:
        init_1 += adjustInput
        posInput = init_1
    elif numInput == 2:
        init_2 += adjustInput
        posInput = init_2
    elif numInput == 3:
        init_3 += adjustInput
        posInput = init_3
    elif numInput == 4:
        init_4 += adjustInput
        posInput = init_4
    elif numInput == 5:
        init_5 += adjustInput
        posInput = init_5
    elif numInput == 6:
        init_6 += adjustInput
        posInput = init_6
    elif numInput == 7:
        init_7 += adjustInput
        posInput = init_7
    elif numInput == 8:
        init_8 += adjustInput
        posInput = init_8
    elif numInput == 9:
        init_9 += adjustInput
        posInput = init_9
    elif numInput == 10:
        init_10 += adjustInput
        posInput = init_10
    elif numInput == 11:
        init_11 += adjustInput
        posInput = init_11
    elif numInput == 12:
        init_12 += adjustInput
        posInput = init_12
    elif numInput == 13:
        init_13 += adjustInput
        posInput = init_13

    three_function("'angle'",numInput-1,posInput);
    pwm_show()


def servo_buttons(x,y):
    global L1, L2, L3, L4, L5, L6, L7, L8, L9, L10, L11, L12, L13
    def call_pwm1_up(event):
        jsonDS(1, 3)
    def call_pwm1_down(event):
        jsonDS(1, -3)
    def call_pwm2_up(event):
        jsonDS(2, 3)
    def call_pwm2_down(event):
        jsonDS(2, -3)
    def call_pwm3_up(event):
        jsonDS(3, 3)
    def call_pwm3_down(event):
        jsonDS(3, -3)
    def call_pwm4_up(event):
        jsonDS(4, 3)
    def call_pwm4_down(event):
        jsonDS(4, -3)
    def call_pwm5_up(event):
        jsonDS(5, 3)
    def call_pwm5_down(event):
        jsonDS(5, -3)
    def call_pwm6_up(event):
        jsonDS(6, 3)
    def call_pwm6_down(event):
        jsonDS(6, -3)
    def call_pwm7_up(event):
        jsonDS(7, 3)
    def call_pwm7_down(event):
        jsonDS(7, -3)
    def call_pwm8_up(event):
        jsonDS(8, 3)
    def call_pwm8_down(event):
        jsonDS(8, -3)
    def call_pwm9_up(event):
        jsonDS(9, 3)
    def call_pwm9_down(event):
        jsonDS(9, -3)
    def call_pwm10_up(event):
        jsonDS(10, 3)
    def call_pwm10_down(event):
        jsonDS(10, -3)
    def call_pwm11_up(event):
        jsonDS(11, 3)
    def call_pwm11_down(event):
        jsonDS(11, -3)
    def call_pwm12_up(event):
        jsonDS(12, 3)
    def call_pwm12_down(event):
        jsonDS(12, -3)
    def call_pwm13_up(event):
        jsonDS(13, 3)   
    def call_pwm13_down(event):
        jsonDS(13, -3)

    L1 = tk.Label(root,width=8,text=init_1,fg=color_text,bg='#212121')
    L1.place(x=x+100,y=y-15)
    Btn_1i = tk.Button(root, width=8, text='angle0+',fg=color_text,bg=color_btn,relief='ridge')
    Btn_1i.place(x=x+100,y=y+10)
    Btn_1i.bind('<ButtonPress-1>', call_pwm1_up)
    Btn_1d = tk.Button(root, width=8, text='angle0-',fg=color_text,bg=color_btn,relief='ridge')
    Btn_1d.place(x=x+100,y=y+45)
    Btn_1d.bind('<ButtonPress-1>', call_pwm1_down)
    leg1 = tk.Label(root,width=8,text='Leg1',fg='#FF1493',bg='#212121')
    leg1.place(x=x+150,y=y-35)
    L2 = tk.Label(root,width=8,text=init_2,fg=color_text,bg='#212121')
    L2.place(x=x+200,y=y-15)
    Btn_2i = tk.Button(root, width=8, text='angle1+',fg=color_text,bg=color_btn,relief='ridge')
    Btn_2i.place(x=x+200,y=y+10)
    Btn_2i.bind('<ButtonPress-1>', call_pwm2_up)
    Btn_2d = tk.Button(root, width=8, text='angle1-',fg=color_text,bg=color_btn,relief='ridge')
    Btn_2d.place(x=x+200,y=y+45)
    Btn_2d.bind('<ButtonPress-1>', call_pwm2_down)
    
    L3 = tk.Label(root,width=8,text=init_3,fg=color_text,bg='#212121')
    L3.place(x=x+300,y=y-15)
    Btn_3i = tk.Button(root, width=8, text='angle2+',fg=color_text,bg=color_btn,relief='ridge')
    Btn_3i.place(x=x+300,y=y+10)
    Btn_3i.bind('<ButtonPress-1>', call_pwm3_up)
    Btn_3d = tk.Button(root, width=8, text='angle2-',fg=color_text,bg=color_btn,relief='ridge')
    Btn_3d.place(x=x+300,y=y+45)
    Btn_3d.bind('<ButtonPress-1>', call_pwm3_down)
    leg2 = tk.Label(root,width=8,text='Leg2',fg='#FF1493',bg='#212121')
    leg2.place(x=x+350,y=y-35)
    L4 = tk.Label(root,width=8,text=init_4,fg=color_text,bg='#212121')
    L4.place(x=x+400,y=y-15)
    Btn_4i = tk.Button(root, width=8, text='angle3+',fg=color_text,bg=color_btn,relief='ridge')
    Btn_4i.place(x=x+400,y=y+10)
    Btn_4i.bind('<ButtonPress-1>', call_pwm4_up)
    Btn_4d = tk.Button(root, width=8, text='angle3-',fg=color_text,bg=color_btn,relief='ridge')
    Btn_4d.place(x=x+400,y=y+45)
    Btn_4d.bind('<ButtonPress-1>', call_pwm4_down)
 
    L5 = tk.Label(root,width=8,text=init_5,fg=color_text,bg='#212121')
    L5.place(x=x+500,y=y-15)
    Btn_5i = tk.Button(root, width=8, text='angle4+',fg=color_text,bg=color_btn,relief='ridge')
    Btn_5i.place(x=x+500,y=y+10)
    Btn_5i.bind('<ButtonPress-1>', call_pwm5_up)
    Btn_5d = tk.Button(root, width=8, text='angle4-',fg=color_text,bg=color_btn,relief='ridge')
    Btn_5d.place(x=x+500,y=y+45)
    Btn_5d.bind('<ButtonPress-1>', call_pwm5_down)
    leg3 = tk.Label(root,width=8,text='Leg3',fg='#FF1493',bg='#212121')
    leg3.place(x=x+550,y=y-35)
    L6 = tk.Label(root,width=8,text=init_6,fg=color_text,bg='#212121')
    L6.place(x=x+600,y=y-15)
    Btn_6i = tk.Button(root, width=8, text='angle5+',fg=color_text,bg=color_btn,relief='ridge')
    Btn_6i.place(x=x+600,y=y+10)
    Btn_6i.bind('<ButtonPress-1>', call_pwm6_up)
    Btn_6d = tk.Button(root, width=8, text='angle5-',fg=color_text,bg=color_btn,relief='ridge')
    Btn_6d.place(x=x+600,y=y+45)
    Btn_6d.bind('<ButtonPress-1>', call_pwm6_down)

    L7 = tk.Label(root,width=8,text=init_7,fg=color_text,bg='#212121')
    L7.place(x=x+100,y=y+100)
    Btn_7i = tk.Button(root, width=8, text='angle6+',fg=color_text,bg=color_btn,relief='ridge')
    Btn_7i.place(x=x+100,y=y+125)
    Btn_7i.bind('<ButtonPress-1>', call_pwm7_up)
    Btn_7d = tk.Button(root, width=8, text='angle6-',fg=color_text,bg=color_btn,relief='ridge')
    Btn_7d.place(x=x+100,y=y+150)
    Btn_7d.bind('<ButtonPress-1>', call_pwm7_down)
    leg4 = tk.Label(root,width=8,text='Leg4',fg='#FF1493',bg='#212121')
    leg4.place(x=x+150,y=y+75)
    L8 = tk.Label(root,width=8,text=init_8,fg=color_text,bg='#212121')
    L8.place(x=x+200,y=y+100)
    Btn_8i = tk.Button(root, width=8, text='angle7+',fg=color_text,bg=color_btn,relief='ridge')
    Btn_8i.place(x=x+200,y=y+125)
    Btn_8i.bind('<ButtonPress-1>', call_pwm8_up)
    Btn_8d = tk.Button(root, width=8, text='angle7-',fg=color_text,bg=color_btn,relief='ridge')
    Btn_8d.place(x=x+200,y=y+150)
    Btn_8d.bind('<ButtonPress-1>', call_pwm8_down)

    L9 = tk.Label(root,width=8,text=init_9,fg=color_text,bg='#212121')
    L9.place(x=x+300,y=y+100)
    Btn_9i = tk.Button(root, width=8, text='angle8+',fg=color_text,bg=color_btn,relief='ridge')
    Btn_9i.place(x=x+300,y=y+125)
    Btn_9i.bind('<ButtonPress-1>', call_pwm9_up)
    Btn_9d = tk.Button(root, width=8, text='angle8-',fg=color_text,bg=color_btn,relief='ridge')
    Btn_9d.place(x=x+300,y=y+150)
    Btn_9d.bind('<ButtonPress-1>', call_pwm9_down)
    leg5 = tk.Label(root,width=8,text='Leg5',fg='#FF1493',bg='#212121')
    leg5.place(x=x+350,y=y+75)
    L10 = tk.Label(root,width=8,text=init_10,fg=color_text,bg='#212121')
    L10.place(x=x+400,y=y+100)
    Btn_10i = tk.Button(root, width=8, text='angle9+',fg=color_text,bg=color_btn,relief='ridge')
    Btn_10i.place(x=x+400,y=y+125)
    Btn_10i.bind('<ButtonPress-1>', call_pwm10_up)
    Btn_10d = tk.Button(root, width=8, text='angle9-',fg=color_text,bg=color_btn,relief='ridge')
    Btn_10d.place(x=x+400,y=y+150)
    Btn_10d.bind('<ButtonPress-1>', call_pwm10_down)
    
    L11 = tk.Label(root,width=8,text=init_11,fg=color_text,bg='#212121')
    L11.place(x=x+500,y=y+100)
    Btn_11i = tk.Button(root, width=8, text='angle10+',fg=color_text,bg=color_btn,relief='ridge')
    Btn_11i.place(x=x+500,y=y+125)
    Btn_11i.bind('<ButtonPress-1>', call_pwm11_up)
    Btn_11d = tk.Button(root, width=8, text='angle10-',fg=color_text,bg=color_btn,relief='ridge')
    Btn_11d.place(x=x+500,y=y+150)
    Btn_11d.bind('<ButtonPress-1>', call_pwm11_down)
    leg6 = tk.Label(root,width=8,text='Leg6',fg='#FF1493',bg='#212121')
    leg6.place(x=x+550,y=y+75)
    L12 = tk.Label(root,width=8,text=init_12,fg=color_text,bg='#212121')
    L12.place(x=x+600,y=y+100)
    Btn_12i = tk.Button(root, width=8, text='angle11+',fg=color_text,bg=color_btn,relief='ridge')
    Btn_12i.place(x=x+600,y=y+125)
    Btn_12i.bind('<ButtonPress-1>', call_pwm12_up)
    Btn_12d = tk.Button(root, width=8, text='angle11-',fg=color_text,bg=color_btn,relief='ridge')
    Btn_12d.place(x=x+600,y=y+150)
    Btn_12d.bind('<ButtonPress-1>', call_pwm12_down)
    
    head = tk.Label(root,width=8,text='Head',fg='#FF1493',bg='#212121')
    head.place(x=x+700,y=y)
    L13 = tk.Label(root,width=8,text=init_13,fg=color_text,bg='#212121')
    L13.place(x=x+700,y=y+25)
    Btn_13i = tk.Button(root, width=8, text='angle12+',fg=color_text,bg=color_btn,relief='ridge')
    Btn_13i.place(x=x+700,y=y+50)
    Btn_13i.bind('<ButtonPress-1>', call_pwm13_up)
    Btn_13d = tk.Button(root, width=8, text='angle12-',fg=color_text,bg=color_btn,relief='ridge')
    Btn_13d.place(x=x+700,y=y+85)
    Btn_13d.bind('<ButtonPress-1>', call_pwm13_down)

def connent_input(x,y):
    global E1, Btn14
    E1 = tk.Entry(root,show=None,width=16,bg="#37474F",fg='#eceff1')
    E1.place(x=x+5,y=y+25)                           #Define a Entry and put it in position

    l_ip_3=tk.Label(root,width=10,text='Port:',fg=color_text,bg='#000000')
    l_ip_3.place(x=x,y=y)                        #Define a Label and put it in position

    Btn14= tk.Button(root, width=8,height=2, text='Connect',fg=color_text,bg=color_btn,relief='ridge')
    Btn14.place(x=x+130,y=y)                          #Define a Button and put it in position

    root.bind('<Return>', connect)
    Btn14.bind('<ButtonPress-1>', connect)

def updata_angle_file():    #Call this function to updata in 'angle.h' file
    filename = "angle.h"
    
    init_values = {
        "ANGLE0": init_1,
        "ANGLE1": init_2,
        "ANGLE2": init_3,
        "ANGLE3": init_4,
        "ANGLE4": init_5,
        "ANGLE5": init_6,
        "ANGLE6": init_7,
        "ANGLE7": init_8,
        "ANGLE8": init_9,
        "ANGLE9": init_10,
        "ANGLE10": init_11,
        "ANGLE11": init_12,
        "ANGLE12": init_13
    }

    with open(filename, "w") as f:
        f.write("#ifndef __ANGLE_H__\n")
        f.write("#define __ANGLE_H__\n\n")
        for key, value in init_values.items():
            f.write(f"#define {key} {value}\n")
        f.write("\n#endif\n")
    print(f"File '{filename}' updata succeed.")

def updata_current_file():   #Call this function to updata in current file
    filename = __file__
    
    updates = {
        "init_1": init_1,
        "init_2": init_2,
        "init_3": init_3,
        "init_4": init_4,
        "init_5": init_5,
        "init_6": init_6,
        "init_7": init_7,
        "init_8": init_8,
        "init_9": init_9,
        "init_10": init_10,
        "init_11": init_11,
        "init_12": init_12,
        "init_13": init_13,
    }
    
    with open(filename, "r") as f:
        content = f.read()

    for var_name, new_value in updates.items():
        pattern = r"(^|\s)" + re.escape(var_name) + r"\s*=\s*\d+"
        replacement = f"\\1{var_name} = {new_value}"
        content = re.sub(pattern, replacement, content, flags=re.MULTILINE)

    with open(filename, "w") as f:
        f.write(content)

    print(f"File '{filename}' updated with new variable values succeed.")

def initSet(event):
    updata_angle_file()
    updata_current_file()

def set_button(x,y):
    global L_select_feedback
    L_select_feedback = tk.Label(root,width=23,text='Click here after debugging',fg=color_text,bg='#000000')
    L_select_feedback.place(x=x-200,y=y-25)

    Btn_Switch_1 = tk.Button(root, width=8, text='SET',fg=color_text,bg=color_btn,relief='ridge')
    Btn_Switch_1.place(x=x-100,y=y)
    Btn_Switch_1.bind('<ButtonPress-1>', initSet)

def loop():
    global root
    global_init()
    
    root = tk.Tk()          
    root.title('Adjustment Servos')
    root.geometry('725x320')
    root.config(bg=color_bg)

    try:
        logo =tk.PhotoImage(file = 'logo.png')
        l_logo=tk.Label(root,image = logo,bg=color_bg)
        l_logo.place(x=630,y=13)
    except:
        pass

    connent_input(25,15)
    
    set_button(630,35)
    
    servo_buttons(-70,120)

    root.mainloop()


if __name__ == '__main__':
    loop()
