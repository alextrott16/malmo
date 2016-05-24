// --------------------------------------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation.  All rights reserved.
// --------------------------------------------------------------------------------------------------------------------

#ifndef _MISSIONSPEC_H_
#define _MISSIONSPEC_H_

// Boost:
#include <boost/shared_ptr.hpp>

// Schemas:
#include <Mission.h>

// STL:
#include <string>
#include <vector>

namespace malmo
{
    const std::string xml_namespace("http://ProjectMalmo.microsoft.com");

    //! Specifies a mission to be run.
    class MissionSpec
    {
        public:

            //! Constructs a mission with default parameters: a flat world with a 10 seconds time limit and continuous movement.
            MissionSpec();

            //! Constructs a mission from the supplied XML as specified here: <a href="../Schemas/Mission.html">Schemas/Mission.html</a>
            //! \param xml The full XML of the mission.
            //! \param validate If true, then throws an xml_schema::exception if the XML is not compliant with the schema.
            MissionSpec(const std::string& xml, bool validate);

            //! Gets the mission specification as an XML string. Only use if you want to save the mission to file.
            //! \param prettyPrint If true, add indentation and newlines to the XML to make it more readable.
            //! \returns The mission specification as an XML string.
            std::string getAsXML( bool prettyPrint ) const;

            // -------------------- settings for the server -------------------------

            //! Sets the time limit for the mission.
            //! \param s The time limit in seconds.
            void timeLimitInSeconds(float s);
            
            //! Instead of the default flat world, make a world using Minecraft's terrain generator.
            void createDefaultTerrain();
            
            //! Sets the time of day for the start of the mission.
            //! \param t The time of day, in Minecraft ticks (thousandths of an hour since dawn).
            //! eg. 0 = Dawn, 6000 = Noon, 12000 = Sunset, 18000 = Midnight.
            //! \param allowTimeToPass If false then the sun does not move. 
            void setTimeOfDay(int t,bool allowTimeToPass);

            //! Draw a Minecraft block in the world.
            //! \param x The east-west location.
            //! \param y The up-down location.
            //! \param z The north-south location.
            //! \param blockType A string corresponding to one of the Minecraft block types.
            void drawBlock(int x, int y, int z, const std::string& blockType);
            
            //! Draw a solid cuboid in the world.
            //! \param x1 The west-most location.
            //! \param y1 The down-most location.
            //! \param z1 The north-most location.
            //! \param x2 The east-most location.
            //! \param y2 The up-most location.
            //! \param z2 The south-most location.
            //! \param blockType A string corresponding to one of the Minecraft block types.
            void drawCuboid(int x1, int y1, int z1, int x2, int y2, int z2, const std::string& blockType);

            //! Draw a Minecraft item in the world.
            //! \param x The east-west location.
            //! \param y The up-down location.
            //! \param z The north-south location.
            //! \param itemType A string corresponding to one of the Minecraft item types.
            void drawItem(int x, int y, int z, const std::string& itemType);

            //! Draw a solid sphere of blocks in the world.
            //! \param x The east-west location of the center.
            //! \param y The up-down location of the center.
            //! \param z The north-south location of the center.
            //! \param radius The radius of the sphere.
            //! \param blockType A string corresponding to one of the Minecraft block types.
            void drawSphere(int x, int y, int z, int radius, const std::string& blockType);

            //! Draw a line of blocks in the world.
            //! \param x1 The east-west location of the first end.
            //! \param y1 The up-down location of the first end.
            //! \param z1 The north-south location of the first end.
            //! \param x2 The east-west location of the second end.
            //! \param y2 The up-down location of the second end.
            //! \param z2 The north-south location of the second end.
            //! \param blockType A string corresponding to one of the Minecraft block types.
            void drawLine(int x1, int y1, int z1, int x2, int y2, int z2, const std::string& blockType);
            
            // -------------------- settings for the agents -------------------------

            //! Sets the start location for the agent. Only supports single agent missions.
            //! \param x The east-west location.
            //! \param y The up-down location.
            //! \param z The north-south location.
            void startAt(int x, int y, int z);

            //! Sets the end location for the agent. Only supports single agent missions.
            //! Can be called more than once if there are multiple positions that end the mission for this agent.
            //! \param x The east-west location.
            //! \param y The up-down location.
            //! \param z The north-south location.
            void endAt(int x, int y, int z);
            
