import network
import utime
from .storage import Storage


class Controller:
    db: Storage
    sta: network.WLAN

    def __init__(self, db):
        self.db = db

    def connect(self, timeout=10):
        self.sta = network.WLAN(network.STA_IF)
        self.sta.active(True)
        self.sta.connect(self.db.get('ssid'), self.db.get('password'))

        while not self.sta.isconnected() and timeout:
            utime.sleep(1)
            timeout -= 1

        if not self.sta.isconnected():  # Timeout
            return False
        else:
            self.db.update('ip', self.sta.ifconfig()[0])
            return True
