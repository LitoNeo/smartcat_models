#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <iostream>

int main(int argc,char** argv){
    ros::init(argc,argv,"load_pcd_file");
    ros::NodeHandle nh("~");
    std::string pcd_file;

    nh.param<std::string>("pcd_file",pcd_file,"please_confirm_pcd_file");

    sensor_msgs::PointCloud2::Ptr msg_input_cloud(new sensor_msgs::PointCloud2);
    pcl::io::loadPCDFile(pcd_file,*msg_input_cloud);
    msg_input_cloud->header.frame_id = "map";

    ros::Publisher pub_map = nh.advertise<sensor_msgs::PointCloud2>("/globalmap/map_for_costmap",1000);
    while(true){
        msg_input_cloud->header.stamp = ros::Time::now();
        pub_map.publish(msg_input_cloud);
        ros::Duration(1.0).sleep();
    }
    return 0;
}