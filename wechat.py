#coding=utf8
import itchat, time
import xlrd


data = xlrd.open_workbook('outside_students.xlsx')
table = data.sheet_by_index(0)
nrows = table.nrows
print(nrows)
names=[]
for i in range(1,nrows):
    itmes = table.row_values(i)
    if(str(itmes[3])=='是'):
        names.append(str(itmes[1]))

print(names)
print(len(names))


itchat.auto_login(True)

friendList=itchat.get_friends(update=True)[1:]
sexDict={}
nick_names=[]


total=len(friendList)
for friend in friendList:

    nick_names.append(friend['UserName']+' '+friend['NickName']+' '+friend['RemarkName'])

print(nick_names)

send_name=[]
value="hi,这是定向消息，发自^(00)^ 。请填写问卷，请回复： 是 "

for i in names:
    find = False
    for k in nick_names:
        if i in k:
            send_name.append(k)
            find = True
            itchat.send(value, k.split(' ', 1)[0])
            break
    if not find:
        print("not found user:",i)
print(send_name)
print(len(send_name))
