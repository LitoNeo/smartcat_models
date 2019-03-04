# convert depth image to pointCloud

Currently, this module is used to convert the depth image to pointCloud.
usages are as followed:
> 1. read in `.txt` file from local-path, which is format at `x y z` in one line
  2. create PCL pointcloud and sensor_msgs/PointCloud2 msg to store these points
  3. TODO:: voxel it

usage:
> 1. configure the site of `.txt` file and its format
  2. run `rosrun convert_depth_image convert_depth_image_node`
  3. launch rviz and show; when the reading process is done, write `pub` in termial to publish PC, or `exit` to exit.