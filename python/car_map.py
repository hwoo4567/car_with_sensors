import matplotlib
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure
import socket
import asyncio
import threading
from tkinter import *

# 센서 값을 한 번에 받도록 프로그래밍 하는 것이 좋을 것 같다.

class AppUI(Frame):
    def __init__(self, parent: Tk):
        Frame.__init__(self, parent)
        matplotlib.use("TkAgg", force=True)
        
        self.parent = parent
        self.points = dict()
        self.loop_func = None  # loop event
        
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
        self.start_btn = Button(self, text="Start", command=self.carStart)
        self.start_btn.pack(side="bottom", fill="both")
        
        fig = Figure(figsize=(10, 10), dpi=128)
        self.subplt = fig.add_subplot(1, 1, 1)
        
        self.canvas = FigureCanvasTkAgg(fig, master=self)
        self.canvas.draw()
        self.tkcanvas = self.canvas.get_tk_widget()
        self.tkcanvas.pack(fill="both")
        self.tkcanvas.after(50, self.updatePoints)

    def updatePoints(self):
        for k, v in self.points.items():
            x, y = k.getPos()
            v.set_data([x],[y])
            
        self.subplt.set_xticks([1, 2, 3, 4, 5])
        self.subplt.set_yticks([1, 2, 3, 4, 5])
        self.subplt.grid(True)

        self.canvas.draw()
        self.tkcanvas.update()
        self.tkcanvas.after(50, self.updatePoints)
        
    def createPoint(self, car):
        point, = self.subplt.plot(0, 0, marker="o")
        self.points[car] = point
        print("Point:", car)
        
    def carStart(self):
        self.start_btn.config(bg="gray", command=lambda: ...)
        for car in self.points.keys():
            car.startDrive()
 
# 자동차가 항상 위를 보고 있다고 가정   
class Car:
    port = 1

    def __init__(self, name, mac_address=None):
        self.address = mac_address
        self._name = name
        self.driving = False
        
        self.x, self.y = 0, 0  # 0 - 5
        self.dest = 0, 0
        self.light_sensor = 0.0
        self.distance = 0.0
        
        if mac_address is not None:
            self.socket = socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, socket.BTPROTO_RFCOMM)
            self.socket.connect((self.address, self.port))
            self.stop()
        
    def setPos(self, x, y):
        self.x, self.y = x, y
    def getPos(self):
        return self.x, self.y
    
    @property
    def name(self):
        return self._name
    @name.setter
    def name(self, name):
        self._name = name
    def setDest(self, dest):
        self.dest = dest
    def startDrive(self):
        self.driving = True
    
    async def drive(self):
        print(self.driving)
        if not self.driving:
            return

        self.go("forward")
        await asyncio.sleep(5)
        await asyncio.wait([
            asyncio.create_task(self.getLightSensor()),
            asyncio.create_task(self.getDistance()),
        ])
        print(self.light_sensor, self.distance)

        self.stop()
        self.driving = False

    def send(self, msg: str):
        self.socket.send(bytes(msg, "ascii"))
    
    def close(self):
        self.socket.close()

    def go(self, direction):
        cmd = f"go {direction}"
        self.send(cmd)
    def stop(self):
        self.send("stop")
    def turn(self, direction):
        cmd = f"turn {direction}"
        self.send(cmd)

    async def receive(self):
        self.data = ""
        try:
            for _ in range(10):
                self.data += self.socket.recv(1024).decode("ascii")  # 정보를 받을 때까지 대기
                if "\n" in self.data:
                    self.data = self.data.replace("\r", "").replace("\n", "")
                    print("Received:", self.data)
                    break
        except UnicodeDecodeError:
            print("Received: !!Error!!")
        
    async def getLightSensor(self):
        self.send(f"sensor light")
        await self.receive()
        self.light_sensor = float(self.data)
        
    async def getLineSensor(self):
        self.send(f"sensor lineL")
        await self.receive()
        print("a")
        self.send(f"sensor lineR")
        await self.receive()
        print("b")
        
    async def getDistance(self):
        self.send("sensor distance")
        await self.receive()
        self.distance = float(self.data)

async def main_async(*args: Car):
    while True:
        await asyncio.wait([
            asyncio.create_task(car.drive())
            for car in args
        ])
        await asyncio.sleep(1)

def communication():
    car1 = Car("test car", "00:22:09:01:FE:87")
    app.createPoint(car1)
    
    loop = asyncio.new_event_loop()
    loop.run_until_complete(main_async(car1))
    loop.close()

def appExec():
    root = Tk()
    global app
    app = AppUI(root)
    app.pack(fill="both", expand=True)
    root.mainloop()

if __name__ == "__main__":
    t1 = threading.Thread(target=communication)
    t1.daemon = True 
    t1.start()
    appExec()