import socket
import threading
import ui

# 센서 값을 한 번에 받도록 프로그래밍 하는 것이 좋을 것 같다.
# 자동차가 항상 위를 보고 있다고 가정   
class Car:
    port = 1

    def __init__(self, name, mac_address=None):
        self.address = mac_address
        self._name = name
        self._path = "..."
        self.driving = False
        
        self.x, self.y = 0, 0  # 0 - 5
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
    
    # /////////////////////////////////////////////////////
    @property
    def path(self):
        return self._path
    @path.setter
    def path(self, p):
        self._path = p
    @property
    def name(self):
        return self._name
    @name.setter
    def name(self, name):
        self._name = name
    
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
    def getSensor(self):
        self.send("sensor")
        print(self.receive())
    # /////////////////////////////////////////////////////

    def receive(self):
        string_data = ""
        try:
            for _ in range(10):
                string_data += self.socket.recv(1024).decode("ascii")  # 정보를 받을 때까지 대기
                if "\n" in string_data:
                    string_data = string_data.replace("\r", "").replace("\n", "")
                    print("Received:", string_data)
                    break
        except UnicodeDecodeError:
            print("Received: !!Error!!")
        finally:
            return string_data
        
import random
def communication():
    car1 = Car("Test Car 1")  # "00:22:09:01:FE:87"
    car2 = Car("Test Car 2")
    car3 = Car("Test Car 3")
    for car in (car1, car2, car3):
        car.setPos(random.randint(0, 3), random.randint(0, 3))
        app.register_car(car)
    
def appDef():
    global app, root
    root = ui.Tk()
    app = ui.AppUI(root)
    app.pack(fill="both", expand=True)

if __name__ == "__main__":
    t1 = threading.Thread(target=communication)
    t1.daemon = True 
    appDef()
    t1.start()
    root.mainloop()