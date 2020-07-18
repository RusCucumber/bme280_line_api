import datetime
from mods.common.DB import DB

class InsertMessage(DB):
    def __init__(self, msg):
        super().__init__()
        self.msg = msg
        self.data = {}

    def __str2dict(self):
        for key_val in self.msg.split(","):
            key, val = key_val.split(":")
            val = round(float(val), 2)
            self.data.update({key: val})

    def __set_id(self):
        result = self.col.find()
        if result.count() == 0:
            new_id = 1
        else:
            resule = result.sort([("id", -1)])
            new_id = int(result[0]["id"]) + 1
        self.data.update({"id": new_id})

    def __set_dt(self):
        dt = datetime.datetime.now()
        dt += datetime.timedelta(hours = 9) # heroku の時差補正
        self.data.update({"rcd_dt": dt})

    def insert(self):
        self.__set_id()
        self.__set_dt()
        self.__str2dict()
        self.col.insert_one(self.data)