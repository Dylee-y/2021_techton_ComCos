import serial		
import MySQLdb		

port = serial.Serial("/dev/ttyACM0", "115200")


db = MySQLdb.connect("localhost", "external", "dyn148467^^@", "test1425")
curs = db.cursor()
 
while True:
        try:
            data = port.readline()	 
            print("weight: ")
            print(data)  
 			
            
            curs.execute( "SELECT * FROM cosmetics WHERE 'lip_balm' LIKE %s", [data] )

            db.commit()
 
        except KeyboardInterrupt:
                break
                
port.close()
db.close()