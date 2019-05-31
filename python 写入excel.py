import xlrd
import sys
import xlsxwriter

class Student2:
    def __init__(self,id,country,school,get_check,pes_check):
        self.id=id
        self.country= country
        self.school=school
        self.get_check=get_check
        self.pes_check=pes_check


students={}

# 读取xlsx
table = xlrd.open_workbook('情况摸底.xls').sheet_by_index(0)
nrows = table.nrows
for i in range(1, nrows):
    items = table.row_values(i)
    items[0]=str(items[0])
    student = Student2(items[0],str(items[4]),str(items[5]),str(items[7]),str(items[8]))
    # print(items[0])
    # students.setdefault(items[0], Student(items[0]))
    # student = students[items[0]]
    if items[0] not in students.keys():
        students[items[0]]= student
# print(names)

# for key in students.keys():
#     print(key)
#     print(students[key].pes_check)

# 读取第二个数据表
table2 = xlrd.open_workbook('20190531.xlsx').sheet_by_index(0)
nrows2 = table.nrows
# print(nrows)
nrows2 = 57
names=[]
for i in range(1, nrows2):
    items = table2.row_values(i)
    names.append(str(items[2]))

book = xlsxwriter.Workbook('result.xlsx')
sh = book.add_worksheet('1')

idx = 0
col = 0

def write(s):
	global col
	sh.write(idx, col, s)
	col += 1

#写入数据
write('姓名')
write('出国国家')
write("出国学校")
write("是否获得签证")
write("预计是否获得签证")
write("备注")
for name in names:
    col=0
    idx+=1
    if name in students.keys():
        write(students[name].id)
        write(students[name].country)
        write(students[name].school)
        write(students[name].get_check)
        write(students[name].pes_check)
        write("")
    else:
        write(name)
        write("")
        write("")
        write("")
        write("")
        write("不是出国深造")


book.close()
