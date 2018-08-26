from selenium import webdriver
from bs4 import BeautifulSoup

# 현재 크롬 위치를 지정 후, 새 크롬창을 띄워준다.
driver = webdriver.Chrome('C:\chromedriver_win32\chromedriver.exe')
# 해당 URL로 이동한다.
driver.get('http://dsm2015.cafe24.com/#/')


html = driver.page_source
soup = BeautifulSoup(html,'lxml')

meal_list = soup.find_all('div',{"class":"meal"})

for i in meal_list:
    print(i.get_text())
    
driver.quit()
