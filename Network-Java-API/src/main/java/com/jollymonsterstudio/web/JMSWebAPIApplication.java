package com.jollymonsterstudio.web;

import com.jollymonsterstudio.web.domain.UserEntity;
import com.jollymonsterstudio.web.repository.UserRepository;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

import javax.annotation.PostConstruct;
import java.util.List;

@SpringBootApplication
public class JMSWebAPIApplication {

    private final Logger logger = LoggerFactory.getLogger(this.getClass());

    @Autowired
    private UserRepository userRepository;

    @PostConstruct
    private void initDb() {

        logger.info(String.format("****** Check table: %s ******", "Users"));
        List<UserEntity> users = userRepository.findAll();
        for(UserEntity user : users)
        {
            logger.info(user.toString());
        }
    }

    public static void main(String[] args) {
        SpringApplication.run(JMSWebAPIApplication.class, args);
    }
}
