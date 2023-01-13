import cv2
import numpy as np
from keras.models import load_model
import serial

import sys
import glob
from time import sleep


def serial_ports():
    """ Lists serial port names

        :raises EnvironmentError:
            On unsupported or unknown platforms
        :returns:
            A list of the serial ports available on the system
    """
    if sys.platform.startswith('win'):
        ports = ['COM%s' % (i + 1) for i in range(256)]
    elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
        # this excludes your current terminal "/dev/tty"
        ports = glob.glob('/dev/tty[A-Za-z]*')
    elif sys.platform.startswith('darwin'):
        ports = glob.glob('/dev/tty.*')
    else:
        raise EnvironmentError('Unsupported platform')

    result = []
    for port in ports:
        try:
            s = serial.Serial(port)
            s.close()
            result.append(port)
        except (OSError, serial.SerialException):
            pass
    return result


if __name__ == '__main__':
    print(serial_ports())
    sleep(2) # waits 2 seconds

    PORT = "COM3" # selected port that we will use for communicating with arduino

    print("[ARDUINO AI] Loading model (it may take some time)...")
    model = load_model('keras_model.h5')
    print("[ARDUINO AI] model loaded successfully")

    print("[ARDUINO AI] opening camera")
    camera = cv2.VideoCapture(0)

    print("[ARDUINO AI] loading labels")
    labels = open('labels.txt', 'r').readlines()

    print("[ARDUINO AI] opening serial communication")
    ser = serial.Serial(PORT)
    ser.baudrate = 9600

    while not camera.isOpened():
        print("[ARDUINO AI]: Error, camera unavailable. Check if other programs are using the camera")
        exit(-1)

    while True:
        ret, image = camera.read() # catches an image from the camera

        if not ret:
            print("[ARDUINO AI]: Error, image is empty. Check if other programs are using the camera")
            exit(-1)
        
        image = cv2.resize(image, (224, 224), interpolation=cv2.INTER_AREA) # Resizes the image into (224-height, 224-width) pixels.

        cv2.imshow('Webcam Image', image) # Shows the image

                                                        # batch - width - height - channels
        image = np.asarray(image, dtype=np.float32).reshape(1, 224, 224, 3) # transforms the image to an np.array of float32 and reshapes it to match the NN input shape

        image = (image / 127.5) - 1 # Normalizes the image array

        # Have the model predict what the current image is. Model.predict
        # returns an array of percentages. Example:[0.2,0.8] meaning its 20% sure
        # it is the first label and 80% sure its the second label.
        probabilities = model.predict(image)

        # Print what the highest value probabilitie label
        print(labels[np.argmax(probabilities)])
        
        # writes the label to arduino through serial
        if np.argmax(probabilities) == 0:
            ser.write(b'0')
        elif np.argmax(probabilities) == 1:
            ser.write(b'1')
        elif np.argmax(probabilities) == 2:
            ser.write(b'2')
        else:
            ser.write(b'255')


        keyboard_input = cv2.waitKey(1) # Listens to the keyboard if it is pressed

        
        if keyboard_input == 27: # 27 is the ASCII for the ESC key on your keyboard.
            print("[ARDUINO AI] quitting")
            break

    camera.release()
    cv2.destroyAllWindows()
    ser.close()