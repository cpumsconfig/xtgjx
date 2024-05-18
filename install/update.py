import os
import requests
from time import sleep
url='http://xtcctvhd.hostfree.asia/1.txt'
res=requests.get(url)
f=open('1.txt', 'wb')
f.write(res.content)
f.close
url_1='http://xtcctvhd.hostfree.asia/2.txt'
res_1=requests.get(url_1)
e=open('2.txt', 'wb')
e.write(res_1.content)
e.close
print("正在加载中......")
sleep(10)
os.system("cls")
print("""欢迎安装系统工具箱
如果想安装的请回车，不想安装的请叉掉
           谢谢""")
os.system("1.txt")
os.system("pause")
os.system("cls")
x=input("是否同意以下协议(Y/N):")
if x==y:
  print("拉取数据中......")
  sleep(10)
  print("正在安装中......")
  y='https://github.com/cpumsconfig/xtgjx/1.zip'
  os.system("download.dll"y)
  os.system("zip.dll 1.zip")
  print("安装完成")
  os.system("pause")
  print("正在清理文件中......")
  os.system("del 1.zip")
  os.system("del 1.txt")
  os.system("del 2.txt")
  os.system("del download.dll")
  os.system("del zip.dll")
  print("完成！")
  break
else:
  break
