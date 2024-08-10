import cv2
import numpy as np
import serial
import time

ser = serial.Serial('/dev/ttyUSB0', 115200)
ser.flush()

cap = cv2.VideoCapture(0)

try:
    while True:
        ret, frame = cap.read()
        if not ret:
            print("Error: Failed to capture image.")
            break

        frame = cv2.resize(frame, (600, 400))
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

        lower_bound = np.array([109, 46, 37])
        upper_bound = np.array([121, 200, 214])
        mask = cv2.inRange(hsv, lower_bound, upper_bound)
        result = cv2.bitwise_and(frame, frame, mask=mask)

        _, mask = cv2.threshold(mask, 127, 255, cv2.THRESH_BINARY)
        cv2.imshow("original", frame)
        cv2.imshow("Result", result_rgb)
        cv2.imshow("Mask", mask)

        if np.sum(mask) > 1000:
            ser.write(b'1')
            print('1')
        else:
            ser.write(b'0')
            print('0')

        time.sleep(1)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

finally:
    cap.release()
    cv2.destroyAllWindows()
