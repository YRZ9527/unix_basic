# -*- coding: utf-8 -*-
# 生成文件夹中所有文件的路径到txt
import os
def listdir(path, list_name):  # 传入存储的list
    for file in os.listdir(path):
        file_path = os.path.join(path, file)
        if os.path.isdir(file_path):
            listdir(file_path, list_name)
        else:
            list_name.append(file_path)
 
list_name=[]

path='/Users/zong/Code/unix/temp/data'   #文件夹路径
listdir(path,list_name)
# print(list_name)
 
def file_handler(filePath):
    fr = open(filePath, 'rt')
    next(fr)
    fw = open('data_nex.txt', 'a+')
    ls = []
 
    for line in fr:
        line = line.replace('\n', '')  # 删除每行后面的换行符
        line = line.split(' ')  # 将每行数据以逗号切割成单个字符
        ls.append(line)  # 将单个字符追加到列表ls中
 
    for row in ls:
        fw.write(' '.join(row) + '\n')
 
    fr.close()
    ls.clear()
    fw.close()


# for filename in list_name:
#     # file_handler(filename)
#     # print(filename)
#     file_handler(filename)
head = open('data_nex.txt', 'a')
head.write('WRITE_TIME,GROUP_ID,DEVICE_TYPE,DEVICE_ID,CHANNEL_ID,CAN/CANFD,CAN_FD_FLAG,TX/RX,TX_TYPE,RX_TIMESTAMP,SYS_MS,RESERVED,PAD(HEX),MAKE_CAN_ID(HEX),FORMAT,FRAME_TYPE,DLC,__PAD,__RES0,__RES1,DATA(HEX)')
head.close()
for filename in list_name:
    # file_handler(filename)
    # print(filename)
    file_handler(filename)
