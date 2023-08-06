"""
pip install pybluez2

pip install bleak

"""

import socket
import asyncio

address = "00:22:09:01:FE:87"

async def main_async():
    while True:
        if await send() == "q":
            break
        await receive()
    
async def send():
    global s
    msg = input("send message : ")
    if msg == "q":
        return "q"
    
    s.send(bytes(msg, 'utf-8'))

async def receive():
    global s
    data = s.recv(1024)
    print("Received: [%s]" % data.decode("utf-8").replace("\n", "\\n").replace("\r", "\\r"))
    
with socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, socket.BTPROTO_RFCOMM) as s:
    s.connect((address, 1))
    print("bluetooth connected!")
    
    loop = asyncio.get_event_loop()
    loop.run_until_complete(main_async())
    loop.close()
    
    print("finished")