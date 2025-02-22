///////////////////////////////////////////////////////////////////////////////
//
//  Original System: Collaborative Robot Programming Interface
//  Subsystem:       Robot Interface
//  Workfile:        Robotiq.h
//  Revision:        1.0 - 13 March, 2014
//  Author:          J. Marvel
//
//  Description
//  ===========
//  Robotiq interface declarations.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef crpi_robotIQ_H
#define crpi_robotIQ_H

#include "crpi.h"
#include <bitset>

#ifdef WIN32
#include "ulapi.h"
#else
#include "../ulapi/src/ulapi.h"
#endif

#include <time.h>

using namespace std;

namespace crpi_robot 
{
  enum parameter
  {
    ACTIVATE=1,
    GRIP=2,
    MOVE=3,
    AUTO_RELEASE=4,
    AUTO_CENTER=5,
    ADVANCED_CONTROL=6,
    SCISSOR_CONTROL=7
  };

  //! @ingroup crpi_robot
  //!
  //! @brief CRPI interface for the Robotiq robotic hand
  //!
  class LIBRARY_API CrpiRobotiq
  {
  public:
    //! @brief Default constructor
    //!
    //! @param params Configuration parameters for the CRPI instance of this robot
    //!
    CrpiRobotiq (CrpiRobotParams &params);

    //! @brief Default destructor
    //!
    ~CrpiRobotiq ();

    //! @brief Apply a Cartesian Force/Torque at the TCP, expressed in robot base coordinate system
    //!
    //! @param robotForceTorque are the Cartesian command forces and torques applied at the end-effector
    //!        activeAxes is used to toggle which axes will be slated for active force control. TRUE = ACTIVE, FALSE = INACTIVE
    //!       manipulator is used to toggle which manipulators will be slated for active force control. TRUE = ACTIVE, FALSE = INACTIVE (useful for hands)
    //!
    //! @return SUCCESS if command is accepted and is executed successfully, REJECT if the command is
    //!         not accepted, and FAILURE if the command is accepted but not executed successfully
    //!
    CanonReturn ApplyCartesianForceTorque (robotPose &robotForceTorque, vector<bool> activeAxes, vector<bool> manipulator);

    //! @brief Apply joint torques
    //!
    //! @param robotJointTorque are the command torques for the respective joint axes
    //!
    //! @return SUCCESS if command is accepted and is executed successfully, REJECT if the command is
    //!         not accepted, and FAILURE if the command is accepted but not executed successfully
    //!
    CanonReturn ApplyJointTorque (robotAxes &robotJointTorque);

    //! @brief Dock with a specified target object
    //!
    //! @param targetID The name of the object with which the robot should dock
    //!
    //! @return SUCCESS if command is accepted and is executed successfully, REJECT if the command is
    //!         not accepted, and FAILURE if the command is accepted but not executed successfully
    //!
    CanonReturn Couple (const char *targetID);

    //! @brief Display a message on the operator console
    //!
    //! @param message The plain-text message to be displayed on the operator console
    //!
    //! @return SUCCESS if command is accepted and is executed successfully, REJECT if the command is
    //!         not accepted, and FAILURE if the command is accepted but not executed successfully
    //!
    CanonReturn Message (const char *message);

    //! @brief Move the robot in a straight line from the current pose to a new pose and stop there
    //!
    //! @param pose        The target 6DOF pose for the robot
    //! @param useBlocking Whether or not to use additional code to ensure blocking on motion commands
    //!
    //! @return SUCCESS if command is accepted and is executed successfully, REJECT if the command is
    //!         not accepted, and FAILURE if the command is accepted but not executed successfully
    //!
    CanonReturn MoveStraightTo (robotPose &pose, bool useBlocking);

    //! @brief Move the controlled point along a trajectory passing through or near all but the last
    //!        of a series of poses, and then stop at the last pose
    //!
    //! @param poses         An array of 6DOF poses through/near which the robot is expected to pass
    //! @param numPoses      The number of sub-poses in the submitted array
    //! @param accelerations (optional) An array of 6DOF accelaration profiles for each motion
    //!                      associated with the target poses
    //! @param speeds        (optional) An array of 6DOF speed profiles for each motion assiciated
    //!                      with the target poses
    //! @param tolerances    (optional) An array of 6DOF tolerances in length and angle units for the
    //!                      specified target poses
    //!
    //! @return SUCCESS if command is accepted and is executed successfully, REJECT if the command is
    //!         not accepted, and FAILURE if the command is accepted but not executed successfully
    //!
    //! @note The length of the optional parameter arrays, if provided, must be equal to numPoses.
    //! @note Defining accerlations, speeds, and tolerances does not overwrite the defined default
    //!       values
    //!
    CanonReturn MoveThroughTo (robotPose *poses,
                               int numPoses,
                               robotPose *accelerations = NULL,
                               robotPose *speeds = NULL,
                               robotPose *tolerances = NULL);

