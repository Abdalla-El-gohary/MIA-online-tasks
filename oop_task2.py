import cv2
import numpy as np

class image:           
    def __init__(self,img) -> None:
        pass
        self.img=cv2.resize(img,(0,0),fx=0.7,fy=0.7)
        self.orginal_img=cv2.resize(img,(0,0),fx=0.7,fy=0.7)
        #self.img=cv2.resize(self.img_1,(0,0),fx=0.7,fy=0.7)  #resizing img
        self.gray=cv2.cvtColor(self.img,cv2.COLOR_BGR2GRAY)
        _,self.thresold=cv2.threshold(self.gray,240,255,cv2.THRESH_BINARY)
        self.contours,_=cv2.findContours(self.thresold,cv2.RETR_TREE,cv2.CHAIN_APPROX_NONE)   #find contours
        self.font=cv2.FONT_HERSHEY_COMPLEX #type of font
        self.rows=self.img.shape[0]
        self.cols=self.img.shape[1]

    
    def detectShape(self):      #function to detect shapes at the image

        for contour in self.contours:
            approx=cv2.approxPolyDP(contour,0.01*cv2.arcLength(contour,True),True)    #approx contours
            #cv2.drawContours(img,[approx],0,(0,0,0),1)

            x=approx.ravel()[0]              #find top of shape
            y=approx.ravel()[1]

            if len(approx) ==3:        #as it has 3 contours ,the shape is traingle
                #print(approx)
                cv2.putText(self.img,'traingle',(x,y),self.font,0.5,(0,0,0),1)


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
                    cv2.putText(self.img,shape,(x,y),self.font,0.5,(0,0,0),1)

                
                
            
            elif len(approx)==6:
                #cv2.drawContours(img,[approx],0,(0,0,0),3)
                pass



            else:                    #if else ,the shape is a circle
                cv2.putText(self.img,'circle',(x,y),self.font,0.5,(0,0,0),1)


    def detectColor(self):      #function to detect color at the image
        for contour in self.contours:
            approx=cv2.approxPolyDP(contour,0.01*cv2.arcLength(contour,True),True)    #approx contours
            M=cv2.moments(contour)
            if M['m00']!=0.0:                  #find centre of shape
                x=int(M['m10']/M['m00'])    
                y=int(M['m01']/M['m00'])

            color="undefined"
            if self.img[y,x][0]>=0 and  self.img[y,x][0]<=50 and self.img[y,x][1]>=0 and  self.img[y,x][1]<=50 and self.img[y,x][2]>=50 and  self.img[y,x][2]<=255:
                color="red"
                cv2.putText(self.img,color,(x,y),self.font,0.5,(0,0,0),1)
            elif self.img[y,x][0]>=0 and  self.img[y,x][0]<=150 and self.img[y,x][1]>=160 and  self.img[y,x][1]<=255 and self.img[y,x][2]>=150 and  self.img[y,x][2]<=255:
                color="yellow"
                cv2.putText(self.img,color,(x,y),self.font,0.5,(0,0,0),1)
            elif self.img[y,x][0]>=0 and  self.img[y,x][0]<=100 and self.img[y,x][1]>=50 and  self.img[y,x][1]<=255 and self.img[y,x][2]>=0 and  self.img[y,x][2]<=100:
                color="green"
                cv2.putText(self.img,color,(x,y),self.font,0.5,(0,0,0),1)
            elif self.img[y,x][0]>=50 and  self.img[y,x][0]<=255 and self.img[y,x][1]>=0 and  self.img[y,x][1]<=100 and self.img[y,x][2]>=0 and  self.img[y,x][2]<=100:
                color="blue"
                cv2.putText(self.img,color,(x,y),self.font,0.5,(0,0,0),1)
            else:
                color=" "

    def detectDirection(self): #function to detect the street direction
        direction="undefined"
        for i in range (0,self.rows,1):
            if self.orginal_img[i,0][0]<50 and self.orginal_img[i,0][1]<50 and self.orginal_img[i,0][2]<50:
                cv2.putText(self.img,'left direction',(0,i+29),self.font,2,(255,0,0),2)
                print(i,0)
                direction="left"
                break
        if(direction=="undefined"):
            for i in range (0,self.rows,1):
                if self.orginal_img[i,self.cols-1][0]<50 and self.orginal_img[i,self.cols-1][1]<50 and self.orginal_img[i,self.cols-1][2]<50:
                    cv2.putText(self.img,'right direction',(self.rows//2 +50,i+25),self.font,2,(255,0,0),2)
                    print(i,self.cols-1)
                    direction="right"
                    break
        if(direction=="undefined"):
            cv2.putText(self.img,'forward direction',(100 ,30),self.font,1,(255,0,0),1)

    def getOriginal(self):   #show the orginal image
        cv2.imshow('window',self.orginal_img)      #show image
        cv2.waitKey(0)
        cv2.destroyAllWindows()
    def getCurrentImg(self):  #show img after editing
        cv2.imshow('window',self.img)      #show image
        cv2.waitKey(0)
        cv2.destroyAllWindows()
    

img=image(cv2.imread('images/test3.png'))   #you should pass the path of your img
img.detectShape()
img.detectColor()
img.detectDirection()
#img.getOriginal()
img.getCurrentImg()