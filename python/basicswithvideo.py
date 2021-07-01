import cv2 as cv

capture = cv.VideoCapture("/home/arkaprabha/CViiing/videos/pexels-polina-tankilevitch-8216948.mp4")
isTrue = True
frame_count = 0

def reframe(frame,scale=0.75):
    width= int(frame.shape[1]*scale)
    height = int(frame.shape[0]*scale)
    dimen = (width,height)
    return cv.resize(frame,dimen,cv.INTER_AREA)



while isTrue:
    isTrue, frame = capture.read()
    cv.imshow("Video",frame)
    #resized_frames
    frame2 = reframe(frame)
    cv.imshow("Video2",frame2)
    #to loop the video
    frame_count = frame_count + 1
    if(frame_count == capture.get(cv.CAP_PROP_FRAME_COUNT)):
        frame_count=0
        capture.set(cv.CAP_PROP_POS_FRAMES,0)
    #exit_key
    if (cv.waitKey(60) & 0xFF == ord('p')):
        break

capture.release()
cv.destroyAllWindows()