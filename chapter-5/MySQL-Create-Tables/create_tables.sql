USE telemetry;

CREATE TABLE IF NOT EXISTS stations (
                                        id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
                                        stationName VARCHAR(255),
                                        lat FLOAT,
                                        lon FLOAT,
                                        alt FLOAT,
                                        installedOn DATE DEFAULT(CURRENT_DATE)
);

CREATE TABLE IF NOT EXISTS readings(
                                       id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
                                       stationID INT,
                                       epochs TIMESTAMP DEFAULT(CURRENT_TIMESTAMP),
                                       temperature FLOAT,
                                       humidity FLOAT,
                                       FOREIGN KEY (stationID) REFERENCES stations(id) ON UPDATE RESTRICT ON DELETE RESTRICT
);