#!/usr/bin/python
import mariadb
import serial
import sys
#import pymysql

# connect to mariaDB Platform
try:
    conn = mariadb.connect(
        host='localhost',
        user='external',
        password='dyn148467^^@',
        db='test1425',
        charset='utf8'
    )
except mariadb.Error as e:
    print(f"Error connecting to MariaDB Platform: {e}")
    sys.exit(1)
# You ust chose the DB by this code

port = serial.Serial("/dev/ttyACM0", "115200")

'''
conn = mariadb.connect(
    user="db_user",
    password="db_user_passwd",
    host="localhost",
    database="employees")
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
for lip_balm, lip in cur:
    print(f"lip balm: {lip_balm}, tint: {last_name}")
'''
# insert information


while True:
    try:
        data = port.readline()
        print("weight: ")
        print(data)

        cur.execute("INSERT INTO cosmetics2 (lip_balm,test) VALUES (%s, %s)", ("data", "data"))

        #conn.commit()

    except KeyboardInterrupt:
        break

conn.commit()
print(f"Last Inserted ID: {cur.lastrowid}")
port.close()
conn.close()