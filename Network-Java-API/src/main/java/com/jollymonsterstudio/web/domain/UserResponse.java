package com.jollymonsterstudio.web.domain;

import java.io.Serializable;
import java.util.List;

public class UserResponse implements Serializable {
    private List<UserEntity> users;

    public UserResponse(List<UserEntity> users) {
        this.users = users;
    }

    public List<UserEntity> getUsers() {
        return users;
    }
}
