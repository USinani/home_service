#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include "add_markers/DeleteMarker.h"
#include "add_markers/CreateMarker.h"

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

void goToPosition(char* frame_id, float x, float y, float w, MoveBaseClient& ac);

int main(int argc, char** argv){
    // Initialize the pick_objects node
    ros::init(argc, argv, "pick_objects");
    ros::NodeHandle n;

    //tell the action client that we want to spin a thread by default
    MoveBaseClient ac("move_base", true);

    // Wait 5 sec for move_base action server to come up
    while(!ac.waitForServer(ros::Duration(5.0))){
        ROS_INFO("Waiting for the move_base action server to come up");
    }

    char* frame_id = "map";

    ros::ServiceClient dropClient = n.serviceClient<add_markers::CreateMarker>("add_markers/draw_marker");
    ros::ServiceClient pickupClient = n.serviceClient<add_markers::DeleteMarker>("add_markers/delete_marker");

    add_markers::DeleteMarker deleteSrv;
    add_markers::CreateMarker createSrv;

    createSrv.request.id = 0;
    createSrv.request.X = 4.8;
    createSrv.request.Y = -2.7;
    deleteSrv.request.id = 0;

    dropClient.call(createSrv);
    ROS_INFO("Going to the object");
    goToPosition(frame_id , 4.8, -2.7, 1, ac);

    ROS_INFO("Picking object");
    ros::Duration(5.0).sleep();
    pickupClient.call(deleteSrv);

    ROS_INFO("Delivering object");
    createSrv.request.X = 6.5;
    createSrv.request.Y = -1.2;
    goToPosition(frame_id, 6.5, -1.2, 1, ac);
    dropClient.call(createSrv);
    ROS_INFO("Object delivered");

    // Don't exit the program.
    ros::spin();

    return 0;
}

void goToPosition(char* frame_id, float x, float y, float w, MoveBaseClient& ac)
{
    move_base_msgs::MoveBaseGoal goal;

    // set up the frame parameters
    goal.target_pose.header.frame_id = frame_id;
    goal.target_pose.header.stamp = ros::Time::now();

    // Define a position and orientation for the robot to reach
    goal.target_pose.pose.position.x = x;
    goal.target_pose.pose.position.y = y;
    goal.target_pose.pose.orientation.w = w;

    // Send the goal position and orientation for the robot to reach
    ROS_INFO("Sending goal");
    ac.sendGoal(goal);

    // Wait an infinite time for the results
    ac.waitForResult();

    // Check if the robot reached its goal
    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
        ROS_INFO("Goal reached");
    else
        ROS_INFO("The base failed to reach goal");
}