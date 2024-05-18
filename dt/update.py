import os
import requests
print("检查更新中......")
url_1='http://xtcctvhd.hostfree.asia/2.txt'
res_1=requests.get(url_1)
e=res_1.content
a=open("update.txt", 'a')
b=a.read(3)
if a<e
  print("发现新版本！")
  x=input("是否更新？:")
  if x=y:
    print("正在更新中......")
    os.system("download.exe https://github.com/cpumsconfig/update.zip")
    os.system("zip.exe update.zip")
    print("更新成功！")
    os.system("pause")
  else:
    break
else:
   print("已经是最新版本")
   break









