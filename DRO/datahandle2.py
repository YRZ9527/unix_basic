from hashlib import new
import matplotlib.pyplot as plt
import numpy as np
write_file = open('11.bin','a')
tmp = ''
resTmp = ''
blank = 'aa'
sum = 0
list_tmp = []
arrayRes = []
list_result = []
array_result = []
final_result = []
new_array = '' #存放新数据
read_file = open('/Users/zong/Code/SLR_Work/DRO/20220613-6.csv')
lines = read_file.readlines()
binfile = open('711.bin', 'ab+') #打开二进制文件(追加完成)
for line in lines:
    # print (line.strip().split('A:'))
    # print(line[1])
    line = line.strip().split(',')
    if line:
        list_tmp.append((line[20].replace(" ", "")))
# print(len(list_tmp))
# print(list_tmp[1:100])
# for i in range(0, len(list_tmp)):
# c = list_tmp.count('eb9ac00d0200f9f9')
# print(c)
for i in range(0, len(list_tmp)):
    if list_tmp[i] == 'eb9ac00d0200f9f9':
        for j in range(64):
            tmp = tmp + list_tmp[i + j]
        tmp = tmp[120:1016]
        list_result.append(tmp)


for i in range(0, len(list_result)):
    new_array = new_array + list_result[i]

# print (len(list_result[0]))
# print (len(list_result))




# for i in range(10):
#     new_array = new_array + array_result[i]
# new_array = array_result[0] + array_result[1]
    

# print (len(new_array))
# # print (new_array[0:1919])

for i in range(0,int(len(new_array) / 3840) + 1):
    array_result.append(new_array[i * 3840:(i+1) * 3840])

for i in range(len(array_result)):
    tmp = '352ef853' + blank*120 + array_result[i] + '5a5a5a5a'
    for i in range(1,len(tmp),2):
        twoByte = ''
        twoByte = tmp[i-1:i+1]
        twoByte = int(twoByte,16)
        twoByte = twoByte.to_bytes(1, 'big')
        binfile.write(twoByte)
    # by = bytes(tmp,'UTF-8')    #先将输入的字符串转化成字节码
    # hexstring = by.hex()    #得到16进制字符串，不带0x
    # final_result.append(hexstring) 
    # write_file.write((tmp))
# print(final_result[0])
    
# print(len(final_result[0]))
# print(len(final_result))





           

            