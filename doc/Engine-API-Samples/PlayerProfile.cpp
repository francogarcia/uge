#include <Core/PlayerProfile/PlayerProfiles.h>

int main()
{
    uge::PlayerProfile profile;
    profile.Init("player_profiles/average_user/profile.xml");

    uge::PlayerProfiles profiles;
    profiles.Init("player_profiles/player_profiles.xml");

    return 0;
}
