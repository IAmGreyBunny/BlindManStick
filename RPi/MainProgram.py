import serial
import pyrebase
import time

#firebase config
firebaseConfig = {
    "apiKey": "AIzaSyAhOlzeYhZ0r33e30PjYmkpHQph9D56HhM",
    "authDomain": "blindmanstick-53d92.firebaseapp.com",
    "databaseURL": "https://blindmanstick-53d92-default-rtdb.firebaseio.com",
    "projectId": "blindmanstick-53d92",
    "storageBucket": "blindmanstick-53d92.appspot.com",
    "messagingSenderId": "1015829312152",
    "appId": "1:1015829312152:web:a6d8258359f8b2cc30d6ed",
    "measurementId": "G-MRYLG4RHZC"
  };

#firebase initialisation
firebase = pyrebase.initialize_app(firebaseConfig)

#create firebase database object
db=firebase.database()

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM1',115200,timeout=1)
    ser.flush()

    while True:
        ser.flush()
        if ser.in_waiting>0:
            line = ser.readline().decode('utf-8').rstrip()
            line = line.split(",")
            print(line)
            if(line[0]=="Data"):
                db.child("Data").child("HorizontalDistance").set(line[1])
                db.child("Data").child("VerticalDistance").set(line[2])
            ser.write(b"Setting\n")
            time.sleep(1)
            
