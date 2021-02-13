import serial
import pyrebase

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
    ser = serial.Serial('/dev/ttyACM0',9600,timeout=1)
    ser.flush()

    while True:
        if ser.in_waiting>0:
            line = ser.readline().decode('utf-8').rstrip()
            print(line)
            db.child("HorizontalDistance").set(line)
