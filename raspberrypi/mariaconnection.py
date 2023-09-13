import pymysql

db = pymysql.connect(host='localhost', user='root', password='8467', 
db = 'test1425', charset='utf8')
cur = db.cursor()
cur.execute("SELECT*FROM cosmetics2")
rows = cur.fetchall()
print(rows)
db.close()