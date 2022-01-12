import ssd1306
from machine import I2C, Pin
from .define import *


class Display:
    i2c: I2C
    display: ssd1306.SSD1306_I2C
    wifi: str = 'Not Connected'
    ip: str = '0.0.0.0'

    def __init__(self):
        self.i2c = I2C(scl=Pin(D1), sda=Pin(D2))
        self.display = ssd1306.SSD1306_I2C(128, 64, self.i2c)

    def show_connecting_screen(self):
        self.clean()
        self.display.text('Connecting...', 10, 30)
        self.display.show()

    def show_wifi_detail(self, name, ip):
        self.clean()
        self.display.text('WIFI Detail', 20, 0)
        self.display.text(name, 10, 25)
        self.display.text(ip, 10, 40)
        self.display.show()

    def show_play_detail(self, name, ip, volume):
        self.clean()
        self.display.text('Player info', 20, 0)
        self.display.text(f'WIFI: {name.decode()}', 5, 15)
        self.display.text(ip, 5, 25)
        self.display.text(f'Volume: {volume}', 5, 40)
        self.display.show()

    def show_fallback(self):
        self.clean()
        self.display.text('Connect failed.', 0, 0)
        self.display.text('Please reboot manually', 0, 25)
        self.display.show()

    def clean(self):
        self.display.init_display()