    //! @brief Move the controlled pose along any convenient trajectory from the current pose to the
    //!        target pose, and then stop.
    //!
    //! @param pose        The target 6DOF Cartesian pose for the robot's TCP in Cartesian space coordinates
    //! @param useBlocking Whether or not to use additional code to ensure blocking on motion commands
    //!
    //! @return SUCCESS if command is accepted and is executed successfully, REJECT if the command is
    //!         not accepted, and FAILURE if the command is accepted but not executed successfully
    //!
    CanonReturn MoveTo (robotPose &pose, bool useBlocking);

    //! @brief Get feedback from the robot regarding its current axis configuration
    //!
    //! @param axes Axis array to be populated by the method
    //!
    //! @return SUCCESS if command is accepted and is executed successfully, REJECT if the command is
    //!         not accepted, and FAILURE if the command is accepted but not executed successfully
    //!
    CanonReturn GetRobotAxes (robotAxes *axes);

    //! @brief Get the measured Cartesian forces from the robot
    //!
    //! @param forces Cartesian force data structure to be populated by the method
    //!
    //! @return SUCCESS if command is accepted and is executed successfully, REJECT if the command is
    //!         not accepted, and FAILURE if the command is accepted but not executed successfully
    //!
    CanonReturn GetRobotForces (robotPose *forces);

    //! @brief Get I/O feedback from the robot
    //!
    //! @Param io Digital and analog I/O data structure to be populated by the method
    //!
    //! @return SUCCESS if command is accepted and is executed successfully, REJECT if the command is
    //!         not accepted, and FAILURE if the command is accepted but not executed successfully
    //!
    CanonReturn GetRobotIO (robotIO *io);

    //! @brief Get feedback from the robot regarding its current position in Cartesian space
    //!
    //! @param pose Cartesian pose data structure to be populated by the method
    //!
    //! @return SUCCESS if command is accepted and is executed successfully, REJECT if the command is
    //!         not accepted, and FAILURE if the command is accepted but not executed successfully
    //!
    CanonReturn GetRobotPose (robotPose *pose);

    //! @brief Get instantaneous Cartesian velocity
    //!
    //! @param speed Cartesian velocities to be populated by the method
    //!
    //! @return SUCCESS if command is accepted and is executed successfully, REJECT if the command is
    //!         not accepted, and FAILURE if the command is accepted but not executed successfully
    //!
    CanonReturn GetRobotSpeed (robotPose *speed);

    //! @brief Get instantaneous joint speeds
    //!
    //! @param speed Joint velocities array to be populated by the method
    //!
    //! @return SUCCESS if command is accepted and is executed successfully, REJECT if the command is
    //!         not accepted, and FAILURE if the command is accepted but not executed successfully
    //!
    CanonReturn GetRobotSpeed (robotAxes *speed);

    //! @brief Get joint torques from the robot regarding
    //!
    //! @param torques Axis array to be populated by the method
    //!
    //! @return SUCCESS if command is accepted and is executed successfully, REJECT if the command is
    //!         not accepted, and FAILURE if the command is accepted but not executed successfully
    //!
    CanonReturn GetRobotTorques (robotAxes *torques);

    //! @brief Move a virtual attractor to a specified coordinate in Cartesian space for force control
    //!
    //! @param pose The 6DOF destination of the virtual attractor 
    //!
    //! @return SUCCESS if command is accepted and is executed successfully, REJECT if the command is
    //!         not accepted, and FAILURE if the command is accepted but not executed successfully
    //!
    CanonReturn MoveAttractor (robotPose &pose);

    //! @brief Move the robot axes to the specified target values
    //!
    //! @param axes        An array of target axis values specified in the current axial unit
    //! @param useBlocking Whether or not to use additional code to ensure blocking on motion commands
    //!
    //! @return SUCCESS if command is accepted and is executed successfully, REJECT if the command is
    //!         not accepted, and FAILURE if the command is accepted but not executed successfully
    //!
    CanonReturn MoveToAxisTarget (robotAxes &axes, bool useBlocking);

    //! @brief Set the accerlation for the controlled pose to the given value in length units per
    //!        second per second
    //!
    //! @param acceleration The target TCP acceleration 
    //!
    //! @return SUCCESS if command is accepted and is executed successfully, REJECT if the command is
    //!         not accepted, and FAILURE if the command is accepted but not executed successfully
    //!
    CanonReturn SetAbsoluteAcceleration (double acceleration);

