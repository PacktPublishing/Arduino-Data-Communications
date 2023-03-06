var express = require('express');
var router = express.Router();

/* MySQL DB connection credentials */
var conn = require('./dbConn');

/* GET readings listing. */
router.get('/', function(req, res, next) {
    const query = 'SELECT * FROM readings';
    conn.query(query, function(error, results, fields) {
        if (error) throw error;

        res.send(results);
    });
});

/* POST readings listing. */
router.post('/', function(req, res, next) {
    const query = 'INSERT INTO `readings` (`stationid`, `epochs`, `temperature`, `humidity`) VALUES (?, ?, ?, ?)';
    conn.query(query, [req.body.stationid, new Date(), req.body.temperature, req.body.humidity], function (error, results) {
        if (error) throw error;

        res.send(results);
    });
});

/* PUT reading listing. */
router.put('/', function(req, res, next) {
    res.send('update a reading');
});

/* DELETE station listing. */
router.delete('/', function(req, res, next) {
    res.send('delete a reading');
});

module.exports = router;
