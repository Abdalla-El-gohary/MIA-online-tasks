#!/usr/bin/env python3
from std_msgs.msg import Float32






#initalize state and uncertaintly
x=0   #initial value for the sensor reading(yaw angle)
p=4 #uncertainty state

q=4 #process noise variance
r=4 #measuremeant uncertaintly

def predict(x,p):
    x=x  #predict the state using system dynamic model
    p=p+q  #predict the uncertaintly
    return x,p  

# def measure():
#     z=z[i]
#     return z
def update(x,p,z):
    k= p/(p+r)  #kalman gain
    x= z * k + (1-k)*x
    p =  (1-k)*p
    return x, p



def callback(data):
    rospy.loginfo(rospy.get_caller_id() + "data of imu_node is %f",data.data)
    z=data.data  #data of the sensor(yaw angle)
    x,p=predict(x,p)
    x,p=update(x,p,z)
    pub.publish(x)



import rospy
if __name__ == '__main__':
    rospy.init_node("kalman_filter",anonymous=True)
    pub =rospy.Publisher("topic",Float32,queue_size=10)
    sub= rospy.Subscriber("chatter",Float32,callback)
    rospy.loginfo("subscribe to imu_node")
    rospy.spin()

