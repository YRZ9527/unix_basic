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
read_file = open('/Users/zong/Code/SLR_Work/DRO/时差20220710.csv',encoding='gbk')
lines = read_file.readlines()

for line in lines:
    line = line.strip().split(',')
    if line:
        list_tmp.append((line[15].replace("-", "")))
        # print(list_tmp)
    # print(line)
# print(list_tmp[2])
# print(list_tmp)
print(list_tmp[0:3])
c = list_tmp.count('EB9AC00D0200F9F9')
print(c)

# print(list_tmp)




# for i in range(0, len(list_tmp)):
#     if list_tmp[i] == 'EB9AC00D0200F9F9':
#         print(1)
#         tmp = ''
#         for j in range(64):
#             tmp = tmp + list_tmp[i + j]
#             print(tmp)
#         tmp = tmp[60:508]
#         print(tmp)
        
#         list_result.append(tmp)
#         # print(list_result)
# print(list_result[0])






# array_file = []
# for i in range(0,len(list_result)):
#     array_file.extend(list_result[i])

# data_1920 = []
# head = ['35','2e','f8','53']
# tail = ['5a','5a','5a','5a']

# array_length = int(len(array_file) / 1920 + 1)
# for i in range(0,len(array_file)):
#     if(i < array_length):
#         tmp = []
#         tmp = array_file[i*1920 : (i+1)*1920]
#         data_1920.append(head + blank * 120 + tmp + tail )
# print(data_1920[1][0:200])

# for i in range(array_length - 1):
#     for j in range(2048):
#         data_1920[i][j] =int(data_1920[i][j],16)
#         content= data_1920[i][j].to_bytes(1, 'big')
#         binfile.write(content)
# binfile.close()

