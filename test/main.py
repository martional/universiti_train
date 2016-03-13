__author__ = 'SeyyedMojtaba'

# import tkinter
import tkinter,time
from tkinter import *
from tkinter import filedialog

# window options
screen = Tk()
screen.geometry("640x480") # window size
screen.tk.call('wm','iconphoto',screen,PhotoImage(file="data\\img\\icon.gif")) # icon
screen.title("آزمون چهارگزینه ای") # window title
screen.configure(background="white") # background color
screen.option_add('*font',('tahoma',8,'normal')) # default font
screen.option_add('*background','white') # default background color

# menu
def tab_minimize():
    screen.state('iconic')
def tab_help():
    showframe(Frame6,x=160,y=170,width=300,height=100)
    hideframe(Frame7)
def tab_about():
    showframe(Frame7,x=160,y=170,width=300,height=100)
    hideframe(Frame6)

menu = Menu(screen)
file_menu = Menu(menu,tearoff=0)
menu.add_cascade(label="پرونده",menu=file_menu)
file_menu.add_command(label="کمینه سازی",command=tab_minimize)
file_menu.add_command(label="خروج",command=screen.destroy)

help_menu = Menu(menu,tearoff=0)
menu.add_cascade(label="راهنما",menu=help_menu)
help_menu.add_command(label="راهنمای استفاده از نرم افزار",command=tab_help)
help_menu.add_command(label="درباره طراح نرم افزار",command=tab_about)

screen.config(menu=menu)

# image
logo_image = PhotoImage(file="data\\img\\logo.gif")
logo = Label(screen,image=logo_image)
logo.place(x=380,y=0,width=250,height=100)

def showframe(master,x,y,width,height):
    master.place(x=x,y=y,width=width,height=height)

def hideframe(master):
    master.place(x=0,y=0,width=0,height=0)

# FRAME 1 : Information
Frame1 = Frame(screen,width=640,height=360)
Frame1.place(x=0,y=100)

# text
frame1_0 = Label(Frame1, text=":لطفاً اطلاعات زیر را پر کنید",anchor="ne")
frame1_0.place(x=380,y=20,width=200)

# name
frame1_1_0_image = dot_image = PhotoImage(file="data\\img\\dot.gif")
frame1_1_0 = Label(Frame1,image=frame1_1_0_image)
frame1_1_0.place(x=560,y=59,width=5,height=5)
frame1_1_1 = Label(Frame1,text=":نام و نام خانوادگی",fg="dark blue",anchor="ne")
frame1_1_1.place(x=450,y=50,width=100)

# entry
frame1_2 = name = Entry(Frame1,bg="#f4f4f4",justify="right")
frame1_2.place(y=50,x=275,height=20,width=160)

frame1_3 = Label(Frame1, text=":لطفاً آزمونی را انتخاب کنید",anchor="ne")
frame1_3.place(y=100,x=380,width=200)

# test properties
frame1_4_0_image = line_image = PhotoImage(file="data\\img\\line.gif")
frame1_4_0 = Label(Frame1,image=frame1_4_0_image)
frame1_4_0.place(y=140,x=562,height=100,width=3)

frame1_4_1_image = test_name_image = PhotoImage(file="data\\img\\test_name.gif")
frame1_4_1 = Label(Frame1,image=frame1_4_1_image)
frame1_4_1.place(y=153,x=535,height=12,width=12)
frame1_4_2 = test_properties_name = Label(Frame1,anchor="ne")
frame1_4_2.place(y=150,x=230,width=300,height=20)

frame1_4_3_image = test_number_image = PhotoImage(file="data\\img\\test_number.gif")
frame1_4_3 = Label(Frame1,image=frame1_4_3_image)
frame1_4_3.place(y=173,x=535,height=12,width=12)
frame1_4_4 = test_properties_number = Label(Frame1,anchor="ne")
frame1_4_4.place(y=170,x=230,width=300,height=20)

frame1_4_5_image = test_time_image = PhotoImage(file="data\\img\\test_time.gif")
frame1_4_5 = Label(Frame1,image=frame1_4_5_image)
frame1_4_5.place(y=193,x=535,height=12,width=12)
frame1_4_6 = test_properties_time = Label(Frame1,anchor="ne")
frame1_4_6.place(y=190,x=230,width=300,height=20)

frame1_4_7_image = test_hardness_image = PhotoImage(file="data\\img\\test_hardness.gif")
frame1_4_7 = Label(Frame1,image=frame1_4_7_image)
frame1_4_7.place(y=213,x=535,height=12,width=12)
frame1_4_8 = test_properties_hardness = Label(Frame1,anchor="ne")
frame1_4_8.place(y=210,x=230,width=300,height=20)

