package com.jollymonsterstudio.web.repository;

import com.jollymonsterstudio.web.domain.UserEntity;
import org.springframework.data.repository.CrudRepository;

import java.util.List;

public interface UserRepository extends CrudRepository<UserEntity, Integer> {
    List<UserEntity> findAll();
    UserEntity findByUsername(final String username);
}
