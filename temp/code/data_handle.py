import os
def readname():
    filepath = 'temp/data'
    name = os.listdir(filepath)

    return name
def file_handler(filePath):
    fr = open(filePath, 'rt')
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

name = readname();
for filename in name:
    # file_handler(filename)
    # print(filename)
    file_handler('temp/data/' + filename)