            //! Sets the player mode for the agent to creative, allowing them to fly and to not sustain damage. Only supports single agent missions.
            void setModeToCreative();
            
            //! Sets the player mode for the agent to spectator, allowing them to fly and pass through objects. Only supports single agent missions.
            void setModeToSpectator();
            
            //! Asks for image data to be sent from Minecraft for the agent. Only supports single agent missions.
            //! \param width The width of the image in pixels. Ensure this is divisible by 4.
            //! \param height The height of the image in pixels. Ensure this is divisible by 2.
            void requestVideo(int width, int height);
            
            //! Asks for a reward to be sent to the agent when it reaches a certain position. Only supports single agent missions.
            //! \param x The east-west location.
            //! \param y The up-down location.
            //! \param z The north-south location.
            //! \param amount The reward value to send.
            //! \param tolerance The radius that the agent must be within to receive the reward. Euclidean distance.
            void rewardForReachingPosition(int x, int y, int z, float amount, float tolerance);

            //! Asks for the list of commands acted upon since the last timestep to be returned in the observations. Only supports single agent missions.
            //! The commands are returned in a JSON entry called 'CommandsSinceLastObservation'.
            //! Documentation link: <a href="../Schemas/MissionHandlers.html#element_ObservationFromRecentCommands">Schemas/MissionHandlers.html</a>
            void observeRecentCommands();

            //! Asks for the contents of the player's hot-bar to be included in the observations. Only supports single agent missions.
            //! The commands are returned in JSON entries 'Hotbar_0_size', 'Hotbar_0_item', etc.
            //! Documentation link: <a href="../Schemas/MissionHandlers.html#element_ObservationFromHotBar">Schemas/MissionHandlers.html</a>
            void observeHotBar();

            //! Asks for the full item inventory of the player to be included in the observations. Only supports single agent missions.
            //! The commands are returned in JSON entries 'Inventory_0_size', 'Inventory_0_item', etc.
            //! Documentation link: <a href="../Schemas/MissionHandlers.html#element_ObservationFromFullInventory">Schemas/MissionHandlers.html</a>
            void observeFullInventory();
            
            //! Asks for observations of the block types within a cuboid relative to the agent's position. Only supports single agent missions.
            //! The commands are returned in a JSON entry 'Cells'.
            //! Documentation link: <a href="../Schemas/MissionHandlers.html#element_ObservationFromGrid">Schemas/MissionHandlers.html</a>
            //! \param x1 The west-most location.
            //! \param y1 The down-most location.
            //! \param z1 The north-most location.
            //! \param x2 The east-most location.
            //! \param y2 The up-most location.
            //! \param z2 The south-most location.
            //! \param name An name to identify the JSON array that will be returned.
            void observeGrid(int x1,int y1,int z1,int x2,int y2,int z2,const std::string& name);
            
            //! Asks for the Euclidean distance to a location to be included in the observations. Only supports single agent missions.
            //! The commands are returned in a JSON element 'distanceFromNAME', where NAME is replaced with the name of the point.
            //! Documentation link: <a href="../Schemas/MissionHandlers.html#element_ObservationFromDistance">Schemas/MissionHandlers.html</a>
            //! \param x The east-west location.
            //! \param y The up-down location.
            //! \param z The north-south location.
            //! \param name A label for this observation. The observation will be called "distanceFrom<name>".
            void observeDistance(int x,int y,int z,const std::string& name);
            
            //! Asks for chat messages to be included in the observations.
            void observeChat();
            
            // -------------------- settings for the agents : command handlers -------------------------

            //! Remove any existing command handlers from the mission specification. Use with other functions to add exactly the command handlers you want.
            //! Only applies to the first agent in the mission. For multi-agent missions, specify the command handlers for each in the XML.
            void removeAllCommandHandlers();
            
            //! Adds a continuous movement command handler if none present, with neither an allow-list or a deny-list, thus allowing any command to be sent.
            //! Only applies to the first agent in the mission. For multi-agent missions, specify the command handlers for each in the XML.
            void allowAllContinuousMovementCommands();
            
