// this is where queries for the textbook_sets table will go

var db = require('./connection.js');
const fs = require('fs')
const bwipjs = require('bwip-js');
const PdfPrinter = require('pdfmake');
const csv = require('fast-csv');


//used in createSets... inserts books into books table
function newBooks(firstBookNum, numBooks, isbn, year) {

    return new Promise(function (resolve) {

        var textbooks = [];

        for (i = firstBookNum; i < firstBookNum + parseInt(numBooks); i++) {

            let assetTag = "";
            let bookNum = "" + i;

            bookNum = bookNum.padStart(4, '0')

            // assetTag = isbn + last two digits of year + bookNum
            assetTag = isbn + year.substr(year.length - 2) + bookNum;

            db.none('INSERT INTO books VALUES ($1, $2, $3, $4, $5)',
                [assetTag, isbn, year.substr(year.length - 2), bookNum, null])
                .then()
                .catch(error => {
                    console.log('error in newBooks', error);
                })
            textbooks.push({assetTag: assetTag});
        }
        resolve(textbooks);

    });
}


//used in createSet... creates barcodes
async function getBarcodes(items) {


    for (let item of items) {
        const buffer = await bwipjs.toBuffer({
            bcid: 'code128',
            text: item.assetTag,
            scale: 3,
            height: 10,
            includetext: true,
            textxalign: 'center'
        });
        const barcodeBase64 = `data:image/gif;base64,${buffer.toString('base64')}`
        item.barcodeImage = barcodeBase64;

    }
    return items;
}

//used in createSet... inserts into textbook_sets
function insertSet(isbn, title, department) {

    db.none('INSERT INTO textbook_sets VALUES ($1, $2, $3)', [isbn, title, department])
        .then(() => {
            console.log(title + " inserted into textbook_sets");
        })
        .catch(error => {
            console.log('error in insertSet', error)
        })
}

//used in createSet... gets content for pdf using barcode information
function getContent(codes) {

    var content = [];

    for (i = 0; i < codes.length; i++) {
        let width = 175;
        let height = 45;
        let image = codes[i].barcodeImage;

        //column
        let xPos;
        //row
        let yPos = 42.5 + 72.5 * Math.floor((i % 30) / 3)
        let pageBreak = undefined;

        //xPos
        if (i % 3 == 0) {
            xPos = 15
        } else if (i % 3 == 1) {
            xPos = 215
        } else if (i % 3 == 2) {
            xPos = 415
            if (i % 30 == 29) {
                pageBreak = 'after';
            }
        }

        let absolutePosition = {x: xPos, y: yPos};

        content.push({width, height, image, absolutePosition, pageBreak});

    }

    console.log("the content creation for new set was successful");
    return content;

}


//used in createSet... takes in response and content to make document of barcodes using pdfmake
async function createPdf(res, content) {

    var dd = {
        pageSize: 'LETTER',
        content: content,
        styles: {
            header: {
                fontSize: 18,
                bold: true,
                alignment: 'right',
                margin: [0, 190, 0, 80]
            },
            subheader: {
                fontSize: 14
            },
            superMargin: {
                margin: [20, 0, 40, 0],
                fontSize: 15
            }
        }
    }

    var fonts = {
        Roboto: {
            normal: 'fonts/Roboto/Roboto-Regular.ttf',
            bold: 'fonts/Roboto/Roboto-Medium.ttf',
            italics: 'fonts/Roboto/Roboto-Italic.ttf',
            bolditalics: 'fonts/Roboto/Roboto-MediumItalic.ttf'
        }
    };

    const filePath = '/books/current.pdf';
    var printer = new PdfPrinter(fonts);

    var pdfDoc = printer.createPdfKitDocument(dd, {});
    console.log("document created, trying to pipe");

    pdfDoc.pipe(fs.createWriteStream(filePath));
    pdfDoc.pipe(res);

    pdfDoc.end();


}


