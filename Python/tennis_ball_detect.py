#!/usr/bin/python
from statistics import median
import cv2 as cv
import numpy as np
cap = cv.VideoCapture(0)
lower = np.array([(10/179)*255, 37, 60])
upper = np.array([(28/179)*255, 255, 255])

font = cv.FONT_HERSHEY_SIMPLEX
while(True):
    ret, frame = cap.read()
    framec = frame.copy()
    
    framec = cv.GaussianBlur(framec, (9, 9), 39)
    framec = cv.medianBlur(framec, 9,1)
    framec = cv.dilate(framec,(10000,10000),iterations=10)
    hsv = cv.cvtColor(framec, cv.COLOR_BGR2HSV)
    median = cv.inRange(hsv, lower, upper)
    median = cv.erode(median,(100000,100000),iterations=15)
    median = cv.medianBlur(median,9,10)
    median = cv.GaussianBlur(median, (9, 9), 3)

    ret2, thresh = cv.threshold(median, 0, 255, 0)
    contour, hier = cv.findContours(thresh, cv.RETR_TREE, cv.CHAIN_APPROX_SIMPLE)
    radius_highest = 0
    center = (0, 0)
    circles_img = cv.HoughCircles(median,cv.HOUGH_GRADIENT,1.155,30,param1=80,param2=38,minRadius=20,maxRadius=100)
    if circles_img is not None:
        circles_img = np.round(circles_img[0, :]).astype("int")
        for (x,y,r) in circles_img:
            cv.circle(frame,(int(x),int(y)),int(r),(0,255,0),2)
            cv.circle(frame,(int(x),int(y)),2,(0,0,255),3)
            cv.putText(frame, 'Tennis Ball',(int(x-r),int(y+r)), font, 0.5, (0, 255, 0), 2, cv.LINE_AA)
    cv.imshow("frame", frame)
    cv.imshow("mask", median)
    if cv.waitKey(1) & 0xFF == ord('q'):
        break
cap.release()
cv.destroyAllWindows()