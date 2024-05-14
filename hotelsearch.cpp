#include "hotelsearch.h"
static std::vector<QString> amenities = {"SWIMMING_POOL", "SPA", "FITNESS_CENTER", "AIR_CONDITIONING", "RESTAURANT",\
"PARKING", "PETS_ALLOWED", "AIRPORT_SHUTTLE", "BUSINESS_CENTER", "DISABLED_FACILITIES", "WIFI", "MEETING_ROOMS", "NO_KID_ALLOWED", \
"TENNIS", "GOLF", "KITCHEN", "ANIMAL_WATCHING", "BABY-SITTING", "BEACH", "CASINO", "JACUZZI", "SAUNA", "SOLARIUM", "MASSAGE", \
"VALET_PARKING", "KIDS_WELCOME", "NO_PORN_FILMS", "MINIBAR", "TELEVISION", "WI-FI_IN_ROOM", "ROOM_SERVICE", "GUARDED_PARKG",
                                         "SERV_SPEC_MENU"};
#include "hotelsearch.h"


QString amenitiesToQString(uint32_t am_flag)
{
    QString res = "";
    for(int i =0;i<amenities.size();i++)
    {
        if(am_flag & (1<<i))
        {
            res+=amenities[i];
            res+=",";
        }
    }
    res = res.removeLast();
    return res;
}