    //! @brief Set the speed for the controlled pose to the given value in length units per second
    //!
    //! @param speed The target Cartesian speed
    //!
    //! @return SUCCESS if command is accepted and is executed successfully, REJECT if the command is
    //!         not accepted, and FAILURE if the command is accepted but not executed successfully
    //!
    CanonReturn SetAbsoluteSpeed (double speed);

    //! @brief Set angel units to the unit specified
    //!
    //! @param unitName The name of the angle units in plain text ("degree" or "radian")
    //!
    //! @return SUCCESS if command is accepted and is executed successfully, REJECT if the command is
    //!         not accepted, and FAILURE if the command is accepted but not executed successfully
    //!
    CanonReturn SetAngleUnits (const char *unitName);

    //! @brief Set the axis-specific speeds for the motion of axis-space motions
    //!
    //! @param speeds Array of target axial motion speeds
    //!
    //! @return SUCCESS if command is accepted and is executed successfully, REJECT if the command is
    //!         not accepted, and FAILURE if the command is accepted but not executed successfully
    //!
    CanonReturn SetAxialSpeeds (double *speeds);

    //! @brief Set specific axial units to the specified values
    //!
    //! @param unitNames Array of axis-specific names of the axis units in plain text
    //!
    //! @return SUCCESS if command is accepted and is executed successfully, REJECT if the command is
    //!         not accepted, and FAILURE if the command is accepted but not executed successfully
    //!
    CanonReturn SetAxialUnits (const char **unitNames);

    //! @brief Set the default 6DOF tolerances for the pose of the robot in current length and angle
    //!        units
    //!
    //! @param tolerances Tolerances of the 6DOF end pose during Cartesian motion commands
    //!
    //! @return SUCCESS if command is accepted and is executed successfully, REJECT if the command is
    //!         not accepted, and FAILURE if the command is accepted but not executed successfully
    //!
    CanonReturn SetEndPoseTolerance (robotPose &tolerance);

    //! @brief Set the default 6DOF tolerance for smooth motion near intermediate points
    //!
    //! @param tolerances Tolerances of the 6DOF poses during multi-pose motions
    //!
    //! @return SUCCESS if command is accepted and is executed successfully, REJECT if the command is
    //!         not accepted, and FAILURE if the command is accepted but not executed successfully
    //!
    CanonReturn SetIntermediatePoseTolerance (robotPose *tolerances);

    //! @brief Set length units to the unit specified
    //!
    //! @param unitName The name of the length units in plain text ("inch," "mm," and "meter")
    //!
    //! @return SUCCESS if command is accepted and is executed successfully, REJECT if the command is
    //!         not accepted, and FAILURE if the command is accepted but not executed successfully
    //!
    CanonReturn SetLengthUnits (const char *unitName);

    //! @brief Set a robot-specific parameter (handling of parameter type casting to be handled by the
    //!        robot interface)
    //!
    //! @param paramName The name of the parameter variable to set
    //! @param paramVal  The value to be set to the specified robot parameter
    //!
    //! @return SUCCESS if command is accepted and is executed successfully, REJECT if the command is
    //!         not accepted, and FAILURE if the command is accepted but not executed successfully
    //!
    CanonReturn SetParameter (const char *paramName, void *paramVal);

    //! @brief Set the accerlation for the controlled pose to the given percentage of the robot's
    //!        maximum acceleration
    //!
    //! @param percent The percentage of the robot's maximum acceration in the range of [0, 1]
    //!
    //! @return SUCCESS if command is accepted and is executed successfully, REJECT if the command is
    //!         not accepted, and FAILURE if the command is accepted but not executed successfully
    //!
    CanonReturn SetRelativeAcceleration (double percent);

    //! @brief Set the digital and analog outputs
    //!
    //! @Param io Digital and analog I/O outputs to set
    //!
    //! @return SUCCESS if command is accepted and is executed successfully, REJECT if the command is
    //!         not accepted, and FAILURE if the command is accepted but not executed successfully
    //!
    CanonReturn SetRobotIO (robotIO &io);

    //! @brief Set a specific digital output
    //!
    //! @param dig_out Digital output channel to set
    //! @param val     Value to set the digital output
    //!
    //! @return SUCCESS if command is accepted and is executed successfully, REJECT if the command is
    //!         not accepted, and FAILURE if the command is accepted but not executed successfully
    //!
    CanonReturn SetRobotDO (int dig_out, bool val);

