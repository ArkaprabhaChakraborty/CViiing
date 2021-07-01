import cv2 as cv
import copy
img  = cv.imread("/home/arkaprabha/CViiing/photos/cameron.jpeg")
cv.imshow("image",img)

def reframe(frame=None,scale=0.75):
    width= int(frame.shape[1] + scale)
    height = int(frame.shape[0] + scale)
    dimen = (width,height)
    return cv.resize(frame,dimen,cv.INTER_AREA)

def drawshapes(frame,n1,m1,n2,m2):
    cv.rectangle(frame,(n1,m1),(n2,m2),(0,255,0),thickness=2)
    cv.circle(frame,(n2//2,m2 + m2//2),40,(0,0,255),thickness = 3)
    cv.putText(frame,"Didn't meant to put the circle there :)",(0,m2+10),cv.FONT_HERSHEY_TRIPLEX,0.25,(255,255,255),1)
    cv.imshow("Bound",frame)

#basically shows our hot Dr.Cameron magnified/zoomed 500 times
im2 = reframe(img,500)
cv.imshow("image2",im2)

#draw shapes on the image
x = copy.copy(img)
drawshapes(x,10,10,img.shape[0]//2,img.shape[1]//2)

#grayscale
gray = cv.cvtColor(img,cv.COLOR_BGR2GRAY)

#blur (gaussian blurr)
x = copy.copy(im2)
blurrr = cv.GaussianBlur(x,(41,41),cv.BORDER_DEFAULT)
cv.imshow("Blur",blurrr)

#edge cascade
canny = cv.Canny(x,90,100)
cv.imshow("canny",canny)

#dilating the image
dilated = cv.dilate(x,(40,40),iterations=5)
cv.imshow("Dilated",dilated)

#eroding the image
eroded = cv.erode(x,(10,10),iterations = 5)
cv.imshow("eroded",eroded)



cv.imshow("Gray",gray)


cv.waitKey(0)