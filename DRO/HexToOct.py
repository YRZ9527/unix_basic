
# import re 
# openFile = open('mac.txt','r') 
# lines = openFile.readlines() 
# # print(a)
# for line in lines: 
#     line = line.strip().split(',')
#     if line:
#         line = line.replace("-", " ")
#         b=re.findall(r'.{2}',line)
#         c=' '.join(b) 


#     #  b=re.findall(r'.{2}',aa) 
#     #  c=' '.join(b) 
#     print(c) 
# openFile.close()


# # lines = read_file.readlines()

# # for line in lines:
# #     line = line.strip().split(',')
# #     if line:
# #         list_tmp.append((line[15].replace("-", "")))
# #         # print(list_tmp)
# #     # print(line)
# # # print(list_tmp[2])
# # # print(list_tmp)
# # print(list_tmp[0:3])

import re 
A = open('mac.txt','r') 
a = A.readlines() 
for aa in a: 
    b=re.findall(r'.{2}',aa) 
    c=' '.join(b) 
    print(c)
A.close()

def cut_text(text,lenth): 
 textArr = re.findall('.{'+str(lenth)+'}', text) 
 textArr.append(text[(len(textArr)*lenth):]) 
 return textArr 
