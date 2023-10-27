"""
"""

import socket
import threading
import sys

ADDRESS = {
    1: "00:22:09:01:F8:**",
    2: "00:22:09:01:FE:**",
    3: "00:22:09:01:FD:**",
}

def send():
    global s
    msg = input()
    if msg == "q":
        return "q"
    
    s.send(bytes(msg, 'utf-8'))

def receive():
    global s
    while True:
        data = s.recv(1024)
        print("Received: [%s]" % data.decode("utf-8").replace("\n", "\\n").replace("\r", "\\r"))
    
with socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, socket.BTPROTO_RFCOMM) as s:
    s.connect((ADDRESS[int(sys.argv[1])], 1))
    print("bluetooth connected!")

    t1 = threading.Thread(target=receive)
    t1.daemon = True
    t1.start()
    while True:
        if send() == "q":
            break

    print("finished")
