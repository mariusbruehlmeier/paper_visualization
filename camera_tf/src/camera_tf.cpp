#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
#include <turtlesim/Pose.h>

int main(int argc, char** argv) {
  ros::init(argc, argv, "my_tf_broadcaster");
  ros::Time::init();

  ros::Rate r(100);
  tf::TransformListener listener;
  while (ros::ok()) {
    tf::StampedTransform transform;
    try {
      listener.lookupTransform("vehicle", "mrh_lidar", ros::Time(0), transform);
      static tf::TransformBroadcaster br_1;
      tf::Transform transform_1;
      transform_1.setOrigin(tf::Vector3(-.05, -.1, .05));
      tf::Quaternion q_1;
      q_1.setRPY(0, 0.28, .078);
      transform_1.setRotation(q_1);
      br_1.sendTransform(tf::StampedTransform(transform_1, ros::Time::now(),
                                              "mrh_lidar", "gopro"));

      static tf::TransformBroadcaster br_2;
      tf::Transform transform_2;
      transform_2.setOrigin(tf::Vector3(0., 0, 0));
      tf::Quaternion q_2;
      q_2.setRPY(-1.57, 0, -1.57);
      transform_2.setRotation(q_2);

      br_2.sendTransform(tf::StampedTransform(transform_2, ros::Time::now(),
                                              "gopro", "gopro_camera"));
    } catch (tf::TransformException ex) {
      ros::Duration(1.0).sleep();
    }
    r.sleep();
  }
  return 0;
};
