#include <moveit/move_group_interface/move_group.h>
#include <geometry_msgs/Pose.h>

// make a subscriber that listens to the husky_ur5Arm topic. 

move_group_interface::MoveGroup * group;

void ee_mover(const geometry_msgs::Pose pose)
{
   //group->setPoseTarget(pose); 
   group->setApproximateJointValueTarget(pose, "ur5_arm_wrist_3_link");
   ROS_INFO("Received goal pose");
   // specify that our target will be a random one
   //group->setPoseTarget(pose, "ur5_arm_ee_link");
   //group.setRandomTarget();
   //ROS_INFO("Set random target");
   // plan the motion and then move the group to the sampled target 
   while(group->move());
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "move_group_interface_demo", ros::init_options::AnonymousName);
  ros::NodeHandle nh;
  // start a ROS spinning thread
  ros::AsyncSpinner spinner(1);
  spinner.start();
  group = new move_group_interface::MoveGroup("ur5_arm");
  ros::Subscriber sub = nh.subscribe("/husky_ur5Arm", 10, ee_mover);
  ROS_INFO("Subscribed to husky_ur5Arm");
  ROS_INFO("Starting move group..");

  ros::spin();
  //ros::waitForShutdown();

}
