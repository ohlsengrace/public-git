//makes sure that we have the right files to access the db

var bookQuery = require('./query_groups/books');
var setQuery = require('./query_groups/textbook_sets');
var studentQuery = require('./query_groups/students');

module.exports = {
    bookQuery,
    setQuery,
    studentQuery
}
