from mods.common.DB import DB

class GetMessage(DB):
    def msg(self):
        self.__find()
        self.__dict2str()
        return self.__message

    def __find(self):
        result = self.col.find()
        if result.count() == 0:
            self.latest_data = {"result": "No data."}
        else:
            result = result.sort([("id", -1)])
            self.latest_data = result[0]
            del self.latest_data["_id"]

    def __dict2str(self):
        self.__message = "Latest Data"
        for key in self.latest_data:
            tmp_str = "\n{0}: {1}".format(key, self.latest_data[key])
            self.__message += tmp_str

    __message = ""
