import requests
from bs4 import BeautifulSoup

URL = "http://dsm2015.cafe24.com/#/"
response = requests.get(URL)

soup = BeautifulSoup(response.text,'lxml')

test=list()
test02=list()

test=soup.find_all('div',{"id":"app"})
for i in test:
    print(i)