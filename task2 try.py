import cv2
import numpy as np

direction=True


#function to detect color using r g b values
def findcolor(x,y,test_img):
    color="undefined"
    if test_img[y,x][0]>=0 and  test_img[y,x][0]<=50 and test_img[y,x][1]>=0 and  test_img[y,x][1]<=50 and test_img[y,x][2]>=50 and  test_img[y,x][2]<=255:
        color="red"
    elif test_img[y,x][0]>=0 and  test_img[y,x][0]<=150 and test_img[y,x][1]>=160 and  test_img[y,x][1]<=255 and test_img[y,x][2]>=150 and  test_img[y,x][2]<=255:
        color="yellow"
    elif test_img[y,x][0]>=0 and  test_img[y,x][0]<=100 and test_img[y,x][1]>=50 and  test_img[y,x][1]<=255 and test_img[y,x][2]>=0 and  test_img[y,x][2]<=100:
        color="green"
    elif test_img[y,x][0]>=50 and  test_img[y,x][0]<=255 and test_img[y,x][1]>=0 and  test_img[y,x][1]<=100 and test_img[y,x][2]>=0 and  test_img[y,x][2]<=100:
        color="blue"
    else:
        color=" "
    return color
font=cv2.FONT_HERSHEY_COMPLEX #type of font

        




img=cv2.imread('images/test3.png')  #reading image
img=cv2.resize(img,(0,0),fx=0.7,fy=0.7)  #resizing img

# print(img.shape)
rows=img.shape[0]
cols=img.shape[1]

gray=cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)   #convert it to gray

_,thresold=cv2.threshold(gray,240,255,cv2.THRESH_BINARY)
contours,_=cv2.findContours(thresold,cv2.RETR_TREE,cv2.CHAIN_APPROX_NONE)   #find contours

for contour in contours:
    approx=cv2.approxPolyDP(contour,0.01*cv2.arcLength(contour,True),True)    #approx contours
    #cv2.drawContours(img,[approx],0,(0,0,0),1)


    x=approx.ravel()[0]              #find top of shape
    y=approx.ravel()[1]


    M=cv2.moments(contour)
    if M['m00']!=0.0:                  #find centre of shape
        x_centre=int(M['m10']/M['m00'])    
        y_centre=int(M['m01']/M['m00'])


    if len(approx) ==3:        #as it has 3 contours ,the shape is traingle
        #print(approx)
        cv2.putText(img,'traingle',(x,y),font,0.5,(0,0,0),1)
        a=findcolor(x_centre,y_centre,img)
        cv2.putText(img,a,(x_centre,y_centre),font,0.5,(0,0,0),1)

    elif len(approx)==4:          #the shale is square or rectangle
        area=cv2.contourArea(contour)
        print(area)
        if area>133000:
            pass
            #cv2.drawContours(img,[approx],0,(0,0,0),3)
        else:
            x1,y1,w,h=cv2.boundingRect(approx)
            aspectRatio=float(w)/h
            shape="square" if aspectRatio >= 0.95 and aspectRatio <= 1.05 else "rectangle"
            cv2.putText(img,shape,(x,y),font,0.5,(0,0,0),1)
            a=findcolor(x_centre,y_centre,img)
            cv2.putText(img,a,(x_centre,y_centre),font,0.5,(0,0,0),1)

        
        
    
    elif len(approx)==6:
        #cv2.drawContours(img,[approx],0,(0,0,0),3)
        if x==0 and y==0 :
            direction=False
            cv2.putText(img,'Left Direction',(rows//2 -50,30),font,1,(255,0,0),1)
        else:
            direction=False
            cv2.putText(img,'Right Direction',(rows//2 -50,30),font,1,(255,0,0),1)



    else:                    #if else ,the shape is a circle
        cv2.putText(img,'circle',(x,y),font,0.5,(0,0,0),1)
        a=findcolor(x_centre,y_centre,img)
        cv2.putText(img,a,(x_centre,y_centre),font,0.5,(0,0,0),1)


if(direction):
    cv2.putText(img,'Forward Direction',(rows//2 -200,30),font,1,(255,0,0),1)
    print(rows)


cv2.imshow('window',img)      #show image
cv2.waitKey(0)
cv2.destroyAllWindows()







