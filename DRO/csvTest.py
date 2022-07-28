from hashlib import new
import matplotlib.pyplot as plt
import numpy as np
write_file = open('11.bin','a')
tmp = ''
resTmp = ''
blank = 'aa'
sum = 0
# filename = input("请输入文件路径，相对路径或者绝对路径\n")
list_tmp = []
arrayRes = []
list_result = []
array_result = []
final_result = []
new_array = '' #存放新数据
read_file = open('/Users/zong/Code/SLR_Work/DRO/20220629-13 2.csv')
lines = read_file.readlines()

for line in lines:
    # print (line.strip().split('A:'))
    # print(line[1])
    line = line.strip().split(',')
    if line:
        # list_tmp.append((line[20].replace(" ", "")))
        list_tmp.append(line[20].split())
        print(list_tmp)
