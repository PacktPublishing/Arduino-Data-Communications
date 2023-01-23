var express = require('express');
var router = express.Router();
var mysql = require('mysql2');

/* MySQL DB connection credentials */
var conn = mysql.createConnection({
    host: '192.168.68.127',
    user: 'johnthas',
    password: 'oddeseyus',
    database: 'telemetry'
});

/* GET station listing. */
router.get('/', function(req, res, next) {
    conn.connect();
    const query = 'SELECT * FROM stations';
    conn.query(query, function(error, results, fields) {
        if (error) throw error;

        res.send(results);
    });
    conn.end();
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
