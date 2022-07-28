# 使用说明 
CsvPath = input("csv文件路径")
outputPath = input("请输入输出文件名，以.bin结尾")
filepath = outputPath
binfile = open(filepath, 'ab+') #打开二进制文件(追加完成)
array_result = []
blank = ['aa']
list_result = []

new_array = '' #存放新数据
read_file = open(CsvPath)
lines = read_file.readlines()
list_tmp = []



for line in lines:
    line = line.strip().split(',')
    if line:
        list_tmp.append(line[0].split())


for i in range(0, len(list_tmp)):
    if list_tmp[i] == ['EB', '9A' ,'C0' ,'0D' ,'02' ,'00' ,'F9' ,'F9']:
        tmp = []
        for j in range(64):
            tmp = tmp + list_tmp[i + j]
        tmp = tmp[60:508]
        list_result.append(tmp)
array_file = []
for i in range(0,len(list_result)):
    array_file.extend(list_result[i])

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
        content= data_1920[i][j].to_bytes(1, 'big')
        binfile.write(content)
binfile.close()
