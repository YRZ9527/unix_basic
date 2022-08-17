import struct
import os
from hashlib import new
import matplotlib.pyplot as plt
import numpy as np
# write_file = open('17.bin','ab+')
array_result = []

resTmp = ''
blank = ['aa']
list_result = []
sum = 0
list_tmp = []

new_array = '' #存放新数据
read_file = open('/Users/zong/Code/SLR_Work/DRO/20220630-10.csv')
lines = read_file.readlines()


def WriteFile(data):
    filepath='16.bin'
    content= data.to_bytes(1, 'big')
    binfile = open(filepath, 'ab+') #打开二进制文件(追加完成)
    # a = struct.pack('B',data)
    binfile.write(content)
    binfile.close()

for line in lines:
    line = line.strip().split(',')
    if line:
        # list_tmp.append(hex(line[20].replace(" ", "")))
        list_tmp.append(line[20].split())
print(len(list_tmp))


for i in range(0, len(list_tmp)):
    if list_tmp[i] == ['eb', '9a' ,'c0' ,'0d' ,'02' ,'00' ,'f9' ,'f9']:
        tmp = []
        for j in range(64):
            tmp = tmp + list_tmp[i + j]
        tmp = tmp[60:508]
        # list_result += tmp
        list_result.append(tmp)
# print(len(list_result))
print(list_result[0])
print(len((list_result[2])))
array_file = []
for i in range(0,len(list_result)):
    array_file.extend(list_result[i])
print(len(array_file))
print(type(array_file))


data_1920 = []
head = ['35','2e','f8','53']
tail = ['5a','5a','5a','5a']

array_length = int(len(array_file) / 1920 + 1)
for i in range(0,len(array_file)):
    if(i < array_length):
        tmp = []
        tmp = array_file[i*1920 : (i+1)*1920]
        data_1920.append(head + blank * 120 + tmp + tail )
# print(data_1920[1][0:200])

for i in range(array_length - 1):
    for j in range(2048):
        data_1920[i][j] =int(data_1920[i][j],16)
        # data_1920[i][j] =hex(data_1920[i][j])
        WriteFile(data_1920[i][j])

    
# print((data_1920[0]))


# # for i in range(0, int((len(data_1920) / 1920) + 1)):
# #     tmp = ['35','2e','f8','53']
# #     # tmp.extend(array_file)
# #     tmp = tmp + data_1920[i]


#     tmp.extend(['5a','5a','5a','5a'])
# print(len(tmp))
# print(tmp)

    
#     array_result.extend(list_result[i])
# print(array_result[0])




# for i in range(0,int(len(new_array) / 3840) + 1):
#     array_result.append(new_array[i * 3840:(i+1) * 3840])
#     # print(new_array)
# # print (len(array_result[]))



# for i in range(len(array_result)):
#     tmp = '352ef853' + blank*120 + array_result[i] + '5a5a5a5a'

#     by = bytes(tmp,'UTF-8')    #先将输入的字符串转化成字节码
#     hexstring = by.hex()    #得到16进制字符串，不带0x
#     final_result.append(hexstring) 
#     # write_file.write((final_result[i]))
# print(final_result[0])

# for i in range(len(data_1920)):
#     da


# test[0] =int(test[0],16)
# print(test[1])


# WriteFile()