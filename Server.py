import os
import time
import timm
import socket

from PyQt5.QtCore import QThread, pyqtSignal
from huggingface_hub import hf_hub_download
from torchvision import  transforms
from supervision import Detections
from ultralytics import YOLO

class Thread(QThread):
    update = pyqtSignal()

    def __init__(self, sec=0, parent=None):
        super().__init__()
        self.main = parent
        self.running = True

    def run(self):
        while self.isRunning:
            self.update.emit()
            time.sleep(0.07)

    def stop(self):
        self.running = False

class TCP():
    def __init__(self):
        self.esp32_ip = '192.168.**.**'  # ESP32의 IP 주소
        self.esp32_port = 8080 
        self.message = None

    def encodeMsg(self, msg):
        match(msg):
            case "connect":
                self.message = "11\n"
            case "soyoung": # user_name
                self.message = "21\n"
            case "drive":
                self.message = "31\n"
            case "stop":
                self.message = "32\n"
            case "reverse":
                self.message = "33\n"
            case "accel":
                self.message = "34\n"
            case "L1":
                self.message = "41\n"
            case "L2":
                self.message = "42\n"
            case "L3":
                self.message = "43\n"
            case "R1":
                self.message = "51\n"
            case "R2":
                self.message = "52\n"
            case "R3":
                self.message = "53\n"
            case "side_parking":
                self.message = "88\n"
            case "no_drive_way":
                self.message = "77\n"
            case "emergency":
                self.message = "99\n"
        
        return self.message

class SeverSocket(QThread):
    update = pyqtSignal(str)
    def __init__(self, sec=0, parent=None):
        super().__init__()
        self.HOST = '***.***.**.**'
        self.PORT = **** 

        self.main = parent
        self.isRunning = True
        self.client_socket = None

    def run(self):
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_socket.bind((self.HOST, self.PORT))
        self.server_socket.listen(2)

        while self.isRunning:
            try:
                self.client_socket, _ = self.server_socket.accept()

            # 클라이언트로부터 데이터 수신
                data = self.client_socket.recv(1024).decode('utf-8')
                self.update.emit(data)
            
            except:
                # 클라이언트 연결 종료
                self.client_socket.close()

    def stop(self):
        self.isRunning = False