    //! @brief Set the attached tool to a defined output rate
    //!
    //! @param percent The desired output rate for the robot's tool as a percentage of maximum output
    //!
    //! @return SUCCESS if command is accepted and is executed successfully, REJECT if the command is
    //!         not accepted, and FAILURE if the command is accepted but not executed successfully
    //!
    CanonReturn SetTool (double percent);

    //! @brief Set the speed for the controlled point to the given percentage of the robot's maximum
    //!        speed
    //!
    //! @param percent The percentage of the robot's maximum speed in the range of [0, 1]
    //!
    //! @return SUCCESS if command is accepted and is executed successfully, REJECT if the command is
    //!         not accepted, and FAILURE if the command is accepted but not executed successfully
    //!
    CanonReturn SetRelativeSpeed (double percent);

    //! @brief Stop the robot's motions based on robot stopping rules
    //!
    //! @param condition The rule by which the robot is expected to stop (Estop category 0, 1, or 2);
    //!                  Estop category 2 is default
    //!
    //! @return SUCCESS if command is accepted and is executed successfully, REJECT if the command is
    //!         not accepted, and FAILURE if the command is accepted but not executed successfully
    //!
    CanonReturn StopMotion (int condition = 2);

    //! @brief Move the base to a specified position and orientation on a horizontal plane
    //!
    //! @param to Target position in the robot's world frame toward which the robot will attempt to move
    //!
    //! @return SUCCESS if command is accepted and is executed successfully, REJECT if the command is
    //!         not accepted, and FAILURE if the command is accepted but not executed successfully
    //!
    //! @note This function only uses the x, y, and zrot components of the pose object
    //!
    CanonReturn MoveBase(robotPose &to);

    //! @brief Point the head at an location relative to the robot�s base coordinate frame
    //!
    //! @param to Target pose toward which the head is attempting to point
    //!
    //! @return SUCCESS if command is accepted and is executed successfully, REJECT if the command is
    //!         not accepted, and FAILURE if the command is accepted but not executed successfully
    //!
    //! @note This function only uses the x, y, and z components of the pose object
    //!
    CanonReturn PointHead(robotPose &to);

    //! @brief Point the appendage at a location relative to the robot�s base coordinate frame
    //!
    //! @param app_ID Identifier of which appendage is being pointed
    //! @param to     Target pose toward which the appendage is attempting to point
    //!
    //! @return SUCCESS if command is accepted and is executed successfully, REJECT if the command is
    //!         not accepted, and FAILURE if the command is accepted but not executed successfully
    //!
    //! @note This function only uses the x, y, and z components of the pose object
    //! @note It is not always possible for the indicated appendage to point exactly along the vector
    //!       specified.  The robot should attempt to get as close as possible.
    //!
    CanonReturn PointAppendage(CanonRobotAppendage app_ID, robotPose &to);

  private:
    CrpiRobotParams *params_;
    ulapi_integer clientID_;

    char commandRegister_[43];
    int ackCommand_[12];
    char statusRegister_[12];
    int ackStatus_[128];

    int  ReqEcho_PosFingerA, ReqEcho_PosFingerB, ReqEcho_PosFingerC, ReqEcho_PosScissor, gripperMode;
    int PosFingerA, PosFingerB, PosFingerC, PosScissor;
    int CurFingerA, CurFingerB, CurFingerC, CurScissor;
    int PrevFingerA, PrevFingerB, PrevFingerC, PrevScissor;
    int gACT, gMOD, gGTO, gIMC, gSTA;
    int gDTA, gDTB, gDTC, gDTS, gFLT;

    bitset<8> *action_request;
    bitset<8> *gripper_options;
  
    bool graspedOnClose_, graspedOnOpen_, allFingersAtPos_;

    char inbuffer[8192];
    int option;

    void setHandParam (int param, int val);

    void sendCommand ();

    void getStatusRegisters();

    int setGrip(int param);

    void setPositionFingerA(int);

    void setSpeedFingerA(int); 

    void setForceFingerA(int);

    void setPositionFingerB(int);

    void setSpeedFingerB(int); 

    void setForceFingerB(int);

    void setPositionFingerC(int);

    void setSpeedFingerC(int); 

    void setForceFingerC(int);

    void setPositionScissor(int);

    void setSpeedScissor(int); 

    void setForceScissor(int);

    void writeStatus ();

    bool grasped_;
    void *task;
    keepalive ka_;
    unsigned long threadID_;

    //! @brief The name of the gripper configuration
    //!
    char configName[32];
    bool configured;

    //RobotiqGripper::RobotiqGripper *iqGrip;
  }; // CrpiRobotiq

} // namespace crpi_robot

#endif