// adds new set to textbook_sets, adds new books to books, and returns barcodes
async function createSet(req, res) {

    const isbn = req.body.isbn;
    const title = req.body.title;
    const numBooks = req.body.numBooks;
    const year = req.body.year;
    const department = req.body.department;


    await insertSet(isbn, title, department)

    var tags = await newBooks(1, numBooks, isbn, year);

    var codes = await getBarcodes(tags);

    var content = await getContent(codes);

    createPdf(res, content);

}


// adds books to a pre-existing textbook_set, returns assetTags... not complete or used in current product
function addToSet(req, res) {

    const isbn = req.body.isbn;
    const year = req.body.year;
    const numNewBooks = req.body.numNewBooks;

    db.any('SELECT COUNT(*) FROM books WHERE isbn = $1 AND year = $2', [isbn, year.substr(year.length - 2)])
        .then(rows => {

            var currentNum = parseInt(rows[0].count, 10);

            var textbooks = newBooks(currentNum + 1, numNewBooks, isbn, year)

            res.json(textbooks);


        })
        .catch(error => {
            console.log(error)
            console.log("the error is in getNumBooksByYear");
            res.status(500).send();
        })

}

//returns all textbook_sets
function getSets(req, res) {

    db.any('SELECT * FROM textbook_sets')


        .then(rows => {
            console.log(rows);
            res.json(rows).send();
        })
        .catch(error => {
            console.log(error);
            res.status(400).send();
        })
}

//used in importSet... takes in fileRows from csv and inserts textbooks + sets into database and returns json of assetTags
async function importBooks(fileRows) {

    // inserts all sets
    for (i = 1; i < fileRows.length; i++) {
        //isbn, year, number, book name, department
        let isbn = fileRows[i][0];
        let title = fileRows[i][3];
        let department = fileRows[i][4];

        isbn = isbn.padStart(13, '0');

        // check if textbook set is already in the system
        let result = await setDoesntExist(isbn)
        if (result) {
            console.log("insert set")
            insertSet(isbn, title, department); //adds set if not already in database
        }
    }

    return new Promise(function (resolve) {

        const assetTags = [];

        for (i = 1; i < fileRows.length; i++) {
            //isbn, year, number, book name, department
            let isbn = fileRows[i][0];
            let year = fileRows[i][1];
            let bookNum = fileRows[i][2];

            isbn = isbn.padStart(13, '0');


            // assetTag = isbn + last two digits of year + bookNum
            bookNum = bookNum.padStart(4, '0');
            let assetTag = isbn + year + bookNum;

            db.none('INSERT INTO books VALUES ($1, $2, $3, $4, $5)',
                [assetTag, isbn, year, bookNum, null])
                .then()
                .catch(error => {
                    console.log('error in creating books', error);
                })
            assetTags.push({assetTag: assetTag});
        }
        resolve(assetTags);

    });
}


//takes in Csv, inserts sets into textbook_sets, inserts individual books into books, returns pdf of barcodes
async function importSet(req, res) {

    const fileRows = [];
    csv.parseFile(req.file.path)
        .on("data", function (data) {
            fileRows.push(data); //push each row
        })
        .on("end", async function () {
            console.log(fileRows) //contains array of arrays. Each inner array represents row of csv

            res.status(200);



            // add each of the books into the books table while creating array of assetTags

            const assetTags = await importBooks(fileRows)

            console.log(assetTags);

            const codes = await getBarcodes(assetTags);

            const content = await getContent(codes);

            createPdf(res, content);

            fs.unlinkSync(req.file.path)
        })


}

//returns true if set doesn't exist and false if set does
function setDoesntExist(isbn) {
    return new Promise((resolve, reject) => {
        db.oneOrNone('SELECT FROM textbook_sets WHERE isbn = $1', [isbn])
            .then(result => {
                console.log(result);
                resolve(result == null)
            })
            .catch(error => {
                console.log(error);
                reject(error);
            })
    });

}


module.exports = {
    createSet, addToSet, importSet, getSets
}

