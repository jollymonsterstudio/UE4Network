package com.jollymonsterstudio.web.controller;

import com.jollymonsterstudio.web.domain.UserEntity;
import com.jollymonsterstudio.web.domain.UserResponse;
import com.jollymonsterstudio.web.repository.UserRepository;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RestController;

import javax.servlet.http.HttpServletRequest;
import java.util.Collections;
import java.util.List;

@RestController
public class UserController {

    private final Logger logger = LoggerFactory.getLogger(this.getClass());

    @Autowired
    private UserRepository userRepository;

    @GetMapping("/users")
    public ResponseEntity<UserResponse> getUsers(HttpServletRequest request) {
        logHeaders(request);

        List<UserEntity> users = userRepository.findAll();
        if(users.size() > 0)
        {
            return ResponseEntity.status(HttpStatus.OK).body(new UserResponse(users));
        }
        return ResponseEntity.status(HttpStatus.NOT_FOUND).body(null);
    }

    @GetMapping("/user/{username}")
    public ResponseEntity<UserEntity> getUserByUsername(@PathVariable String username, HttpServletRequest request) {
        logHeaders(request);

        UserEntity user = userRepository.findByUsername(username);
        if(user != null)
        {
            return ResponseEntity.status(HttpStatus.OK).body(user);
        }

        return ResponseEntity.status(HttpStatus.NOT_FOUND).body(null);
    }

    private void logHeaders(HttpServletRequest request) {

        try{
            Thread.sleep(2000);
        }  catch (InterruptedException e) {
            logger.error(e.getMessage(), e);
        }
        for(String key : Collections.list(request.getHeaderNames()))
        {
            logger.info("**  header: {} - value: {}  **", key, request.getHeader(key));
        }
    }
}
