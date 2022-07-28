import re
result = []
read_file = open('/Users/zong/Code/SLR_Work/DRO/时差测量数据.csv',encoding='gbk')
writeFile = open('shichadata.csv','a+') 
lines = read_file.readlines()

for line in lines:
    line = line.strip().split(',')
    # print (line)
    ex = line[15].replace("-", "")
    ex = str(ex)
    result.append(ex)
    # print (ex)

    # ex = re.findall(r'.{2}', ex)
    # # tmp = ''
    # # tmp2= '\n'
    # # for i in range(8):
    # #     tmp = tmp + ' ' + ex[i]
    # # writeFile.write(tmp)
    # # writeFile.write(tmp2)
    # # print(ex)
    # # for i in range(0,7):
    # #     print(ex2[i])



# openFile = open('mactest.txt','a+') 
# string = 'EB90-09F3-0000-0077'
# ex = string.replace("-", "")
# ex2 = re.findall(r'.{2}', ex)
# tmp = ''
# for i in range(8):
#     tmp = tmp + ' ' + ex2[i]

# # print(ex)

# # print(ex2)
# openFile.write(tmp)



for i in range(0,len(result)):
    writeFile.write(result[i][0:2] + ' ')
    writeFile.write(result[i][2:4] + ' ')
    writeFile.write(result[i][4:6] + ' ')
    writeFile.write(result[i][6:8] + ' ')
    writeFile.write(result[i][8:10] + ' ')
    writeFile.write(result[i][10:12] + ' ')
    writeFile.write(result[i][12:14] + ' ')
    writeFile.write(result[i][14:16] + ' ')

    writeFile.write('\n')
    # test = re.findall(r'.{2}', result[i])
    # for j in range(0,8):
    #     tmp = ''
    #     tmp = tmp + ' ' + test[i]
        
        
        
    #     writeFile.write(tmp)
    #     writeFile.write('\n')

    





