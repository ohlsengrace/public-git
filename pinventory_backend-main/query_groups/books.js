// all functions for checkouts table

var db = require('./connection.js');

//returns all the books in the books table
function getAll(req, res){

    if (req.gmail.includes('@student')){
       db.oneOrNone('SELECT student_number FROM students WHERE email = $1', [req.gmail])
           .then(result => {
               if (result){
                   let studentId = result.student_number;
                   console.log('found student id ' + studentId);
                   db.any('SELECT * FROM books FULL OUTER JOIN students on books.student_number = students.student_number NATURAL JOIN textbook_sets WHERE books.student_number = $1;', [studentId])
                       .then(rows => {
                           console.log(rows);
                           res.status(200).json(rows);
                       })
                       .catch(error => {
                           console.log(error);
                           res.status(500).send();
                       })
               }else{
                   res.status(409).send('Student Not Found');
               }
           })
    }else{
        db.any('SELECT * FROM books NATURAL JOIN students NATURAL JOIN textbook_sets WHERE books.teacher = $1 ORDER BY title, last_name, first_name', [req.gmail])
            .then(rows => {
                console.log(rows);
                res.status(200).json(rows);
            })
            .catch(error => {
                console.log(error);
                res.status(500).send();
            })
    }

}

//returns all checked out books
function getAllCheckedOut(req,res){

    //better than NATURAL JOIN because books with checked out owner that is not in students table is still listed
    db.any('SELECT * FROM books FULL OUTER JOIN students on students.student_number = books.student_number NATURAL JOIN textbook_sets WHERE books.student_number IS NOT NULL')

        .then(rows => {
            console.log(rows);
            res.status(200).json(rows);
        })
        .catch(error => {
            console.log(error);
            res.status(500).send();
        })
}


//updates student_number of book to given studentId
function checkOut (req,res){

    const studentId = req.body.studentId;
    const assetTag = req.body.assetTag;

    canCheckout(assetTag)
        .then(result => {
            if(result){
                db.none('UPDATE books SET student_number = $1, teacher = $2, edited = $2, updated = $3 WHERE asset_tag = $4', [studentId, req.gmail, new Date(), assetTag])
                    .then(() => {
                        console.log(assetTag + " was checked out for " + studentId)
                        res.status(200).send();
                    })
                    .catch(error => {
                        console.log(error);
                        res.status(500).send();
                    })
            }else{
                res.status(409).send("Book already checked out");
            }
        })
        .catch(error => {
            console.log(error);
            res.status(409).send("Book doesn't exist");
        });

}

// updates student_number of book to null
function checkIn (req,res){

    const assetTag = req.body.assetTag;

    db.none('UPDATE books SET student_number = $1, teacher = $1, edited = $2, updated = $3 WHERE asset_tag = $4', [null, req.gmail, new Date(), assetTag])
        .then( () => {
            console.log(assetTag + " was checked in!")
            res.status(200).send()
        })
        .catch(error => {
            res.status(500).send();
            console.log('check in failed')
        })
}

//returns all checked out books under one email address
function getBooksByStudent (req,res) {

    let gmail = req.gmail;

    console.log(gmail);

    db.any('SELECT * FROM books NATURAL JOIN textbook_sets NATURAL JOIN students WHERE students.email = $1',[gmail])
        .then( rows => {
            console.log('getBooksByStudent was successful for ', [gmail])
            res.status(200).json(rows)
        })
        .catch(error => {
            console.log(error);
            res.status(500).send();
            console.log('getBooksByStudent for ' + gmail + ' failed')
        })


}

//Checks to see if a particular book is available to be checked out
function canCheckout(assetTag){
    return new Promise((resolve, reject) => {
        db.one('SELECT student_number FROM books WHERE asset_tag = $1', [assetTag])
            .then( result => {
                console.log(result);
                resolve(result.student_number == null)
            })
            .catch(error =>{
                console.log(error);
                reject(error);
            })
    });
}

module.exports = {

    checkOut, checkIn, getAll, getAllCheckedOut, getBooksByStudent

}
