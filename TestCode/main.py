import cv2
import numpy as np

camera = cv2.VideoCapture(0)

while True:
    _, frame = camera.read()


    laplacian = cv2.Laplacian(frame, cv2.CV_64F)
    laplacian = np.uint8(laplacian)
    cv2.imshow('Laplacian', laplacian)

    edges = cv2.Canny(frame, 250,250)
    cv2.imshow('Canny', edges)

    hsv = cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    lower_range = np.array([0, 0, 0])
    upper_range = np.array([255, 255, 255])

    mask = cv2.inRange(hsv, lower_range, upper_range)
    mask = cv2.erode(mask, None, iterations=2)
    mask = cv2.dilate(mask, None, iterations=2)

    contours, hierarchy = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    if len(contours) > 0:
        for contour in contours:
            if cv2.contourArea(contour) > 200:
                print(cv2.contourArea(contour))
              

                x,y,w,h = cv2.boundingRect(contour)
                print("X: " , x , "\tY: ", y, "\tW: " , w ,"\tH: ", h)
                cv2.rectangle(frame, (x,y), (x+w,y+h), (0,0,255), 3)



    cv2.imshow('Camera', frame)
    

    if cv2.waitKey(5) == ord('x'):
        break


camera.release()
cv2.destroyAllWindows()