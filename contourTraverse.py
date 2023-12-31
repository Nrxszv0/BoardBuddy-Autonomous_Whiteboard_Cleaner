import cv2
import numpy as np
import time
import math
# image = cv2.imread('ColorfulMichael.png')
camera = cv2.VideoCapture(0)
class Contour:
    def __init__(self, xC, yC, x, y, w, h):
        self.xC = xC
        self.yC = yC
        self.x = x
        self.y = y
        self.w = w
        self.h = h
    def __repr__(self): 
        return "xC:% s yC:% s x:% s y:% s w:% s h:% s" % (self.xC, self.yC,self.x,self.y,self.w,self.h) 
   
# coords = []
def findContours():
    start = time.time()
    while time.time() < start + 5000:
        _, image = camera.read()
        img_gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        ret, thresh = cv2.threshold(img_gray, 100, 255, cv2.THRESH_BINARY)
        cv2.imshow('Binary image', thresh)
        contours, hierarchy = cv2.findContours(image=thresh, mode=cv2.RETR_TREE, method=cv2.CHAIN_APPROX_NONE)

        # draw contours on the original image
        image_copy = image.copy()
        cv2.drawContours(image=image_copy, contours=contours, contourIdx=-1, color=(0, 255, 0), thickness=2, lineType=cv2.LINE_AA)
        # see the results
        cv2.imshow('None approximation', image_copy)
        image_copy2 = image.copy()

        contours1, hierarchy1 = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
        # if len(contours1) > 0:
        #     for contour in contours1:
        #         if cv2.contourArea(contour) > 200:
        #             # print(cv2.contourArea(contour))
        #             # print(str(width) + "\t" + str(height))

        #             x,y,w,h = cv2.boundingRect(contour)
        #             cv2.rectangle(image_copy2, (x,y), (x+w,y+h), (255,0,255), 3)

        # draw contours on the original image for `CHAIN_APPROX_SIMPLE`
        image_copy1 = image.copy()
        cv2.drawContours(image_copy1, contours1, -1, (0, 255, 0), 2, cv2.LINE_AA)
        # see the results

        coords = []
        
        for contour in contours:
            if cv2.contourArea(contour) > 15 and cv2.contourArea(contour) < 100000:
                x,y,w,h = cv2.boundingRect(contour)
                attr = [x,y,w,h]
                
                print(cv2.contourArea(contour))
                cv2.rectangle(image_copy2, (x,y), (x+w,y+h), (0,0,255), 3)
                xC =  int((x+x+w)/2) 
                yC = int((y+y+h)/2)
                cirCenter = xC, yC
                ctr = Contour(xC,yC,x,y,w,h)
                coords.append(ctr)
                BLUE = (255, 0, 0)
                axes = 0, 0
                angle = 0
                cv2.ellipse(image_copy2, cirCenter, axes, angle, 0, 360, BLUE, 20)
        



        cv2.imshow('Simple approximation', image_copy1)
        cv2.imshow('Drawing stuff', image_copy2)




        if cv2.waitKey(5) == ord('x'):
            break
    # cv2.destroyAllWindows()
    return coords

def findClosest(arrayCoords, dCoord):
    if len(arrayCoords) > 1:
        deviceCoord = dCoord
        dist = (arrayCoords[0].xC - deviceCoord[0]) ** 2 + (arrayCoords[0].yC - deviceCoord[1]) **2
        minDist = math.sqrt(dist)
        minCoord = arrayCoords[0]
        for coord in arrayCoords:
            dist = (coord.xC - deviceCoord[0]) ** 2 + (coord.yC - deviceCoord[1]) **2
            dist = math.sqrt(dist)
            if(dist < minDist):
                minDist = dist
                minCoord = coord
        return minCoord
    return dCoord


conts = findContours()
print(conts)

rCoord = [0,0]
closestCont = findClosest(conts,rCoord)
print(closestCont)
while True:
    if cv2.waitKey(5) == ord('x'):
       cv2.destroyAllWindows()
       break