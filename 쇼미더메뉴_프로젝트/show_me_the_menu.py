from selenium import webdriver
from bs4 import BeautifulSoup
import json
from datetime import datetime
import requests
import pymongo

#############################웹 페이지에서 정보 받아오기############################
if(datetime.today().month<10):
    URL = "http://dsm2015.cafe24.com/v2/meal/" + str(datetime.today().year) + "-0" + str(datetime.today().month) + '-' + str(datetime.today().day)
else:
    URL = "http://dsm2015.cafe24.com/v2/meal/" + str(datetime.today().year) + '-' + str(datetime.today().month) + '-' + str(datetime.today().day)
res=requests.get(URL)
meals=json.loads(res.text)
#############################웹 페이지에서 정보 받아오기############################
#############################몽고 디비 연계하여 데이터 입력하기#####################
connection = pymongo.MongoClient("localhost", 27017)
db = connection.Menu
collection = db.meal

num=1

for i in meals:
    collection.insert_one({str(i):meals[i]})
    num+=1
#############################몽고 디비 연계하여 데이터 입력하기#####################
#############################몽고 디비 연계하여 데이터 받아오기#####################
db=connection.get_database('Menu')
collection=db.get_collection('meal')
result = list(collection.find())

dinner = result[0]['dinner']
breakfast = result[1]['breakfast']
lunch = result[2]['lunch']

print(breakfast, lunch,dinner, sep="\n")
#############################몽고 디비 연계하여 데이터 받아오기#####################
#################################몽고 디비 데이터 삭제하기#########################
collection.remove({"ObjectId":{"$gt":1}})
#################################몽고 디비 데이터 삭제하기#########################