
const studentQuery = require('../query_groups/students');
const https = require('https');

//run this script to update students and student emails to match powerschool

    try{

        const options = {
            hostname: 'powerschool.psdr3.org',
            port: 8443,
            path: '/ords/ps/capstone/students/hs',
            method: 'GET'
        }

        const req = https.request(options, (res) => {
            var dataQueue = ""
            res.on('data', function (d) {
                dataQueue += d;
            });
            res.on("end", function() {
                let myObj;
                try {
                    myObj = JSON.parse(dataQueue);
                    //myObj.items[i] accesses individual students at a given point i
                    studentQuery.updateStudents(myObj);

                }catch(err){
                    parsedData = {}
                    console.log(err)
                }
            });
        });
        req.end()
    }catch (e) {
        console.log(e)
    }

try{

    const options = {
        hostname: 'powerschool.psdr3.org',
        port: 8443,
        path: '/ords/ps/capstone/voting',
        method: 'GET'
    }

    const req = https.request(options, (res) => {
        var dataQueue = ""
        res.on('data', function (d) {
            dataQueue += d;
        });
        res.on("end", function() {
            let myObj;
            try {
                myObj = JSON.parse(dataQueue);
                //myObj.items[i] accesses individual students at a given point i
                studentQuery.updateEmails(myObj.items);
            }catch(err){
                parsedData = {}
                console.log(err)

            }
        });
    });
    req.end()
}catch (e) {
    console.log(e)
}