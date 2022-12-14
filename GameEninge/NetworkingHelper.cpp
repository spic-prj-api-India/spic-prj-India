#include "NetworkingHelper.hpp"

std::string spic::networkingHelper::GetParsedIPConfigData(const std::string& Columb)
{
    //Set up command file path and command line command
    std::string APPDATA = getenv("APPDATA");
    std::string path = APPDATA + "\\localipdata.txt";
    std::string cmd = "ipconfig > " + path;

    //execute ipconfig command and save file to path
    system(cmd.c_str());

    //current line
    std::string line;

    //Line array : Here is all lines saved
    std::string lineArray[500];
    int arrayCount = 0;

    std::ifstream file(path);
    if (file.is_open())
    {
        //Get all lines
        while (std::getline(file, line))
        {
            //Save each line into a element in an array
            lineArray[arrayCount] = line;
            arrayCount++;
        }

        for (int arrayindex = 0; arrayindex <= arrayCount; arrayindex++)
        {
            std::string s = Columb;
            std::string s2 = ":";

            //Search all lines and get pos
            std::size_t i = lineArray[arrayindex].find(s);
            std::size_t i2 = lineArray[arrayindex].find(s2);

            //Found a match for Columb
            if (lineArray[arrayindex].find(s) != std::string::npos)
            {
                //Validate
                if (i != std::string::npos)
                {
                    //Earse Columb name
                    lineArray[arrayindex].erase(i, s.length());

                    //Erase all blanks
                    lineArray[arrayindex].erase(remove_if(lineArray[arrayindex].begin(), lineArray[arrayindex].end(), isspace), lineArray[arrayindex].end());

                    //Found match for ':'
                    if (lineArray[arrayindex].find(s2) != std::string::npos)
                    {
                        //Validate
                        if (i2 != std::string::npos)
                        {
                            //Delete all characters prior to ':'
                            lineArray[arrayindex].erase(0, lineArray[arrayindex].find(":"));
                            lineArray[arrayindex].erase(std::remove(lineArray[arrayindex].begin(), lineArray[arrayindex].end(), ':'), lineArray[arrayindex].end());
                        }
                    }
                    //Return our data
                    return lineArray[arrayindex];
                }
            }

            //Only go through all lines once
            if (arrayindex == arrayCount)
                break;
        }

        //Close file
        file.close();
    }
    //Something went wrong
    return "Invalid";
}
