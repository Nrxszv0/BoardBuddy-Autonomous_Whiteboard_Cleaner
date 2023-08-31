import cv2
import numpy as np

image = cv2.imread('ColorfulMichael.png')
camera = cv2.VideoCapture(0)

while True:
    _, image1 = camera.read()
    


    # image1 = cv2.imread('ColorfulMichael.png')
    img_gray1 = cv2.cvtColor(image1, cv2.COLOR_BGR2GRAY)
    ret, thresh1 = cv2.threshold(img_gray1, 150, 255, cv2.THRESH_BINARY)
    contours2, hierarchy2 = cv2.findContours(thresh1, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    image_copy2 = image1.copy()
    cv2.drawContours(image_copy2, contours2, -1, (0, 255, 0), 2, cv2.LINE_AA)
    cv2.imshow('SIMPLE Approximation contours', image_copy2)

    image_copy3 = image1.copy()
    for i, contour in enumerate(contours2): # loop over one contour area
        for j, contour_point in enumerate(contour): # loop over the points
            # draw a circle on the current contour coordinate
            cv2.circle(image_copy3, ((contour_point[0][0], contour_point[0][1])), 2, (0, 255, 0), 2, cv2.LINE_AA)
# see the results
    cv2.imshow('CHAIN_APPROX_SIMPLE Point only', image_copy3)



    if cv2.waitKey(5) == ord('x'):
        break
cv2.destroyAllWindows()