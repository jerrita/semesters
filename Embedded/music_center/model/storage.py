import btree


class Storage:
    path: str
    db: btree

    def __init__(self, store_path):
        self.path = store_path
        try:
            f = open(store_path, "rb")
        except OSError:
            f = open(store_path, "wb")
        self.db = btree.open(f)

    def update(self, name, value):
        self.db[name] = value
        self.db.flush()

    def get(self, name):
        return self.db[name]