# open test button
test = None
def test_open():
    global test
    test = filedialog.askopenfile(mode="r",defaultextension=".test",filetypes=[("Test Files","*.test")])
    if test != None:
        global test_lines,test_name,test_number,test_number_text,test_time,test_hardness,test_hardness_text
        test_lines = test.readlines()
        test_name = test_lines[1]
        test_number = int(test_lines[3])
        test_number_text = test_number+1
        test_time = int(test_lines[5])
        test_time_text = test_lines[6]
        test_hardness = int(test_lines[8])
        test_properties_name['text'] = test_name
        test_properties_number['text'] = test_number_text
        test_properties_time['text'] = test_time_text

        if test_hardness == 1:
            test_hardness_text = 'بسیار آسان'
        elif test_hardness == 2:
            test_hardness_text = 'آسان'
        elif test_hardness == 3:
            test_hardness_text = 'متوسط'
        elif test_hardness == 4:
            test_hardness_text = 'سخت'
        elif test_hardness == 5:
            test_hardness_text = 'بسیار سخت'
        else:
            test_hardness_text = 'نا مشخص'

        test_properties_hardness['text'] = test_hardness_text

frame1_5 = Button(Frame1, text="باز کردن آزمون",bg="#78e7e6",activebackground="#3d8e8d",command=test_open)
frame1_5.place(y=100,x=362)

