///Header include
#include "social_network.hpp"
#include "user.hpp"

///STD include
#include <iostream>

namespace SocialNetworkNS {
size_t SocialNetwork::CUserIndex(const std::string &name,
                                 const std::string &surname) const {
  size_t i;

  User u(name, surname);

  bool found = false;

  for (i = 0; i < users.size() && !found; ++i)
    if (users[i] == u)
      found = true;

  if (found)
    return --i;
  else
    return users.size();
}

void SocialNetwork::AddUser(const std::string &name,
                            const std::string &surname) {
  User newUser(name, surname);

  // The check on already existing users function is coded in CUserIndex therefore
  // we just have to check if found -> return error
  // if not found -> we have to insert it in users and provide him an empty vector of size_ts to be employed to store friendships;
 if (CUserIndex(name, surname) == users.size())
  {
    // User not found
    users.push_back(newUser);
    friends.push_back(std::vector<size_t>());

   std::cout << "User: " << newUser.ToString() << " correctly added to the social media" << std::endl ;
  }
 else
  {
    std::cout << "User: " << newUser.ToString() << " profile already added" << std::endl;
  }
}

const std::vector<User> SocialNetwork::CGetUsers() const {
  return users;
}

const std::vector<User> SocialNetwork::CGetFriends(const User &user) const {

  // we have to get the user's friends.
  // we know that SocialNetwork has a cpp vector of vectors named friends as a private member.
  // we get a user -> we get name and surname and check if he/she is an actual user
  size_t UserIdx = CUserIndex(user.CGetName(), user.CGetSurname());
  std::vector<User> UserFriends{};
  if (UserIdx == users.size())
  {
    std::cout << "User not found" << std::endl;
    return UserFriends;
  }

  // now that we have the user's idx, friends[idx] contains the list of user's friends in indices
  // we want to fill UserFriends once we've converted all the indices in users:
  for (size_t idx = 0; idx < friends[UserIdx].size(); ++idx)
  {
    size_t FriendIdx = friends[UserIdx][idx];
    UserFriends.push_back(users[FriendIdx]);
  }
  return UserFriends;
}

const std::vector<User> SocialNetwork::CGetFriends(const std::string &name,
                                                   const std::string &surname) const {
  User user(name, surname);
  return CGetFriends(user);
}

void SocialNetwork::AddFriendship(const std::string &first_name,
                                  const std::string &first_surname,
                                  const std::string &second_name,
                                  const std::string &second_surname) {
  User firstUser(first_name, first_surname), secondUser(second_name, second_surname);
  size_t firstUserIdx = CUserIndex(first_name, first_surname), secondUserIdx = CUserIndex(second_name, second_surname);

  if (firstUser == secondUser or (firstUserIdx == users.size() or secondUserIdx == users.size()))
  {
    std::cout << "This friendship can't happen" << std::endl;
    return;
  }

  bool alreadyFriends = false;
  for (size_t i = 0; i < friends[firstUserIdx].size() && !alreadyFriends; ++i)
    if (friends[firstUserIdx][i] == secondUserIdx)
      alreadyFriends = true;

  if (alreadyFriends) {
    std::cout << "They are already friends" << std::endl;
    return;
  }

  friends[firstUserIdx].push_back(secondUserIdx);
  friends[secondUserIdx].push_back(firstUserIdx);

}

}
