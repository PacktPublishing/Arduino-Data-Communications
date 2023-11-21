USE telemetry;

INSERT INTO stations (stationName, lat, lon, alt)
VALUES ('Station 4', 3.4, 0.1, 90);

SELECT * FROM stations;

UPDATE stations SET alt = 92 WHERE id = 2;

SELECT * FROM stations;