#include <ros/ros.h>
#include "add_markers/DeleteMarker.h"
#include "add_markers/CreateMarker.h"
#include <visualization_msgs/Marker.h>

void drawMarker(int id, float pos_x, float pos_y);

ros::Publisher marker_pub;
const char* frame_id = "odom";
uint32_t shape = visualization_msgs::Marker::CYLINDER;

bool delete_request(add_markers::DeleteMarker::Request& req, add_markers::DeleteMarker::Response& res)
{
    int id = req.id;

    visualization_msgs::Marker marker;
    
    // set up the frame parameters
    marker.header.frame_id = frame_id;
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "marker";
    marker.id = id;

    marker.action = visualization_msgs::Marker::DELETE;

    marker_pub.publish(marker);
    ROS_INFO("Deleting Marker");

    res.msg_feedback = "Deleted Marker";
    ROS_INFO_STREAM(res.msg_feedback);

    return true;
}

bool draw_request(add_markers::CreateMarker::Request& req, add_markers::CreateMarker::Response& res)
{
    int id = req.id;
    float x  = req.X;
    float y  = req.Y;

    drawMarker(id, x, y);
    ROS_INFO("Drawing Marker");

    res.msg_feedback = "Marker added";
    ROS_INFO_STREAM(res.msg_feedback);

    return true;
}

int main(int argc, char** argv){
    // Initialize the add_markers node
    ros::init(argc, argv, "add_markers");

    ros::NodeHandle n;
    marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

    ros::ServiceServer createService = n.advertiseService("add_markers/draw_marker", draw_request);
    ros::ServiceServer deleteService = n.advertiseService("add_markers/delete_marker", delete_request);

    ROS_INFO("Ready to handle markers");

    // Don't close the node
    ros::spin();

    return 0;
}

void drawMarker(int id, float pos_x, float pos_y)
{
    visualization_msgs::Marker marker;

    // set up the frame parameters
    marker.header.frame_id = frame_id;
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "marker";
    marker.id = id;

    marker.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    marker.pose.position.x = pos_x;
    marker.pose.position.y = pos_y;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.2;
    marker.scale.y = 0.2;
    marker.scale.z = 0.5;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    // Publish the marker
    if (marker_pub.getNumSubscribers() < 1)
    {
        if(!ros::ok()){
            return;
        }
        ROS_WARN_ONCE("Please create a subscriber to the marker");
        sleep(1);
    }
    marker_pub.publish(marker);
}
