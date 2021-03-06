//
//  SuperUser.hpp
//  intercom_ios
//
//  Created by Sascha Arlt on 07.09.20.
//

#ifndef SuperUser_hpp
#define SuperUser_hpp

#include <stdio.h>
#include "User.h"

class SuperUser : public User {
  
public:
    SuperUser(ZDB * a_zdb);
    ~SuperUser();

    void openUserConfig();
    void openChannelConfig();
    void setRoles();  
};

#endif /* SuperUser_hpp */
