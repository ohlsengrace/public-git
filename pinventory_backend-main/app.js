//Contains all routes for the application, as well as authentication middleware

const express = require('express')
const cors = require('cors')
const app = express()
const port = process.env.PORT || 3000
const db = require('./queries.js');
const hostname = process.env.HOST;
const multer = require('multer');
const upload = multer({dest: './books/csv/'});


//Middleware
app.use(express.json());
app.use(cors());


//Authentication
app.use('/', function (req, res, next) {
    console.log('using middleware');
    const id_token = req.headers['authorization'];
    if(id_token){

        const split = id_token.split(' ');
        const token = (split[1]);

        let user = {};
        async function verify(){
            const ticket = await client.verifyIdToken({
                idToken: token,
                audience: CLIENT_ID,
            });
            const payload = ticket.getPayload();
            user.name = payload.name;
            user.email = payload.email;
            req.gmail = user.email;
            user.picture = payload.picture;
            console.log(payload)

            if(user.email.includes("student")){
                req.isStudent = "student";
            }else{
                req.isStudent = "admin";
            }

            console.log(req.isStudent);
        }
        verify()
            .then(() =>{
                next();
            })
            .catch(err=>{
                console.log(err);
                res.status(401).send('Permission Denied');
            })

    }
    else{
        console.log('in backend else block');
        res.status(401);
        res.send('No token was provided');
    }
})


//==================================
//Server Routes
//==================================


//books
app.get('/search/books', db.bookQuery.getAll);
app.get('/search/books/checkout', db.bookQuery.getAllCheckedOut);
app.get('/search/books/student', db.bookQuery.getBooksByStudent);
app.post('/checkins', db.bookQuery.checkIn);
app.post('/checkouts', db.bookQuery.checkOut);

//textbook_sets
app.post('/sets/add', db.setQuery.createSet);
app.post('/sets/add/newBooks', db.setQuery.addToSet);
app.post('/sets/add/csv', upload.single('file'), db.setQuery.importSet);

//Google Auth
const {OAuth2Client} = require('google-auth-library');
const CLIENT_ID = '180374672702-vad12pe1q4og9dr4mjra0hrsj57ol1im.apps.googleusercontent.com'
const client = new OAuth2Client(CLIENT_ID);



app.listen(port, () => {
    console.log('Server running on port %d', port);
 })

