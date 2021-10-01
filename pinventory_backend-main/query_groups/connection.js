//connects to the db

// change connectionString to match environment
const pgp = require('pg-promise')()

const connectionString = require('../config')(process.env.NODE_ENV);

const db = pgp(connectionString)

module.exports = db;