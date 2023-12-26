import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
host = "127.0.0.1"
port = 9090
s.bind((host, port))
s.listen(1)

print("wait for client...")
sock, addr = s.accept()
print("client info: ", addr)

info = ""
while info != 'byebye':
    info = sock.recv(1024).decode()
    print("接收到的内容:" + info)
    if info == 'byebye':
        break

    send_data = input("输入发送内容:")
    sock.send(send_data.encode())
    if send_data == 'byebye':
        break

sock.close()
s.close()
