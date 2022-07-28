from hashlib import new
import matplotlib.pyplot as plt
import numpy as np
write_file = open('3.bin','ab+')
tmp = ''
resTmp = ''
blank = '11'
sum = 0
# filename = input("请输入文件路径，相对路径或者绝对路径\n")
list_tmp = []
arrayRes = []
list_result = []
array_result = []
final_result = []
new_array = '' #存放新数据
read_file = open('/Users/zong/Code/SLR_Work/DRO/data2.csv')
lines = read_file.readlines()

for line in lines:
    # print (line.strip().split('A:'))
    # print(line[1])
    line = line.strip().split(',')
    if line:
        list_tmp.append(line[20].replace(" ", ""))
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

print (len(list_result[0]))
print (len(list_result))


# for i in range(0, len(list_result),5):
#         for j in range(5):
#             if(i + j < len(list_result)):
#                 resTmp = resTmp + list_result[i + j]
#                 # arrayRes = '352ef853' + blank*120 + resTmp
#                 arrayRes =  resTmp
#         array_result.append(arrayRes)
# # 得到2240个字节


# for i in range(10):
#     new_array = new_array + array_result[i]
# new_array = array_result[0] + array_result[1]
    

# print (len(new_array))
# # print (new_array[0:1919])

for i in range(0,int(len(new_array) / 3840) + 1):
    array_result.append(new_array[i * 3840:(i+1) * 3840])
    # print(new_array)
# print (len(array_result[]))



for i in range(len(array_result)):
    final_result.append('352ef853' + blank*120 + array_result[i] + '5a5a5a5a') 
    write_file.write((hex(final_result[i])).to_bytes(512, 'big'))
    
print(len(final_result[0]))
print(len(final_result))
print(final_result[0])
    





           

            