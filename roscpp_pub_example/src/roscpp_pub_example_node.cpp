#include "ros/ros.h"
#include "std_msgs/String.h"

int main(int argc, char ** argv) {
    ros::init(argc, argv, "pub_node");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<std_msgs::String>("chatter", 10);
    ros::Rate loop_rate(10);
    int count = 0;
    while (ros::ok()) {
        std_msgs::String msg;
        msg.data = "Hello World!";
        ROS_INFO("Spin %d", ++count);
        pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}