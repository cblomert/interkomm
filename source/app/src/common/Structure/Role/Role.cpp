//
//  Role.cpp
//  Intercom User structure
//
//  Created by Sascha Arlt on 08.09.20.
//  Copyright © 2020 Sascha Arlt. All rights reserved.
//

#include "Role.h"
#include "Session.h"

Role::Role(ZDB * a_zdb) : StructureBase(a_zdb){
    init();
}

Role::Role(ZDB * a_zdb, string a_name): StructureBase(a_zdb, a_name){
    init();
}

void Role::init(){
    
}


bool Role::save_role(mss * session, Role * a_role, ZDB * a_zdb){
    session->write_string(a_role->_name());
    return false;
}

Role * Role::load_role(mss * session, ZDB * a_zdb){
    Role * a_role = new Role(a_zdb,session->read_string());
    return a_role;
}

bool Role::save_roles(Session * a_session, ZDB * a_zdb){
    
    if (a_zdb->gl->in_background->value()) {
        return false;
    }
    
    mss * session = new mss(0001);
    string a_name = "asda";
    session->write_string(a_name);
    session->write_int(static_cast<int>(a_session->_roles()->size()));
    
    for (Role * a_role:*a_session->_roles()) {
        save_role(session, a_role,a_zdb);
    }
    
    a_zdb->dispatch->on_default([=]{
        writeDataWithLengthToPath(path_for_session(a_session,Role::get_extension()), session->session_content, session->write_offset);
        delete session;
    });
    
    return true;
}
bool Role::load_roles(Session * a_session, ZDB * a_zdb){
    
    
    unsigned long length = 0;
    void * content = loadDataAtPath(path_for_session(a_session,Role::get_extension()), &length);
    
    if (content) {
        mss * session = new mss((char*)content, (int)length);
        session->version = 2;
        string aname = session->read_string();
        int a_size = session->read_int();
        
        for (int i = 0; i<a_size; i++) {
            a_session->_roles()->push_back(Role::load_role(session, a_zdb));
        }
        
        delete session;
    }
    
    return true;
}
