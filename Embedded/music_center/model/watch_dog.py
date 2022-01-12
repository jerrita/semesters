import machine


class WatchDog:
    def status_check(self):
        pass

    @staticmethod
    def restart(self):
        machine.reset()
