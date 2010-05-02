
DROP TABLE IF EXISTS events;
DROP TABLE IF EXISTS room;
DROP TABLE IF EXISTS building;
DROP TABLE IF EXISTS campus;
DROP TABLE IF EXISTS users;
DROP TABLE IF EXISTS priv;

CREATE TABLE priv(
role CHAR(1) NOT NULL PRIMARY KEY,
description VARCHAR(20) NOT NULL,
reserv_priority INT NOT NULL,
read_events BOOL NOT NULL,
write_events BOOL NOT NULL
) ENGINE=InnoDB;


CREATE TABLE users(
huid CHAR(8) NOT NULL PRIMARY KEY,
pwd VARCHAR(40) NOT NULL,
name VARCHAR(40) NOT NULL,
affiliation ENUM('college', 'grad', 'other'),
email VARCHAR(30) NOT NULL,
phone VARCHAR(11) NOT NULL,
role CHAR(1) NOT NULL,
FOREIGN KEY (role) REFERENCES priv(role)
) ENGINE=InnoDB;


CREATE TABLE campus(
id CHAR(1) NOT NULL PRIMARY KEY,
name VARCHAR(30) NOT NULL
) ENGINE=InnoDB;


CREATE TABLE building(
id CHAR(2) NOT NULL PRIMARY KEY,
region CHAR(1) NOT NULL,
name VARCHAR(30) NOT NULL,
FOREIGN KEY (region) REFERENCES campus(id)
) ENGINE=InnoDB;


CREATE TABLE room(
room_num VARCHAR(6) NOT NULL,
building CHAR(2) NOT NULL,
projector BOOL NOT NULL,
capacity INT NOT NULL,
PRIMARY KEY (room_num,building),
FOREIGN KEY (building) REFERENCES building(id)
) ENGINE=InnoDB;


CREATE TABLE events(
event_id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
huid CHAR(8) NOT NULL,
room VARCHAR(6) NOT NULL,
building CHAR(2) NOT NULL,
date_req DATETIME NOT NULL,
description VARCHAR(60) NOT NULL,
start_time DATETIME NOT NULL,
end_time DATETIME NOT NULL,
recurring VARCHAR(10),
FOREIGN KEY (room,building) REFERENCES room(room_num,building),
FOREIGN KEY (huid) REFERENCES users(huid)
) ENGINE=InnoDB;