            //! Adds an allow-list to the continuous movement command handler if none present. Adds the specified verb to the allow-list.
            //! Note that when an allow-list is present, only the commands listed are allowed.
            //! Adds a continuous movement command handler if none present. Removes the deny-list from the continuous movement command handler if present.
            //! Only applies to the first agent in the mission. For multi-agent missions, specify the command handlers for each in the XML.
            //! \param verb The command verb, e.g. "move".
            void allowContinuousMovementCommand(const std::string& verb);
            
            //! Adds a discrete movement command handler if none present, with neither an allow-list or a deny-list, thus allowing any command to be sent.
            //! Only applies to the first agent in the mission. For multi-agent missions, specify the command handlers for each in the XML.
            void allowAllDiscreteMovementCommands();
            
            //! Adds an allow-list to the discrete movement command handler if none present. Adds the specified verb to the allow-list.
            //! Note that when an allow-list is present, only the commands listed are allowed.
            //! Adds a discrete movement command handler if none present. Removes the deny-list from the discrete movement command handler if present.
            //! Only applies to the first agent in the mission. For multi-agent missions, specify the command handlers for each in the XML.
            //! \param verb The command verb, e.g. "movenorth".
            void allowDiscreteMovementCommand(const std::string& verb);
            
            //! Adds an absolute movement command handler if none present, with neither an allow-list or a deny-list, thus allowing any command to be sent.
            //! Only applies to the first agent in the mission. For multi-agent missions, specify the command handlers for each in the XML.
            void allowAllAbsoluteMovementCommands();
            
            //! Adds an allow-list to the absolute movement command handler if none present. Adds the specified verb to the allow-list.
            //! Note that when an allow-list is present, only the commands listed are allowed.
            //! Adds an absolute movement command handler if none present. Removes the deny-list from the absolute movement command handler if present.
            //! Only applies to the first agent in the mission. For multi-agent missions, specify the command handlers for each in the XML.
            //! \param verb The command verb, e.g. "tpx".
            void allowAbsoluteMovementCommand(const std::string& verb);
            
            //! Adds an inventory command handler if none present, with neither an allow-list or a deny-list, thus allowing any command to be sent.
            //! Only applies to the first agent in the mission. For multi-agent missions, specify the command handlers for each in the XML.
            void allowAllInventoryCommands();
            
            //! Adds an allow-list to the inventory command handler if none present. Adds the specified verb to the allow-list.
            //! Note that when an allow-list is present, only the commands listed are allowed.
            //! Adds an inventory command handler if none present. Removes the deny-list from the inventory command handler if present.
            //! Only applies to the first agent in the mission. For multi-agent missions, specify the command handlers for each in the XML.
            //! \param verb The command verb, e.g. "selectInventoryItem".
            void allowInventoryCommand(const std::string& verb);
            
            //! Adds a chat command handler if none present, with neither an allow-list or a deny-list, thus allowing any command to be sent.
            //! Only applies to the first agent in the mission. For multi-agent missions, specify the command handlers for each in the XML.
            void allowAllChatCommands();
            
            // ------------------------- information --------------------------------------
            
            //! Returns the number of agents involved in this mission.
            //! \returns The number of agents.
            int getNumberOfAgents() const;

            //! Gets whether video has been requested for one of the agents involved in this mission.
            //! \param role The agent index. Zero based.
            //! \returns True if video was requested.
            bool isVideoRequested(int role) const;
            
            //! Returns the width of the requested video for one of the agents involved in this mission.
            //! \param role The agent index. Zero based.
            //! \returns The width of the video in pixels.
            int getVideoWidth(int role) const;
            
            //! Returns the height of the requested video for one of the agents involved in this mission.
            //! \param role The agent index. Zero based.
            //! \returns The height of the video in pixels.
            int getVideoHeight(int role) const;
            
            //! Returns the number of channels in the requested video for one of the agents involved in this mission.
            //! \param role The agent index. Zero based.
            //! \returns The number of channels in the requested video: 3 for RGB, 4 for RGBD.
            int getVideoChannels(int role) const;

        private:
        
            void putVerbOnList( ::xsd::cxx::tree::optional< malmo::schemas::ModifierList >& mlo
                              , const std::string& verb
                              , const std::string& on_list
                              , const std::string& off_list );
        
            friend class MissionInitSpec;
        
            boost::shared_ptr<schemas::Mission> mission;
    };
}

#endif