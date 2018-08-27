from selenium import webdriver
from bs4 import BeautifulSoup
import pymongo

#############################웹 페이지에서 정보 받아오기############################
driver = webdriver.Chrome('C:\chromedriver_win32\chromedriver.exe')
driver.get('http://dsm2015.cafe24.com/#/')

html = driver.page_source
soup = BeautifulSoup(html,'lxml')

meal_list = soup.find_all('div',{"class":"meal"})
driver.quit()
#############################웹 페이지에서 정보 받아오기############################
#############################몽고 디비 연계하여 데이터 입력하기#####################\
key=1

connection = pymongo.MongoClient("localhost", 27017)
db = connection.Menu
collection=db.Breakfast

for i in meal_list[0]:
    collection.insert_one({str(key):str(i.get_text())})
    

#############################몽고 디비 연계하여 데이터 입력하기#####################
