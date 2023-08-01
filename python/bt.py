"""
pip install pybluez2

pip install bleak

"""

from bluetooth import *
import asyncio

address = "98:DA:60:08:7E:10"

async def main_async():
    while True:
        if await send() == "q":
            break
        await receive()
    
async def send():
    global socket
    msg = input("send message : ")
    if msg == "q":
        return "q"
    
    socket.send(bytes(msg, 'utf-8'))

async def receive():
    data = socket.recv(1024)
    print("Received: [%s]" % data.decode("utf-8").replace("\n", "\\n").replace("\r", "\\r"))
    
with BluetoothSocket() as socket:
    socket.connect((address, 1))
    print("bluetooth connected!")
    
    loop = asyncio.get_event_loop()
    loop.run_until_complete(main_async())
    loop.close()
    
    print("finished")

