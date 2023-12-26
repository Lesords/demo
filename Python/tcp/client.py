import socket

print("This is " + socket.gethostname())

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
host = "127.0.0.1"
port = 9090
s.connect((host, port))

info = ""
while info != 'byebye':
    send_data = input("输入发送内容：")
    s.send(send_data.encode())
    if send_data == 'byebye':
        break

    info = s.recv(1024).decode()
    print("接收到的内容：" + info)

s.close()
