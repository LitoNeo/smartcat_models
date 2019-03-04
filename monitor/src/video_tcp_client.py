#!/usr/bin/python
# -*- coding:utf-8 -*-

import sys
import cv2
import numpy as np
import socket


class Client:
    def __init__(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            self.sock.connect(('127.0.0.1', 9999))
        except:
            print("Cannot connct server.")
            exit(1)
        self.cap = cv2.VideoCapture(0)
        print("Client is ready...")

    def send_pic(self, frame):
        # cv2.imencode将图片格式转换(编码)成流数据，赋值到内存缓存中;主要用于图像数据格式的压缩，方便网络传输
        result, imgencode = cv2.imencode('.jpg', frame)
        data = np.array(imgencode)
        stringData = data.tostring()

        """首先发送图片的大小信息"""
        self.sock.send(str(len(stringData)).ljust(16))
        # 返回一个原字符串左对齐,并使用空格填充至指定长度的新字符串。
        # 如果指定的长度小于原字符串的长度则返回原字符串

        self.sock.sendall(stringData)
        # 如果server端是Python的socket,那么可以一次性发送
        # 但是如果server端是C++写的,那么需要一个字节一个字节的发送 --因为编码里有字符串结束标识位C++会进行截断处理
        # e.g:
        # for i in range(0, len(stringData)):
        #   sock.send(stringData[i])

        data_rec = self.sock.recv(50)
        print(data_rec)

    def run(self):
        # cap = cv2.VideoCapture(0)
        if not self.cap.isOpened():
            print("Cannot open camera, exit.")
            exit(1)
        while True:
            ret, frame = self.cap.read()
            if ret:
                self.send_pic(frame)
            else:
                break
            # if cv2.waitKey(25) == ord('q'):
            #     break
            # cv2.imshow("client", frame)
        self.cap.release()
        # cv2.destroyAllWindows()

    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        if self.cap.isOpened():
            self.cap.release()
        cv2.destroyAllWindows()
        self.sock.sendall("exit".ljust(16))
        self.sock.close()
        print("Current connection closed")


if __name__ == '__main__':
    with Client() as client:
        client.run()



