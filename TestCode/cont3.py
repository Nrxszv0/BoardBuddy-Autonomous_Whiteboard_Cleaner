import cv2
import numpy as np
import time
import math

def findClosest(arrayDists, rCoord):
    if len(arrayDists) > 1:
        roombaCoord = rCoord
        # print(roombaCoord[0])
        # print(roombaCoord[1])
        # print(arrayDists[0])
        # print(arrayDists[0][0])
        # print(arrayDists[0][1])
        dist = (arrayDists[0][0] - roombaCoord[0]) ** 2 + (arrayDists[0][1] - roombaCoord[1] ) ** 2
        # print(dist)
        minDist = math.sqrt(dist)
        # print(minDist)
        minCoord = arrayDists[0]
        # print(minCoord)
        for coord in arrayDists:
            dist = (coord[0] - roombaCoord[0]) ** 2 + (coord[1] - roombaCoord[1] ) ** 2
            # print(coord)
            # print(dist)
            dist = math.sqrt(dist)
            # print(dist)
            # print("\n\n\n")
            if( dist < minDist):
                minDist = dist
                minCoord = coord
        return minCoord
    return(rCoord)

camera = cv2.VideoCapture(0)
# time.sleep(.5)
while True:
    _, image = camera.read()
    img_gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    ret, thresh = cv2.threshold(img_gray, 100, 255, cv2.THRESH_BINARY)
    # cv2.imshow('Binary image', thresh)
    contours, hierarchy = cv2.findContours(image=thresh, mode=cv2.RETR_TREE, method=cv2.CHAIN_APPROX_NONE)
    # draw contours on the original image
    image_copy = image.copy()
    cv2.drawContours(image=image_copy, contours=contours, contourIdx=-1, color=(0, 255, 0), thickness=2, lineType=cv2.LINE_AA)
    # see the results
    image_copy2 = image.copy()
    image_copy3 = image.copy()


    
    hsv = cv2.cvtColor(image,cv2.COLOR_BGR2HSV)

    color = np.uint8([[[0, 0, 255]]]) #here insert the bgr values which you want to convert to hsv
    hsvColor = cv2.cvtColor(color, cv2.COLOR_BGR2HSV)

    lower_range = hsvColor[0][0][0] - 150, 100, 100
    upper_range = hsvColor[0][0][0] + 150, 100, 100

    lower_range = np.array([hsvColor[0][0][0] - 10, 100, 100])
    upper_range = np.array([hsvColor[0][0][0] + 10, 100, 100])

    lower_range = np.array([159, 50, 70])  
    upper_range = np.array([180, 255, 255])

    mask = cv2.inRange(hsv, lower_range, upper_range)
    mask = cv2.erode(mask, None, iterations=2)
    mask = cv2.dilate(mask, None, iterations=2)

    contours2, hierarchy2 = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    if len(contours2) > 0:
        for contour in contours2:
            if cv2.contourArea(contour) > 0:
                # print(cv2.contourArea(contour))
                # print(str(width) + "\t" + str(height))

                x,y,w,h = cv2.boundingRect(contour)
                cv2.rectangle(image_copy3, (x,y), (x+w,y+h), (255,0,255), 3)


   

    coords = []
    for contour in contours:
        if cv2.contourArea(contour) > 200:
            x,y,w,h = cv2.boundingRect(contour)
            cv2.rectangle(image_copy2, (x,y), (x+w,y+h), (0,0,255), 3)
            coorX =  int((x+x+w)/2) 
            coorY = int((y+y+h)/2)
            cirCenter = coorX, coorY
            coords.append([coorX,coorY])
            BLUE = (255, 0, 0)
            axes = 0, 0
            angle = 0
            cv2.ellipse(image_copy2, cirCenter, axes, angle, 0, 360, BLUE, 20)
    # image_copy5 = image.copy()
    print(coords)
    print("\n\n")
    while len(coords) > 1:
        image_copy5 = image.copy()

        roombaCoord = [0,200]
        
        axes = 0, 0
        angle = 0
        cv2.ellipse(image_copy5, (roombaCoord[0],roombaCoord[1]), axes, angle, 0, 360, (0,255,255), 20)
        
        closestContour = findClosest(coords,roombaCoord)
        cv2.ellipse(image_copy5, (closestContour[0],closestContour[1]), axes, angle, 0, 360, (0,255,255), 30)
        cv2.line(image_copy5, (roombaCoord[0],roombaCoord[1]), (closestContour[0],closestContour[1]), (255,255,0),5)
        
        if(closestContour != roombaCoord):
            roombaCoordx = closestContour[0] - roombaCoord[0]  
            roombaCoordy = closestContour[1] - roombaCoord[1]
            if roombaCoordx > 0:
                for i in range(0,roombaCoordx,1):
                    roombaCoord[0] +=1
                    print(roombaCoord)
                    # cv2.line(image_copy4, (roombaCoord[0],roombaCoord[1]), (closestContour[0],closestContour[1]), (255,255,0),5)
                    # cv2.ellipse(image_copy4, (roombaCoord[0],roombaCoord[1]), axes, angle, 0, 360, (0,255,255), 20)


                    # cv2.imshow('Lines', image_copy4)
                    # time.sleep(.005)
            elif roombaCoordx < 0:
                for i in range(roombaCoordx,0,-1):
                    roombaCoord[0] -=1
                    print(roombaCoord)
            if roombaCoordy > 0:
                for i in range(0,roombaCoordy,1):
                    roombaCoord[1] +=1
                    print(roombaCoord)
                    # cv2.line(image_copy4, (roombaCoord[0],roombaCoord[1]), (closestContour[0],closestContour[1]), (255,255,0),5)
                    # cv2.ellipse(image_copy4, (roombaCoord[0],roombaCoord[1]), axes, angle, 0, 360, (0,255,255), 20)


                    # cv2.imshow('Lines', image_copy4)
                    # time.sleep(.005)
            elif roombaCoordy < 0:
                for i in range(roombaCoordy,0,-1):
                    roombaCoord[1] -=1
                    print(roombaCoord)
        print("coords\n")
        print(roombaCoord)
        print(closestContour)
        coords.remove(closestContour)
        print("Going to next contour" + "\n\n\n")
        cv2.imshow('Lines', image_copy5)
        # time.sleep(.001)

        # cv2.ellipse(image_copy2, (roombaCoord[0],roombaCoord[1]), axes, angle, 0, 360, (0,255,255), 20)
        

    
    # time.sleep(1)
    # cv2.imshow('None approximation', image_copy)
    # cv2.imshow('Countours in recs', image_copy2)
    # cv2.imshow('Certain Colors', image_copy3)







    if cv2.waitKey(5) == ord('x'):
        break
cv2.destroyAllWindows()



color_dict_HSV = {'black': [[180, 255, 30], [0, 0, 0]],
              'white': [[180, 18, 255], [0, 0, 231]],
              'red1': [[180, 255, 255], [159, 50, 70]],
              'red2': [[9, 255, 255], [0, 50, 70]],
              'green': [[89, 255, 255], [36, 50, 70]],
              'blue': [[128, 255, 255], [90, 50, 70]],
              'yellow': [[35, 255, 255], [25, 50, 70]],
              'purple': [[158, 255, 255], [129, 50, 70]],
              'orange': [[24, 255, 255], [10, 50, 70]],
              'gray': [[180, 18, 230], [0, 0, 40]]}