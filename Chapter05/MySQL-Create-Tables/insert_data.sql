USE telemetry;

INSERT INTO stations (stationName, lat, lon, alt)
VALUES ('Station 1', 3.3, 0.0, 100);

INSERT INTO readings (stationid, epochs, temperature, humidity) VALUES (1, NOW(), 11.6, 66);
INSERT INTO readings (stationid, epochs, temperature, humidity) VALUES (1, TIMESTAMPADD(MINUTE, 1, NOW()), 11.6, 65);
INSERT INTO readings (stationid, epochs, temperature, humidity) VALUES (1, TIMESTAMPADD(MINUTE, 2, NOW()), 11.6, 64);