# start button
def test_start():
    errors = 0
    if test == None:
        error_message = '!لطفاً آزمونی را باز کنید'
        errors +=1

    if name.get() == '':
        error_message = '!لطفاً نامتان را وارد کنید'
        errors +=1
        name['bg'] = "pink"
    else:
        name['bg'] = "light green"

    if errors > 0:
        error_image_image_image = error_image_image
        error_text['text'] = error_message
        error_image['image'] = error_image_image_image
        error_text.place(y=440,x=425,height=20,width=200)
        error_image.place(y=445,x=625,height=12,width=12)
    else:
        error_message = ''
        error_image_image_image = ''
        error_text['text'] = error_message
        error_image['image'] = error_image_image_image
        showframe(Frame2,x=0,y=100,width=640,height=360)
        hideframe(Frame1)
        showframe(Frame3,x=0,y=0,width=300,height=100)
        showinformation()
        global answer_ticked
        answer_ticked = [0]
        for i in range(((test_number//5)+1)*5):
            answer_ticked.append(0)
        global answer_correct
        answer_correct = ['']
        for i in range(test_number):
            answer_correct.append('')
        for i in range(test_number+1):
            index = 0
            number = '#%s\n' %(i)
            while index < len(test_lines):
                if test_lines[index] == number:
                    answer_correct[i] = int(test_lines[index+1][1])
                index +=1
        global current_test
        current_test = 0
        showtests(0,5)

frame1_6 = Button(Frame1, text="شروع آزمون",bg="#78e7e6",activebackground="#3d8e8d",command=test_start)
frame1_6.place(y=260,x=368)

# Frame 2 : The Questions
Frame2 = Frame(screen,width=640,height=360)

# questions
question = ['','','','','','','','','',''] # 10 blocks for 5 questions!
question_dot = ['','','','',''] # 5 blocks for 5 questions dot!
question_number = ['','','','',''] # 5 blocks for 5 questions number!

# answers
answer = [['','','','',''],['','','','',''],['','','','',''],['','','','',''],['','','','','']] # 5 blocks for 5 answers for each 5 questions!
answer_radio = [['','','','',''],['','','','',''],['','','','',''],['','','','',''],['','','','','']] # 5 blocks for 5 answers for each 5 questions!

# question 0
frame2_0_0_number = question_number[0] = Label(Frame2,font="Calibri 22")
frame2_0_0_number.place(x=575, y=15)
frame2_0_0_image = question_dot[0] = Label(Frame2)
frame2_0_0_image.place(x=565,y=25)
frame2_0_0 = question[0] = Label(Frame2,anchor="ne")
frame2_0_0.place(x=20,y=20,width=540)
frame2_0_1 = question[1] = Label(Frame2,anchor="ne")
frame2_0_1.place(x=20,y=40,width=540)


# answer 0
answer_0 = IntVar()
frame2_0_2 = answer_radio[0][0] = Radiobutton(Frame2,variable=answer_0,value=1,anchor="ne",activebackground="white")
frame2_0_2.place(x=545,y=60,width=0,height=20)
frame2_0_2_text = answer[0][0] = Label(Frame2,anchor="ne")
frame2_0_2_text.place(x=440,y=60,width=100,height=20)


frame2_0_3 = answer_radio[0][1] = Radiobutton(Frame2,variable=answer_0,value=2,anchor="ne",activebackground="white")
frame2_0_3.place(x=420,y=60,width=0,height=20)
frame2_0_3_text = answer[0][1] = Label(Frame2,anchor="ne")
frame2_0_3_text.place(x=315,y=60,width=100,height=20)

frame2_0_4 = answer_radio[0][2] = Radiobutton(Frame2,variable=answer_0,value=3,anchor="ne",activebackground="white")
frame2_0_4.place(x=295,y=60,width=0,height=20)
frame2_0_4_text = answer[0][2] = Label(Frame2,anchor="ne")
frame2_0_4_text.place(x=190,y=60,width=100,height=20)

frame2_0_5 = answer_radio[0][3] = Radiobutton(Frame2,variable=answer_0,value=4,anchor="ne",activebackground="white")
frame2_0_5.place(x=150,y=60,width=0,height=20)
frame2_0_5_text = answer[0][3] = Label(Frame2,anchor="ne")
frame2_0_5_text.place(x=45,y=60,width=100,height=20)

frame2_0_6 = answer_radio[0][4] = Radiobutton(Frame2,variable=answer_0,value=0,anchor="nw",activebackground="white")
frame2_0_6.place(x=575,y=60,width=0,height=20)
frame2_0_6_text = answer[0][4] = Label(Frame2,anchor="ne")
frame2_0_6_text.place(x=600,y=60,width=30,height=20)

# question 1
frame2_1_0_number = question_number[1] = Label(Frame2,font="Calibri 22")
frame2_1_0_number.place(x=575, y=75)
frame2_1_0_image = question_dot[1] = Label(Frame2)
frame2_1_0_image.place(x=565,y=85)
frame2_1_0 = question[2] = Label(Frame2,anchor="ne")
frame2_1_0.place(x=20,y=80,width=540)
frame2_1_1 = question[3] = Label(Frame2,anchor="ne")
frame2_1_1.place(x=20,y=100,width=540)

# answer 1
answer_1 = IntVar()
frame2_1_2 = answer_radio[1][0] = Radiobutton(Frame2,variable=answer_1,value=1,anchor="ne",activebackground="white")
frame2_1_2.place(x=545,y=120,width=0,height=20)
frame2_1_2_text = answer[1][0] = Label(Frame2,anchor="ne")
frame2_1_2_text.place(x=440,y=120,width=100,height=20)

frame2_1_3 = answer_radio[1][1] = Radiobutton(Frame2,variable=answer_1,value=2,anchor="ne",activebackground="white")
frame2_1_3.place(x=420,y=120,width=0,height=20)
frame2_1_3_text = answer[1][1] = Label(Frame2,anchor="ne")
frame2_1_3_text.place(x=315,y=120,width=100,height=20)

frame2_1_4 = answer_radio[1][2] = Radiobutton(Frame2,variable=answer_1,value=3,anchor="ne",activebackground="white")
frame2_1_4.place(x=295,y=120,width=0,height=20)
frame2_1_4_text = answer[1][2] = Label(Frame2,anchor="ne")
frame2_1_4_text.place(x=190,y=120,width=100,height=20)

frame2_1_5 = answer_radio[1][3] = Radiobutton(Frame2,variable=answer_1,value=4,anchor="ne",activebackground="white")
frame2_1_5.place(x=150,y=120,width=0,height=20)
frame2_1_5_text = answer[1][3] = Label(Frame2,anchor="ne")
frame2_1_5_text.place(x=45,y=120,width=100,height=20)

frame2_1_6 = answer_radio[1][4] = Radiobutton(Frame2,variable=answer_1,value=0,anchor="nw",activebackground="white")
frame2_1_6.place(x=575,y=120,width=0,height=20)
frame2_1_6_text = answer[1][4] = Label(Frame2,anchor="ne")
frame2_1_6_text.place(x=600,y=120,width=30,height=20)

# question 2
frame2_2_0_number = question_number[2] = Label(Frame2,font="Calibri 22")
frame2_2_0_number.place(x=575, y=135)
frame2_2_0_image = question_dot[2] = Label(Frame2)
frame2_2_0_image.place(x=565,y=145)
frame2_2_0 = question[4] = Label(Frame2,anchor="ne")
frame2_2_0.place(x=20,y=140,width=540)
frame2_2_1 = question[5] = Label(Frame2,anchor="ne")
frame2_2_1.place(x=20,y=160,width=540)

# answer 2
answer_2 = IntVar()
frame2_2_2 = answer_radio[2][0] = Radiobutton(Frame2,variable=answer_2,value=1,anchor="ne",activebackground="white")
frame2_2_2.place(x=545,y=180,width=0,height=20)
frame2_2_2_text = answer[2][0] = Label(Frame2,anchor="ne")
frame2_2_2_text.place(x=440,y=180,width=100,height=20)

frame2_2_3 = answer_radio[2][1] = Radiobutton(Frame2,variable=answer_2,value=2,anchor="ne",activebackground="white")
frame2_2_3.place(x=420,y=180,width=0,height=20)
frame2_2_3_text = answer[2][1] = Label(Frame2,anchor="ne")
frame2_2_3_text.place(x=315,y=180,width=100,height=20)

frame2_2_4 = answer_radio[2][2] = Radiobutton(Frame2,variable=answer_2,value=3,anchor="ne",activebackground="white")
frame2_2_4.place(x=295,y=180,width=0,height=20)
frame2_2_4_text = answer[2][2] = Label(Frame2,anchor="ne")
frame2_2_4_text.place(x=190,y=180,width=100,height=20)

frame2_2_5 = answer_radio[2][3] = Radiobutton(Frame2,variable=answer_2,value=4,anchor="ne",activebackground="white")
frame2_2_5.place(x=150,y=180,width=0,height=20)
frame2_2_5_text = answer[2][3] = Label(Frame2,anchor="ne")
frame2_2_5_text.place(x=45,y=180,width=100,height=20)

frame2_2_6 = answer_radio[2][4] = Radiobutton(Frame2,variable=answer_2,value=0,anchor="nw",activebackground="white")
frame2_2_6.place(x=575,y=180,width=0,height=20)
frame2_2_6_text = answer[2][4]= Label(Frame2,anchor="ne")
frame2_2_6_text.place(x=600,y=180,width=30,height=20)

# question 3
frame2_3_0_number = question_number[3] = Label(Frame2,font="Calibri 22")
frame2_3_0_number.place(x=575, y=195)
frame2_3_0_image = question_dot[3] = Label(Frame2)
frame2_3_0_image.place(x=565,y=205)
frame2_3_0 = question[6] = Label(Frame2,anchor="ne")
frame2_3_0.place(x=20,y=200,width=540)
frame2_3_1 = question[7] = Label(Frame2,anchor="ne")
frame2_3_1.place(x=20,y=220,width=540)

# answer 3
answer_3 = IntVar()
frame2_3_2 = answer_radio[3][0] = Radiobutton(Frame2,variable=answer_3,value=1,anchor="ne",activebackground="white")
frame2_3_2.place(x=545,y=240,width=0,height=20)
frame2_3_2_text = answer[3][0] = Label(Frame2,anchor="ne")
frame2_3_2_text.place(x=440,y=240,width=100,height=20)

frame2_3_3 = answer_radio[3][1] = Radiobutton(Frame2,variable=answer_3,value=2,anchor="ne",activebackground="white")
frame2_3_3.place(x=420,y=240,width=0,height=20)
frame2_3_3_text = answer[3][1] = Label(Frame2,anchor="ne")
frame2_3_3_text.place(x=315,y=240,width=100,height=20)


frame2_3_4 = answer_radio[3][2] = Radiobutton(Frame2,variable=answer_3,value=3,anchor="ne",activebackground="white")
frame2_3_4.place(x=295,y=240,width=0,height=20)
frame2_3_4_text = answer[3][2] = Label(Frame2,anchor="ne")
frame2_3_4_text.place(x=190,y=240,width=100,height=20)


frame2_3_5 = answer_radio[3][3] = Radiobutton(Frame2,variable=answer_3,value=4,anchor="ne",activebackground="white")
frame2_3_5.place(x=150,y=240,width=0,height=20)
frame2_3_5_text = answer[3][3] = Label(Frame2,anchor="ne")
frame2_3_5_text.place(x=45,y=240,width=100,height=20)

frame2_3_6 = answer_radio[3][4] = Radiobutton(Frame2,variable=answer_3,value=0,anchor="nw",activebackground="white")
frame2_3_6.place(x=575,y=240,width=0,height=20)
frame2_3_6_text = answer[3][4] = Label(Frame2,anchor="ne")
frame2_3_6_text.place(x=600,y=240,width=30,height=20)

# question 4
frame2_4_0_number = question_number[4] = Label(Frame2,font="Calibri 22")
frame2_4_0_number.place(x=575, y=255)
frame2_4_0_image = question_dot[4] = Label(Frame2)
frame2_4_0_image.place(x=565,y=265)
frame2_4_0 = question[8] = Label(Frame2,anchor="ne")
frame2_4_0.place(x=20,y=260,width=540)
frame2_4_1 = question[9] = Label(Frame2,anchor="ne")
frame2_4_1.place(x=20,y=280,width=540)

# answer 4
answer_4 = IntVar()
frame2_4_2 = answer_radio[4][0] = Radiobutton(Frame2,variable=answer_4,value=1,anchor="ne",activebackground="white")
frame2_4_2.place(x=545,y=300,width=0,height=20)
frame2_4_2_text = answer[4][0] = Label(Frame2,anchor="ne")
frame2_4_2_text.place(x=440,y=300,width=100,height=20)

frame2_4_3 = answer_radio[4][1] = Radiobutton(Frame2,variable=answer_4,value=2,anchor="ne",activebackground="white")
frame2_4_3.place(x=420,y=300,width=0,height=20)
frame2_4_3_text = answer[4][1] = Label(Frame2,anchor="ne")
frame2_4_3_text.place(x=315,y=300,width=100,height=20)

frame2_4_4 = answer_radio[4][2] = Radiobutton(Frame2,variable=answer_4,value=3,anchor="ne",activebackground="white")
frame2_4_4.place(x=295,y=300,width=0,height=20)
frame2_4_4_text = answer[4][2] = Label(Frame2,anchor="ne")
frame2_4_4_text.place(x=190,y=300,width=100,height=20)

frame2_4_5 = answer_radio[4][3] = Radiobutton(Frame2,variable=answer_4,value=4,anchor="ne",activebackground="white")
frame2_4_5.place(x=150,y=300,width=0,height=20)
frame2_4_5_text = answer[4][3] = Label(Frame2,anchor="ne")
frame2_4_5_text.place(x=45,y=300,width=100,height=20)

frame2_4_6 = answer_radio[4][4] = Radiobutton(Frame2,variable=answer_4,value=0,anchor="nw",activebackground="white")
frame2_4_6.place(x=575,y=300,width=0,height=20)
frame2_4_6_text = answer[4][4] = Label(Frame2,anchor="ne")
frame2_4_6_text.place(x=600,y=300,width=30,height=20)

# save answers of each page
def saveanswers(current_test):
    next_test = current_test + 5
    answers = [answer_0.get(),answer_1.get(),answer_2.get(),answer_3.get(),answer_4.get()]
    for i in range (current_test,next_test):
        j = i - current_test
        answer_ticked[i] = answers[j]

# showing page number
def pagenumber():
    global current_test
    page_number_text = current_test//5+1
    page_number['text'] = page_number_text

# prev page button
def prevtests():
    global current_test
    if current_test < 5 :
        return
    saveanswers(current_test)
    current_test -= 5
    next_test = current_test + 5
    showtests(current_test,next_test)
    pagenumber()

# next page button
def nexttests():
    global current_test
    if current_test+5 >= test_number:
        return
    saveanswers(current_test)
    current_test += 5
    next_test = current_test + 5
    showtests(current_test,next_test)
    pagenumber()

frame2_5_image = prev_image = PhotoImage(file="data\\img\\prev.gif")
frame2_5 = Button(Frame2,image=frame2_5_image,command=prevtests,border=0,activebackground="white")
frame2_5.place(x=2,y=345,width=12,height=12)

frame2_6 = page_number = Label(Frame2,text="1")
frame2_6.place(x=12,y=340,width=32)

frame2_7_image = next_image = PhotoImage(file="data\\img\\next.gif")
frame2_7 = Button(Frame2,image=frame2_7_image,command=nexttests,border=0,activebackground="white")
frame2_7.place(x=40,y=345,width=12,height=12)

# stopping test button
def stoptest():
    screen.bell()
    showframe(Frame4,x=160,y=170,width=300,height=100)
    hideframe(Frame2)
    question_text['text'] = 'آیا شما مایل به اتمام آزمون هستید؟'
    question_text.place(x=155,y=180,width=270,height=20)
    question_image['image'] = question_image_image
    question_image.place(y=185,x=427,height=12,width=12)

    # show frame 2
    def showframe2():
        showframe(Frame2,x=0,y=100,width=640,height=360)
        question_text.place(x=-1000,y=-1000,height=0)
        question_image.place(x=-1000,y=-1000,height=0)
        sample_button0.place(x=-1000,y=-1000)
        sample_button1.place(x=-1000,y=-1000)
        hideframe(Frame4)

    # show frame 5
    def showframe5():
        global stopped
        stopped = 1
        hideframe(Frame3)
        hideframe(Frame4)
        showframe(Frame5,x=0,y=100,width=640,height=360)
        question_text.place(x=0,y=0,width=0,height=0)
        question_image.place(x=-1000,y=-1000)
        sample_button0.place(x=-1000,y=-1000)
        sample_button1.place(x=-1000,y=-1000)
        showresult()

    sample_button0['text'] = 'بله، مشاهده نتایج'
    sample_button0['command'] = showframe5
    sample_button0.place(x=340,y=210)
    sample_button1['text'] = 'خیر، ادامه آزمون'
    sample_button1['command'] = showframe2
    sample_button1.place(x=250,y=210)

frame2_8_image = error_image = PhotoImage(file="data\\img\\error.gif")
frame2_8 = Button(Frame2,image=frame2_8_image,command=stoptest,border=0,activebackground="white")
frame2_8.place(x=60,y=345,width=12,height=12)

# showing tests of each page
answer_correction = [answer_0,answer_1,answer_2,answer_3,answer_4]
def showtests(current_test,next_test):
    # clearation !!
    for i in range(5):
        question[2*(i)]['text'] = ''
        question[2*(i)+1]['text'] = ''
        question_dot[i]['image'] = ''
        question_number[i]['text'] = ''
        for j in range (5):
            answer[i][j]['text'] = ''
            answer_radio[i][j].place(width=0)

    # putting elements in their place
    for i in range(current_test,next_test):
        index = 0
        number = '#%s\n'%(i)
        while index < len(test_lines):
            if test_lines[index] == number:
                answer_correction[i - current_test].set(answer_ticked[i])
                question[2*(i-current_test)]['text'] = test_lines[index+2]
                question[2*(i-current_test)+1]['text'] = test_lines[index+3]
                question_dot[i-current_test]['image'] = dot_image
                question_number[i-current_test]['text'] = i+1
                answer[i-current_test][0]['text'] = test_lines[index+4]
                answer[i-current_test][1]['text'] = test_lines[index+5]
                answer[i-current_test][2]['text'] = test_lines[index+6]
                answer[i-current_test][3]['text'] = test_lines[index+7]
                answer[i-current_test][4]['text'] = 'سفید'
                answer_radio[i-current_test][0].place(width=25)
                answer_radio[i-current_test][1].place(width=25)
                answer_radio[i-current_test][2].place(width=25)
                answer_radio[i-current_test][3].place(width=25)
                answer_radio[i-current_test][4].place(width=25)
            index +=1

# Frame 3
Frame3 = Frame(screen,width=300,height=100)

# test time
stopped = 0
def showtime():
    global stopped
    if stopped == 1:
        return

    elapsed = int(time.clock())
    elapsed_hour = elapsed//360
    if elapsed_hour < 10:
        elapsed_hour_text = '0%s' %elapsed_hour
    else:
        elapsed_hour_text = elapsed_hour

    elapsed_min = (elapsed - (elapsed_hour*360))//60
    if elapsed_min < 10:
        elapsed_min_text = '0%s' %elapsed_min
    else:
        elapsed_min_text = elapsed_min

    elapsed_sec = (elapsed - (elapsed_hour*360) - (elapsed_min*60))
    if elapsed_sec < 10:
        elapsed_sec_text = '0%s' %elapsed_sec
    else:
        elapsed_sec_text = elapsed_sec
    elapsed_clock = '[%s:%s:%s]' %(elapsed_hour_text,elapsed_min_text,elapsed_sec_text)

    remaining = test_time - elapsed

    remaining_hour = remaining//360
    if remaining_hour < 10:
        remaining_hour_text = '0%s' %remaining_hour
    else:
        remaining_hour_text = remaining_hour

    remaining_min = (remaining - (remaining_hour*360))//60
    if remaining_min < 10:
        remaining_min_text = '0%s' %remaining_min
    else:
        remaining_min_text = remaining_min

    remaining_sec = (remaining - (remaining_hour*360) - (remaining_min*60))
    if remaining_sec < 10:
        remaining_sec_text = '0%s' %remaining_sec
    else:
        remaining_sec_text = remaining_sec
    remaining_clock = '[%s:%s:%s]' %(remaining_hour_text,remaining_min_text,remaining_sec_text)

    time_hour = test_time//360
    if time_hour < 10:
        time_hour_text = '0%s' %time_hour
    else:
        time_hour_text = time_hour

    time_min = (test_time - (time_hour*360))//60
    if time_min < 10:
        time_min_text = '0%s' %time_min
    else:
        time_min_text = time_min

    time_sec = (test_time - (time_hour*360) - (time_min*60))
    if time_sec < 10:
        time_sec_text = '0%s' %time_sec
    else:
        time_sec_text = time_sec
    time_clock = '[%s:%s:%s]' %(time_hour_text,time_min_text,time_sec_text)

    information_test_time['text'] = '%s %s %s' %(elapsed_clock,remaining_clock,time_clock)
    screen.after(1000,showtime)

    if remaining == 0:
        screen.bell()
        sample_button1.place(x=-1000,y=-1000)
        question_text.place(x=-1000,y=-1000)
        question_image.place(x=-1000,y=-1000)
        stopped = 1
        showframe(Frame4,x=160,y=170,width=300,height=100)
        hideframe(Frame2)
        error_text['text'] = '!وقت شما تمام شد'
        error_text.place(x=155,y=180,width=270,height=20)
        error_image['image'] = error_image_image
        error_image.place(y=185,x=427,height=12,width=12)

        # show frame 5
        def showframe5():
            hideframe(Frame3)
            hideframe(Frame4)
            showframe(Frame5,x=0,y=100,width=640,height=360)
            error_text.place(x=-1000,y=-1000,)
            error_image.place(x=-1000,y=-1000,)
            sample_button0.place(x=-1000,y=-1000)
            showresult()

        sample_button0['text'] = 'مشاهده نتایج'
        sample_button0['command'] = showframe5
        sample_button0.place(x=365,y=210)


# show test information
def showinformation():
    information_name['text'] = name.get()
    information_test_name['text'] = test_name
    information_test_number['text'] = test_number_text
    information_test_hardness['text'] = test_hardness_text
    showtime()

frame3_line = Label(Frame3,image=line_image)
frame3_line.place(x=0,y=0)

frame3_0_image_image = name_image = PhotoImage(file="data\\img\\person.gif")
frame3_0_image =  Label(Frame3,image=name_image)
frame3_0_image.place(x=10,y=6)
frame3_0 = information_name = Label(Frame3,anchor="nw",justify="left")
frame3_0.place(x=25,y=3)

frame3_1_image = Label(Frame3,image=test_name_image)
frame3_1_image.place(x=10,y=26)
frame3_1 = information_test_name = Label(Frame3,anchor="nw",justify="left")
frame3_1.place(x=25,y=23)

frame3_2_image = Label(Frame3,image=test_number_image)
frame3_2_image.place(x=10,y=46)
frame3_2 = information_test_number = Label(Frame3,anchor="nw",justify="left")
frame3_2.place(x=25,y=43)

frame3_3_image = Label(Frame3,image=test_time_image)
frame3_3_image.place(x=10,y=66)
frame3_3 = information_test_time = Label(Frame3,anchor="nw",justify="left")
frame3_3.place(x=25,y=63)

frame3_4_image = Label(Frame3,image=test_hardness_image)
frame3_4_image.place(x=10,y=86)
frame3_4 = information_test_hardness = Label(Frame3,anchor="nw",justify="left")
frame3_4.place(x=25,y=83)

# Frame 4  : Messages on the exam page
Frame4 = Frame(screen,width=300,height=100)

frame4_0_image = line_image
frame4_0 = Label(Frame4,image=frame4_0_image)
frame4_0.place(x=295,y=0)


# Frame 5 : The Results!
result_correct_text = 0
result_wrong_text = 0
result_null_text = 0
result_precent_text = 0

# showing result
def showresult():
    for i in range(((test_number+1)//5)+1):
        nexttests()
    prevtests()

    # calculating result
    global result_correct,result_wrong,result_null,result_percent,result_correct_text,result_wrong_text,result_null_text,result_percent_text
    for i in range (test_number+1):
        if answer_ticked[i] == 0:
            result_null_text +=1
        elif answer_ticked[i] == answer_correct[i]:
            result_correct_text +=1
        else:
            result_wrong_text +=1
    result_percent_text = int(((result_correct_text*3)-result_wrong_text)/((test_number+1)*3)*10000)/100
    result_correct['text'] = result_correct_text
    result_wrong['text'] = result_wrong_text
    result_null['text'] = result_null_text
    result_percent['text'] = result_percent_text

Frame5 = Frame(screen,width=640,height=360)

frame5_0_image_image = info_image_image = PhotoImage(file="data\\img\\info.gif")
frame5_0_image = Label(Frame5,image=frame5_0_image_image)
frame5_0_image.place(x=525,y=78)
frame5_0 = Label(Frame5,text="نتایج آزمون",font="tahoma 8 bold",anchor="ne")
frame5_0.place(x=325,y=75,width=200)

frame5_1_image_image = ok_image_image = PhotoImage(file="data\\img\\ok.gif")
frame5_1_image = Label(Frame5,image=frame5_1_image_image)
frame5_1_image.place(x=505,y=103)
frame5_1 = Label(Frame5,text=":تعداد صحیح",anchor="ne")
frame5_1.place(x=305,y=100,width=200)

frame5_2 = result_correct = Label(Frame5, font="tahoma 8 bold", fg="dark green")
frame5_2.place(x=380,y=100,width=50)

frame5_3_image_image = error_image_image = PhotoImage(file="data\\img\\error.gif")
frame5_3_image = Label(Frame5,image=frame5_3_image_image)
frame5_3_image.place(x=505,y=123)
frame5_3 = Label(Frame5,text=":تعداد غلط",anchor="ne")
frame5_3.place(x=305,y=120,width=200)

frame5_4 = result_wrong = Label(Frame5, font="tahoma 8 bold", fg="dark red")
frame5_4.place(x=380,y=120,width=50)

frame5_5_image_image = error_image_info = PhotoImage(file="data\\img\\info.gif")
frame5_5_image = Label(Frame5,image=frame5_5_image_image)
frame5_5_image.place(x=505,y=143)
frame5_5 = Label(Frame5,text=":تعداد نزده",anchor="ne")
frame5_5.place(x=305,y=140,width=200)

frame5_6 = result_null = Label(Frame5, font="tahoma 8 bold", fg="dark blue")
frame5_6.place(x=380,y=140,width=50)

frame5_7_image_image = percent_image_info = PhotoImage(file="data\\img\\percent.gif")
frame5_7_image = Label(Frame5,image=frame5_7_image_image)
frame5_7_image.place(x=505,y=163)
frame5_7 = Label(Frame5,text=":درصد",anchor="ne")
frame5_7.place(x=305,y=160,width=200)

frame5_8 = result_percent = Label(Frame5, font="tahoma 8 bold")
frame5_8.place(x=380,y=160,width=50)


# Frame 6 : Help
Frame6 = Frame(screen,width=300,height=100,relief="ridge",border=5,borderwidth=5)

frame6_0_image_image = question_image_image = PhotoImage(file="data\\img\\question.gif")
frame6_0_image = Label(Frame6,image=frame6_0_image_image)
frame6_0_image.place(x=268,y=9,width=12,height=12)

frame6_0 = Label(Frame6,text="راهنمای استفاده از نرم افزار",anchor="ne",font="tahoma 8 bold")
frame6_0.place(x=65,y=5,width=200)

frame6_1 = Label(Frame6,text=".ابتدا مشخصات خود را وارد کرده سپس آزمون را باز کنید\nدر مرحله ی بعد جواب سوال ها را علامت زده و در آخر از\n.نتیجه خود مطلع شوید",anchor="ne",justify="right")
frame6_1.place(x=5,y=25,width=260)

# hide frame 6
def hideframe6():
    hideframe(Frame6)
frame6_2 = Button(Frame6,text="بازگشت",anchor="ne",bg="#78e7e6",activebackground="#3d8e8d",command=hideframe6)
frame6_2.place(x=10,y=63)

# Frame 7 : About
Frame7 = Frame(screen,width=300,height=100,relief="ridge",border=5,borderwidth=5)

frame7_0_image_image = info_image_image = PhotoImage(file="data\\img\\info.gif")
frame7_0_image = Label(Frame7,image=frame7_0_image_image)
frame7_0_image.place(x=268,y=9,width=12,height=12)

frame7_0 = Label(Frame7,text="درباره طراح نرم افزار",anchor="ne",font="tahoma 8 bold")
frame7_0.place(x=65,y=5,width=200)

frame7_1 = Label(Frame7,text=".این نرم افزار پروژه درس مبانی کامپیوتر است\nطراحان: مصطفی مرادی، سعید صفرزاده و سیّدمجتبی\n.اکرم زاده اردکانی\nاستاد: آقای محسن صابری",anchor="ne",justify="right")
frame7_1.place(x=5,y=25,width=260)

# hide frame 7
def hideframe7():
    hideframe(Frame7)
frame7_2 = Button(Frame7,text="بازگشت",anchor="ne",bg="#78e7e6",activebackground="#3d8e8d",command=hideframe7)
frame7_2.place(x=10,y=63)

showframe(Frame1,x=0,y=100,width=640,height=360)

# error message
error_image_image = PhotoImage(file="data\\img\\error.gif")
error_image = Label(screen)
error_text = Label(screen,fg="dark red",anchor="ne")

# question message
question_image_image = PhotoImage(file="data\\img\\question.gif")
question_image = Label(screen)
question_text = Label(screen,fg="dark orange",anchor="ne")

# info message
info_image_image = PhotoImage(file="data\\img\\info.gif")
info_image = Label(screen)
info_text = Label(screen,fg="dark blue",anchor="ne")

# ok message
ok_image_image = PhotoImage(file="data\\img\\ok.gif")
ok_image = Label(screen)
ok_text = Label(screen,fg="dark green",anchor="ne")

# sample buttons
sample_button0 = Button(screen,bg="#78e7e6",activebackground="#3d8e8d")
sample_button1 = Button(screen,bg="#78e7e6",activebackground="#3d8e8d")
sample_button2 = Button(screen,bg="#78e7e6",activebackground="#3d8e8d")
sample_button3 = Button(screen,bg="#78e7e6",activebackground="#3d8e8d")

screen.mainloop()