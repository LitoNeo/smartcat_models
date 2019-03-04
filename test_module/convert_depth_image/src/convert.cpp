#include <ros/ros.h>
#include <ros/duration.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types.h>
#include <pcl/conversions.h>
#include <pcl_ros/transforms.h>
#include <pcl_ros/point_cloud.h>
#include <pcl/filters/filter.h>
#include <pcl/common/centroid.h>
#include <pcl/filters/extract_indices.h>
#include <fstream>
#include <string>
#include <iostream>

// using eigen lib
#include <Eigen/Dense>

#include <sensor_msgs/PointCloud2.h>

// namespace Convert_Depth
// {
//   std::string file = "~/Downloads/p3d.txt";
//   void load(const std::string path_file);



// };


int main(int argc, char** argv){
  ros::init(argc,argv,"convert_depth2pc");
  ros::NodeHandle nh;
  ros::Publisher pub_pc = nh.advertise<sensor_msgs::PointCloud2>("converted_pc", 10);
  sensor_msgs::PointCloud2 sensor_pc;
  // pc.header.frame_id = "depth_pc";
  pcl::PointCloud<pcl::PointXYZ> pcl_pc;

  
  std::string file = "/home/sin/Downloads/p3d.txt";
  std::ifstream infile;
  infile.open(file.data());
  assert(infile.is_open());
  std::string s;
  // while(getline(infile,s)){
  //   std::cout << s << std::endl;

  // }
  int cnt = 1;
  while(!infile.eof()){
  // for(int i=0;i<80000;i++){
    pcl::PointXYZ p;
    infile >> p.x;
    infile >> p.y;
    infile >> p.z;
    // std::cout << p.x << " : " << p.y << " : " << p.z << std::endl;
    if(p.x == 0 && p.y == 0 && p.z == 0){
      std::cout << "end at: " << cnt << std::endl;
      break;
    }
    cnt++;
    pcl_pc.push_back(p);
  }

  pcl_pc.header.frame_id = "map";
  std::cout << "size  : " << pcl_pc.size() << std::endl;
  std::cout << "width : " << pcl_pc.width << std::endl;
  std::cout << "height: " << pcl_pc.height << std::endl;
  pcl::toROSMsg(pcl_pc, sensor_pc);

  for(int i=0;i<100;i++){
    std::string in;
    std::cin >> in;
    if(in == "pub"){
      std::cout << "Publish msg" << std::endl;
      pub_pc.publish(sensor_pc);
    }else{
      break;
    }

    ros::Duration(1.0).sleep();
  }

  return 0;

}