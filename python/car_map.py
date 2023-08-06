import matplotlib
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure
import numpy as np
import socket
import asyncio
from tkinter import *
from tkinter import ttk


class AppUI(Frame):
    def __init__(self, parent: Tk):
        Frame.__init__(self, parent)
        matplotlib.use("TkAgg")
        
        self.parent = parent
        
        self.initVar()
        self.initUI()
        
    def initVar(self):
        self.parent.title("tkinter GUI")
        self.parent.geometry("500x500+40+40")  # 가로 x 세로 + x좌표 + y좌표
        self.parent.resizable(True, True)  # 가로 세로 크기 변경 여부

    def initUI(self):
        # <menu>
        self.menu_ = Menu(self.parent)
          # <file>
        file_menu = Menu(self.menu_, tearoff=False)
        self.menu_.add_cascade(label="File", menu=file_menu)
          # <help>
        help_menu = Menu(self.menu_, tearoff=False)
        self.menu_.add_cascade(label="Help", menu=help_menu)

        self.parent.config(menu=self.menu_)

        # <main>
        fig = Figure(figsize=(10, 10), dpi=128)
        subplt = fig.add_subplot(1, 1, 1)
        
        self.canvas = FigureCanvasTkAgg(fig, master=self.parent)
        self.canvas.draw()
        self.tkcanvas = self.canvas.get_tk_widget()
        self.tkcanvas.pack()
        self.tkcanvas.after(1000, self.movePoint)
        
        self.point, = subplt.plot(0, 1, marker="o")
        
        subplt.set_xticks([1, 2, 3, 4, 5])
        subplt.set_yticks([1, 2, 3, 4, 5])
        subplt.grid(True)
        
    def movePoint(self):
        x = np.random.sample() * 5
        y = np.random.random() * 5
        self.point.set_data([x],[y])
        
        print(round(x, 2), round(y, 2))
        self.canvas.draw()
        self.tkcanvas.update()
        self.tkcanvas.after(1000, self.movePoint)
        
class Car:
    port = 1

    def __init__(self, mac_address):
        self.address = mac_address
        
        self.socket = socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, socket.BTPROTO_RFCOMM)
        self.socket.connect((self.address, self.port))
        
    async def send(self):
        msg = input("send message : ")
        if msg == "quit":
            self.socket.close()
        
        self.socket.send(bytes(msg, 'utf-8'))
    
    async def receive(self):
        data = self.socket.recv(1024).decode("utf-8")
        print("Received: [%s]" % data.replace("\n", "\\n").replace("\r", "\\r"))

async def appExec():
    root = Tk()
    app = AppUI(root)
    app.pack(fill="both", expand=True)
    root.mainloop()

async def main_async():
    car1 = Car("")
    car2 = Car("")
    car3 = Car("")
    
    tasks = [asyncio.create_task(appExec())]
    for c in (car1, car2, car3):
        tasks.append(asyncio.create_task(c.receive()))
        tasks.append(asyncio.create_task(c.send()))

    await asyncio.wait(tasks)

if __name__ == "__main__":
    loop = asyncio.get_event_loop()
    loop.run_until_complete(main_async())
    loop.close()