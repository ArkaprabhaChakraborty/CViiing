import cv2 as cv
import copy
import numpy as np
from matplotlib import pyplot as plt

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

def translate(img, x,y):
    # -x -> Left 
    # -y -> Up
    # x -> Right
    # y -> Down
    transMat =  np.float32([[1,0,x],[0,1,y]])
    dimensions = (img.shape[1],img.shape[0])
    return cv.warpAffine(img, transMat, dimensions)

def rotate(img,angle,rotPoint = None,scale=1.0):
    (height,width)= img.shape[:2]
    if (rotPoint is None):
        rotPoint= (width//2,height//2)
    rotmat = cv.getRotationMatrix2D(rotPoint, angle,scale) #third factor is scale here we pass 1.0 as we dont need to scale for rotation
    dimens = (width,height)
    return cv.warpAffine(img,rotmat,dimens)

#basically shows our hot Dr.Cameron magnified/zoomed 50 times
im2 = reframe(img,500)
cv.imshow("image2",im2)

#draw shapes on the image
x = copy.copy(img)
drawshapes(x,10,10,img.shape[0]//2,img.shape[1]//2)

#grayscale
gray = cv.cvtColor(img,cv.COLOR_BGR2GRAY)
cv.imshow("Gray",gray)

# blur 
# gaussian blurr
x = copy.copy(im2)
blurrr = cv.GaussianBlur(x,(41,41),cv.BORDER_DEFAULT)
cv.imshow("Blur",blurrr)
# median blurr
mblur = cv.medianBlur(x,3)
cv.imshow("Median blur",mblur)
# bilateral
bilateral = cv.bilateralFilter(x, 5 ,15,15)
cv.imshow("Bilateral",bilateral)


#edge cascade
canny = cv.Canny(x,90,100)
cv.imshow("canny",canny)

#dilating the image
dilated = cv.dilate(x,(40,40),iterations=5)
cv.imshow("Dilated",dilated)

#eroding the image
eroded = cv.erode(x,(10,10),iterations = 5)
cv.imshow("eroded",eroded)

#translate
translated = translate(x,-100,10)
cv.imshow("Translated",translated)

#rotate
rotated = rotate(x,45)
cv.imshow("Rotated",rotated)

#resize
resized = cv.resize(x,(1000,1000), interpolation = cv.INTER_CUBIC)
cv.imshow("Resized", resized)

#flipping
flip = cv.flip(x,0)
cv.imshow('Flipped',flip)

#thresholding
gray2 =  cv.cvtColor(im2,cv.COLOR_BGR2GRAY)
ret,thresh = cv.threshold(gray2,100,125,cv.THRESH_BINARY)
cv.imshow("Thresholded",thresh)  #produces a really hot image
print(ret)


#contours 
#RETR_LIST = list of all contours
#RETR_EXTERNAL = list of all external contours
#RETR_TREE = list of all heirarchical contours
#Contour approximations
#CHAIN_APPROX_NONE = No approximations
#CHAIN_APPROX_SIMPLE = Compresses all contours into simpler ones(layman explanation)

contours, heirarchies = cv.findContours(thresh,cv.RETR_LIST,cv.CHAIN_APPROX_SIMPLE)
print(f'{len(contours)} contours found')

blank = np.zeros(x.shape[:2],dtype='uint8')
cv.drawContours(blank,contours,-1,(255,0,0),1)
cv.imshow("Contours",blank)


#color spaces
hsv = cv.cvtColor(x, cv.COLOR_BGR2HSV)
cv.imshow("HSV",hsv)

#rgb
rgb = cv.cvtColor(x, cv.COLOR_BGR2RGB)
cv.imshow("RGB",rgb)

#lab
lab = cv.cvtColor(x, cv.COLOR_BGR2LAB)
cv.imshow("LAB",lab)

#color_channels
b,g,r = cv.split(im2)


blank = np.zeros(im2.shape[:2],dtype='uint8')
blue = cv.merge([b,blank,blank])
green = cv.merge([blank,g,blank])
red = cv.merge([blank,blank,r])


cv.imshow("Blue",blue)
cv.imshow("Green",green)
cv.imshow("red",red)

#edge detection
#laplacian
lap  = cv.Laplacian(gray, cv.CV_64F)
lap = np.uint8(np.absolute(lap))
cv.imshow("Laplacian edge",lap)

#sobel
sobelx = cv.Sobel(gray, cv.CV_64F,1,0)
sobely = cv.Sobel(gray, cv.CV_64F,0,1)


cv.imshow("Sobelx gray",sobelx)
cv.imshow("Sobely gray",sobely)



#histogram
#grayscale histogram
gray_hist = cv.calcHist([gray],[0],None,[256],[0,256])
plt.plot(gray_hist)
plt.title("HISTORGRAM")

#color histogram
colors = ('b','g','r')
for i,col in enumerate(colors):
    hist = cv.calcHist([img],[i],None,[256],[0,256])
    plt.plot(hist , color = col)
plt.show()


cv.waitKey(0)