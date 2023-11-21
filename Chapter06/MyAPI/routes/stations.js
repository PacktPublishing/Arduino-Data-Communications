var express = require('express');
var router = express.Router();

/* MySQL DB connection credentials */
var conn = require('./dbConn');

/* GET station listing. */
router.get('/', function(req, res, next) {
    const query = 'SELECT * FROM stations';
    conn.query(query, function(error, results, fields) {
        if (error) throw error;

        res.send(results);
    });
});

/* POST station listing. */
router.post('/', function(req, res, next) {
    res.send('post a station');
});

/* PUT station listing. */
router.put('/', function(req, res, next) {
    res.send('update a station');
});

/* DELETE station listing. */
router.delete('/', function(req, res, next) {
    res.send('delete a station');
});

module.exports = router;
