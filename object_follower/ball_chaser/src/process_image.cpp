#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service the robot in the specified direction
void drive_robot(float lin_x, float ang_z){
  // TODO: Request a service and pass the velocities to it to drive the robot

  ROS_INFO_STREAM("Moving the robot to desired position");
  ball_chaser::DriveToTarget srv;
  srv.request.linear_x = lin_x;
  srv.request.angular_z = ang_z;

  // Call the command_robot service and pass the requested velocities
    if (!client.call(srv))
        ROS_ERROR("Failed to call service command_robot");

}

// This callback function continuously extends and reads the image data
void process_image_callback(const sensor_msgs::Image img){
  int white_pixel = 255;
  bool ball_in_image = false;
  float lcr_index = -1;

  // TODO: Loop through each pixel in the image and check if there is a bright white one. 
  // Then, identify if this pixel falls in the left, mid, or right side of the image
  // Depending on the white ball position, call the drive_bot function and pass velocities to it
  // Request a stop when there's no white ball seen by camera

  for (int i = 0; i < img.height * img.step; i++){
    if (img.data[i] == white_pixel){
      ball_in_image = true;
      lcr_index = i % img.step;
      break;
    }  
  }
  // Condition for stop
  float linear_x = 0.0;
  float angular_z = 0.0;
  // Drive left
  if (lcr_index < img.step * 0.3 && lcr_index >= 0){
    angular_z = 0.5;
  }
  // Drive right
  else if(lcr_index > img.step * 0.7){
    angular_z = -0.5;
  }
  // Drive forward
  else if(ball_in_image){
    linear_x = 0.5;
  }

  drive_robot(linear_x, angular_z);
  
  // Publish status of callback
  if (ball_in_image){
    ROS_INFO_STREAM("White ball in image! Moving towards ball.");
  } 
  else {
    ROS_INFO_STREAM("No white ball in image. Stop.");
  }
}

int main(int argc, char** argv){
  // Initialize the process_image node and create a handle to it
  ros::init(argc, argv, "process_image");
  ros::NodeHandle n;

  // Define a client service capable of requesting services from command_robot
  client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

  // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image _callback function
  ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

  // Handle ROS communication events
  ros::spin();

  return 0;
}
