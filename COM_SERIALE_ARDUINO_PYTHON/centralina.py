#!/usr/bin/python
import serial
import time
import struct
import ctypes
import traceback

MAXTEMP = 60
MINVOLT = 40

USBDELAY = 50
receive = 1
global_data = (0, 0, 0)


#***************************** CHECKING INCOMING DATA ****************************
def check_data(data):   
    result = [1, 1, 0]

    if data[0] < MAXTEMP:
        result[0] = 0

    if data[1] > MINVOLT:
        result[1] = 0

    return tuple(result)


#************************* RECEIVING DATA FROM ARDUINO ***************************
def receive_data(ser, STRUCT_VARIABLES, struct_size):
    if ser.in_waiting == 0:
        return 0 
    data = (0, 0, 0)
    try:
        try:
            raw_data = ser.readline(ser.in_waiting)
            buff = ctypes.create_string_buffer(raw_data, struct_size)
            data = struct.unpack(STRUCT_VARIABLES, buff)
            print(data)
            global_data = data
        except ValueError:
            pass
    except serial.serialutil.SerialException:
        print("Connection Error, retrying...")
    
    if 0 in data:
        return 0
    else: 
        return 1


#*************************** SENDING DATA TO ARDUINO ************************
def send_data(ser, STRUCT_VARIABLES):
    result = check_data(global_data)
    packet =  struct.pack(STRUCT_VARIABLES, *result)
    x = ser.write(packet)
    if x == 0:
        return 0 
    if ser.out_waiting == 0:
        return 0

    ser.flush()
    return 1

#********************************** MAIN ***********************************
if __name__ == "__main__":
    port = '/dev/ttyUSB0'
    baudrate = 9600

    ser = serial.Serial(port, baudrate, timeout=5)
    ser.close()
    ser.open()

    STRUCT_VARIABLES = "<BBB"
    struct_size = struct.calcsize(STRUCT_VARIABLES)
    while True:
        if receive:
            ser.flush()
            if receive_data(ser, STRUCT_VARIABLES, struct_size):
                receive = 0
            time.sleep(USBDELAY/1000)
        else:
            if send_data(ser, STRUCT_VARIABLES):
                receive = 1
            time.sleep(USBDELAY/1000)

    ser.close()
