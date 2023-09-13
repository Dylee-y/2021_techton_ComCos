import serial  #module to modify serial communication via python
import MySQLdb   #module to modify DB via python

# set serial communication environment
# "/dev/ttyACMO" means the communication port with arduino
# make sure to check yours because it might not be the same
port = serial.Serial("/dev/ttyACMO", "115200")

# set the DB access environment
db = MySQLdb.connect("localhost","root","8467","cosmetics")
curs = db.cursor()

while True:
try:
data = port.readline()  #save the value which was read from the serial port to the variable named data

print("weight: ")
print(data)

# save the value   to the DB
# form: """INSERT INTO tablename (column name) VALUES (type of data)""",  (data to save)
curs.execute("""INSERT INTO cosmetics (lip_balm) VALUES (float)""", (data))
db.commit


except KeyboardInterrupt:
break

port.close()
db.close()
