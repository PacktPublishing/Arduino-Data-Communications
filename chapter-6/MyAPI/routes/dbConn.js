var mysql = require('mysql2');

/* MySQL DB connection credentials */
var conn = mysql.createPool({
    host: '192.168.68.100',
    user: 'johnthas',
    password: 'oddeseyus',
    database: 'telemetry',
    waitForConnections: true,
    connectionLimit: 10,
    maxIdle: 10,
    idleTimeout: 60000,
    queueLimit: 0
});

module.exports = conn;

