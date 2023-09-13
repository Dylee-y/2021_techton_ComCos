#!/usr/bin/python
#import mariadb
import time
import serial
import sys
import pymysql

port = serial.Serial("/dev/ttyACM0", "115200")
conn = pymysql.connect(
        host='localhost',
        user='external',
        password='dyn148467^^@',
        db='test1425',
        charset='utf8'
    )
'''
# connect to mariaDB Platform
try:
    conn = pymysql.connect(
        host='localhost',
        user='external',
        password='dyn148467^^@',
        db='test1425',
        charset='utf8'
    )
except mariadb.Error as e:
    print(f"Error connecting to MariaDB Platform: {e}")
    sys.exit(1)
# You must chose the DB by this code
'''

# Get Cursor
# The cursor provides you with an interface for interacting with the Server,
# such as running SQL queries and managing transactions.
cur = conn.cursor()

'''
# retrieving information from DB
some_name = "Georgi"
cur.execute("SELECT first_name,last_name FROM employees WHERE first_name=?", (some_name,))

# Print Result-set
for lip_balm, lip in cur: # for column in cur
    print(f"lip balm: {lip_balm}, tint: {last_name}") 
'''
# insert information


while True:
    try:
        data1 = port.readline()
        data2 = port.readline()
        date = time.localtime()
        # date = time.strftime("%Y-%m-%d %H: %M: %S", time.localtime())

        print("weight1: %sweight2:  %s" % (data1.decode('utf-8'), data2.decode('utf-8')))
        cur.execute("INSERT INTO cosmetics2 (dt_create,lip_balm,tint) VALUES (%s, %s, %s)", (date, data1, data2))
	#cur.execute(sql, ('cosmetics2',time.strftime("%Y-%m-%d %H: %M: %S", time.localtime()), lip_balm, tint))
        #conn.commit()

    except KeyboardInterrupt:
        break

conn.commit()
print(f"Last Inserted ID: {cur.lastrowid}")
port.close()
conn.close()