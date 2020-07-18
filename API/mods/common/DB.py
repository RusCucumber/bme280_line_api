import os
from pymongo import MongoClient

class DB(object):
    def __init__(self):
        uri = os.getenv("DB_URI")

        client = MongoClient(uri)
        db = client[self.__DB]
        self.col = db[self.__COLLECTION]

    __DB = os.getenv("DB_DBNAME")
    __COLLECTION = os.getenv("DB_COLLECTION")