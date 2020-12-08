import numpy as np
from tensorflow.keras.models import model_from_json
import operator
import cv2
import serial
import time

json_file = open("model-bw.json", "r")
model_json = json_file.read()
json_file.close()
loaded_model = model_from_json(model_json)
loaded_model.load_weights("model-bw.h5")
print("Loaded model")

ard = serial.Serial('COM3', 9600, timeout=.1)
cap = cv2.VideoCapture(0)

previous=""
current=""

while True:
    _, frame = cap.read()
    frame = cv2.flip(frame, 1)

    x1 = int(0.5*frame.shape[1])
    y1 = 10
    x2 = frame.shape[1]-10
    y2 = int(0.5*frame.shape[1])

    cv2.rectangle(frame, (x1-1, y1-1), (x2+1, y2+1), (255,0,0) ,5)

    roi = frame[y1:y2, x1:x2]

    roi = cv2.resize(roi, (64, 64)) 
    roi = cv2.cvtColor(roi, cv2.COLOR_BGR2GRAY)
    _, test_image = cv2.threshold(roi, 120, 255, cv2.THRESH_BINARY)
    cv2.imshow("test", test_image)
    final_image=test_image.reshape(1, 64, 64, 1)
    result = loaded_model.predict(final_image)

    prediction = {'0': result[0][0],
                  '1': result[0][1],
                  '2': result[0][2],
                  '3': result[0][3],
                  '4': result[0][4],
                  '5': result[0][5]}
    prediction = sorted(prediction.items(), key=operator.itemgetter(1), reverse=True)
    current=prediction[0][0]

    cv2.putText(frame,prediction[0][0], (10, 120), cv2.FONT_HERSHEY_PLAIN, 1, (0,255,255), 1)
    cv2.imshow("Frame", frame)

    interrupt = cv2.waitKey(10)
    if interrupt & 0xFF == 27:
        break
    if interrupt & 0xFF == ord("z"):
        ard.write(current.encode('utf-8'))
        print("sent")

cap.release()
cv2.destroyAllWindows()
