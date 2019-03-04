#include <ros/ros.h>
#include <ros/duration.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <dirent.h>

#include <path_msgs/Lane.h>
#include <path_msgs/Cross.h>
#include <path_msgs/choose.h>

#include <vector>
#include <algorithm>
#include <math.h>
#include <Eigen/Core>
#include <Eigen/Eigen>
#include <tf/transform_datatypes.h>
#include <climits>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include <tf/transform_broadcaster.h>

namespace Vis_Space{
class vis_smartcat{
private:
    ros::Subscriber sub_pose;
    ros::Publisher pub_current_pose;
    visualization_msgs::Marker marker_car;
    std::string topic_current_pose;
    bool is_vis_current_pose;

    ros::Subscriber sub_global_path;
    ros::Publisher pub_global_path;
    nav_msgs::Path global_path;
    std::string topic_global_path;
    bool is_vis_global_path;
    
    void current_pose_cb(const geometry_msgs::PoseStampedConstPtr &pose);
    // void global_path_cb(const nav_msgs::PathConstPtr &path);

    void marker_initial();

public:
    vis_smartcat(){}
    ~vis_smartcat(){}

    void init();

};

}

namespace Vis_Space{
void vis_smartcat::init(){
    ros::NodeHandle pnh("~");
    ros::NodeHandle nh;

    pnh.param<std::string>("topic_current_pose",topic_current_pose,"/ndt/current_pose");
    pnh.param<bool>("vis_current_pose",is_vis_current_pose,true);
    pnh.param<std::string>("topic_global_path",topic_global_path,"global_path");
    pnh.param<bool>("vis_global_path",is_vis_global_path,true);

    marker_initial();

    if(is_vis_current_pose){
        sub_pose = nh.subscribe(topic_current_pose, 1, &Vis_Space::vis_smartcat::current_pose_cb, this);
    }
    
    // sub_global_path = nh.subscribe(topic_global_path, 1, &Vis_Space::vis_smartcat::global_path_cb, this);
 
    pub_current_pose = nh.advertise<visualization_msgs::Marker>("/vis/current_pose",1);
    // pub_global_path = nh.advertise<visualization_msgs::Marker>("/vis/global_path",10);
}


void vis_smartcat::current_pose_cb(const geometry_msgs::PoseStampedConstPtr &pose){
    marker_car.header.stamp = ros::Time::now();
    marker_car.pose.position = pose->pose.position;
    double current_roll, current_yaw, current_pitch;
    tf::Quaternion quat;
    tf::quaternionMsgToTF(pose->pose.orientation, quat);
    tf::Matrix3x3(quat).getRPY(current_roll, current_pitch, current_yaw);
    marker_car.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(90 * (M_PI / 180.0),
                                                                            0 * (M_PI / 180.0),
                                                                            current_yaw + M_PI / 2.0);
    pub_current_pose.publish(marker_car);
}

void vis_smartcat::marker_initial(){
    marker_car.header.frame_id = "map";
    marker_car.header.stamp = ros::Time();
    marker_car.ns = "car";
    marker_car.id = 0;
    marker_car.type = visualization_msgs::Marker::MESH_RESOURCE;
    marker_car.action = visualization_msgs::Marker::ADD;
    // set marker_car.pose.position marker.pose.orientation
    marker_car.color.r = 1;
    // marker_car.color.g = 1;
    // marker_car.color.b = 1;
    marker_car.color.a = 1;
    marker_car.scale.x = 1.0;
    marker_car.scale.y = 1.0;
    marker_car.scale.z = 1.0;
    marker_car.mesh_use_embedded_materials = true;
    marker_car.mesh_resource = "package://car_model/ferrari/dae.DAE";

}

}

int main(int argc,char** argv){
    ros::init(argc,argv,"visualization_node");
    Vis_Space::vis_smartcat app;
    app.init();
    ros::spin();
    return 0;
}