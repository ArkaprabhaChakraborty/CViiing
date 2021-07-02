import cv2 as cv
img = cv.imread("/home/arkaprabha/CViiing/photos/cameron2.jpg")

gray = cv.cvtColor(img,cv.COLOR_BGR2GRAY)

h_cascade = cv.CascadeClassifier("/home/arkaprabha/CViiing/models/cascade.xml")

faces_rect = h_cascade.detectMultiScale(gray, scaleFactor = 1.1,minNeighbors = 6)

print(f"Number of faces = {len(faces_rect)}")

for (x,y,w,h) in faces_rect:
    x = cv.rectangle(img,(x,y),(x+w,y+h),(0,255,0),thickness = 2)

cv.imshow("Detected face",x)
cv.waitKey(0)
