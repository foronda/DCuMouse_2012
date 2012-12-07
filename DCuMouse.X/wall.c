#include "common.h"
#include "wall.h"
#include "sensor.h"

#define FRW 140
#define FLW 123
#define SRW 148
#define SLW 140

#define RTRACKOFFSET 1
#define LTRACKOFFSET 1

bool FrontWall()
{
    return ((ReadFR() < FRW) || (ReadFL() < FLW));
}

bool RightWall()
{
    return (ReadSR() < SRW);
}

bool LeftWall()
{
    return (ReadSL() < SLW);
}
